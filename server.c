//include all the header files
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include <unistd.h>
#include <stdlib.h>
int k=1;
void dostuff(int);

int main()
{
int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

//preparing a socket
server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

//assigning port no.
server_address.sin_port = 9734;
server_len = sizeof(server_address);
bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

//server will be set to the listening mode
listen(server_sockfd, 5);

int pid;

//while loop will let server to keep on accepting the connections
while(1) 
{
  printf("\nserver waiting\n");

  client_len = sizeof(client_address);
  client_sockfd = accept(server_sockfd,
  (struct sockaddr *)&client_address, &client_len);

//fork() function call in order to avoid daemon formation
  pid=fork();
  
  if(pid==0)
  {
   close(server_sockfd);
   dostuff(client_sockfd);
   exit(0);
  }
  else
  {
   close(client_sockfd);
  }
  k++;

}

//close server when no more connections are to be accepted
close(server_sockfd);
return 0;
}

//here reading and writing from the client will be done
void dostuff(int sock)
{
 char ch[40] = "assignment received";
 char data[25500];
 int n;
 n = read(sock, data, 25500); //read data send by client

 if (n < 0) 
 {
 printf("ERROR reading from socket");
 }
 
 printf("data from client: %s",data); 

//here for each client , different file will be created
 FILE *fp; 

 char filename[50];

     sprintf(filename, "Documents/input%d.txt", k);
     
     fp = fopen(filename,"w");
     fputs(data,fp);
     fclose(fp);

 write(sock, ch, 39);

 close(sock);
}
