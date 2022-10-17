#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

struct message
{
    char command[1024];
    char message[1024];
    char to[1024];
};

int handeleMessage(int fd)
{
    struct message mes;
    char buff[1024];
    int n;
    int id;
    int flag = 0;
    id = fork();
    if (id == 0)
    {

        for (;;)
        {
            bzero(buff, 1024);
            if (flag == 0)
                printf("SOCKET[input]=> ");
            flag = 0;
            n = 0;
            while ((buff[n++] = getchar()) != '\n')
                ;
            sscanf(buff, "%s \"%[a-zA-Z ]\" %s", mes.command, mes.message, mes.to);
            if (strlen(buff) >= 3)
            {

                if (strcmp("list", mes.command) == 0)
                {
                    bzero(buff, 1024);
                    strcat(buff, "ok");
                    strcat(buff, "|");
                    strcat(buff, "list");
                    write(fd, buff, 1024);
                    bzero(buff, 1024);
                    flag = 1;
                }
                else if (strcmp(":exit", mes.command) == 0)
                {
                    write(fd, "", 1);
                    return (id);
                }
                else if (strlen(mes.to) > 5)
                {
                    bzero(buff, 1024);
                    strcat(buff, mes.to);
                    strcat(buff, "|");
                    strcat(buff, mes.message);
                    write(fd, buff, sizeof(buff));
                    bzero(buff, 1024);
                }
            }
        }
    }
    else

    {
        while (1)
        {
            read(fd, buff, sizeof(buff));
            if (strncmp(":exit", buff, 4) == 0 || strcmp(buff, "") == 0)
                return (id);
            printf("\nSOCKET[output]=> %s\nSOCKET[input]=> ", buff);
            fflush(stdout);
            bzero(buff, 1024);
        }
    }
}
int main(int argc, char **argv)
{
    int sockfd, len, pid;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("[-] Socket connection failed \n");
        return 0;
    }
    else
        printf("[+] Socket connetcion successful \n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(1234);
    len = sizeof(servaddr);
    if (connect(sockfd, (struct sockaddr *)&servaddr, len) != 0)
    {
        printf("[-] Conection close\n");
        close(sockfd);
        return -1;
    }
    else
        printf("[+] Connected to the server\n");
    pid = handeleMessage(sockfd);
    printf("[-] Closing client\n");
    close(sockfd);
    kill(pid, SIGKILL);
    return 0;
}