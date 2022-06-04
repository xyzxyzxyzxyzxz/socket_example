#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>


#define MYPORT 3490
#define BACKLOG 10

int main (void)
{
    int sockfd,new_fd,sockfd_tmp;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int sin_size;

    if ((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket");
        exit(1);
    }
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(MYPORT);
    my_addr.sin_addr.s_addr=INADDR_ANY;
    bzero(&(my_addr.sin_zero),8);

    sockfd_tmp=sockfd;

    if (bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) { 
        perror("listen"); 
        exit(1); 
    } 

    while (1)
    {
        sin_size=sizeof(struct sockaddr_in);
        memset(&their_addr, 0, sizeof(struct sockaddr_in));
        if ((new_fd=accept(sockfd,(struct sockaddr *)&their_addr,(socklen_t*)&sin_size))==-1)
        {
            perror("accept");
            continue;
        }
        printf("=====================\n");

        printf("server:got connect from%s\n",inet_ntoa(their_addr.sin_addr));
        printf("+++++++++++++++++++++++++\n");
        if(!fork())
        {
            if(send(new_fd,"Hello ,world\n",14,0)==-1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd);
        while (waitpid(-1,NULL,WNOHANG)>0);
    }
}