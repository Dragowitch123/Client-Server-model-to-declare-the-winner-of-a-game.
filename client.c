//client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>
int main()
{
int clientSocket,len,n;
long port;
struct sockaddr_in cli_addr;
char buffer[1024];
len = sizeof(cli_addr);
printf("Enter the port number, you got from server side:");
scanf("%ld",&port);
while((getchar())!='\n');
cli_addr.sin_family=AF_INET;
cli_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
cli_addr.sin_port=htons(port);
clientSocket = socket(AF_INET, SOCK_STREAM, 0);
connect(clientSocket,(struct sockaddr *)&cli_addr,len);
printf("\n***Type \"exit\" to terminate*\n");

printf("\n\nCLIENT(Enter a number) :");
fgets(buffer, 1024, stdin);
send(clientSocket, buffer, 1024, 0);
int x,y;
while(1)
{
recv(clientSocket, buffer, 1024, 0);
// receive number from server
printf("SERVER :%s \n",buffer);
sscanf(buffer,"%d",&x);
if(x>=100)
{
printf("\n***SERVER(A) is the winner.***\n\nConnection terminated!!\n\n");
break;
}
// Generate a random number between 1-10
srand(time(NULL));
int randnum;
randnum = (rand() % 10)+1;
int currvalue = x+randnum;
snprintf(buffer,sizeof(buffer),"%d",currvalue);
printf("\nCLIENT :%s\n",buffer);
// printf("Enter yes to continue or no to exit(yes/no):\n");
// fgets(buffer, 1024, stdin);
sleep(2);
send(clientSocket, buffer, 1024, 0); // send number to server
//buffer[strlen(buffer)-1]='\0';
if(currvalue>=100)
{
printf("\n\n*****CLIENT(B) IS THE WINNER!!*****\n\n***CONNECTION TERMINATED***\n\n\n");
break;
}
sscanf(buffer,"%d",&y);
if(y>=100 || y<=1)
{
printf("Connection terminated!!\n\n");
break;
}
}
printf("\n\n");
close(clientSocket);
exit(0);
//return 0;
}
