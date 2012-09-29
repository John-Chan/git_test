/*
 * File:   socket_opt.cpp
 * Author: xRoy
 *
 * Created on 2012年9月19日, 下午3:33
 */

#include <muradin/net/socket_opt.h>
#include <sys/socket.h>
#include <errno.h>

namespace muradin
{
namespace net
{
int socket_opt::set_reuse_addr(int fd,bool enabled)
{
  int optval = enabled ? 1 : 0;
  return ::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

}    
int socket_opt::retrieve_error(int fd)
{
    int       optval;
    socklen_t optlen = sizeof(optval);

    if (::getsockopt(fd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        return errno;
    }
    else
    {
        return optval;
    }
}


}
}

