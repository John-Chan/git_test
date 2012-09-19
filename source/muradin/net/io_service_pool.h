#ifndef MURADIN_NET_IO_SERVICE_POOL_H__
#define	MURADIN_NET_IO_SERVICE_POOL_H__


#include <boost/utility.hpp>
//#include <boost/smart_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

namespace muradin
{
namespace net
{

class io_service;
class io_service_thread ;

class io_service_pool :public boost::noncopyable
{
    typedef std::vector<io_service*>     service_list;
    typedef boost::ptr_vector <io_service_thread> thread_vec;
public:
    io_service_pool(unsigned int size);
    io_service* get_services();
    unsigned int size()const;
    void        run();
    //void        join_all();
    ~io_service_pool();
private:
    //bool         m_running;
    unsigned int m_next_thread_index;
    service_list m_services;
    thread_vec   m_threads;
    
};

}
}

#endif	/* MURADIN_NET_IO_SERVICE_POOL_H__ */

