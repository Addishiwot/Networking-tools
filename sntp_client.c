#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

void usage(void);

int main(int argc, char *argv[]) {
 struct timeval tv;
  time_t t;
  unsigned long int  z;    
//char *hostname=(char *)"163.117.202.33";
//char *hostname=(char *)"pool.ntp.br";
//char *hostname=(char *)"200.20.186.76";
short int port;
char *hostname;
       int option;
	 while ((option = getopt(argc, argv,"h")) != -1)
	 {
		 switch(option)
		 {
		 case 'h':
		 usage();
		 }
	 }
if(argc<3)
{
	hostname=(char *)"200.20.186.76";
	port=123;                                  //NTP is port 123
}
else{
     hostname=(char *)argv[1];
     port=atoi(argv[2]);
   }                   
int maxlen=1024; 
int sock_desc,i,n;  // socket
long tmit;
 gettimeofday(&tv, NULL); 
      z = 2208988800U;
      unsigned long int tt= htonl(tv.tv_sec + z);
      unsigned long int kk= tv.tv_usec;        
unsigned char msg[48]={0b00100011,0,0,0,tt,kk,0,0,0,0,0,0};	   // the packet we send
unsigned long  buf[maxlen];                    // the buffer we get back  
struct sockaddr_in server;
 

     // system calls
/*socket()->send()->recvfrom()*/

sock_desc=socket(AF_INET, SOCK_DGRAM, 0);
if(sock_desc<0)
{
printf("unable to create socket");
}

bzero( &server, sizeof( server ));
server.sin_family=AF_INET;
server.sin_addr.s_addr = inet_addr(hostname);
server.sin_port=htons(port);

// send the data
printf("sending request to ntp server..............\n");
n=sendto(sock_desc,msg,sizeof(msg),0,(struct sockaddr *)&server,sizeof(server));
if(n<0)
{	
	printf("unable to send Request");
	
	}
// get the data back
struct sockaddr saddr;
socklen_t saddr_l = sizeof (saddr);
n=recvfrom(sock_desc,buf,48,0,&saddr,&saddr_l);
if(n<0)
{	
	printf("unable to receive from Server");
	
	}

//We get 12 long words back in Network order

for(i=0;i<12;i++) {
   //printf("%d\t%-8x\n",i,ntohl(buf[i]));
    long tmit2=ntohl((time_t)buf[i]);
}

tmit=ntohl((time_t)buf[10]);    //# get transmit time
tmit-= 2208988800U; 

printf("Time: %s",ctime(&tmit));

return 0;
}


	void usage()
          {       
			 printf( "\nUsage :from live server:  [./program_name]\n" );			 
			 printf( "Usage :from localhost [./program_name][127.0.0.1][port]\n\n" );
			 exit(1);
	       }
