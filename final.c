// C implementation of functional bar graph

//including header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
// structure to store data
typedef struct _ {
	int all;
	char name[50];
	struct _ * next;
}data_t;

// prototyping functions
int timeSeconds(char str[10]); 
int maxLen(int limit);
long int numLen(int n);
int fileRead(char *);
long int strLen(char *);
void print(int a,int val, int ind, char* str);
void printFinalLine(int maxlen);
void printSpaces(int maxlen);
void printSquares(int squares);
long long int sum();
void graph();
int isNumber(char s[]);
void sort();
void printAll();
static void reverse(data_t** head_ref);
void removeDuplicates(data_t*);
void swap(data_t *a, data_t *b);
float factor();

// global variables
data_t* data ;
int ind = -1;
int mval=0;
int pval =0;
int tval =0;
int lval = 10;
int scale =0;
int filenameIndex = -1;
char filenames[1000][100];
int printarea;
float pfactor;
int maxlen=0;
int maxdig=0;
int ext =0;
data_t *head = NULL;
data_t *current = NULL;


int main(int argc, char **argv){
	
	// argument handeling
	if(argc==1){ // if there isn't any input file
		printf("No input files were given\n");
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
		return 0;
	}
	
	for (int i=1; i<argc; i++){
		if(!strcmp(argv[i],"-m")){
			mval = 1;
		}
		else if(!strcmp(argv[i],"-t")){
			tval = 1;
			
		}
		else if(!strcmp(argv[i],"-p")){
			pval = 1;
			
		}
		else if(!strcmp(argv[i],"--scaled")){
			scale = 1;
			
		}
		else if(!strcmp(argv[i],"-l")){
			if(argc>=(i+1)){
				// checcking conditions for value after -l flag 
				if(strLen(argv[i+1])==numLen(atoi(argv[i+1])) ){
					
					if(argv[i+1][0]=='-' && isNumber(argv[i+1])){
						printf("Invalid option(negative) for [-l]\n");
						printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
						return 0;
						}
					else if(argv[i+1][0]=='-' && !isNumber(argv[i+1])){
						printf("Invalid options for [-l]\n");
						printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);	
						return 0;
						
					}else{
						lval=atoi(argv[i+1]);
						i++;
					}
					
				}else{
					printf("Invalid options for [-l]\n");
					printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);	
					return 0;
				}
				
			}else{
				printf("Not enough options for [-l]\n");
				printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
				return 0;
			}
			
		}
		else if( argv[i][0]=='-' && ( strcmp(argv[i],"-m") && strcmp(argv[i],"-p") && strcmp(argv[i],"-t") && strcmp(argv[i],"-l") && strcmp(argv[i],"--scaled") )){
			printf("Invalid option [%s]\n",argv[i]);
			printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
			return 0;
		}
		else{
			// making array with filenames (everything which won't flag)
			filenameIndex++;
			strcpy(filenames[filenameIndex],argv[i]);
			
		}
	}
	
	
	// going through the filenaame array
	for (int i=0; i<filenameIndex+1; i++){
		

		if (strcmp(&filenames[i][strlen(filenames[i]) - 4], ".csv") == 0){
			// checking extension of files
			// correct file
		}else{
			printf("Only .csv files should be given as inputs.\n");
			return 0;
		}
	}
	
	// condition to check for multiple options
	if(mval+tval+pval>1){
		printf("Cannot plot multiple parameters in same graph.\n");
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
		return 0;
	}
	
	// loop to read files
	for (int i=0; i<filenameIndex+1; i++){
		fileRead(filenames[i]);
		if(ext==1){
			return 0;
		}
		
	}
	
	if(filenameIndex==-1){
		printf("No input files were given\n");
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
		return 0;
	}
	
	// to check files were empty
	if(ind==-1 && filenameIndex>-1){
		printf("No data to process\n");
		return 0;
	}
	
	// condition to handle -l value exceeding the entry values
	if(lval>ind+1){
		lval=ind+1;;
		
	}
	
	// printing newline before graph
	if(lval>0){
		printf("\n");
	}
	
	reverse(&head);	
	sort();
	graph();
	
    return 0;
}

// function to convert time in HH:MM:SS to minutes
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
	return  /*atoi(array[2])+*/(atoi(array[1])*60)+(atoi(array[0])*3600);
	// see that the sample program won't care about summation of seconds
}

// function to calculate maximum length of the name
int maxLen(int limit){
	int val = 0;
	for(int i=0; i<limit;i++){
		if(strlen(data[i].name)>val){
			val = strlen(data[i].name);
		}
		
	}
	return val;
}

// function to calculate how many digits in the number
long int numLen(int n) {
  int count = 0;
 
  do {
    n /= 10;
    ++count;
  } while (n != 0);

  return count;
}

// function to read files
int fileRead(char *str){
	FILE* fp = fopen(str, "r");
  
    if (!fp){
		// if program connot open give file
        printf("Cannot open one or more given files\n");
		ext = 1;
		return 0;
	}
    else {

        // array 1024 ( can modify )
        char str[1024];
  
        int row = 0;
        int column = 0;
  
        while (fgets(str,1024, fp)) {
            column = 0;
            row++;
  
            // Splitting the data
            char* value = strtok(str, ",");
			ind++;
			
			data_t *add = (data_t*)malloc(sizeof(data_t));
			
            while (value) {
				
                // Column 1
                if (column == 0) {
					strcpy(add->name,value); 
                }
  
                // Column 2
                if (column == 1 && pval==1) {
				   add->all = atoi(value);
                }
  
                // Column 3
                if (column == 2 && tval==1) {
					add->all= timeSeconds(value)/60;
					//strcpy(add->time,value);
                }

                value = strtok(NULL, ","); // updating value
                column++;
            }
			//add->seconds = timeSeconds(add->time);
			if(pval==0 && tval==0){
				add->all =1;
			}
			add->next = head;
			head= add;
			removeDuplicates(add);
        }
        // Close the file
        fclose(fp);
    }
	return 0;	
}

// special function to calculate length of string 
long int strLen(char * str){
	if (str[0] == '-'){
		return strlen(str)-1;
	}else{
		return strlen(str);
	}	
}

// function to print a single bar
void print(int a,int val,int ind, char* str){
	float squares ;
	int s= sum();
	
	if(scale==1){ // scaled mode
		if(ind==0){
			squares = printarea; // initial bar lengths
		}
		else{ 
			squares = (float)val/factor(); // other bar lengths
		}
	}else{// non scaled mode
		 
		squares = (float)printarea * (float)val / (float)s;
	}
	
	//line1
	printSpaces(maxlen);
	printf("\u2502");
	printSquares(squares);
	printf("\n");
	
	//line 2
	printf(" %s",str);
	for (int i=0; i<maxlen+1-a; i++){
		printf(" ");
	}
	printf("\u2502");
	printSquares(squares);
	printf("%d", val);
	//printf(" %d", pfacor);
	printf("\n");
	
	//line 3
	printSpaces(maxlen);
	printf("\u2502");
	printSquares(squares);
	printf("\n");
	
	//line4 
	printSpaces(maxlen);
	printf("\u2502");
	printf("\n");
		
}

// function to print the final line of the graph
void printFinalLine(int maxlen){
	printSpaces(maxlen);
	printf("\u2514");
	for (int i=0; i<80-maxlen-1-2; i++){
		printf("\u2500");	
	}
	printf("\n");
}

// function to print initial spaces in the graph
void printSpaces(int maxlen){
	for (int i=0; i<maxlen+2; i++){
		printf(" ");	
	}
}

// function to print square patterns in the graph
void printSquares(int squares){
	for (int i=0; i<squares; i++){
		printf("\u2591");
		
	}
	
}

// getting sum of all elements in specific kind
long long int sum(){
	long long int sum=0;
	data_t* current=head;
	while(current!=NULL){
		sum+=current->all;
		current=current->next;
	}
	return sum;
}

// to handle preprocesses before printing meeting count
void graph(){
	// calculating maxlen maxdig values
	{
	data_t* current = head;
	for (int i=0; i<lval; i++){
		if(strlen(current->name)>maxlen){
			maxlen = strlen(current->name);
		}
		if(numLen(current->all)>maxdig){
			maxdig = numLen(current->all);
		}
		current=current->next;
	}
}
	
	// calculating printarea value
	printarea = 80-maxlen - 3 -maxdig; 
	data_t* current = head;
	
	for (int i=0; i<lval; i++){
		int len = strlen(current->name);
		print(len,current->all,i,current->name);
		current= current->next;
	}
	
	if (lval>0){
		printFinalLine(maxlen);
	}	
}

// funcction to check that geven string is Number or not
int isNumber(char s[]){
    for (int i = 1; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
              return 0;
    }
    return 1;
}

// function to sort 
void sort() {

   int i, j, k;
   data_t *current;
   data_t *next;
   char tempname[50];
   int meet;
   int size = ind+1 ;
   k=size;
	
   for ( i = 0 ; i < size-1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if (current->all < next->all ) {
			// only take care about participants number and names
			meet = current->all;
			current->all = next->all;
			next->all = meet;
			
			strcpy(tempname , current->name);
			strcpy(current->name , next->name);
			strcpy(next->name , tempname);	
		 }	
         current = current->next;
         next = next->next;
      }
   }   
}

// function to remove same name entries
void removeDuplicates(data_t* element){
    // Pointer to traverse the linked list 
    data_t* now = head;
 
    // Pointer to store the next pointer of a node to be deleted
    data_t* next_next;
   
    // do nothing if the list is empty 
    if (now == NULL)
       return ;

    // Traverse the list till last node 
    while (now->next != NULL)
    {
       // Compare current node with next node 
       if (!strcmp((element->name) , (now->next->name)))
       {
		   element->all =now->next->all + element->all;             
           next_next = now->next->next;
           free(now->next);
           now->next = next_next; 
		   ind--;
       }
       else //if no deletion 
       {
          now = now->next;
       }
    }
}

// Function to reverse the linked list 
static void reverse(data_t** head_ref){
    data_t* prev = NULL;
    data_t* current = *head_ref;
    data_t* next = NULL;
    while (current != NULL) {
        // Store next
        next = current->next;
        // Reverse current node's pointer
        current->next = prev;
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

// function to calculating printing factor
float factor(){
	pfactor = (float)(head->all)/(float)printarea;
	return pfactor;
}
