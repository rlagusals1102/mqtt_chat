// network_utils.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "network_utils.h"

// IP 주소를 가져오는 함수
char* get_ip_address()
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];
    char *ip_address = NULL;

    // 네트워크 인터페이스 정보를 가져옴
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    // 각 인터페이스를 순회하면서 IP 주소를 찾음
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        // IPv4 주소를 찾음
        if (family == AF_INET) {
            s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }
            // 루프백 주소를 제외함
            if (strcmp(ifa->ifa_name, "lo") != 0) {
                ip_address = strdup(host);
                break;
            }
        }
    }

    freeifaddrs(ifaddr);
    return ip_address;
}

