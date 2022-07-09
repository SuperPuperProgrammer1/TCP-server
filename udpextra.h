typedef struct client{
	socklen_t c_len;
	struct sockaddr_in c_addr;
	clientdp *next;
	clientdp *prev;
}clientdp;

typedef struct infodp{
        int sock;
        int port;
        char ip[40];
        struct sockaddr_in addr;
}infodp;

typedef struct recvinfo{
        int flag;
        char recv[1024];
        socklen_t clen;
        struct sockaddr_in caddr;
        int bytes;
}recvinfo;

void recv_init(recvinfo info){
        info.flag = 0;
        memset(info.recv, 0, sizeof(info.recv));
        info.clen = 0;
        info.bytes = 0;
}

void client_init(clientdp client){
	client.c_len=0;
	client->next=NULL;
	client->prev=NULL;
}
