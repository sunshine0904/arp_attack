#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/ethernet.h>
#include <net/if_arp.h>

#define unsigned int u32_t

void main(int argc,char **argv)
{
	int i = 0;
	if(argc < 5)
	{
		printf("error arg\n");
	}
	for(i = 0;i<5;i++)
	{
		printf("%s\n",argv[0]);
	}

	u32_t raw_socket = 0;



}
