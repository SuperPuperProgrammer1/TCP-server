#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(void){
	fork();
	char *box[2];
	box[0]="ls";
	box[1]=NULL;
	execvp(box[0], box);
}
