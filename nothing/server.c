#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server, newSock;
    char climsg[1024];
    int length;
    struct sockaddr_in servAddr, client_addr;
    socklen_t addrSize;
    struct sockaddr_storage store;
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0)
    {
        printf("fail");
        exit(1);
    }
    printf("socket crreated\n");
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        printf("did not bind");
    }
    if (listen(server, 5) == 0)
    {
        printf("Listening\n");
    }
    else
    {
        printf("error");
    }
    newSock = accept(server, (struct sockaddr *)&store, &addrSize);
    recv(newSock, climsg, 1024, 0);
    printf("%d", strlen(climsg));
    length = strlen(climsg);
    send(newSock, &length, 19, 0);
    close(newSock);
    close(server);
}