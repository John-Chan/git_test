#include <muradin/net/tcp_server.h>
/*
#include <muradin/net/acceptor.h>
#include <muradin/net/io_service.h>
#include <muradin/net/io_service_pool.h>
#include <muradin/net/end_point.h>
#include <muradin/net/connection.h>
*/
#include <boost/bind.hpp>

namespace muradin{
namespace net{
    
tcp_server::tcp_server(const endpoint_v4& local_addr,unsigned int thread_size)
:m_service_poll( new io_service_pool(thread_size) )
{
    m_service_poll->run();
    //get_services();
    m_acceptor.reset(new acceptor(*m_service_poll->get_services(),local_addr ));
    m_acceptor->set_accept_callback( boost::bind(&tcp_server::on_accept,this,_1,_2));
}


int tcp_server::run()
{
    return m_acceptor->start();
}
int tcp_server::stop()
{
    m_acceptor->stop();
    //m_service_poll->join_all();
}
void    tcp_server::on_accept(int fd,const endpoint_v4& peer )
{
    BOOST_ASSERT( m_conn_map.find(fd) == m_conn_map.end() );
    m_conn_map.insert(fd, (new tcp_connection(fd,*m_service_poll->get_services(),peer) ));
    //
}

void    tcp_server::on_close()
{
    //BOOST_ASSERT( m_conn_map.find(fd) != m_conn_map.end() );
    //m_conn_map.erase();
}
}
}

