#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAXLINE 1024

typedef struct arr_int {
    int n;
    int nums[10];
} arr_int;

int main(int argc, char *argv[])
{
    int sock_fd, portno;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    struct hostent hostentstruct, *hostentptr;
    
    if (argc < 3)
    {
        printf("Usage: udp_client <serverIP> <serverPort>\n");
        exit(-1);
    }
    if ((hostentptr = gethostbyname(argv[1])) == NULL)
    {
        printf("gethostbyname error\n");
        exit(-1);
    }
    hostentstruct = *hostentptr;
    portno = atoi(argv[2]);

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(portno);
    servaddr.sin_addr = *((struct in_addr *)hostentstruct.h_addr);

    arr_int number;
    printf("Enter number of arrays : ");
    scanf("%d", &number.n);
    for (int i = 0; i < number.n; i++)
    {
        printf("Enter number %d : ", i + 1);
        scanf("%d", &number.nums[i]);
    }

    int len = sizeof(servaddr);
    sendto(sock_fd, (const arr_int *)&number, sizeof(number), 0, (const struct sockaddr *)&servaddr, len);

    printf("\nFrom Server: ");

    arr_int numberServ;
    recvfrom(sock_fd, (arr_int *)&numberServ, sizeof(numberServ), 0, (struct sockaddr *)&servaddr, (socklen_t *)&len);

    for (int i = 0; i < numberServ.n; i++)
    {
        printf("%d ", numberServ.nums[i]);
    }
    printf("\n");

    close(sock_fd);
    return 0;
    return 0;
}
