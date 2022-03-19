#include "superlib.h"
int main(void){
	
	int v = fork();
        if(v==0){
		printf("I am child: (pid) %d\n", getpid());
//		int proc_w = waitpid(0, 0, WNOHANG);
	}
	else{
		int proc_w = wait(NULL);
		printf("I am parent: (pid) %d\n", getpid());
	}
}
