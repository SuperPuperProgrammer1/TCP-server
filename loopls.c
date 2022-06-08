#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int Dirc(char *name){
	DIR *fd = opendir(name);
	int count = 1;
	while(1){
	        
		if(readdir(fd)==0){ break; }
		count++;
	}
        closedir(fd);
	return count;

void IfDir(char *name, char *ptrc[], int *ptri){
	DIR *fd = opendir(name);
	struct dirent *d;
	struct stat s;
	for(;;){
		d = readdir(fd);
		if(d == 0){ break; }
		stat(d->d_name, &s);
		if(s.st_size == 4096){
			ptrc[&ptri] = d->d_name;
			&ptri++;
			printf("DIR: %s ------- DIR: %s", &name, d->d_name);
		}
		printf("DIR: %s ------- File: %s\n", &name, d->d_name); 
	}
}	


struct stat lsStart(char *name){
	struct stat st;
	stat(name, &st);
	return st;
}
	

int main(int argc, char *argv[]){
	DIR *fd = opendir(".");
	struct dirent *f;
	struct stat s;
	int flag = 0;
	int *ptrf=flag;
	char *ptrflag[1000];
	while(1){
		if(&ptrf != 0){
			IfDir(ptrflag[&ptrf], ptrflag, ptri);
			&ptrf--;
		}
		f = readdir(fd);
		if(f==0){ break; }
		if(s.st_size == 4096){	
			IfDir(f->d_name, ptrflag, ptrf);
			printf("DIR: %s ------- DIR: %s","HOMEDIR", f->d_name);
		}
		printf("DIR: %s ------- File: %s\n", "HOMEDIR", f->d_name);
	}
}
		
