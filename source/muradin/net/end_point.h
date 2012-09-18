#ifndef MURADIN_NET_ENDPOINT_H_
#define MURADIN_NET_ENDPOINT_H_


#include <muradin/config/integer_define.h>
#include <netinet/in.h>
#include <string>

namespace muradin{
	namespace net{

		typedef	sockaddr_in			SockecAddressV4;	// same as struct sockaddr

		/// POD class
		class endpoint_v4
		{

		public:
			endpoint_v4();
			endpoint_v4(uint16_t port);
			explicit endpoint_v4(const std::string& ip);
			endpoint_v4(const std::string& ip,uint16_t port);
			explicit endpoint_v4(const SockecAddressV4& address );


			~endpoint_v4();

			const SockecAddressV4&	address()const;
			SockecAddressV4&		address();
			const std::string		get_ip()const;
			uint16_t				get_port()const;

			static std::string		address_any();
			static uint16_t			port_any();

			const endpoint_v4&		operator=(const SockecAddressV4& rh);
		private:
			SockecAddressV4	m_address;
			enum {kPortAny=0};
		};
	};//base
};//muradin


#endif // MURADIN_NET_ENDPOINT_H_
