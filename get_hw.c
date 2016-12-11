#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>

int main()
{
    int fd = 0,i = 0;
    struct ifreq ifr;
    struct sockaddr *addr;
    strncpy(ifr.ifr_name,"wlan0",IFNAMSIZ-1);
    if(0 == (fd = socket(AF_INET,SOCK_DGRAM,0)))
    {
        printf("socket error\n");
        return -1;
    }
    printf("sock fd:%d\n",fd); 
    if(-1 == (ioctl(fd,SIOCGIFHWADDR,&ifr)))/* Get hardware addres*/
    {
        printf("ioctl error\n");
        return -1;
    }
    addr = (struct sockaddr *)(&ifr.ifr_hwaddr);
    for(i = 0;i<14;i++)
    {
        printf("%02x ",(unsigned char)(addr->sa_data[i]));
        
    }
    printf("\n");

}
