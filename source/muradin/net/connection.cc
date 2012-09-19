#include <muradin/net/connection.h>
#include <muradin/net/io_channel.h>
#include <muradin/net/tcp_socket.h>

#include <boost/bind.hpp>
#include <boost/assert.hpp>

namespace muradin{
namespace net{
        
tcp_connection::tcp_connection(int fd,io_service&	services,const endpoint_v4& peer)
:m_services(services),
m_peer(peer),
m_channel( new io_channel(fd,services))
{
    m_channel->set_read_cb( boost::bind(&tcp_connection::on_read,this ) );
    m_channel->set_write_cb( boost::bind(&tcp_connection::on_write,this ));
    m_channel->set_error_cb( boost::bind(&tcp_connection::on_error,this ));
    m_channel->set_close_cb( boost::bind(&tcp_connection::on_close,this ));
}
tcp_connection::~tcp_connection()
{
    //
}
void	tcp_connection::write(const void* data,size_t len)
{
    //
}
void	tcp_connection::read(void* data,size_t max_read)
{
    //
}

void	tcp_connection::write(const channel_buffer& data)
{
    //
}
void	tcp_connection::read(channel_buffer& data)
{
    //
}

void	tcp_connection::close ()
{
    // run in loop?
    //shutdown_w(m_channel->fd());
}

void	tcp_connection::set_conn_cb(const connect_callback& func)
{
    BOOST_ASSERT(m_on_connect == NULL);
    m_on_connect = func;
}
void	tcp_connection::set_read_cb(const read_callback& func)
{
    BOOST_ASSERT(m_on_read == NULL);
    m_on_read = func;
}
void	tcp_connection::set_write_cb(const write_callback& func)
{
    BOOST_ASSERT(m_on_write == NULL);
    m_on_write= func;
}
void	tcp_connection::set_err_cb(const err_callback& func)
{
    BOOST_ASSERT(m_on_error == NULL);
    m_on_error = func;
}
void	tcp_connection::set_close_cb(const close_callback& func)
{
    BOOST_ASSERT(m_on_close == NULL);
    m_on_close=func;
}

void    tcp_connection::on_read()
{
    //do read
    //do callback;
}
void    tcp_connection::on_write()
{
    //do write
    //do callback;
}
void    tcp_connection::on_error()
{
    //do retrieve error
    //do callback;
}
void    tcp_connection::on_close()
{
    //do callback;
}

};//net
};//muradin