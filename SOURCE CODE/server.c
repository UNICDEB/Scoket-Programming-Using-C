#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
int CLIENTNO = 3;
struct argument
{
    char *client;
    char *message;
};
char clients[7][10] = {"client1", "client2", "client3", "client4", "client5"};
struct argument split(char *str)
{
    struct argument arg;
    int i = 0, j = 0;
    char str1[1024], str2[1024];
    int flag = 0;
    bzero(str1, 1024);
    bzero(str2, 1024);
    while (*str != '\0')
    {
        if (*str != '|')
        {
            if (flag == 0)
                str1[i++] = *str;
            else
                str2[j++] = *str;
        }
        else
            flag = 1;
        str++;
    }
    arg.client = str1;
    arg.message = str2;
    return arg;
}

void handleClient(struct sockaddr_in clientaddr[], int clientfd[], int current)
{
    struct argument arg;
    char buff[1024];
    char clientString[1024];
    int index = 0;

    while (1)
    {
        fflush(stdout);
        bzero(buff, 1024);
        read(clientfd[current], buff, sizeof(buff));
        arg = split(buff);
        fflush(stdout);
        if (strcmp(arg.client, "server") == 0)
        {

            fflush(stdout);
            printf("From client: %s\n", arg.message);
            fflush(stdout);
        }
        else if (strcmp(arg.message, ":exit") == 0 || strcmp(arg.message, "") == 0)
        {
            fflush(stdout);
            printf("Disconnected from %s:%d\n", inet_ntoa(clientaddr[current].sin_addr), ntohs(clientaddr[current].sin_port));
            fflush(stdout);
            break;
        }
        else if (strcmp(arg.message, "list") == 0)
        {
            bzero(clientString, 1024);
            for (index = 0; index < CLIENTNO; index++)
            {
                if (index != current)
                {
                    strcat(clientString, clients[index]);
                    if (index < CLIENTNO - 1)
                        strcat(clientString, ", ");
                }
            }
            write(clientfd[current], clientString, 1024);
            bzero(clientString, 1024);
        }
        else
        {
            if (strcmp(arg.client, "client1") == 0 && current != 0)
            {
                bzero(buff, 1024);
                strcat(buff, "Get \"");
                strcat(buff, arg.message);
                strcat(buff, "\" from ");
                strcat(buff, clients[current]);
                write(clientfd[0], buff, 1024);
            }
            else if (strcmp(arg.client, "client2") == 0 && current != 1)
            {
                bzero(buff, 1024);
                strcat(buff, "Get \"");
                strcat(buff, arg.message);
                strcat(buff, "\" from ");
                strcat(buff, clients[current]);
                write(clientfd[1], buff, 1024);
            }
            else if (strcmp(arg.client, "client3") == 0 && current != 2)
            {
                bzero(buff, 1024);
                strcat(buff, "Get \"");
                strcat(buff, arg.message);
                strcat(buff, "\" from ");
                strcat(buff, clients[current]);
                write(clientfd[2], buff, 1024);
            }
            else if (strcmp(arg.client, "client4") == 0 && current != 3)
            {
                bzero(buff, 1024);
                strcat(buff, "Get \"");
                strcat(buff, arg.message);
                strcat(buff, "\" from ");
                strcat(buff, clients[current]);
                write(clientfd[3], buff, 1024);
            }
            else if (strcmp(arg.client, "client5") == 0 && current != 4)
            {
                bzero(buff, 1024);
                strcat(buff, "Get \"");
                strcat(buff, arg.message);
                strcat(buff, "\" from ");
                strcat(buff, clients[current]);
                write(clientfd[4], buff, 1024);
            }
            else
            {
                fflush(stdout);
                printf("Invalid client %s\n", arg.client);
                fflush(stdout);
            }
            bzero(arg.message, 1024);
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    int c = 0;
    if (argc > 1)
    {
        c = atoi(argv[1]);
        if (c < 2)
        {
            printf("[-] Minimum client number is 2 \n");
            exit(0);
        }
        else if (c > 5)
        {
            printf("Max client number is 5 \n");
            exit(0);
        }
        else
            CLIENTNO = c;
    }
    printf("Maximum number of clients are connected at a time = 5 \n");
    printf("The default number of clients = 3 \n");
    printf("SERVER RUN COMMAND:\n");
    printf("    ./server   :- if you not provide the client number then client no is 3\n");
    printf("    ./server client_number  :- client_number is an possitive integer between 2 to 5 \n");
    socklen_t peer_addr_size;
    pid_t childpid;
    int sockfd;
    int clientfd[CLIENTNO];
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr[CLIENTNO];
    int i = -1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Error in connection.\n");
        return 0;
    }
    else
        printf("Server Socket is created.\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1234);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Error in binding.\n");
        close(sockfd);
        return -1;
    }
    else
        printf("Bind to port %d\n", 1234);
    if ((listen(sockfd, 5)) != 0)
    {
        printf(" Error in binding.\n");
        close(sockfd);
        return -1;
    }
    else
        printf("Listening....\n");
    printf(" Please connect %d clients first then the data communication is possiblle otherwise not!!\n", CLIENTNO);
    for (i = 0; i < CLIENTNO; i++)
    {
        clientfd[i] = accept(sockfd, (struct sockaddr *)&clientaddr[i], &peer_addr_size);
        if (clientfd[i] < 0)
        {
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(clientaddr[i].sin_addr), ntohs(clientaddr[i].sin_port));
    }
    printf("All clients are connected succesfully, now you can communicate with each other\n");
    i = -1;
    while (1)
    {
        i++;
        if (i < CLIENTNO && (childpid = fork()) == 0)
        {
            close(sockfd);
            handleClient(clientaddr, clientfd, i);
        }
    }
    close(sockfd);
    return 0;
}