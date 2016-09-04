           /* ****************************************************************
            *           A simple SNTP SERVER program                         *                                     
            *          written by Addishiwot T.                              *
            *                                 
            *                     SERVER PROGRAM                             *
            *                               30 Nov 2013, mid night 02:35AM   *
            ******************************************************************/
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

#define portnumberdefault 123

void usage(void);
int main ( int argc, char * argv[])
{    
	
	int n, i, sd;
	struct sockaddr_in server;
	struct sockaddr_in client;	
	int  client_length;
	unsigned long client_packet[48];
	unsigned long transmit_time, segment, server_ntp_packet[12];
	time_t t;
  
  short int port;
           int option;
	 while ((option = getopt(argc, argv,"h")) != -1)
	 {
		 switch(option)
		 {
		 case 'h':
		 usage();
		 }
	 }

 switch (argc)
    {
    case 2:      
         port = atoi(argv[1]);
         break;
    case 1:
         port=portnumberdefault;
         break;
    default:
         printf(" you didn't provide a valid port number");
         usage();
    }	
	
    //socket creation
       if ((sd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
		   printf("unable to create failed \n");
		   exit(0); }
	 
	   bzero(&server, sizeof(server));
	   server.sin_family = AF_INET;
	   server.sin_port = htons(port);
	   server.sin_addr.s_addr = htonl(INADDR_ANY);
	  
       //binding
      
       if ((bind(sd,(struct sockaddr *)&server,sizeof(server))) < 0) 
       {
       printf("binding error\n");
       exit(0); 
       }
      printf("server running...........\n");
		client_length=sizeof(client);         
       
       for(;;) {
       
       //receiving request
       if ((n = recvfrom(sd, client_packet, 48, 0,(struct sockaddr*)&client, &client_length))< 0) {
		   printf("unable to receive from client \n");
		   exit(0);}
		  
	  
	  t = time(NULL);
	  t += 2208988800U;
	  transmit_time = htonl(t);
	  
  
      for(i=0;i<12;i++)
      {
		  server_ntp_packet[i]=client_packet[i];
	  }
	  segment = htonl(610100e3);
	  server_ntp_packet[0]=segment;
	  server_ntp_packet[4]= client_packet[4];
	  server_ntp_packet[8]=transmit_time;
	  server_ntp_packet[9]=0;
	  server_ntp_packet[10]=transmit_time;
	  server_ntp_packet[11]=0;
      	     
  sendto(sd, server_ntp_packet, sizeof(server_ntp_packet), 0,(struct sockaddr*)&client, client_length);
       
   }
   close(sd);
   return(0);
}
  
void usage()
          {       			 
			 printf( "\nUsage :[./program_name][port]\n\n" );
			 exit(1);
	       }
