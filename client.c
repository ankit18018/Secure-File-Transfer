#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h> 

#define PORT 9009


void decrypt(char* filename, char* key){        // Will decrypt the received file
    char first[] = "python3 Decryption.py ";
    char second[100];
    char space[] = " ";
    strcpy(second, filename);
    char third[100];
    strcpy(third, key);
    strcat(first,second);
    strcat(first,space);
    strcat(first,third);
	system(first);
}



int main()
{
 int sock = 0;
 struct sockaddr_in server;
 
 //Create buffers for sending & receiving data
 char buffer[64];
 
 

 server.sin_family = AF_INET;     //For IPV4
 server.sin_port = htons(PORT);   //Host to Network Short
 server.sin_addr.s_addr = INADDR_ANY;  //Remote host IP
 
 
 
 //Creating socket and its error handling
 sock = socket(AF_INET, SOCK_STREAM, 0);
 if(sock < 0){
     printf("Error in creating socket\n");
     exit(1);
 }
 printf("Socket Created Sucessfully\n");

 
 
 
 //Establishing connection and its error handling
 int connection_status = connect(sock, (struct sockaddr * )&server, sizeof(server));
 if(connection_status == -1){
     printf("[-]Error while establishing connection\n");
 }
 printf("[+]Connection established\n");
 

 //Client send OTP for confirmation
 char user[30];
 printf("Enter Username(Email address): ");
 scanf("%s",user);
 send(sock, user, strlen(user),0);
 
 char OTP[5];
 printf("Enter OTP: ");
 scanf("%s",OTP);
 send(sock,OTP,strlen(OTP),0);



 FILE *fp;
 //  Client asking for correct file name
 while(1){
    
    printf("Enter File name: ");
    scanf("%s", buffer);
 
    // Sending the file name to server  
    send(sock, buffer, strlen(buffer), 0);
    // receive the status of file found on server
    char status[2];
    recv(sock,status,2,0);
    

    if(strcmp(status,"0") == 0){
        printf("File Found on server!\n");
        break;
    }
    else{
        printf("[-]No file received\n");
        printf("Do you want to ask for file again\n");
        printf("Enter Y for Yes and anything for No\n");
        char input[5];
        char exit_status[5] = "Y";
        scanf("%s",input);
        if(strcmp(input,"Y") == 0){
            
            continue;
        }
        else{
            
            exit(1);
        }
        
    }
 }
    
 
 //opening the file in write mode and writing into it
 char filename[] = "cipher_";
 strcat(filename,buffer);
 fp = fopen(filename,"w"); 

 while(1){
    
    int r = recv(sock,buffer,64,0);  // Number of bytes received will be stored in r
    
    if(r > 0){                        // If some bytes are received
        fwrite(buffer , 1,r,fp);     // Write it in file
    }
    else{                            // Else break the loop
        break;
    }

 }
 decrypt(filename, OTP);          // Decrypting recieved file

 printf("[+]File received");
 fclose(fp);

 
 close(sock);
 
}