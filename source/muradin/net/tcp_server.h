#ifndef MURADIN_NET_TCP_SERVER_H__
#define MURADIN_NET_TCP_SERVER_H__

#include <muradin/net/app_callback.h>

#include <boost/smart_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/ptr_container/ptr_map.hpp>


namespace muradin{
namespace net{
	
	class endpoint_v4;
    class tcp_connection;
    class io_service_pool;
    class acceptor;
    class tcp_server:public boost::noncopyable
    {
        typedef boost::ptr_map<int,tcp_connection> conn_map;
        typedef boost::scoped_ptr <io_service_pool> service_pool_ptr;
        typedef boost::shared_ptr <acceptor> acceptor_ptr;
    public:
        tcp_server(const endpoint_v4& local_addr,unsigned int thread_size);
        int run();
        int stop();
    private:
        void    on_accept(int fd,const endpoint_v4& peer );
        void    on_close();
    private:
        conn_map m_conn_map;
        service_pool_ptr m_service_poll;
        acceptor_ptr     m_acceptor;
    };

};//net
};

#endif//MURADIN_NET_TCP_SERVER_H__