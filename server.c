//server
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>
int main()
{
int sockfd, newSocket, len, n;
char buffer[200];
struct sockaddr_in serveraddr, cliaddr;
len = sizeof(serveraddr);
serveraddr.sin_family=AF_INET;
serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
serveraddr.sin_port=htons(0);
sockfd=socket(AF_INET,SOCK_STREAM,0);
bind(sockfd,(struct sockaddr*)&serveraddr,len);
getsockname(sockfd,(struct sockaddr*)&serveraddr,&len);
printf("Port for client=%ld\n",(long)ntohs(serveraddr.sin_port));
listen(sockfd,5);
newSocket=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
while(1)
{
recv(newSocket, buffer, 1024, 0);
//buffer[strlen(buffer)-1]='\0';
int y;
sscanf(buffer,"%d",&y);
if(y>=100 || y<=1)
{
printf("\n\n*****CLIENT(B) IS THE WINNER!!*****\n\n***CONNECTION TERMINATED***\n\n\n");
sleep(3);
send(newSocket, "terminated", 1024, 0);
break;
}
/*
else if(strcmp(buffer,"yes")==0)
{
continue;
}
*/
else{
int x;
printf("\n\nCLIENT :%s",buffer);
sscanf(buffer,"%d",&x);

// Generate a random number between 1-10
srand(time(NULL));
int randnum;
randnum = (rand() % 10)+1;
int currvalue = x+randnum;

snprintf(buffer,sizeof(buffer),"%d",currvalue);
printf("\nSERVER :%s",buffer);
send(newSocket, buffer, 1024, 0);
if(currvalue>=100)
{
printf("\n\n*****SERVER(A) IS THE WINNER!!*****\n\n***CONNECTION TERMINATED***\n\n\n");
break;
}
}
}
exit(0);
close(newSocket);
}
