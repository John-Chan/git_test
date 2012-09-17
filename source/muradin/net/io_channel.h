#ifndef MURADIN_NET_IO_CHANNEL_H__
#define MURADIN_NET_IO_CHANNEL_H__

#include <muradin/config/integer_define.h>
#include <boost/function.hpp>
#include <muradin/net/buffer.h>

namespace muradin{
namespace net{

	class io_service;

    /// channel register status
    enum cnl_reg_stat{
        k_cnl_ctl_no_reg,
        k_cnl_ctl_reged,
        k_cnl_ctl_removed
    };


    /**
     * @class    io_channel
     *
     * @brief    <description>
     *
     * @note     <em> note </em>
     *
     * See @ref <some class> for more information.
     *
     */
    class io_channel
    {
    public:
		typedef	boost::function<void()>	cb_read_evt;	
		typedef	boost::function<void()>	cb_write_evt;
		typedef	boost::function<void()>	cb_error_evt;
		typedef	boost::function<void()>	cb_close_evt;

        io_channel(int32_t fd,io_service& service);
        ~io_channel();

        int32_t		event_tag()const{return m_evt_tag;};
        void    	set_sevent_tag(int32_t val){m_evt_tag = val;};

        cnl_reg_stat		reg_stat()const {return m_reg_tag;};
        void	    set_reg_stat(cnl_reg_stat val){m_reg_tag = val;};

		int32_t		fd(){return m_fd;};
        bool        no_event(){return k_evt_no_evt== m_evt_tag;};

		void		reg_read_event();
		void		reg_write_event();

		/// reg_read_event + reg_write_event
		void		reg_rw_event();

		void		handle_event(/*int32_t evt_tag*/);

		bool		in_evt_handing(){return m_in_evt_hand;};

		void		set_read_cb(cb_read_evt cb);
		void		set_write_cb(cb_write_evt cb);
		void		set_error_cb(cb_error_evt cb);
		void		set_close_cb(cb_close_evt cb);
    protected:
		//void		on_read();
		//void		on_write();
		//void		on_error();
	private:
		enum{k_evt_no_evt= 0} ;
		io_service&	m_service;
		int32_t		m_fd;
        uint32_t	m_write_bytes;
        uint32_t	m_read_bytes;
		bool		m_in_evt_hand;
        //
        int32_t			m_evt_tag;
        cnl_reg_stat	m_reg_tag;
		cb_read_evt	m_read_cb;
		cb_write_evt	m_write_cb;
		cb_error_evt			m_error_cb;
		cb_close_evt			m_close_cb;
    };
};//net
};//muradin
#endif // MURADIN_NET_IO_CHANNEL_H__
