#include <muradin/net/io_service.h>
#include <muradin/net/evt_poller/epoll_poller.h>
#include <muradin/base/log_warper.h>
#include <muradin/net/io_channel.h>

#include <sys/eventfd.h>


int	create_evt_fd()
{   
	int fd= ::eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK );
	if (fd <= 0){
		fata_loger.stream()<<"create eventfd fail,error = "  <<errno<< EOL();
		::abort ();
	}
	return fd;
}


namespace muradin{
namespace net{

io_service::io_service()
:m_poller(new ep_poller()),
m_init_tid(boost::this_thread::get_id ()),
m_exit(false),
m_weekup_fd(create_evt_fd()),
m_weekup_channel(new io_channel(m_weekup_fd,*this))
{
}
io_service::~io_service()
{
	::close(m_weekup_fd); m_weekup_fd=-1;
}

void		io_service::run()
{
	evt_loop();
}
void	io_service::exit()
{
	m_exit=true;
	weekup ();
}
void	io_service::alter_channel(io_channel* channel)
{
	BOOST_ASSERT(boost::this_thread::get_id () == m_init_tid);
	m_poller->update_channel (channel);
}
void	io_service::run_functor(const functor& func)
{
	// boost::this_thread::get_id () == m_init_tid
}

void	io_service::evt_loop()
{
	while( !m_exit){
		channel_vec signled_channel;

		/// pending in epoll_wait
		m_poller->wait_for_evt (signled_channel,1*1000);

		exec_active_channel(signled_channel);
	}
}
void	io_service::weekup()
{
	uint64_t writ_data=1;
	::write(m_weekup_fd,&writ_data,sizeof(writ_data));
}
void	io_service::exec_active_channel(channel_vec &channel_list)
{
	for(size_t i=0;i<channel_list.size ();++i){
		channel_list[i]->handle_event ();
	}
}

void io_service::exec_pending_func()
{
	functor_vec to_run;
	if(m_pending_func_list.size () > 0)
	{
		boost::mutex::scoped_lock	lock(m_func_list_mutex);
		std::swap (m_pending_func_list,to_run);
	}
	for (size_t i=0;i< to_run.size ();++i){
		to_run[i]();
	}
}

void io_service::on_read( uint32_t size )
{
	char buff[sizeof(uint64_t)];
	::read (m_weekup_fd,buff,sizeof(uint64_t));
}

};//net
};//muradin