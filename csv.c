
#include <stdio.h>
#include <string.h>
  
// Driver Code
struct _{
	char name[30];
	char participants[4];
	char time[8];
	int intParticipants;
	int minutes;
	int meetings;
}data;
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
        char buffer[1024];
  
        int row = 0;
        int column = 0;
  
        while (fgets(buffer,1024, fp)) {
            column = 0;
            row++;
  
            // To avoid printing of column
            // names in file can be changed
            // according to need
            
  
            // Splitting the data
            char* value = strtok(buffer, ", ");
  
            while (value) {
                // Column 1
                if (column == 0) {
                    printf("Name :");
                }
  
                // Column 2
                if (column == 1) {
                    printf("\tAccount No. :");
                }
  
                // Column 3
                if (column == 2) {
                    printf("\tAmount :");
                }
  
                printf("%s", value);
                value = strtok(NULL, ", ");
                column++;
            }
  
            printf("\n");
        }
  
        // Close the file
        fclose(fp);
    }
    return 0;
}
//cd /mnt/d/"my files"/Current/"CO 222 Programming Methodology"/"Project 2"
