#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int client, recvstatus;
    int k = 10;
    char buffer[1024];
    struct sockaddr_in servAddr;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Socket created\n");

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    if (connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        perror("Connect failed");
        close(client);
        exit(1);
    }
    printf("Connected to server\n");

    while (k != 0)
    {
        sprintf(buffer, "%d", k);
        send(client, buffer, sizeof(buffer), 0);
        printf("Sent frame %d\n", k);

        recvstatus = recv(client, buffer, sizeof(buffer), 0);
        if (recvstatus <= 0 || atoi(buffer)==320)
        {
            printf("ACK not received, resending frame %d\n", k);
            continue;
        }
        // buffer[recvstatus] = '\0';
        printf("ACK received %s\n", buffer);
        k--;
    }
    sprintf(buffer, "%d", -1);
    send(client, buffer, sizeof(buffer), 0);
    printf("Sent: Total of %d frames\n", 10);

    close(client);
    return 0;
}
