#include <muradin/net/acceptor.h>


#include <muradin/net/io_service.h>
#include <muradin/net/tcp_socket.h>
#include <muradin/base/log_warper.h>

#include <errno.h>

#include <boost/bind.hpp>

namespace muradin{
namespace net{
    acceptor::acceptor(io_service& service,const endpoint_v4& listen_addr)
    :m_listen_fd( tcp_nbsocket_create() ),
    m_listen_addr(listen_addr),
    m_service(service),
    m_channel(m_listen_fd,service ),
    m_accept_cb(NULL)
    {
        m_channel.set_read_cb( boost::bind(&acceptor::on_accept,this));
        m_service.alter_channel(&m_channel);
    }
    acceptor::~acceptor()
    {
        //
    }
        
    int     acceptor::start()
    {
        int ret_code= tcp_socket_bind(m_listen_fd,m_listen_addr);
        if(ret_code == 0 ) ret_code= tcp_socket_listen(m_listen_fd,256);
        if(ret_code ==0 ) m_channel.reg_read_event();
        return ret_code;
    }
    void    acceptor::stop()
    {
        m_channel.unreg_read_event();
    }
    void    acceptor::on_accept()
    {
        //SOCK_NONBLOCK SOCK_CLOEXEC m_accept_cb
        endpoint_v4 peer;
        int fd=tcp_socket_accept(m_listen_fd,peer);
        if(fd != -1){
            m_accept_cb(fd,peer);
        }else{
            err_loger.stream()<<"tcp_socket_accept fail,errno = " << errno <<EOL();
        }
    }    
    void    acceptor::set_accept_callback(const accept_callback& cb)
    {
        BOOST_ASSERT(m_accept_cb == NULL);
        m_accept_cb=cb;
    }
};//net
};