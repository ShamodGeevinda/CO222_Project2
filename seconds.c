#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int timeSeconds(char str[10]);

int main(){

	
	
	
	char s[10] = "1:20:36";
    
	printf("%d\n",timeSeconds(s));
    
	return 0;
}
int timeSeconds(char str[10]){
	
	int i = 0;
    char *p = strtok (str, ":");
    char *array[3];

    while (p != NULL)
    {
        array[i] = p;
		i++;
        p = strtok (NULL, ":");
    }
	return  atoi(array[2])+(atoi(array[1])*60)+(atoi(array[0])*3600);
	
}