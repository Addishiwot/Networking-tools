           /******************************************************************
            *           A simple Chat Program using TCP socket               *                                     
            *          written by Addishiwot T.                              *
            *                      	CLIENT PROGRAM                       *
            *                                                                *
            *                               30 Nov 2013, mid night 02:35AM   *
            ******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <getopt.h>

#define defaultport 5013
#define BUFFER_SIZE 1024

void input(char *string,int length);
void usage(void);
int main(int argc, char *argv[])
{
    int sd, n;
    int portnumber;
    struct sockaddr_in server;
    struct hostent *hp;
    
char buffer[BUFFER_SIZE];
char BUFFER[BUFFER_SIZE];
char HELLO[20];
char OK[5];
char NICK[20]="NICK ";
char MSG[100] = "MSG ";
int data_len;
char data[BUFFER_SIZE];
char data1[BUFFER_SIZE];
strcat(NICK,argv[1]);
bzero(OK,5);

  
    // memories to store nick name and message
    int option;
	 while ((option = getopt(argc, argv,"h")) != -1)
	 {
		 switch(option)
		 {
		 case 'h':
		 usage();
		 }
	 }   
	 if(argc!=4)
	 {
		 usage();
		 }      
     switch(argc)
    {
    case 4:      
         portnumber = atoi(argv[3]);
         break;
    case 3:
         portnumber = defaultport;
         break;
    default:
         printf(" you didn't provide a valid portnumber");
         break;   
    }
    /* Sequence of system calls for a TCP (connected state) server: */
     /*   socket() -> connect()-> write()-> read()-> close()     */ 
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
         if (sd < 0) 
           {
             printf("ERROR opening socket");
             exit(0);
		    }		   
	//obtaining server information 	 
    hp = gethostbyname(argv[2]);
    if (hp == NULL)
     {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
      }    
    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    bcopy((char *)hp->h_addr, 
         (char *)&server.sin_addr.s_addr,
         hp->h_length);
    server.sin_port = htons(portnumber);
    
bzero(HELLO,20);
bzero(buffer,BUFFER_SIZE);
bzero(BUFFER,BUFFER_SIZE);
bzero(data,BUFFER_SIZE);
bzero(data1,BUFFER_SIZE);
 //connecting to the srver
    
    if(n=connect(sd,(struct sockaddr *)&server,sizeof(server))<0)
        {
			puts("ERROR connecting");
		    exit(0);
		}
recv(sd, HELLO, 20, 0);
printf("The server sent: %s\n",HELLO);


send(sd,NICK,strlen(NICK),0);
recv(sd, OK, 5, 0);
printf("The server sent: %s\n",OK);

printf("Enter your chat message...\n");
fgets(buffer, BUFFER_SIZE, stdin); 
strcat(MSG,strcat(argv[1]," "));
strcat(MSG,buffer); 
send(sd,MSG,strlen(MSG),0);

bzero(buffer,BUFFER_SIZE);
while(1)
{
bzero(data,BUFFER_SIZE);
data_len = recv(sd, data, BUFFER_SIZE, 0);
if(data_len>0)
{
pid_t pid = fork();
if (pid == 0)
{
printf("%s", data);
bzero(data,BUFFER_SIZE);
printf("Enter your chat message...\n");
char msg[100] = "MSG ";
strcat(msg,strcat(argv[1]," "));
fgets(buffer, BUFFER_SIZE, stdin);  
strcat(msg,buffer);
send(sd,msg,100,0);
bzero(data,BUFFER_SIZE);
}
}
}
}
 
/*void input(char *string,int length)
{
    int x;

    fgets(string,length,stdin);
    for(x=0;x<=length;x++)
    {
        if( string[x] == '\n')
        {
            string[x] = '\0';
            break;
        }
    }
}
*/
void usage()
{     
			 printf( "\nUsage :[./program_name][Nickname][ <IP>][PORT] \n\n" );
			 exit(0);
	}
	
