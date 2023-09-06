#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#include<errno.h>
#include<sys/types.h>
#include<ctype.h>
/* link with option -lnsl -lsocket */
/* Protocol
    client -> Message
    capitalized Message <-- server
*/

void main()
{
   int portno=5789;
   int sock_1,sock_2;
   static struct sockaddr_in sock_name,client_info;
   int retval,len;
   char str1[50],ch;

   if ((sock_1 = socket(AF_INET,SOCK_STREAM,0)) == -1) {
      printf("socket error\n");
      exit(-1);
   }
   sock_name.sin_family = AF_INET;
   sock_name.sin_port = htons(portno);
   sock_name.sin_addr.s_addr = htonl(INADDR_ANY);
   if (retval = bind(sock_1,(const struct sockaddr *)&sock_name,sizeof(sock_name))) {
      printf("bind error\n");
      close(sock_1);
      exit(-1);
   }
   if (retval = listen(sock_1,5)) {
      printf("listen error\n");
      close(sock_1);
      exit(-1);
   }
   len = sizeof(client_info);
   do {
   sock_2 = accept(sock_1,(struct sockaddr *)&client_info,&len);
   printf("connect\n");
   if (sock_2 < 0) {
      printf("accept error\n");
      close(sock_1);
      exit(-1);
   }
   len = 0;
   do{
    read(sock_2,&ch,1);
	str1[len++] = toupper(ch);
   } while(ch != '\n');
   write(sock_2,str1,len);
   close(sock_2);
   }
   while (strncmp(str1, "EXIT", 4));
   close(sock_1);
}

