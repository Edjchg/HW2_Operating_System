#include <stdio.h>

int main(){
	int a = 100;
	int index = 0;
	while (index <= a){
		index++;
		printf("%i\n", index);
		sleep(2);
	}
	printf("Terminó\n");


}
