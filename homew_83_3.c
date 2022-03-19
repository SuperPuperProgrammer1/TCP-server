#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
int main(){
	int parent = getpid();
	int flag = 0;
        if(flag==1){
	    printf("goodbye: %d\n", getpid());
	}
	printf("pid: %d\n", getpid());
	fork();
	int if_child = getpid();
	if(if_child!=parent){
            printf("pidchild: %d\n", getpid()); 
	    printf("hello: %d\n", getpid());
	    printf("Now will be killed proc: %d\n", getpid());
	    flag = 1;
	    kill((int)getpid(),SIGHUP);
	    printf("killed: %d\n", if_child);
	}	
}
