#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print(int lim, int val, int ind);

typedef struct _ {
	int val;
	char name[8];
} data;

data array[5];

int maxlen = 4;
int maxdig = 2;
int printarea;
float pfactor;

int main(){
	for (int i=0; i<5; i++){
		array[i].val = (6- i)*3;
		
		
	}
	strcpy(array[0].name , "sff");
	strcpy(array[1].name , "abd");
	strcpy(array[3].name , "aasf");
	strcpy(array[2].name , "gssd");
	strcpy(array[4].name , "adfh");
	int limit = 5;
	 
	printarea = 80-maxlen - 1 -maxdig;
	pfactor = (float)array[0].val/(float)printarea;
	printf("%d\n",printarea);
	printf("%d\n", array[0].val);;
	printf("%f\n",pfactor);
	for (int i=0; i<5; i++){{}
		print(limit,array[i].val,i);
	}
	
	return 0;
}

void print(int lim, int val,int ind){
	int squares = val/pfactor;
	//line1
	for (int i=0; i<maxlen+1; i++){
		printf(" ");
		
	}
	printf("\u2502");
	for (int i=0; i<squares; i++){
		printf("\u2591");
		
	}
	printf("\n");
	
	//line 2
	printf("%s",array[ind].name);
	for (int i=0; i<maxlen+1-strlen(array[ind].name); i++){
		printf(" ");
	}printf("\u2502");
	
	for (int i=0; i<squares; i++){
		printf("\u2591");
		
	}printf("%d", val);
	printf("\n");
	
	//line 3
	for (int i=0; i<maxlen+1; i++){
		printf(" ");
		
	}
	printf("\u2502");
	for (int i=0; i<squares; i++){
		printf("\u2591");
		
	}
	printf("\n");
	
	//line4 
	for (int i=0; i<maxlen+1; i++){
		printf(" ");
		
	}
	printf("\u2502");
	printf("\n");
	
	
	
	
}