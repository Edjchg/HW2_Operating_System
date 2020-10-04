#include <stdio.h>

int main(){
	int a = 5;
	int index = 0;
	while (index <= a){
		index++;
		printf("%i\n", index);
		sleep(2);
	}
	printf("Terminó\n");


}
