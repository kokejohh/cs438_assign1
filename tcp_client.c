#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
/* Protocol
    client -> Message
    capitalized Message <-- server
*/

void main(argc,argv)
int argc;
char *argv[];
{
  char hostname[50];
  int portno;
  int sock_1;
   static struct sockaddr_in sock_name,client_info; 
   struct hostent hostentstruct,*hostentptr;
   int retval;
   char str1[81],ch;
   if(argc < 3) {
    printf("Usage: client  <hostname> <port#>\n");
    exit(-1);
   }
   strcpy(hostname,argv[1]);
   portno = atoi(argv[2]);
   if ((sock_1 = socket(AF_INET,SOCK_STREAM,0)) == -1) {
      printf("socket error\n");
      exit(-1);
   }
   if ((hostentptr = gethostbyname(hostname)) == NULL) {
      printf("gethostbyname error\n");
      close(sock_1);
      exit(-1);
   }
   hostentstruct = *hostentptr;
   sock_name.sin_family = AF_INET;
   sock_name.sin_port = htons(portno);
   sock_name.sin_addr = *((struct  in_addr *)hostentstruct.h_addr);
   if (retval = connect(sock_1,(const struct sockaddr *)&sock_name,sizeof(sock_name))) {
      printf("connect error\n");
      close(sock_1);
      exit(-1);
   }
   printf("Enter Message:");
   fgets(str1,80,stdin);
   strcat(str1,"\n");
   write(sock_1,str1,strlen(str1));
   printf("From Server:");
   do{
	   read(sock_1,&ch,1);
	   putchar(ch);
   } while(ch != '\n');
   close(sock_1);
}
