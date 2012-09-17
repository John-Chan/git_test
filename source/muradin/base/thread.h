#ifndef MURADIN_BASE_THREAD_H__
#define MURADIN_BASE_THREAD_H__

#include <muradin/config/integer_define.h>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <boost/smart_ptr.hpp>
#include <string>

namespace muradin{
namespace base{
	class thread : public boost::noncopyable
	{
	public:
		typedef	boost::function<void()>	thread_func_t;
		thread(const thread_func_t& thread_func,const std::string& name);
		~thread(void);
		void	run();
		void	join();
		bool	running();
	private:
		static void*	start_thread_func(void* para);
		void	run_func();
	private:
		bool		m_running;
		thread_func_t	m_thread_func;
		const std::string	m_name;
		static	uint32_t	g_created_count;
		boost::thread*		m_thread;
	};

};//base
};//muradin
#endif // MURADIN_BASE_THREAD_H__
