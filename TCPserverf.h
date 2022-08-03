int TSERV_OPEN(int port){
        struct sockaddr_in local;
        int sock = socket(AF_INET, SOCK_STREAM, 0);
       
        printf("Socket created:::25%%\n");
        local.sin_family = AF_INET;
        local.sin_port  = htons(port);
        local.sin_addr.s_addr = htonl(INADDR_ANY);
        printf("Final settings set:::70%%\n");
	int a = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(int));

        bind(sock, (struct sockaddr*)&local, sizeof(local));
	listen(sock, 5);
        printf("Server started working:::100%%\n");
        return sock;

}

int CatchHeartBeat(int sock){
        char buf[1440];
        int missedheartbeats = 0;
        uint64_t time1, time2;
        time1 = timer_start();
        while(1){
                int rc = recv(sock, buf, sizeof(buf), 0);
                time2 = timer_stop(time1);
                if(timer_look(time2, 11)>1.0){
                        missedheartbeats++;
                        time1 = timer_start();
                }
                if(rc>0){
                        send(sock, "Catched heartbeat\n", sizeof("Catched heartbeat\n"), 0);
                        return 0;
                }
                if(++missedheartbeats>3){
                        return 1;
                }
        }
}

int TSERV_ISCONNECTED(int csock){
	int sock;
	
        while(1){ 
	     	sock = accept(csock, 0, 0);	
                printf("Host has connected... ('127.0.0.1')\n");
                return sock;
           
        }
}

int TSERV_RECV(int sock, char buf[]){
        int cr;
	char answer[] = "Message recieved\n";
        while(1){
		memset(buf, 1, sizeof(buf));
                cr = recv(sock, buf, sizeof(buf)/sizeof(*buf), MSG_NOSIGNAL);	
		if(cr==0){
			return 1;	
                }
		if(cr>0){
			send(sock, answer, sizeof(answer)/sizeof(*answer), 0);
			break;
		}
        }
	return 0;
}
