#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
    int server;
    char cliMsg[1024], servMsg[1024];
    struct sockaddr_in servAddr,client_addr;
    int client_struct_length =sizeof(client_addr);
    server=socket(AF_INET,SOCK_DGRAM,0);
    if(server<0){
        printf("error");
        exit(1);

    }
    printf("Socket created succesfully");
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2002);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr))<0){
        printf("error");
    }
    printf("binding done");
    if(recvfrom(server,cliMsg,sizeof(cliMsg),0,(struct sockaddr*)&client_addr,&client_struct_length)<0){
        printf("couldnt recieve");

    }
    printf("msg from client:%s\n",cliMsg);
    strcpy(servMsg,cliMsg);
    if(sendto(server,servMsg,strlen(servMsg),0,(struct sockaddr*)&client_addr,client_struct_length)<0){
        printf("cant send");

    }
    close(server);
}