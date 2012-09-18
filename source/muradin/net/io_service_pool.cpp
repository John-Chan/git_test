/* 
 * File:   io_service_pool.cpp
 * Author: xRoy
 * 
 * Created on 2012年9月19日, 上午10:59
 */

#include <muradin/net/io_service_pool.h>
#include <muradin/net/io_service.h>
#include <muradin/net/io_service_thread.h>

#include <boost/assert.hpp>

namespace muradin
{
namespace net
{

io_service_pool::io_service_pool(unsigned int size) 
:m_next_thread_index(0)
{
    BOOST_ASSERT(size > 0);
    for(;size>0;--size){
        m_threads.push_back( new io_service_thread());
    }
}

io_service* io_service_pool::get_services()
{
    BOOST_ASSERT(m_services.size() > 0);
    if(m_next_thread_index >= m_services.size() ) m_next_thread_index=0;
    return m_services[m_next_thread_index++];
}
unsigned int io_service_pool::size()const
{
    return m_services.size();
}

void        io_service_pool::run()
{
    for(size_t i=0;i<m_threads.size();++i )
        m_services.push_back(m_threads[i].run());
}

/*
void        io_service_pool::join_all()
{
    for(size_t i=0;i<m_services.size();++i ){
        m_services[i]->exit();
    }
        
    for(size_t i=0;i<m_threads.size();++i ){
        m_threads[i].join();
    }
}
*/

io_service_pool::~io_service_pool() 
{
}


}
}
