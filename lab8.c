#include <stdio.h>


int printWelcome();
int printOptionMsg();
int insertStudent();
int printRecord();
int printAll();
int deleteRecord();
int size=-1;

typedef struct _ {
    int batch;
    int regNo;
    char firstName[20];
    char lastName[20];
    float cGPA;
}student_t;

student_t students[100];


int main(){

    int num;
    printWelcome();
    printOptionMsg();
    
    while(1){
        if ((scanf("%d",&num))==1 && num<5 && num>-1){
            if (num==0){
                printf("\n");
                break;
                
            }else if(num ==1){
                insertStudent();
                printOptionMsg();

            }else if(num==2){
                printRecord();
                printOptionMsg();
                
            }else if(num==3){               
                printAll();
                printOptionMsg();
                
            }else{               
                deleteRecord();
                printOptionMsg();
            }
            
        }else{
            printOptionMsg();
        }
    }
    return 0;
}

int printWelcome(){
    printf("--------------------------------------------\n");
    printf("A VOLATILE STUDENT RECORD MAINTENANCE SYSTEM\n");
    printf("--------------------------------------------\n");
    printf("0. Quit\n");
    printf("1. Insert a Student Record\n");
    printf("2. Print a Student Record\n");
    printf("3. Print all Student Records\n");
    printf("4. Delete a Student Record\n");
    return 0;
}

int printOptionMsg(){
    printf("------------------\n");
    printf("ENTER OPTION [0-4]\n");
    printf("------------------\n");
    return 0;
}

int insertStudent(){

   size=size+1;
   printf("Enter the batch (14/15/16/17): ");
   scanf("%d", &students[size].batch);
   printf("Enter the registration number: ");
   scanf("%d", &students[size].regNo);
   printf("Enter the first name         : ");
   scanf("%s", students[size].firstName);
   printf("Enter the last name          : ");
   scanf("%s", students[size].lastName);
   printf("Enter the cumulative GPA     : ");
   scanf("%f", &students[size].cGPA);
   
   printf("\n");
  
   return 0;
}

int printRecord(){
    int uBatch, uReg;
    int count =-1;
    char  garbage_val;

    printf("Enter the Registration Number: ");
    scanf(" %c%c%d%c%d",&garbage_val,&garbage_val, &uBatch, &garbage_val,&uReg);
            //printf("%d %d\n",uBatch,uReg);

    if(size>=0){
        for (int i=0; i<size+1 ; i++){ 
        
            if (students[i].batch == uBatch && students[i].regNo == uReg){
                count=i;
                break;
               
            }
        }
    }else{
        
    }
    if (count>=0){
        printf("The student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",students[count].firstName, students[count].lastName, uBatch, uReg, students[count].cGPA);
         printf("\n");
        
        return 0;
    }else{
        printf("No student with the given Registration Number!\n");
        printf("\n");
        
        return 0;
    }
     

}

int printAll(){
    for(int i=0; i<size+1; i++){
        printf("The student %s %s (E/%d/%d) has a cumulative GPA of %.2f\n",students[i].firstName, students[i].lastName, students[i].batch, students[i].regNo, students[i].cGPA);
    }
    printf("\n");
    return 0;
    
}

int deleteRecord(){
    
    int uBatch, uReg;
    int count =-1;
    char  garbage_val;
    char new[20];
    
    printf("Enter the Registration Number: ");
    scanf(" %c%c%d%c%d",&garbage_val,&garbage_val, &uBatch, &garbage_val,&uReg);
    //scanf("%s", new);
           // printf("%s\n",new);
        // printf("%d %d\n",uBatch,uReg);
		if(size>=0){
        for (int j=0; j<size+1 ; j++){ 
        
            if (students[j].batch == uBatch && students[j].regNo == uReg){
                count=j;
                break;
               
            }
        }
    }
    if (count>=0){
        for(int i=count; i<size+1; i++){
            students[i] = students[i + 1];
        } 
        size=size-1; 
        printf("Delete Successful!\n"); 
        printf("\n");
        
    }else{
        printf("No student with the given Registration Number!\n");
        printf("\n");
        
    }
    
   return 0; 
    
}