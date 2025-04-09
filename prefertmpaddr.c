#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/in6.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dlfcn.h>

int (*orig_bind)(int, const struct sockaddr*, socklen_t);
int (*orig_connect)(int, const struct sockaddr*, socklen_t);

#define SAVE_ORIG(fn) \
    orig_##fn = dlsym(RTLD_NEXT, #fn); \
    if ((err = dlerror()) != NULL) { \
        fprintf(stderr, "cannot find next %s: %s\n", #fn, err); \
        abort(); \
    }

void _init(void)
{
    const char *err;
    SAVE_ORIG(bind);
    SAVE_ORIG(connect);
}

int prefer_tmpaddr(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if (addr->sa_family == AF_INET6) {
        uint32_t flags = IPV6_PREFER_SRC_TMP;
        setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADDR_PREFERENCES, (void*) &flags, sizeof(flags));
    }
}

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    prefer_tmpaddr(sockfd, addr, addrlen);
    return orig_bind(sockfd, addr, addrlen);
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    prefer_tmpaddr(sockfd, addr, addrlen);
    return orig_connect(sockfd, addr, addrlen);
}
