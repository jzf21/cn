#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
    int client;
    struct sockaddr_in servAddr,store;
    int server_struct_length=sizeof(servAddr);
    char servMsg[2000], cliMsg[2000];
    client=socket(AF_INET,SOCK_DGRAM,0);
    
    if(client<0){
        printf("Error while creating socket\n");
        exit(1);
    }
    printf("socket created");
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2002);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    printf("enter message to server");
    gets(cliMsg);
    if(sendto(client,cliMsg,strlen(cliMsg),0,(struct sockaddr*)&servAddr,sizeof(servAddr))<0){
        printf("unable to send message");

    }
    printf("sent message");
    if(recvfrom(client,servMsg,strlen(servMsg),0,(struct sockaddr*)&servAddr,sizeof(servAddr))<0){
        printf("error");
    }
    close(client);
}