#ifndef	MURADIN_NET_IO_SERVICE_H__
#define MURADIN_NET_IO_SERVICE_H__

//#include <muradin/config/integer_define.h>
//#include <muradin/base/error_type.h>

#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>

namespace muradin{
namespace net{

	class io_channel;
	class ep_poller; 

	/** 
	 * @class    <the name>
	 *
	 * @brief    <description>
	 *
	 * @note     <em> note </em>
	 *
	 * See @ref <some class> for more information. 
	 *
	 */
	class io_service:public boost::noncopyable
	{
	public:
		typedef std::vector<io_channel*>	channel_vec;
		typedef boost::function<void()>		functor;
		typedef std::vector<functor>		functor_vec;
		io_service();
		~io_service();

		void	run();
		void	exit();
		void	alter_channel(io_channel* channel);
		void	run_functor(const functor& func);
	protected:
		void	evt_loop();
		void	weekup();
		void	exec_active_channel(channel_vec &channel_list);
		void	exec_pending_func();
	private:
		void	on_read(uint32_t size);
	private:
		boost::scoped_ptr<ep_poller>	m_poller;
		functor_vec						m_pending_func_list;
		boost::mutex					m_func_list_mutex;
		const boost::thread::id			m_init_tid;
		bool							m_exit;
		int								m_weekup_fd;
		boost::scoped_ptr<io_channel>	m_weekup_channel;
		
	};
};//net
};//muradin

#endif//MURADIN_NET_IO_SERVICE_H__