#include <stdio.h>
#include <stdlib.h>

int main(int argc, int* argv){
	int counter = 100;
	char* temp = (char *)malloc(sizeof(char)*argv[1]);
	
	for (int i = 0; i < counter; i++){
		for (int j = 0; j < argv[1]; i++){
			temp[j];
		}
	}
	free(temp);
	return 0;		
}
