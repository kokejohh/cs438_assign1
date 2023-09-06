#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    8080
#define MAXLINE 1024

typedef struct arr_int {
    int n;
    int nums[10];
} arr_int;

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main(int argc, char *argv[])
{
    int sock_fd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sock_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len = sizeof(cliaddr);
    arr_int number;
    recvfrom(sock_fd, (arr_int *)&number, sizeof(number), 0, (struct sockaddr *)&cliaddr, (socklen_t *)&len);

    qsort(number.nums, number.n, sizeof(int), compare);

    sendto(sock_fd, (const arr_int *)&number, sizeof(number), 0, (const struct sockaddr *)&cliaddr, len);

    close(sock_fd);
    return 0;
}
