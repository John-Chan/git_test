/* 
 * File:   io_service_thread.cc
 * Author: xRoy
 * 
 * Created on 2012年9月18日, 下午3:40
 */

#include <muradin/net/io_service_thread.h>
#include <muradin/net/io_service.h>
#include <boost/bind.hpp>

namespace muradin{
namespace net{
    
io_service_thread::io_service_thread() 
:m_service(new io_service()),
m_thread(new muradin::base::thread( boost::bind(&io_service_thread::thread_func, this),"io_service_thread" ) )
{
}

io_service_thread::~io_service_thread() {
    m_service->exit();
    m_thread->join();
}

io_service* io_service_thread::run()
{
    m_thread->run();
    boost::mutex::scoped_lock lock(m_mutex);
    while(m_service == NULL)
        m_cond.wait(lock);
    return m_service;
}
void        io_service_thread::join()
{
    m_thread->join();
}
void io_service_thread::thread_func()
{
    io_service service;
    boost::mutex::scoped_lock lock(m_mutex);
    m_service=&service;
    m_cond.notify_one();
    service.run();
}

}
}
