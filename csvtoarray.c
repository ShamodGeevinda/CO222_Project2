
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int printAll();
int timeSeconds(char str[10]); 
void deleteEntry(int pos);
void search(char str[30], int index);

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

int main()
{
    // Substitute the full file path
    // for the string file_path
    FILE* fp = fopen("meetingData.csv", "r");
  
    if (!fp)
        printf("Can't open file\n");
  
    else {
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
					strcpy(data[ind].name,value); // stpcpy was

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
	for(int i=0;i<ind+1;i++){
		search(data[i].name, i);
	}
	printAll();
	printf("%d\n",ind);
    return 0;
}

int printAll(){
    for(int i=0; i<ind; i++){
        printf("name->%s participants->%d seconds->%d meetings->%d\n",data[i].name,data[i].participants, data[i].seconds, data[i].meetings);
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
	return  atoi(array[2])+(atoi(array[1])*60)+(atoi(array[0])*3600);
	
}
void search(char str[30], int index){
	for (int i =index+1; i< ind+1;i++){
		if(!strcmp(str, data[i].name)){
			data[index].meetings++;
			data[index].participants+=data[i].participants;
			data[index].seconds += data[i].seconds;
			deleteEntry(i);
			ind--;
			
		}
	}	
	
}
void deleteEntry(int pos){
	for(int i=pos; i<ind; i++){
            data[i] = data[i + 1];
        } 
	
}