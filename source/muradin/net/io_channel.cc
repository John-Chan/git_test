#include <muradin/net/io_channel.h>

BOOST_STATIC_ASSERT(  sizeof(int32_t) == sizeof(int));

namespace muradin{
namespace net{

io_channel::io_channel(int32_t fd,io_service& service)
:m_service(service),
m_fd(fd),
m_write_bytes(0),
m_read_bytes(0),
m_in_evt_hand(false),
m_evt_tag(k_evt_no_evt),
m_reg_tag(k_cnl_ctl_no_reg),
m_read_cb(NULL),
m_write_cb(NULL)
{
}

io_channel::~io_channel()
{
}

void		io_channel::reg_read_event()
{ 
	m_evt_tag|= ( EPOLLIN | EPOLLPRI );
	m_service.alter_channel (this);
}
void		io_channel::reg_write_event()
{
	m_evt_tag|= ( EPOLLOUT  );
	m_service.alter_channel (this);
}

void		io_channel::reg_rw_event()
{
	m_evt_tag|= ( EPOLLIN | EPOLLPRI );
	m_evt_tag|= ( EPOLLOUT  );
	m_service.alter_channel (this);
}

void		io_channel::handle_event(/*int32_t evt_tag*/)
{
	m_in_evt_hand = true;
	if ((m_evt_tag & EPOLLHUP) && !(m_evt_tag & EPOLLIN))
	{
		if (m_close_cb) m_close_cb();
	}

	if (m_evt_tag & EPOLLNVAL)
	{
		warn_loger.stream () << " POLLNVAL";
	}

	if (m_evt_tag & (EPOLLERR | EPOLLNVAL))
	{
		if (m_error_cb) m_error_cb(0);
	}
	if (m_evt_tag & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
	{
		if (m_read_cb) m_read_cb( 0 );
	}
	if (m_evt_tag & EPOLLOUT)
	{
		if (m_write_cb) m_write_cb();
	}
	m_in_evt_hand = false;
}


void		io_channel::set_read_cb(cb_read_evt cb)
{
	BOOST_ASSERT(m_read_cb == NULL);
	m_read_cb = cb;
}

void		io_channel::set_write_cb(cb_write_evt cb)
{
	BOOST_ASSERT(m_write_cb == NULL);
	m_write_cb = cb;
}

void io_channel::set_error_cb( cb_error_evt cb )
{
	BOOST_ASSERT(m_error_cb == NULL);
	m_error_cb = cb;
}
void		io_channel::set_close_cb(cb_close_evt cb)
{
	BOOST_ASSERT(m_close_cb == NULL);
	m_close_cb = cb;
}


};//net
};//muradin