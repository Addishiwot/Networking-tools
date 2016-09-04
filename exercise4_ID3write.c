        /************************************************************************
         *                  program to Edit Artist Name and Album                *
         *                  Name of MP3 ID3v2 tags                               *
         *                                                                       *
         *                  Addishiwot Tadesse                                   *
         *                  01 Dec 2014    modified on 9 Dec 2014 08:36          *
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

/* structure to hold the header information*/

 struct header{
        unsigned char header_id[3]; 
        uint8_t version; 
        uint8_t revision; 
        unsigned char flags; 
        uint32_t size; 
        };
/* structure to hold information(if any) about the extended header */
struct extended_header{
	   uint32_t extended_size;
	   unsigned char number_flags;
	   unsigned char extended_flags;	
       };
/* structure to get hold of information about frames*/
struct frames{
	   unsigned char frame_id[4]; 
	   uint32_t frame_size;
	   uint32_t frame_sizeb;	   
	   unsigned char frame_flags[2];	
       };
void usage(void);
 int main (int argc, char *argv[])
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
	   struct header header_info;
	   struct extended_header extended_header_info;
	   struct frames frames_info;
	   int n;
	   int tt;
	   char * a =(char *)malloc(n);
	   a= argv[1];
	   if ( argc != 4 )  
	   	{
			 usage();
		}
		else 
		{	
				
			unsigned char tag_memory[4],
			                 memory[4],
			              frame_flaggs[2], 
			              characters;
			int i;
			unsigned long length_of_data = 0;
			
			char *artist_name=(char *)malloc(n*sizeof(char)); 
			artist_name=argv[2];
			char *album_name=(char *)malloc(n*sizeof(char)); 			
			 album_name=argv[3];
			char ch;
						
			FILE *fp;
			FILE *fpw;                             /* A file pointer.*/
						 
			fp = fopen(a, "r+b");                  /* Open the file for reading */
			fpw= fopen("tester.mp3","w+");
			size_t l1,l2;
			 int ret;
    			
			       int n=sizeof(a);		
                   char *buffer =(char*)malloc(n*sizeof(char));
                    while((l1=fread(buffer,1, sizeof buffer, fp)) > 0) 
                       {
                          l2=fwrite(buffer,1,l1, fpw);
                        }			
												 
			if (fp== NULL) 
				{
					printf( "Unable to open file for reading \n");
					exit(0);
				}			
			else 
				{	 
				   fseek(fp, 0 , SEEK_SET);           /*Set the pointer at at the beginning of the file*/
				   fseek(fpw,0 , SEEK_SET);

				    if ( fread( (void *) memory , 4 , 1 , fp) !=1)				
					  {
						printf("Could not read the file\n");
						fflush(stdout);
						exit (0);
					   }				
				/* copy the string from buffer to tag_id from header_info stuct */
				strncpy( (char *) header_info.header_id , (char *) memory , (size_t) 4);
								
				if ( (size_t) fread( (void *) &header_info.version ,1 , 1 , fp) != 1) 
					{
						printf("Could not read the version\n");
						fflush(stdout);
						exit (0);
					}
				
				if ( fread( (void *) &header_info.revision ,1, 1 ,fp) != 1) 

					{
						printf("Could not read the revision\n");
						fflush(stdout);
						exit (0);
					}				
				/* Read the total size of the header */				
				if ( fread( (void *) memory , sizeof(header_info.size) , 1 , fp) != 1) 

					{
						printf("Unable toread memory\n");
						fflush(stdout);
						exit (0);
					}
				//safe synchronization	integer			
					header_info.size = (memory[3] & 0xFF) |
								((memory[2] & 0xFF) << 7 ) |
								((memory[1] & 0xFF) << 14 ) |
								((memory[0] & 0xFF) << 21 );
				
					/* lengthof the header*/
					length_of_data = header_info.size;
				
					/* Print the data that we have collect so far */
					printf("The mp3 is tagged mp3 with the following information\n");
					fflush(stdout);
					printf(" mp3tag      : %s\n",header_info.header_id);
					printf(" Version     : %d\n",header_info.version);  
				    printf(" Revision    : %d\n",header_info.revision); 
					printf(" Header size : %d\n",header_info.size);
					fflush(stdout);					
					printf("...........................................\n\n");
					
				/* extended hear  6 Bytes */				
				if ( header_info.flags == 0x40)					
					{	
						if ( fread( (void *) memory ,sizeof(extended_header_info.extended_size) , 1 , fp ) != 1)						
							{
								printf("Could not read Memory\n");
								exit (0);
							}						
					/* Break down the packet in pieces and extrac the data */
					extended_header_info.extended_size = (memory[3] & 0xFF) |
										   ((memory[2] & 0xFF) << 7 ) |
										   ((memory[1] & 0xFF) << 14 ) |
										   ((memory[0] & 0xFF) << 21 );
					if ( fread( &extended_header_info.number_flags , 1 , 1 ,fp ) !=1)					
							{
								printf("Could not read Number of Flags\n");
								exit (0);
							}
						
					if ( fread(&extended_header_info.extended_flags ,1 , 1 ,fp ) !=1)					
						{
							printf("Could not read Extended Flags\n");
							exit (0);
						}
						
						fprintf( stdout,"Extended header size: %d\n", extended_header_info.extended_size);
						fflush(stdout);
						/* From the stored value we substract the Extended Header */
						length_of_data = length_of_data - extended_header_info.extended_size;
						/* Reposition the seek pointer after the Extended Header */
						
						if (fseek (fp ,extended_header_info.extended_size + 10 , SEEK_SET ) == -1)						
							{
								fprintf(stderr, "Unable to read extended header size");
								fflush(stdout);
								return EXIT_FAILURE;
							}						
						}					
				else
					{
					 fseek (fp , 10 , SEEK_SET );	
					 fseek (fpw,  10,  SEEK_SET) ;	
					}
						
				while(1) /* Run forever */
						{
							bzero(frames_info.frame_id,4);
							
							if (fread( tag_memory ,4 ,1 , fp ) !=1)							
								{
									printf("Could not read Header_id \n");
									exit (0);
								}							
							strncpy(frames_info.frame_id , tag_memory , 4 );
							fwrite(tag_memory, 4,1,fpw);							
							
							if ( fread( memory , 4 , 1 , fp ) !=1)							
								{
									printf("Could not read Memory\n");
									exit (0);
								}
						
							/* Determine frame size */
							frames_info.frame_size = (memory[3] & 0xFF) |
											         ((memory[2] & 0xFF) << 7 ) |
											         ((memory[1] & 0xFF) << 14 ) |
											         ((memory[0] & 0xFF) << 21 );
											       
											        // printf("\n%d\n",frames_info.frame_size);
										unsigned int x_final=0x00;	
										unsigned int x;        
										if (strncmp( frames_info.frame_id , "TPE1" ,  4 ) == 0 ) 
										{ 
											 x=strlen(artist_name);
											memory[3] = x & 0x7f;
                                            memory[2] = (x >> 7) & 0x7f;
                                            memory[1] = (x >> 14) & 0x7f;
                                            memory[0] = (x >> 21) & 0x7f;											
											fwrite(memory,4,1,fpw);
											 x_final = x_final |  memory[3];
                                             x_final = x_final | ( memory[2]<< 8);
                                             x_final = x_final | ( memory[1]<< 16);
                                             x_final = x_final | ( memory[0] << 24);
                                             frames_info.frame_sizeb=x_final;
                                             // printf("%d\n",frames_info.frame_sizeb);
										} 
							 else if(( strncmp( frames_info.frame_id , "TALB" ,  4 ) == 0 )||
							         ( strncmp(frames_info.frame_id , "TIT2" ,  4 ) == 0 ))
							                {x_final=0;
												x=strlen(album_name);
											memory[3] = x & 0x7f;
                                            memory[2] = (x >> 7) & 0x7f;
                                            memory[1] = (x >> 14) & 0x7f;
                                            memory[0] = (x >> 21) & 0x7f;											
											fwrite(memory,4,1,fpw);
											 x_final = x_final |  memory[3];
                                             x_final = x_final | ( memory[2]<< 8);
                                             x_final = x_final | ( memory[1]<< 16);
                                             x_final = x_final | ( memory[0] << 24);
                                             frames_info.frame_sizeb=x_final;
                                              //printf("%d\n",frames_info.frame_sizeb);
											}
											else{
										fwrite(memory,4,1,fpw);}											   
							if ( fread(frame_flaggs ,2 , 1 , fp) !=1)							
								{
									printf("Could not read Memory\n");
									fflush(stdout);
									exit (0);
								}
							
							strncpy( frames_info.frame_flags , frame_flaggs , 2 );	
							fwrite(frame_flaggs,2,1,fpw);				 
							
							/* Compare the strings */
							if (strncmp( frames_info.frame_id , "TPE1" ,  4 ) == 0 ) 
								{
									//printf("Artist Name  : ");
									//fflush(stdout);
									
									for ( i = 1; i <= frames_info.frame_size; i++ )
										{
											characters = fgetc(fp);											
										}
										
									for ( i = 1; i <= frames_info.frame_sizeb; i++ )
										{
											ch = artist_name[i-1];
											fwrite(&ch,1,1,fpw);
										}										
								}
								
						else if (( strncmp( frames_info.frame_id , "TALB" ,  4 ) == 0 )||
							     ( strncmp(frames_info.frame_id , "TIT2" ,  4 ) == 0 ))
								{
									//printf("%d\n",frames_info.frame_sizeb);
									//printf("Album Title  : ");
									//fflush(stdout);
									
									for ( i=1 ; i <= frames_info.frame_size; i++ )
										{
											characters = fgetc(fp);											
										}
										for ( i=1 ; i <= frames_info.frame_sizeb; i++ )
										{
											ch = album_name[i-1];
									        fwrite(&ch,1,1,fpw);
										}
								}								
							else if (strncmp ( frames_info.frame_id , "TYER" , 4 ) == 0 )							          
								{									
									for ( i = 1; i <= frames_info.frame_size; i++ )
										{
											characters= fgetc(fp);
											//printf("%c",characters);
										    fwrite(&characters,1,1,fpw);											
										}							
								}								
							else if ( strncmp ( frames_info.frame_id , "TCON" ,  4 ) == 0 )
								{
									//printf("content Type : ");
									//fflush(stdout);
									
									for ( i = 1; i <= frames_info.frame_size; i++ )
										{
											characters = fgetc(fp);
											//printf("%c",characters);
											fwrite(&characters,1,1,fpw);
										}							
								}							
							else if ( strncmp (  frames_info.frame_id , "TRCK" ,  4 ) == 0 )
								{
									//printf("Track Number : ");
									//fflush(stdout);
									
									for ( i = 1; i <= frames_info.frame_size; i++ )
										{
											characters = fgetc(fp);
											//printf("%c",characters);
										    fwrite(&characters,1,1,fpw);
										}				
								}
							else if( strncmp ( frames_info.frame_id , "PRIV" ,  4 ) == 0 )
								{
									//printf("Private Info : ");
									//fflush(stdout);
							
									for ( i = 1; i <= frames_info.frame_size; i++ )
										{
											characters = fgetc(fp);
											//printf("%c",characters);
											fwrite(&characters,1,1,fpw);
										}
								
								}								
							else if ( strncmp ( frames_info.frame_id , "TIT2" , 4 ) == 0 )
								{
									//printf("Song Title   : ");
									//fflush(stdout);									
									for ( i = 1; i <= frames_info.frame_sizeb; i++ )
										{
											characters = fgetc(fp);
											//printf("%c",characters);
											fwrite(&characters,1,1,fpw);
										}
								}							
							else
								{
								    break;
									fflush(stdout);
								}
						}						
					if ((int) fflush ((FILE *) fp) !=0)					
						{
							printf("Could not Flush buffer at the end");
							fflush(stdout);
						}
					 fseek(fp, 0 , SEEK_SET);           //Set the pointer at at the beginning of the fil/
				   fseek(fpw,0 , SEEK_SET);
		
		while((l2=fread(buffer,1, sizeof buffer, fpw)) > 0)     //rename back to its original name
                       {
                          l1=fwrite(buffer,1,l2, fp);
                        }
					printf("\t.......EDITING SO SUCCESSFULL!.......\n\n");						
                     	
			}
			    ret=remove(fpw);
                     fclose(fp);
			         fclose(fpw);
		}
				        
	return 0;
	}
	
		void usage()
{
	/* We print argv[0] assuming it is the program name */
       
			 printf( "\nUsage :[./program_name][ <mp3_file_name>][artist_name][album_name] \n\n" );
			 exit(1);
	}
	
