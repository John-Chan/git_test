#include <muradin/net/connection.h>

namespace muradin{
namespace net{

tcp_connection::tcp_connection(io_service&	services,const endpoint_v4& peer)
{
    //
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
    //
}

void	tcp_connection::set_conn_cb(const connect_callback& func)
{
    //
}
void	tcp_connection::set_read_cb(const read_callback& func)
{
    //
}
void	tcp_connection::set_write_cb(const write_callback& func)
{
    //
}
void	tcp_connection::set_err_cb(const err_callback& func)
{
    //
}
void	tcp_connection::set_close_cb(const close_callback& func)
{
    //
}
        
};//net
};//muradin