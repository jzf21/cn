#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client, newSock, k = 5, m = 1, p;
    int length;
    char buffer[1024];
    struct sockaddr_in servAddr, store;
    socklen_t addrSize;
    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    printf("sending data to server");
    scanf("%s", buffer);
    send(client, buffer, sizeof(buffer), 0);
    recv(client, &length, sizeof(length), 0);
    printf("the size is %d", length);
    exit(1);
    close(client);
}
