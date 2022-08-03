infodp CLIENT_OPEN(int port, char ipaddr[40]){
        struct sockaddr_in servaddr;
        int sock;
	infodp result;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        printf("Socket created... 25%%\n");
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = inet_addr(ipaddr);
        printf("Final settings set... 70%%\n");
        printf("Client started working... 100%%\n");
	result.addr = servaddr;
	result.sock = sock;
        return result;
}

int CLIENT_CONNECT(int sock, struct sockaddr_in i){
	int rc = connect(sock, (struct sockaddr*)&i, sizeof(i));
	if(rc == 0){
		return 0;
	}
	else{
		return 1;
	}
}

int sendl(int sock, char buf[], int len, int flag);

int SendHeartBeat(int sock){
        int missedAnswers = 0;
        char buffer[999];
        uint64_t time1, time2;
        for(int i = 3; missedAnswers < 3; missedAnswers++){
                time1=timer_start();
                send(sock, "Pulse", sizeof("Pulse"), MSG_NOSIGNAL);
                while(timer_look(timer_stop(time1), 11)<1.0){
                        if(recv(sock, buffer, sizeof(buffer), 0)>0){
                                printf("Server: %s\n", buffer);
                                return 0;
                        }

                }
        }
        return 1;
}

int CLIENT_WRITE(int sock, char message[256]){
        recvinfo crecv;
        recv_init(crecv);
	printf("1\n");
        crecv.clen = sizeof(crecv.caddr);
        int sbytes = strlen(message);
        char buf[1440];
        int recvf;
        int flag = 0;
        uint64_t time1 = timer_start();
        while(timer_look(timer_stop(time1), 11)<5.0){
               
                send(sock, message, sbytes, 0);
                recvf = recv(sock, buf, sizeof(buf), 0);
                
                if(recvf==-1){
                        break;
                }
                if(recvf>0){  flag = 1; break; }
               
        }
        if(flag==1){
                
                
                printf("Сервер: %s\n", buf);
                return 0;
        }
        else{
                return 1;
        }
}

int sendl(int sock, char buf[], int len, int flag){
	int words = 0;
	int c = 0;
	char *count;
	while(buf[c]!='\0'){
		if(buf[c]==32){
			words++;
		}
		//printf("2\n");
		words++;
		c++;
	}
	*count = words;
	printf("2\n");
	int rc = send(sock, count, sizeof(count), flag);
	printf("2\n");
	if(rc<0){ return 1; }
	if(send(sock, buf, len, flag)<0){ return 1; }
	printf("2\n");
	return 0;
}
