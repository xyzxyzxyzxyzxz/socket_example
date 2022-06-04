#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define PORT 3490 /* 客户机连接远程主机的端口 */ 
#define MAXDATASIZE 100 /* 每次可以接收的最大字节 */ 
int main(int argc, char *argv[]) 
{ 
int sockfd, numbytes; 
char buf[MAXDATASIZE]; 
struct in_addr in_ip; 
struct sockaddr_in their_addr; /* connector's address information */ 
if (argc != 2) { 
fprintf(stderr,"usage: ip\n"); 
exit(1); 
} 


if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 
perror("socket"); 
exit(1); 
} 

in_ip.s_addr=inet_addr("127.0.0.1");
their_addr.sin_family = AF_INET; /* host byte order */ 
their_addr.sin_port = htons(PORT); /* short, network byte order */ 
their_addr.sin_addr = in_ip; 
bzero(&(their_addr.sin_zero),8); /* zero the rest of the struct */ 
if (connect(sockfd, (struct sockaddr *)&their_addr,sizeof(struct 
sockaddr)) == -1) { 
perror("connect"); 
exit(1); 
} 
if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) { 
perror("recv"); 
exit(1); 
} 
buf[numbytes] = '\0'; 
printf("Received: %s",buf); 
close(sockfd); 
return 0; 
} 