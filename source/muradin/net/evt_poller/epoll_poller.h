#ifndef EVT_EPOLL_POLLER_H__
#define EVT_EPOLL_POLLER_H__

#include <muradin/config/integer_define.h>
#include <sys/epoll.h>

#include <map>
#include <vector>

#include <boost/utility.hpp>

namespace muradin{
namespace net{

class io_channel;

/**
 * @class    <the name>
 *
 * @brief    <description>
 *
 * @note     <em> note </em>
 *
 * See @ref <some class> for more information.
 *
 */
class ep_poller:public boost::noncopyable
{
	typedef struct epoll_event ep_evt;
public:
	typedef std::vector<io_channel*>	channel_vec;
	typedef	std::map<int32_t,io_channel*>	    channel_map;
	ep_poller();
	~ep_poller();
	uint64_t wait_for_evt(channel_vec &singled_channel,int32_t timeout);

	/// reg,update
	void		update_channel(io_channel* channel);
	void		remove_channel(io_channel* channel);
protected:
    void    do_update_channel(io_channel* channel,int32_t how);
	void	fill_channel_list(channel_vec &singled_channel,ep_evt* evt_list,int32_t evt_count);
private:
	int32_t		m_ep_fd;
	channel_map	m_registered_channels;
	enum{ k_max_poll_size=256};
};

};//net
};//muradin
#endif
