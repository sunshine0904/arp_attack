#include "arp.h"

u8_t broadcast_mac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
//u8_t broadcast_mac[6] = {0x48,0x5A,0xB6,0x81,0x40,0x21};
u8_t src_mac[6] = {0x48,0x5a,0xb6,0xd0,0x49,0x43};

void main(int argc,char **argv)
{
	int i = 0;
    #if 0
	if(argc < 2)
	{
		printf("error arg\n");
	}
	for(i = 0;i<2;i++)
	{
		printf("%s\n",argv[i]);
	}
    #endif

    u8_t *buffer = malloc(ARP_PKT_LEN * sizeof(u8_t));
    memset(buffer,0,ARP_PKT_LEN);
    struct ethhdr *eth_hdr = buffer;
    struct arphdr *arp_hdr = buffer + sizeof(struct ethhdr);
    
    //fill ether header
    memcpy(eth_hdr->eth_dst_mac,broadcast_mac,6);
    memcpy(eth_hdr->eth_src_mac,src_mac,6);
    eth_hdr->eth_type = htons(0x0806);

    //fill arp header
    arp_hdr->hw_type = htons(0x0001);
    arp_hdr->pro_type = htons(0x0800);
    arp_hdr->hw_len = 0x6;
    arp_hdr->pro_len = 0x4;
    arp_hdr->opcode = htons(0x0002);
    memcpy(arp_hdr->smac,src_mac,6);
    memcpy(arp_hdr->dmac,src_mac,6);
    arp_hdr->sip = htonl(0xc0a80101);
    arp_hdr->dip = htonl(0xc0a80101);
    
    for(i= 0;i<42;i++)
    {
        printf("%02x ",buffer[i]);
    }
    printf("\n");


	u32_t raw_socket = creat_rawsocket();
    bind_socket_dev(raw_socket,"wlan0");

    while(1)
    {
        printf("send ret:%d bytes\n",sendto(raw_socket,buffer,ARP_PKT_LEN,0,NULL,NULL));
        
        usleep(100);
    }

    free(buffer);

}

u32_t creat_rawsocket()
{
    u32_t raw_sock = socket(PF_PACKET,SOCK_RAW,htons(0x0003));
    if(raw_sock == 0)
    {
        printf("socket error\n");
        return -1;
    }
    printf("creat raw_socket ok!raw_sock:%d\n",raw_sock);
    return raw_sock;
}

u32_t bind_socket_dev(u32_t socket,u8_t *device)
{
	u32_t index = if_nametoindex(device);
	printf("device:%s index:%d\n",device,index);
	struct sockaddr_ll sll;
	memset(&sll,0,sizeof(struct sockaddr_ll));
	sll.sll_family = PF_PACKET;
	sll.sll_ifindex = index;
	sll.sll_protocol = htons(0x0003);

	if(0 < bind(socket,(struct sockaddr *)&sll,sizeof(struct sockaddr_ll)))
	{
		printf("bind device error\n");
		return -1;
	}
}
