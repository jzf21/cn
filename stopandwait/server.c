#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    int server, newSock, recvstatus;
    char buffer[1024],error[1024];
    int k = 10;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t addrSize;
    struct sockaddr_storage store;
    srand(time(NULL));

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Socket created\n");

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    if (bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        perror("Bind failed");
        close(server);
        exit(1);
    }
    printf("Bind successful\n");

    if (listen(server, 5) == 0)
    {
        printf("Listening\n");
    }
    else
    {
        perror("Listen failed");
        close(server);
        exit(1);
    }

    addrSize = sizeof(store);
    newSock = accept(server, (struct sockaddr *)&store, &addrSize);
    if (newSock < 0)
    {
        perror("Accept failed");
        close(server);
        exit(1);
    }
    printf("Connection accepted\n");

    int frameno, ackno;
    while (k != 0)
    {
        recvstatus = recv(newSock, buffer, sizeof(buffer), 0);
        if (recvstatus <= 0)
        {
            perror("Receive failed");
            break;
        }
        // buffer[recvstatus] = '\0';
        frameno = atoi(buffer);
        sleep(1);
        if (frameno == k)
        {
            if (rand() % 50 < 10)
            {
                sprintf(error, "%d", 320);
                printf("Lost frame %d\n", frameno);
                send(newSock, error, sizeof(error), 0);
                continue;

            }
            k--;
            ackno = k;
            printf("Received frame %d\n", frameno);
            sprintf(buffer, "%d", ackno);
            send(newSock, buffer, sizeof(buffer), 0);
            printf("Sent ACK %d\n", ackno);
        }
        else if (frameno == -1)
        {
            printf("Received: Total of %d frames\n", 10);
            break;
        }
        else
        {
            printf("Received: Invalid frame %d, out of order\n", frameno);
        }
    }

    close(newSock);
    close(server);
    return 0;
}
