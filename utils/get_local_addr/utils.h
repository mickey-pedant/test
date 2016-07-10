#ifndef __GET_LOCAL_ADDR_
#define __GET_LOCAL_ADDR_

struct iface_addr {
    char ifa_name[32];
    char ifa_ip[16];
};

int get_local_addr(struct iface_addr *addrs, int array_size);

#endif//__GET_LOCAL_ADDR_
