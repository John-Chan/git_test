#include <muradin/net/evt_poller/epoll_poller.h>
#include <muradin/net/io_channel.h>
#include <muradin/base/log_warper.h>
#include <errno.h>

int ep_create_or_exit()
{
    int fd = ::epoll_create1(EPOLL_CLOEXEC);
    if(fd<0){
        fata_loger.stream()<<"epoll_create fail :" <<errno<<EOL();
		::abort();
    }
    return fd;
}

namespace muradin{
namespace net{

ep_poller::ep_poller()
: m_ep_fd(ep_create_or_exit())
{
}
ep_poller::~ep_poller()
{
    ::close(m_ep_fd);
}
uint64_t ep_poller::wait_for_evt(channel_vec &singled_channel,int32_t timeout)
{
	ep_evt	signed_evt[k_max_poll_size];
	int32_t poll_ret= ::epoll_wait(m_ep_fd,signed_evt,k_max_poll_size,timeout);
	if(poll_ret >0){
	    BOOST_ASSERT(k_max_poll_size >= poll_ret);
	    fill_channel_list(singled_channel,signed_evt,poll_ret);
	}else if(poll_ret == 0 ){
	    info_loger.stream()<<"epoll_wait got noting in :" <<timeout<< " millisecond"<<EOL();
	}else{
	    err_loger.stream()<<"epoll_wait fail :"  << errno<<EOL();
	}

	/// FIXME: return timestamp
	return 0;
}
void ep_poller::update_channel( io_channel* channel )
{
    BOOST_ASSERT( channel );
    if(channel->reg_stat() == k_cnl_ctl_no_reg || channel->reg_stat()  == k_cnl_ctl_removed){
        BOOST_ASSERT( m_registered_channels.find (channel->fd() ) == m_registered_channels.end ());
        do_update_channel(channel,EPOLL_CTL_ADD);
    }else if(channel->reg_stat() == k_cnl_ctl_reged){
        BOOST_ASSERT( m_registered_channels.find (channel->fd() ) != m_registered_channels.end ());
        BOOST_ASSERT( m_registered_channels.find (channel->fd() )->second == channel);
        if(channel->no_event()){
            do_update_channel(channel,EPOLL_CTL_DEL);
        }else{
            do_update_channel(channel,EPOLL_CTL_MOD);
        }
    }else{
        BOOST_ASSERT( 1==0 );
    }
}
void	ep_poller::fill_channel_list(channel_vec &singled_channel,ep_evt* evt_list,int32_t evt_count)
{
	for (int32_t i=0;i< evt_count;++i){
	    io_channel* channel=  static_cast<io_channel*>(evt_list[i].data.ptr);
#ifndef NDEBUG
		BOOST_ASSERT( m_registered_channels.find (channel->fd() ) != m_registered_channels.end ());
#endif
		singled_channel.push_back (channel);
	}
}

void    ep_poller::do_update_channel(io_channel* channel,int32_t how)
{
    ep_evt evt;
    evt.events=channel->event_tag();
    evt.data.ptr=channel;
    int32_t ret = epoll_ctl(m_ep_fd, how, channel->fd(), &evt);
    if(ret != 0){
        err_loger.stream()<<"epoll_ctl fail :"  << errno<<EOL();
    }
}

void ep_poller::remove_channel( io_channel* channel )
{
	do_update_channel(channel,EPOLL_CTL_DEL);
#ifndef NDEBUG
	BOOST_ASSERT( m_registered_channels.find (channel->fd() ) != m_registered_channels.end ());
#endif
	m_registered_channels.erase (channel->fd());
}

};//net
};//muradin

