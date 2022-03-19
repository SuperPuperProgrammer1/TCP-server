#include "superlib.h"
int main(void){
	fork();
	close(STDOUT_FILENO);
	printf("O no\n");
}
