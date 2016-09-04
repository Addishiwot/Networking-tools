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
   
    #define MAX_FILE_LENGTH  1024
    
     void usage(void);
     
    // reads the  next line from the text file, returns the pointer to that line
    char* getLine(char* loc, FILE* fileStream);
    // checks pattern match
    int checkStringMatch(char* toSearch, char* pattern);
    // Prints the given line to stdout,
    void printLine(int lineNum, char* fileName, char* text);
    // Processes a file, 
    void processfile(char* filename, char* pattern );
   
    // Global variables hold option state
    int optionn = 0;
      FILE *fpp;
	             

    int main(int argc, char**argv)
    {
		
			int option,n;
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
	
                 
            // Holds the search pattern
                 char* pattern = argv[2];           
                 char* filename = argv[1];
                 char *newfile= (char *)malloc(n*sizeof(char));
                 newfile=argv[3];
                 fpp= fopen( newfile,"w+");
	           
                 processfile(filename, pattern);         
            
            return 0;
    }


    void processfile(char* filename, char* pattern)
    {
            FILE* f = fopen(filename, "r");

            // If the file does not exist print an error message and return, otherwise process it
            if(!f)
            {
                    fprintf(stderr, "File %s filed Doesn't exist.\n", filename);
                    return;
            }

            // Will hold each line scanned in from the file
            char* line = (char*)malloc(MAX_FILE_LENGTH*sizeof(char)); 
            int lineNum = 1;
int counter =0;                         
            while(!feof(f))
            {                       
                    line = getLine(line, f);

                    // Only proceed if the line is non-null
                    if(line)
                    {
                                                   
                                    if(checkStringMatch(line, pattern))
                                    {
										fprintf(fpp,line);
                                            //printLine(lineNum*optionn, filename, line);
                                    counter++;
}
                                          
                            lineNum++;
                    }
               
            }
 printf("%d lines match the pattern \n",counter);

            // Close file and free line
            fclose(f);      
            free(line);
    }

    char* getLine(char* loc, FILE* fileStream)
    {
            return fgets(loc, MAX_FILE_LENGTH, fileStream);
    }

    int checkStringMatch(char* toSearch, char* pattern)
    {       char* exists = strstr(toSearch, pattern);
            if(exists)
            {
                    return 1;
            }
            return 0;
    }

    void printLine(int lineNum, char* fileName, char* text)
    {
            if(lineNum)
            {               
                    printf("%d %s %s", lineNum, fileName, text);
            }
            else
            {
                    printf("%s %s", fileName, text);
            }
    }
void usage()
{
	/* We print argv[0] assuming it is the program name */
        printf( "usage: [%s][source_file][pattern to be matched][destination_file]\n\n", "program_name" );	
	exit(0);
	}
