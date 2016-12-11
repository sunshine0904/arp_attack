#ifndef ARP_H
#define ARP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>

#define u8_t unsigned char
#define u16_t unsigned short int
#define u32_t unsigned int

#define ARP_PKT_LEN 42

/* arp packet 28 bytes */
struct arphdr
{
    u16_t hw_type;   /* hardware type, 1: ethernet */
    u16_t pro_type;  /* protocol type, 0x0800: IP protocol */
    u8_t  hw_len;    /* length of hardware address, 6 for MAC */
    u8_t  pro_len;   /* length of protocol address, 4 for IPV4 */
    u16_t opcode;    /* ARP/RARP operation */
    u8_t    smac[6];   /* sender hardware address */
    u32_t sip;       /* sender protocol address */
    u8_t    dmac[6];   /* target hardware address */
    u32_t dip;       /* target protocol address */
}__attribute__((packed));


/*eth hdr*/
struct ethhdr
{
    u8_t  eth_dst_mac[6];
    u8_t  eth_src_mac[6];
    u16_t eth_type;
}__attribute__((packed));

u32_t creat_rawsocket();    
u32_t bind_socket_dev(u32_t socket,u8_t *device);

#endif /* ARP_H*/
