           /* ****************************************************************
            *           A simple Chat Program using TCP socket               *                                     
            *          written by Addishiwot T.                              *
            *                                 
            *                     SERVER PROGRAM                             *
            *                               30 Nov 2013, mid night 02:35AM   *
            ******************************************************************/
#include <stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/mman.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>
#include<strings.h>
#include<unistd.h>


#define MAX_DATA 1024
#define defaultport 5013

int clients[100];
int i = 1;
   void usage();
//clients Thread
void *Chatroom (void *dest)
{
int data_len;
int sock = *(int*)dest;

//Declaration and initializations

char HELLO[5] = "HELLO";
char data[MAX_DATA];
bzero(data,MAX_DATA);
char OK[5] = "OK";
char NICK[20];
send(sock,HELLO,5,0);
recv(sock, NICK, MAX_DATA, 0);
send(sock,OK,5,0);
while(data_len = recv(sock, data, MAX_DATA, 0))
{
int j;
for (j = 1;j<=i;j++)
{
data[data_len] = '\0';
send(clients[j], data, data_len, 0);
//bzero(data,MAX_DATA);
}
}
close(sock);
}

//Main Thread
main (int argc, char *argv[])
{
   int option;
   short int port;
 while ((option = getopt(argc, argv,"h")) != -1)
	 {
		 switch(option)
		 {
		 case 'h':
		 usage();
		 }
	 }   
     
    //test if the input from the terminal is valid
switch (argc)
    {
       case 2:
          /* No arguments - use default port number. */
           port=atoi(argv[1]);      
           break;
       case 1:
          /* use the default port number */
          port=defaultport;
          break;
       default:     
          printf("please insert a port number");
          break;
    } 
struct sockaddr_in server;
struct sockaddr_in client ;
int sd;
int new;
//int i = 1;
int len = sizeof(struct sockaddr_in);
int data_len;
char data[MAX_DATA];

if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
{
printf("socket Error");
exit(-1);
}

bzero(&server,sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(port);
server.sin_addr.s_addr = htonl(INADDR_ANY);
bzero(&server.sin_zero, 8);


if((bind(sd, (struct sockaddr *)&server, len)) == -1)
{
printf("Bind Error");
exit(-1);
}

listen(sd, 1);
printf("....CHAT SERVER RUNNING....\n");

while(1)
{

if((new = accept(sd, (struct sockaddr *)&client, &len)) ==-1)
{
printf("Accept Error\n");
exit(-1);
}

clients[i] = new;
i++;
pthread_t t;

pthread_create (&t,NULL,Chatroom, &new);
pthread_detach(t);

}
}

   void usage()
{
        printf( "\nusage: [./%s] [PORT]\n\n", "PROGRAM_NAME" );
        exit(1);
	}














