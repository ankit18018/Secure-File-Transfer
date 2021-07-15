#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h> 
#include<time.h>

#define atoa(x) #x

#define PORT 9009

char OTP[5];

void sendOTP(char* email,char* OTP){   // not directly used by main, Call done by generate OTP
    char message[300];
    strcpy(message, "python3 OTP.py ");
    strcat(message,email);
    strcat(message," ");
    strcat(message, OTP);
    system(message);
}


void generateOTP(char* email){     // Will generate OTP and send it to the user
    int OTP1 = 0;
    srand(time(0));
    OTP1 = rand()%253;
    sprintf(OTP, "%d", OTP1);
}



void encrypt(char* file_name, char* OTP){    // Run encryption_file
    // string s = "python3 Encryption.py file_name OTP";
 
    char first[] = "python3 Encryption.py ";
    char second[100];
    char space[] = " ";
    strcpy(second, file_name);
    char third[100];
    strcpy(third, OTP);
    strcat(first,second);
    strcat(first,space);
    strcat(first,third);
    printf("%s %s\n", first, file_name);
    system(first);
 
  }



bool compareOTP(char* otp1, char* otp2){
	int result = strcmp(otp1,otp2);
	if(result == 0) return true;
	else return false;
}


int main()
{
     int socketId, client;
     
     struct sockaddr_in server;
     
     int addLen = sizeof(server);
     
     char buffer[64] = {0};
     
     server.sin_family = AF_INET;
     server.sin_port = htons(PORT);
     server.sin_addr.s_addr = INADDR_ANY;
     
     // creating a socket and its error handling
     socketId = socket(AF_INET, SOCK_STREAM, 0);
     if(socketId < 0){
         printf("[-]Error in creating socket\n");
         exit(1);
     }
     printf("[+]Socket created Sucessfully\n");
     
     
     //binding the socket to port and its error handling
     int binding_status = bind(socketId, (struct sockaddr *)&server, sizeof(server));
     if(binding_status < 0 ){
         printf("[-]Error in binding\n");
         exit(1);
     }
     printf("[+]Binding sucessfully\n");

     // Listening for connection and its error handling
     int listening_status = listen(socketId, 0);
     if(listening_status != 0){
         printf("[-]Error while Listening\n");
         exit(1);
     }
     else{
         printf("[+]Listening..\n");
     }
     
     //Accepting connection
     client = accept(socketId, (struct sockaddr *)&server, (socklen_t *)&addLen);
     printf("[+]Client Connected \n");

     //  Receiving Username and OTP
     char user[30];
 	 recv(client, user, 30,0);
 	 generateOTP(user);
     sendOTP(user, OTP);


 	 char OTP1[5];
 	 recv(client,OTP1,5,0);
 	 printf("%s %s\n", OTP1,OTP);
 	 bool l = compareOTP(OTP1, OTP);

 	 if(!l){
 	 	printf("You have entered Wrong OTP!");
 	 	return -1;
 	 }
 	 else{
 	 	printf("Entered OTP is correct!");
 	 }
     //Reading the file name
     //checking file and opening it in reading mode
     FILE *fp = NULL;
     
     while(fp == NULL){
        recv(client, buffer, 64,0);
        fp = fopen(buffer , "r");
        char status[2] = "0";
        if(fp == NULL){
             printf("[-]Error in opening file\n");
            strcpy(status,"1");
        }
        send(client,status,2,0);
        
     }
     printf("[+]Requested File from client : %s\n", buffer); 
     printf("[+]File opened Sucessfully\n");
     printf("%s\n", buffer);
     encrypt(buffer, OTP);

    // Sending data from file until end of file is reached
     
    char file_nme[64];
    strcpy(file_nme, "cipher_");
    strcat(file_nme, buffer);
    fp = fopen(file_nme,"r");
    if(fp == NULL){
    	printf("File Unable to open! ");
    	return -1; 
    }

    while(1){
         int r = fread(buffer , 1,64,fp);  // r will store number of bytes the file will read
         
         if(r > 0){                          // If valid number of bytes are read from file then 
             send(client,buffer,r,0);        // send it to client
         }
         
        
         if(r<64){                           // If file has not read upto its capacity then either eof has occurred or error
             if(feof(fp)){                    // If we have reached end of file     
                 printf("[+]End of file reached\n"); 
             }
             if(ferror(fp)){                  // If some error has occurred
                 printf("[-]Error in reading\n");
                 exit(1);
             }
             break;
         }
        
     }

     printf("[+]File sent!");
     fclose(fp);        // Close the file
     close(socketId);   // Close the socket
     return 0;
}