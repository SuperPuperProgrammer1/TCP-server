char FCODE[] = "File";
char TCODE[] = "Timer";
char PCODE[] = "Procar";

int sWord(char buf[], int len, int off, char tbuf[]){
	int space = 0;
	int c = 0;
	int flag = 0;
	while(1){
		if(buf[off]==32){
			off++;
			flag = 1;
			continue;
		}
		if(flag != 1){
			tbuf[c] = buf[off];
			c++;
			off++;
			continue;
		}
		break;
	}
	return off;
}	

void cat(char* buf, char** string, int len){
	for(int i = 0; i < len; i++){
		strcat(buf, string[i]);
	}
}

int files(char* buf[]){
	DIR*dd = opendir(".");
	struct dirent* d;
	struct stat s;
	readdir(dd);
	int i = 0;
	int c = 0;
	while(1){
		d = readdir(dd);
		if(d == 0){
			break;
		}
		stat(d->d_name, &s);
		if(S_ISDIR(s.st_mode)){
			continue;
		}
		strcpy(buf[i], d->d_name);
		c++;
	}
	closedir(dd);
	return c;
}

int findfile(char* buf[], char name[], int len){
	for(int i = 0; i < len; i++){
		if(strcmp(buf[i], name)==0){
			return 0;
		}
	}
	return 1;
}

int MEMinfo(char buffer[], int len){
	char tbuf[len];
	struct statvfs buf;
	char word[256];
	int offset = 0;
	char* file = "/";
	FILE* f = fopen("/proc/meminfo", "r");
	FILE* f2 = fopen("/sys/block/sda/size", "r");
	statvfs(file, &buf);
	memset(tbuf, 0, len);
	int size = buf.f_bsize;
	long int x32_space = buf.f_blocks;
	long int x64_space = atoi(fgets(tbuf, len, f2));
	long int x32_free = buf.f_bfree;
	long int x64_free;
	long int usage;
	double proc;

	usage = (x32_space - x32_free)*size/1024/1024;
	x64_free = (x64_space*512/1024/1024 - usage);

	strcat(buffer, "Amount of RAM:\n");
	for(int i = 3; i > 0; i--){
		memset(tbuf, 0, len);
		fgets(tbuf, len, f);
		strcat(buffer, tbuf);
	}
	proc = usage / (x64_space*512/1024/1024);
	char s1[30];
	char s2[30];
	char s3[30];
	char s4[30];
	itoa(x64_space*512/1024/1024, s1);
	itoa(usage, s2);
	itoa(x64_free, s3);
	char* set[] = {"\nDisk size: ", s1, " MB\n", "Used memory: ", s2, " MB\n", "Free memory: ", s3, " MB\n"};
	cat(buffer, set, 9);
}


int CPUinfo(char buf[], int len){
	char tbuf[len];
	char version[256];
	int count = 0;
	int position;
	int proc = 0;
	int flag = 0;

	FILE* f = fopen("/proc/cpuinfo", "r");
	while(1){
		if(count%3 == 0 && flag == 0){
			strcpy(version, tbuf);
			flag = 1;
		}	
		if(count%30==0){
			proc++;
			flag = 0;
		}
		if(fgets(tbuf, len, f)==0){
			break;
		}
		count++;
	}
	memset(tbuf, 0, len);
	char procN[2];
	itoa(proc, procN);

	double load[3];
	getloadavg(load, 3);
	char s1[30];
	char s2[30];
	char s3[30];
	snprintf(s1, 30, "%f", load[0]);
	snprintf(s2, 30, "%f", load[1]);
	snprintf(s3, 30, "%f", load[2]);
	char* set[256] = {"\nNumber of CPU's: ", procN, "\n", "CPU's model: ", version, "\n", "load average: ", s1, " ", s2, " ", s3, " ", "\n\n"};
	cat(buf, set, 14);
}

int SendFile(int sock, char buf[], int len, char name[]){
	char recvbuf[20];
	int size;
	char ack[] = "OK";
	size = strlen(ack);
//	char buffer[256][256];
//	int c1 = files(buffer);
//	if(findfile(buffer, name, c1)==1){
//	       shutdown(sock, SHUT_RDWR);
//	}	       
	FILE *f = fopen(name, "r");
	send(sock, name, strlen(name), 0);
	while(fgets(buf, len, f)!=0){
		send(sock, buf, len, 0);
		memset(buf, 0, len);
	}
	send(sock, ack, size, 0);
	for(int i = 0; i < 99999; i++){
		if(recv(sock, recvbuf, sizeof(recvbuf), 0)>0){
			return 0;
		}
	}
	return 1;		
}

int RecvFile(int sock, int len){
	char buffer[len];
	char ack[] = "OK";
	int size = strlen(ack);
	int rc;
	FILE *fp;
	char p[32];
	memset(buffer, 0, len);
	while(1){
		rc = recv(sock, buffer, len, 0);
		if(rc>0){
			fp = fopen(buffer, "w");
			memset(buffer, 0, len);
			break;
		}
		else{
			continue;
		}
	}
	while(1){
		rc = recv(sock,buffer, len, 0);
		if(rc>0){
			if(strcmp(ack, buffer)==0){
				send(sock, ack, strlen(ack), 0);
				fclose(fp);
				break;
			}
			fputs(buffer, fp);
			memset(buffer, 0, len);
		}
	}
	return 0;
}

char* months[] = {"Января", "Февраля", "Марта", "Апреля", "Мая", "Июня", "Июля", "Августа", "Сентября", "Октября", "Ноября", "Декабря"};
char* week[] = {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};

void SetDate(char buf[], struct tm* t){
	char tbuf[256];
	itoa(t->tm_hour+6, tbuf);
	strcat(buf, tbuf);
	strcat(buf, ":");
	if(t->tm_min == 0){
		for(int i = 0; i<2; i++){
			itoa(t->tm_min, tbuf);
			strcat(buf, tbuf);
		}
	}
	else{
		if(t->tm_min <= 9){
			itoa(0, tbuf);
			strcat(buf, tbuf);
			itoa(t->tm_min, tbuf);
			strcat(buf, tbuf);
		}
		else{
			itoa(t->tm_min, tbuf);
			strcat(buf, tbuf);
		}
	}
	strcat(buf, ", ");
	strcat(buf, week[t->tm_wday]);
	strcat(buf, "  ");
	itoa(t->tm_mday, tbuf);
	strcat(buf, tbuf);
	strcat(buf, "/");
	strcat(buf, months[t->tm_mon]);
	strcat(buf, "/"); 
	itoa(t->tm_year+1900, tbuf);
	strcat(buf, tbuf);
}

int SendTime(int sock, char buf[], int len){
	struct tm* t;
	time_t n = time(NULL);
	t = localtime(&n);
	char tbuf[len];
	int rc;
	SetDate(buf, t);
	send(sock, buf, strlen(buf), 0);
      	rc = recv(sock, tbuf, len, 0);	
        if(rc>0){
		return 0;
	}
	return 1;
}
	
int RecvTime(int sock, char buf[], int len){
	while(1){
		if(recv(sock, buf, len, 0)>0){
			send(sock, "OK", 2, 0);
			return 0;
		}
	}
}


