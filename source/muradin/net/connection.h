//#include <muradin/config/integer_define.h>
#include <muradin/net/buffer.h>
#include <muradin/net/end_point.h>
#include <muradin/net/app_callback.h>

#include <boost/smart_ptr.hpp>


namespace muradin{
namespace net{

	class io_service;
	class io_channel;
	class tcp_connection
	{
		typedef boost::scoped_ptr<io_channel>	channel_ptr;
	public:
		tcp_connection(int fd,io_service&	services,const endpoint_v4& peer);
		~tcp_connection();
		void	write(const void* data,size_t len);
		void	read(void* data,size_t max_read);

		void	write(const channel_buffer& data);
		void	read(channel_buffer& data);

		void	close ();

		void	set_conn_cb(const connect_callback& func);
		void	set_read_cb(const read_callback& func);
		void	set_write_cb(const write_callback& func);
		void	set_err_cb(const err_callback& func);
		void	set_close_cb(const close_callback& func);
	private:
		void    on_read();
        void    on_write();
        void    on_error();
        void    on_close();
	private:
		io_service&	m_services;
		/// cache data that can not send directly
		channel_buffer	m_write_buff;	
		channel_buffer	m_read_buff;
		endpoint_v4		m_peer;
		channel_ptr		m_channel;

		connect_callback	m_on_connect;
		read_callback	m_on_read;
		write_callback	m_on_write;
		err_callback	m_on_error;
		close_callback	m_on_close;
	};

};//net
};//muradin