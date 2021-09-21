#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){ 

	char szFileName[2][255] = {"stories.csv","asfafas.csv"};
	if (strcmp(&szFileName[1][strlen(szFileName[1]) - 4], ".csv") == 0)
    printf("same file extension\n");
	else
    printf("different file extension\n");

	return 0;
}