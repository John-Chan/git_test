#ifndef	MURADIN_NET_APP_CALLBACK_H__
#define MURADIN_NET_APP_CALLBACK_H__

#include <muradin/net/buffer.h>
#include <boost/function.hpp>


namespace muradin
{
namespace net
{
	class channel_buffer;
	class endpoint_v4;

	typedef	boost::function<void(channel_buffer&)>		read_callback;
	typedef	boost::function<void(size_t)>				write_callback;
	typedef	boost::function<void(int)>					err_callback;
	typedef	boost::function<void()>                     close_callback;
	typedef	boost::function<void(const endpoint_v4&)>	connect_callback;

}
}


#endif