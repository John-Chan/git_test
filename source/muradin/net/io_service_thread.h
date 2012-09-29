/* 
 * File:   io_service_thread.h
 * Author: xRoy
 *
 * Created on 2012年9月18日, 下午3:40
 */

#ifndef MURADIN_NET_IO_SERVICES_THREAD_H__
#define	MURADIN_NET_IO_SERVICES_THREAD_H__

#include <muradin/base/thread.h>

#include <boost/utility.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>


namespace muradin{
namespace net{

class io_service;

class io_service_thread : public boost::noncopyable
{
    typedef boost::scoped_ptr<muradin::base::thread> thread_ptr;
    typedef boost::condition_variable                cond_type;
public:
    io_service_thread();
    ~io_service_thread();
    
    io_service* run();
    void        join();
private:
    void thread_func();
private:
    io_service*     m_service;
    thread_ptr      m_thread;
    boost::mutex    m_mutex;
    cond_type       m_cond;
    const boost::thread::id			m_init_tid;
};

}
}

#endif	/* MURADIN_NET_IO_SERVICES_THREAD_H__ */

