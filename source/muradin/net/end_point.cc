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
			m_address.sin_family=AF_INET;
			m_address.sin_port= uint16_hton(port);
			net_pton(AF_INET,ip.c_str(),&m_address.sin_addr);
		}

		endpoint_v4::endpoint_v4(const std::string& ip)
		{
			//address_.sin_len=sizeof(address_);
			m_address.sin_family=AF_INET;
			m_address.sin_port= uint16_hton(kPortAny);
			net_pton(AF_INET,ip.c_str(),&m_address.sin_addr);
		}

		endpoint_v4::endpoint_v4(uint16_t port)
		{
			//address_.sin_len=sizeof(address_);
			m_address.sin_family=AF_INET;
			m_address.sin_port= uint16_hton(port);
			m_address.sin_addr.s_addr = INADDR_ANY;
		}

		endpoint_v4::endpoint_v4()
		{
			//address_.sin_len=sizeof(address_);
			m_address.sin_family=AF_INET;
			m_address.sin_port= uint16_hton(kPortAny);
			m_address.sin_addr.s_addr= INADDR_ANY;
		}
		endpoint_v4::endpoint_v4(const SockecAddressV4& address )
		{
			::memcpy(&m_address,&address,sizeof(SockecAddressV4));
		}

		endpoint_v4::~endpoint_v4()
		{
			//
		}
		SockecAddressV4&		endpoint_v4::address()
		{
			return m_address ;
		}
		const SockecAddressV4&	endpoint_v4::address()const
		{
			return m_address ;
		}

		const std::string		endpoint_v4::get_ip()const
		{
			char addr_str[100]={0};
			net_ntop(m_address.sin_family,&m_address.sin_addr,addr_str,sizeof(addr_str) );
			return std::string(addr_str);
		}

		uint16_t				endpoint_v4::get_port()const
		{
			return uint16_ntoh(m_address.sin_port);
		}

		std::string				endpoint_v4::address_any()
		{
			char addr_str[100]={0};
			int32_t	ip_addr=INADDR_ANY;
			net_ntop(AF_INET,&ip_addr,addr_str,sizeof(addr_str) );
			return std::string(addr_str);
		}

		uint16_t				endpoint_v4::port_any()
		{
			return kPortAny;
		}

		const endpoint_v4&		endpoint_v4::operator=(const SockecAddressV4& rh)
		{
			::memcpy(&m_address,&rh,sizeof(SockecAddressV4));
			return *this;
		}
	};//net
};//muradin
