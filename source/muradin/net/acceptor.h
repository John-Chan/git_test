#ifndef MURADIN_NET_ACCEPTOR_H__
#define MURADIN_NET_ACCEPTOR_H__

#include <muradin/net/end_point.h>
#include <muradin/net/io_channel.h>

#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>

namespace muradin{
namespace net{

    class io_service;
    
	class acceptor : public boost::noncopyable//,boost::enable_shared_from_this<acceptor>
    {
        typedef boost::function<void(int,const endpoint_v4&)> accept_callback;
        //typedef boost::scoped_ptr<io_channel>             channel_ptr;
    public:
        acceptor(io_service& service,const endpoint_v4& listen_addr);
        ~acceptor();
        
        int     start();
        void    stop();
        
        void    set_accept_callback(const accept_callback& cb);
    private:
        void    on_accept();
    private:
        int         m_listen_fd;
        endpoint_v4 m_listen_addr;
        io_service& m_service;
        //channel_ptr m_channel;
        io_channel  m_channel;
        accept_callback m_accept_cb;
    };
	
}//net
}
#endif//MURADIN_NET_ACCEPTOR_H__