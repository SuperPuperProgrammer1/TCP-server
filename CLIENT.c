#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/statvfs.h>

#include "udpextra.h"
#include "tick_timer.h"
#include "TCPclienf.h"
#include "itoa.h"
#include "f.h"

#define SIZE 1400

int main(int argc, char argv[]){
	if(argc<2){
		Error("Too few arguments\n");
	}	
	int port = 1212;
	int get;
	int rc;
	char ip[] = "127.0.0.1";
	infodp cf = CLIENT_OPEN(port, ip);
	int sock = cf.sock;
	char buffer[SIZE];
	char name[256];
	if(CLIENT_CONNECT(sock, cf.addr)==1){ Error("Connect:connection failed: Server not answering"); }
	if(SendHeartBeat(sock)==1){ Error("connection failed: Server not answering"); }
	get = getopt(argc, argv, "tfi");
	memset(buffer, 0, SIZE);
	if(get=='f'){
		printf("Repeat file name: "); 
		scanf("%s", &name);
		printf("\n");
		send(sock, FCODE, strlen(FCODE), 0);
		rc = SendFile(sock, buffer, SIZE, name);
		if(rc==0){
			printf("OK, file has been created and filled\n");
		}
		else{
			Error("Something went wrong...\n");
		}
	}
	if(get=='t'){
		send(sock, TCODE, strlen(TCODE), 0);
		RecvTime(sock, buffer, SIZE);
		printf("Server: ");
		printf("%s\n", buffer);
	}
	if(get=='i'){
		send(sock, PCODE, strlen(PCODE), 0);
		printf("Server: ");
		rc = recv(sock, buffer, SIZE, 0);
		if(rc <= 0){
			Error("Recv: Failed");
		}
		send(sock, "OK", 2, 0);
		printf("%s", buffer);
		memset(buffer, 0, SIZE);
		rc = recv(sock, buffer, SIZE, 0);
		if(rc <= 0){
			Error("Recv: Failed");
		}
		send(sock, "OK", 2, 0);
		printf("%s", buffer);
	}
}
