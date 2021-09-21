
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
int printAll();
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

typedef struct _ {
	char name[30];
	//char participants[8];
	char time[10];
	int participants;
	int seconds;
	int minutes;
	int meetings;
}data_t;

data_t data[100];
int ind = -1;
int arrayCount=0;
int mval=0;
int pval =0;
int tval =0;
int lval = 10;
int scale =0;
int filenameIndex = -1;
char filenames[100][100];


//char csvarray[2][50];

int main(int argc, char **argv)
{
	if(argc==1){
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
			if(argc>=(i+1)){// argc>i
			//printf("%ld %ld\n",strLen(argv[i+1]),numLen(atoi(argv[i+1])));
				if(strLen(argv[i+1])==numLen(atoi(argv[i+1]))){
					
					if(argv[i+1][0]=='-'){
						printf("Invalid option(negative) for [-l]\n");
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
			filenameIndex++;
			strcpy(filenames[filenameIndex],argv[i]);
			//printf("%s\n",argv[i]);
		}
	}
	for (int i=0; i<filenameIndex+1; i++){
		//printf("%s\n", filenames[i]);
	}
	
	for (int i=0; i<filenameIndex+1; i++){
		//printf("%s\n",filenames[i]);
		
		if (strcmp(&filenames[i][strlen(filenames[i]) - 4], ".csv") == 0){
			stringLwr(filenames[i]);
			//printf("%s\n",filenames[i]);
			
		}else{
			printf("Only .csv files should be given as inputs.\n");
			return 0;
		}
	}
	
	char *csvarray[50] ; 
    csvarray[0] = "meetingData.csv";
	//int arrayLen = sizeof(csvarray)/sizeof(csvarray[0]);
	for (int i=0; i<arrayCount; i++){
		fileRead(csvarray[i]);
		
	}
	
	printf("%d\n",arrayCount);
	//fileRead(csvarray[0]);
	secToMin();
	
	// search and delete multiple inputs
	
	for(int i=0;i<ind+1;i++){
		search(data[i].name, i);
	}
	
	
	sortTime();
	
	
	//sortTime();
	//sortParticipants();
	//sortMeetings();
	printAll();
	printf("%d\n",ind);
	//printf("%d\n", maxLen(5));
	//printf("%d\n", numLen(12364));
    return 0;
}

int printAll(){
    for(int i=0; i<ind+1; i++){
        printf("name->%s participants->%d minutes->%d meetings->%d\n",data[i].name,data[i].participants, data[i].minutes, data[i].meetings);
    }
    printf("\n");
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
	return  /*atoi(array[2])+*/(atoi(array[1])*60)+(atoi(array[0])*3600);
	
}



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


void deleteEntry(int pos){
	for(int i=pos; i<ind; i++){
            data[i] = data[i + 1];
        } 
	ind=ind-1;
	
}

void secToMin(){
	for (int i=0;i<ind+1;i++){
		data[i].minutes = data[i].seconds/60;
	}
}

void sortTime(){
    
    data_t tempVal; // variable to gandle function
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

void sortMeetings(){
    
    data_t tempVal; // variable to gandle function
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

void sortParticipants(){
    
    data_t tempVal; // variable to gandle function
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

int maxLen(int limit){
	int val = 0;
	for(int i=0; i<limit;i++){
		if(strlen(data[i].name)>val){
			val = strlen(data[i].name);
		}
		
	}
	return val;
}

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

void fileRead(char *str){
	FILE* fp = fopen(str, "r");
  
    if (!fp)
        printf("Can't open file\n");
  
    else {
		arrayCount++;
        // Here we have taken size of
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
  
        }
  
        // Close the file
        fclose(fp);
    }
	
}
long int strLen(char * str){
	if (str[0] == '-'){
		return strlen(str)-1;
	}else{
		return strlen(str);
	}
	
}

void stringLwr(char *s)
{
    int i=0;
    while(s[i]!='\0')
    {
        if(s[i]>='A' && s[i]<='Z'){
            s[i]=s[i]+32;
        }
        ++i;
    }
}