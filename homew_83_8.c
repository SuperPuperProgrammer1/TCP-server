#include "superlib.h"
int main(void){
	fork();
	int proc = fork();
	if(proc==0){
        	int pipefd[2];
        	pipe(pipefd);
        	printf("ABOBA\n");
	}

}
