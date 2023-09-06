files_tcp = tcp_server tcp_client
files_udp = udp_server udp_client
files_koke_tcp = koke_tcp_server koke_tcp_client
files_koke_udp = koke_udp_server koke_udp_client

CC = gcc
RM = rm -f

all: tcp udp koke_tcp koke_udp

tcp:
	${CC} tcp_client.c -o tcp_client
	${CC} tcp_server.c -o tcp_server
udp:
	${CC} udp_server.c -o udp_server
	${CC} udp_client.c -o udp_client
koke_tcp:
	${CC} koke_tcp_server.c -o koke_tcp_server
	${CC} koke_tcp_client.c -o koke_tcp_client
koke_udp:
	${CC} koke_udp_server.c -o koke_udp_server
	${CC} koke_udp_client.c -o koke_udp_client
	
clean:
	${RM} ${files_tcp} ${files_udp} ${files_koke_tcp} ${files_koke_udp}
re: clean all


.PHONY: all clean re
