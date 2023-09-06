// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<netdb.h>	
#define MAXLINE 1024
	
// Driver code
int main(int argc, char *argv[]) {
	int sockfd;
        int portno;
	char buffer[MAXLINE];
	struct sockaddr_in	 servaddr;
        struct hostent hostentstruct,*hostentptr;
        if(argc < 3) {
           printf("Usage: udp_client <serverIP> <serverPort>\n");
           exit(-1);
        }	
      if ((hostentptr = gethostbyname(argv[1])) == NULL) {
          printf("gethostbyname error\n");
          exit(-1);
       }
      hostentstruct = *hostentptr;
      portno = atoi(argv[2]);
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
        servaddr.sin_addr = *((struct  in_addr *)hostentstruct.h_addr);
		
	int n, len;
        printf("Enter message: ");
        fgets(buffer,80,stdin);
	sendto(sockfd, (const char *)buffer, strlen(buffer),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
			
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				0, (struct sockaddr *) &servaddr,
				(socklen_t *)&len);
	buffer[n] = '\0';
	printf("Receive from Server : %s\n", buffer);
	
	close(sockfd);
	return 0;
}



