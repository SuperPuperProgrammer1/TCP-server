infodp SERV_OPEN(int port){
        int sock;
        sock = socket(PF_INET, SOCK_DGRAM, 0);
        infodp servinfo;
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

        servinfo.sock=sock;
        servinfo.port=port;

	bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

        return servinfo;
}

recvinfo SERV_ISRECV(recvinfo servrecv, int sock){
        recv_init(servrecv);
	char answer[] = "I recieved your message!";
	infodp servinf;
        servrecv.clen = sizeof(servrecv.caddr);
        servrecv.bytes=recvfrom(sock, servrecv.recv, sizeof(servrecv.recv), 0, (struct sockaddr*)&servrecv.caddr, &servrecv.clen);
        if(servrecv.bytes>0){
                servrecv.flag = 1;
		sendto(sock, answer, sizeof(answer), 0, (struct sockaddr *)&servrecv.caddr, sizeof(servrecv.caddr)); 
                return servrecv;
        }
}
