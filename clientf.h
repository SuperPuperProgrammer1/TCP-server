infodp CLIENT_OPEN(infodp info){
        struct sockaddr_in servaddr;
        int sock;
        sock = socket(PF_INET, SOCK_DGRAM, 0);
        infodp clientinfo;
        memset(&servaddr, 0, sizeof(servaddr));

        char ipaddr[40];
        strcpy(ipaddr, info.ip);
        int port = info.port;

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = inet_addr(ipaddr);

        connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));

        clientinfo.sock = sock;
        clientinfo.port = port;
        clientinfo.addr = servaddr;

        return clientinfo;
}

int CLIENT_WRITE(char message[256], infodp cinfo){
	recvinfo crecv;
	recv_init(crecv);
	crecv.clen = sizeof(crecv.caddr);
	int sbytes = strlen(message);
	int recv;
	int flag = 0;
	while(1){
		sendto(cinfo.sock ,message, sbytes, 0, (struct sockaddr*)&cinfo.addr, sizeof(cinfo.addr));
		recv = recvfrom(cinfo.sock, crecv.recv, sizeof(crecv.recv), 0, (struct sockaddr*)&crecv.caddr, &crecv.clen);
	      	if(recv==-1){
			flag = 1;
			break;
		}
		if(recv>0){  flag = 0; break; }
		else{ continue; }
	}
	if(flag==0){
		printf("Сервер: %s\n", crecv.recv);
		return 0;
	}
}


