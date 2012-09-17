#include <muradin/config/integer_define.h>
#include <muradin/net/buffer.h>

namespace muradin{
namespace net{

	class tcp_connection
	{
	public:
		tcp_connection();
		~tcp_connection();
	private:
		/// cache data that can not send directly
		channel_buffer	m_write_buff;	
	};

};//net
};//muradin