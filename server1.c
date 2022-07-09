#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#include "udplib.h"

int main(){
	infodp server_b = SERV_OPEN(8080);
	recvinfo recvs, recvs2;
	while(1){
		recvs = SERV_ISRECV(recvs2, server_b.sock);
		if(recvs.flag==1){
			printf("Server recieved this from client: %s\n", recvs.recv);
			//fputs(recvs.recv, stdout);
		}
	}
}
