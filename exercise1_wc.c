/*************************************************************************
*                  C program for counting the number of lines            *
*                   written by Addishiwot Tadesse                        *
*                                                                        *
*                                                                        *
*************************************************************************/
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
int main ( int argc, char *argv[] )
{
	int option;
	 while ((option = getopt(argc, argv,"h")) != -1)
	 {
		 switch(option)
		 {
		 case 'h':
		 usage();
		 }
	 }
	 
	 if(argc!=2)
	 {
		 usage();
		}
	char ch;	
	int character_counter=0;
	int line_counter=0;

		        // We assume argv[1] is a filename to open
        FILE *file = fopen( argv[1], "r" );

        /* fopen returns 0, the NULL pointer, on failure */
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {         
         
            while  ( ( ch = fgetc( file ) ) != EOF )
            {
                if(ch=='\n'){
			      line_counter++;
			    }
		      character_counter++;
                    printf("%c",ch);
            }
            printf("the number of lines is : %d \n",line_counter);
	    printf("hello");
            printf("the number of characters is : %d \n",character_counter);
            fclose( file );
        
    }
}

void usage()
{
	/* We print argv[0] assuming it is the program name */
        printf( "usage: Fomat is [./%s] [filename]\n", "program_name" );
        exit(1);
	}
