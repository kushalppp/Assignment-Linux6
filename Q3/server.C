#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include<arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#define SIZE 1024

void send_file(FILE *fp,int server_sockfd)
{
int n;
char data[SIZE] ={0};
fgets(data,SIZE,fp);

if(send(server_sockfd,data,sizeof(data),0)==-1)
{
perror("error sendig file");
exit(1);
}
bzero(data,SIZE);

}

int main()
{
FILE *fp;
char *filename="send.txt";
int server_sockfd, client_sockfd;
int server_len, client_len;     
struct sockaddr_in client_address;
struct sockaddr_in server_address;
server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr =inet_addr("127.0.0.1");
server_address.sin_port = 9734;
server_len = sizeof(server_address);
bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

listen(server_sockfd, 5);
signal(SIGCHLD, SIG_IGN);
while(1) 
{
char ch;
printf("server waiting\n");

client_len = sizeof(client_address);
client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);

fp=fopen(filename,"w");
if(fp==NULL)
{
perror("not open file");
exit(1);
}
send_file(fp,server_sockfd);
printf("sending file successfully\n");
close(client_sockfd);
}
}