#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <assert.h>

#include "udplib.h"

int main(int argc, char* argv[]){
	assert(argc==2);
	infodp clientdp;
	strcpy(clientdp.ip, "127.0.0.1");
	clientdp.port = 8080;
	clientdp = CLIENT_OPEN(clientdp);
	
	if(CLIENT_WRITE(argv[1], clientdp)==0){ printf("Сообщение отправлено и получен ответ!\n"); }
	else{ printf("Сообщение отправлено, но не получен ответ от сервера!\n"); }

}

