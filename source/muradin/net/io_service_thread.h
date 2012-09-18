/* 
 * File:   io_service_thread.h
 * Author: xRoy
 *
 * Created on 2012年9月18日, 下午3:40
 */

#ifndef MURADIN_NET_IO_SERVICES_THREAD_H__
#define	MURADIN_NET_IO_SERVICES_THREAD_H__
#include <boost/utility.hpp>
#include <muradin/base/thread.h>
namespace muradin{
namespace net{

class io_service_thread : public boost::noncopyable
{
public:
    io_service_thread();
    ~io_service_thread();
private:

};

};
};

#endif	/* MURADIN_NET_IO_SERVICES_THREAD_H__ */

