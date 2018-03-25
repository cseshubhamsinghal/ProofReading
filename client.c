
//include header files
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
 
int main2(char data[25500]) // this data array size can be adjusted
{
 int sockfd;
 int len;
 struct sockaddr_in address;
 
 int result;
 char ch[40];
 //creation of socket
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = inet_addr("127.0.0.1"); 

 /*"10.9.1.40" is the inet address tested in order to make communication over
   remote system */
 
 //assigning port number
 address.sin_port = 9734;
 
 //connection to server socket
 result = connect(sockfd, (struct sockaddr *) &address, sizeof(address));
 if(result == -1) 
 {
  perror("oops: client4..exit as result is -1\n");
  exit(1);
 }
 
 //sending of data
 write(sockfd, data, strlen(data));
 printf("\n");
 
 read(sockfd, ch, 39);
 
 //receiving of acknowledgement from server
 printf("acknowledgement from server : %s", ch);
 
 close(sockfd);
 exit(0);
}
