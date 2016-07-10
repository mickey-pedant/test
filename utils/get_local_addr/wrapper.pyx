cdef extern from "stdlib.h":
    void *malloc(size_t size)
    void *free(void *ptr)

cdef extern from "utils.h":
    struct iface_addr:
        char ifa_name[32]
        char ifa_ip[16]

    int get_local_addr(iface_addr *addrs, int array_size)

MAX_TRY = 16

def get_local_addrs(iface=[], prefix=[], try_max=MAX_TRY):
    cdef iface_addr *addrs = <iface_addr *>malloc(sizeof(iface_addr) * try_max)
    if addrs == NULL:
        raise MemoryError("Unable allocate address buffer")

    count = get_local_addr(addrs, try_max)
    idx = 0
    ip_addrs = []
    while idx < count:
        name = addrs[idx].ifa_name
        ip_addr = addrs[idx].ifa_ip
        idx += 1

        if len(iface) and name != iface:
            continue
        if len(prefix) and not ip_addr.startswith(prefix):
            continue
        ip_addrs.append(ip_addr)

    free(<void *>addrs)
    return ip_addrs
