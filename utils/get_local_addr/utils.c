#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

int get_local_addr(struct iface_addr *addrs, int array_size)
{
    char *ip_addr;
    int ret, family, nums;
    struct ifaddrs *ifa, *ifaddr;
    struct iface_addr *addr;

    ret = getifaddrs(&ifaddr);
    if (ret < 0) {
        freeifaddrs(ifaddr);
        return ret;
    }

    nums = 0;
    for (ifa = ifaddr; ifa != NULL && nums < array_size; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;
        family = ifa->ifa_addr->sa_family;
        /* get ipv4 address */
        if (family == AF_INET) {
            addr = &addrs[nums++];
            strncpy(addr->ifa_name, ifa->ifa_name, sizeof(addr->ifa_name));
            ip_addr = inet_ntoa(((struct sockaddr_in *)ifa->ifa_addr)->sin_addr);
            strncpy(addr->ifa_ip, ip_addr, sizeof(addr->ifa_ip));
        }
    }

    freeifaddrs(ifaddr);

    return nums;
}

/*
int main(int argc, char *argv[])
{
    int n;
    struct iface_addr iface_addr[16];

    n = get_local_addr(iface_addr, sizeof(iface_addr)/sizeof(iface_addr[0]));
    if (n < 0) {
        perror("Error while get local addr");
        return -1;
    } else
        printf("get %d ip addres\n", n);

    return 0;
}
*/
