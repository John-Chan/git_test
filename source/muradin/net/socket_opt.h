/* 
 * File:   socket_opt.h
 * Author: xRoy
 *
 * Created on 2012年9月19日, 下午3:33
 */

#ifndef MURADIN_NET_SOCKET_OPT_H
#define	MURADIN_NET_SOCKET_OPT_H

namespace muradin
{
namespace net
{
    class socket_opt
    {
    public:
        static int retrieve_error(int fd);
    };
}
}


#endif	/* MURADIN_NET_SOCKET_OPT_H */

