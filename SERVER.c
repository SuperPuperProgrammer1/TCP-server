#include <dirent.h>
#include <sys/stat.h>
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
#include <sys/statvfs.h>
#include <stdarg.h>

#include "tick_timer.h"
#include "udpextra.h"
#include "TCPserverf.h"
#include "itoa.h"
#include "f.h"

#define SIZE 1400

int main(int argc, char*argv[]){
	int csock = TSERV_OPEN(1212);
	int sock;
   	char buffer[SIZE];
	char cpubuf[SIZE];
	char membuf[SIZE];
	char rbuf[SIZE];
	int rc;
	while(1){
		sock = TSERV_ISCONNECTED(csock);
		if(sock < 0){ printf("Failed to connect to client\n"); continue;}
		memset(buffer, 0, SIZE);
		memset(cpubuf,0,SIZE);
		memset(membuf,0,SIZE);
		memset(rbuf,0,SIZE);
	        if(CatchHeartBeat(sock)==1){
       			printf("Connection failed...\n");
			continue;
	 	}
		rc = recv(sock, rbuf, SIZE, 0);
		if(rc == 4){
			RecvFile(sock, SIZE);
		}	
		if(rc == 5){
			SendTime(sock, buffer, SIZE);
		}
		if(rc == 6){
			CPUinfo(cpubuf, SIZE);
			MEMinfo(membuf, SIZE);
			send(sock, cpubuf, SIZE, 0);
			rc = recv(sock, rbuf, SIZE, 0);
			if(rc <= 0){
				printf("Recv: Client not answering...\n");
				continue;
			}
			send(sock, membuf, SIZE, 0);
			rc = recv(sock, rbuf, SIZE, 0);
			if(rc <= 0){
		        	printf("Recv: Client not answering...\n");
				continue;
			}
		}
	}
}
