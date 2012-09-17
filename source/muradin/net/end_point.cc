#include <muradin/net/end_point.h>
#include <string.h>
#include <netinet/in.h>
#include <muradin/net/socket_addr.h>
#include <muradin/net/endian.h>


namespace muradin{
	namespace net{

		endpoint_v4::endpoint_v4(const std::string& ip,uint16_t port)
		{
			//address_.sin_len=sizeof(address_);
			address_.sin_family=AF_INET;
			address_.sin_port= uint16_hton(port);
			net_pton(AF_INET,ip.c_str(),&address_.sin_addr);
		}

		endpoint_v4::endpoint_v4(const std::string& ip)
		{
			//address_.sin_len=sizeof(address_);
			address_.sin_family=AF_INET;
			address_.sin_port= uint16_hton(kPortAny);
			net_pton(AF_INET,ip.c_str(),&address_.sin_addr);
		}

		endpoint_v4::endpoint_v4(uint16_t port)
		{
			//address_.sin_len=sizeof(address_);
			address_.sin_family=AF_INET;
			address_.sin_port= uint16_hton(port);
			address_.sin_addr.s_addr = INADDR_ANY;
		}

		endpoint_v4::endpoint_v4()
		{
			//address_.sin_len=sizeof(address_);
			address_.sin_family=AF_INET;
			address_.sin_port= uint16_hton(kPortAny);
			address_.sin_addr.s_addr= INADDR_ANY;
		}
		endpoint_v4::endpoint_v4(const SockecAddressV4& address )
		{
			::memcpy(&address_,&address,sizeof(SockecAddressV4));
		}

		endpoint_v4::~endpoint_v4()
		{
			//
		}
		SockecAddressV4&		endpoint_v4::Address()
		{
			return address_ ;
		}
		const SockecAddressV4&	endpoint_v4::Address()const
		{
			return address_ ;
		}

		const std::string		endpoint_v4::GetIP()const
		{
			char addr_str[100]={0};
			net_ntop(address_.sin_family,&address_.sin_addr,addr_str,sizeof(addr_str) );
			return std::string(addr_str);
		}

		uint16_t				endpoint_v4::GetPort()const
		{
			return uint16_ntoh(address_.sin_port);
		}

		std::string				endpoint_v4::AddressAny()
		{
			char addr_str[100]={0};
			int32_t	ip_addr=INADDR_ANY;
			net_ntop(AF_INET,&ip_addr,addr_str,sizeof(addr_str) );
			return std::string(addr_str);
		}

		uint16_t				endpoint_v4::PortAny()
		{
			return kPortAny;
		}

		const endpoint_v4&		endpoint_v4::operator=(const SockecAddressV4& rh)
		{
			::memcpy(&address_,&rh,sizeof(SockecAddressV4));
			return *this;
		}
	};//net
};//muradin
