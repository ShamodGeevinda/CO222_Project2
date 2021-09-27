// C implementation of functional bar graph

//includong headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 

// prototyping functions
int timeSeconds(char str[10]); 
void deleteEntry(int pos);
void search(char str[30], int index);
void secToMin();
void sortTime();
void sortMeetings();
void sortParticipants();
int maxLen(int limit);
long int numLen(int n);
void fileRead(char *);
long int strLen(char *);
void stringLwr(char *);
void print(int lim, int val, int ind);
void printFinalLine(int maxlen);
void printSpaces(int maxlen);
void printSquares(int squares);
int sum();
void meetings();
void time();;
void participants();
int isNumber(char s[]);

// structure to store data
typedef struct _ {
	int participants;
	int seconds;
	int minutes;
	int meetings;
	char name[30];
	char time[10];
	
}data_t;


// global variables
data_t* data ;
int ind = -1;
int mval=0;
int pval =0;
int tval =0;
int lval = 10;
int scale =0;
int filenameIndex = -1;
char filenames[100][100];
int printarea;
float pfactor;
int maxlen=0;
int maxdig=0;


//char csvarray[2][50];

int main(int argc, char **argv){
	// argument handeling
	if(argc==1){ // if there isn't any input file
		printf("No input files were given\n");
		printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
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
						printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
						return 0;
						}
					else if(argv[i+1][0]=='-' && !isNumber(argv[i+1])){
						printf("Invalid options for [-l]\n");
						printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");	
						return 0;
						
					}else{
						lval=atoi(argv[i+1]);
						i++;
					}
					
				}else{
					printf("Invalid options for [-l]\n");
					printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");	
					return 0;
				}
				
			}else{
				printf("Not enough options for [-l]\n");
				printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
				return 0;
			}
			
		}
		else if( argv[i][0]=='-' && ( strcmp(argv[i],"-m") && strcmp(argv[i],"-p") && strcmp(argv[i],"-t") && strcmp(argv[i],"-l") && strcmp(argv[i],"--scaled") )){
			printf("Invalid option [%s]\n",argv[i]);
			printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
			return 0;
		}
		else{
			// making array with filenames
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
		printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
		return 0;
	}
	
	// loop to read files
	for (int i=0; i<filenameIndex+1; i++){
		fileRead(filenames[i]);
		
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
	
	// sorting array acccording to given flags
	if(tval==1){
		sortTime();
		time();
	}else if(pval==1){
		sortParticipants();
		participants();
	}else{
		sortMeetings();
		meetings();
	}
	
	
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
	
}

// function to see occurence of the elemnt
void search(char str[30], int index){
	for (int i =(index+1); i< ind+1;i++){ // search for whole array excluding index val
		
		if(!(strncmp( data[i].name, str,29))){
			data[index].meetings++;
			data[index].participants+=data[i].participants;
			data[index].seconds += data[i].seconds;
			data[index].minutes += data[i].minutes;
			deleteEntry(i);
			i--;
			//printAll();
			
		}
	}	
	
}

// function to delete entry
void deleteEntry(int pos){
	for(int i=pos; i<ind; i++){
            data[i] = data[i + 1];
        } 
	ind=ind-1;
	
}

// function to convert secondss to minutes
void secToMin(){
		data[ind].minutes = data[ind].seconds/60;
}

// funcction to sort array according to time
void sortTime(){
    
    data_t tempVal; // variable to handle function
    for(int index1=0; index1<ind+1; index1++){
        for(int index2=index1+1; index2<ind+1; index2++){
            if(data[index1].minutes<data[index2].minutes){
                tempVal = data[index1];
                data[index1]= data[index2];
                data[index2]= tempVal;
                
            }
            
        }
        
    }
	
}

// function to sort array according to meeting count
void sortMeetings(){
    
    data_t tempVal; // variable to handle function
    for(int index1=0; index1<ind+1; index1++){
        for(int index2=index1+1; index2<ind+1; index2++){
            if(data[index1].meetings<data[index2].meetings){
                tempVal = data[index1];
                data[index1]= data[index2];
                data[index2]= tempVal;
                
            }
            
        }
        
    }
	
}

// function to sort array accordding to participants count
void sortParticipants(){
    
    data_t tempVal; // variable to handle function
    for(int index1=0; index1<ind+1; index1++){
        for(int index2=index1+1; index2<ind+1; index2++){
            if(data[index1].participants<data[index2].participants){
                tempVal = data[index1];
                data[index1]= data[index2];
                data[index2]= tempVal;
                
            }
            
        }
        
    }
	
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
 
  // iterate at least once, then until n becomes 0
  // remove last digit from n in each iteration
  // increase count by 1 in each iteration
  do {
    n /= 10;
    ++count;
  } while (n != 0);

  return count;
}

// function to read files
void fileRead(char *str){
	FILE* fp = fopen(str, "r");
  
    if (!fp){
		// if program connot open give file
        printf("Cannot open one or more given files\n");
		exit (0);
	}
    else {

        // array 1024 you can modify it
        char str[1024];
  
        int row = 0;
        int column = 0;
  
        while (fgets(str,1024, fp)) {
            column = 0;
            row++;
  
            // Splitting the data
            char* value = strtok(str, ",");
			ind++;
			if(ind>0){
				// memory reallocations
				data = realloc(data, (ind+1)*sizeof(data_t));
				
			}else{
				// initial dynamic memory allocation
				data = (data_t*)malloc(sizeof(data_t)); 
			}
            while (value) {
                // Column 1
				
                if (column == 0) {
					strncpy(data[ind].name,value,29); // stpcpy was

                }
  
                // Column 2
                if (column == 1) {
				   //strcpy(data[ind].participants,value);
				   data[ind].participants = atoi(value);
                }
  
                // Column 3
                if (column == 2) {
					strcpy(data[ind].time,value);
                }
				
                value = strtok(NULL, ","); // updating value
                column++;
            }
			data[ind].seconds = timeSeconds(data[ind].time);
			data[ind].meetings =1;
			
			secToMin();
			for(int i=0;i<ind+1;i++){
				search(data[i].name, i);
				
			}
  
        }
  
        // Close the file
        fclose(fp);
    }
	
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
void print(int lim, int val,int ind){
	float squares ;
	int s= sum();
	
	if(scale==1){ // scaled mode
		if(ind==0){
			squares = printarea; // initial bar
		}
		else{ 
			squares = (float)val/pfactor; // other bars
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
	printf(" %s",data[ind].name);
	for (int i=0; i<maxlen+1-strlen(data[ind].name); i++){
		printf(" ");
	}printf("\u2502");
	
	printSquares(squares);
	printf("%d", val);
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
int sum(){
	int sum=0;
	for (int i=0; i<ind+1; i++){
		if(pval==1){
			sum+=data[i].participants;
		}
		else if(tval==1){
			sum+=data[i].minutes;
		}
		else{
			sum+=data[i].meetings;
		}
	}
	return sum;
}

// to handle preprocesses before printing meeting count
void meetings(){
	// calculating maxlen maxdig values
	for (int i=0; i<lval; i++){
		if(strlen(data[i].name)>maxlen){
			maxlen = strlen(data[i].name);
		}
		if(numLen(data[i].meetings)>maxdig){
			maxdig = numLen(data[i].meetings);
		}
		
		
	}
	// calculating useful value
	printarea = 80-maxlen - 3 -maxdig; 
	pfactor = (float)data[0].meetings/(float)printarea;
	
	for (int i=0; i<lval; i++){
		print(lval,data[i].meetings,i);
	}
	if (lval>0){
		printFinalLine(maxlen);
	}
	
}

// to handle preprocesses before printing participants count
void participants(){
	// calculating maxlen maxdig values
	for (int i=0; i<lval; i++){
		if(strlen(data[i].name)>maxlen){
			maxlen = strlen(data[i].name);
		}
		if(numLen(data[i].participants)>maxdig){
			maxdig = numLen(data[i].participants);
		}
		
		
	}
	// calculating useful value 
	printarea = 80-maxlen - 3 -maxdig; 
	pfactor = (float)data[0].participants/(float)printarea;
	
	for (int i=0; i<lval; i++){
		print(lval,data[i].participants,i);
	}
	if (lval>0){
		printFinalLine(maxlen);
	}
}

// to handle preprocesses before printing meeting time
void time(){
	// calculating maxlen maxdig values
	for (int i=0; i<lval; i++){
		if(strlen(data[i].name)>maxlen){
			maxlen = strlen(data[i].name);
		}
		if(numLen(data[i].minutes)>maxdig){
			maxdig = numLen(data[i].minutes);
		}
		
		
	}
	// calculating useful value
	printarea = 80-maxlen - 3 -maxdig; 
	pfactor = (float)data[0].minutes/(float)printarea;
	
	for (int i=0; i<lval; i++){
		print(lval,data[i].minutes,i);
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