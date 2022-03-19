#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int a = 0;
int main(void){
	a = 100;
	printf("a parent: %d\n", a);
	fork();
	a = 200;
	printf("a child; %d\n", a);
	return 0;
}
