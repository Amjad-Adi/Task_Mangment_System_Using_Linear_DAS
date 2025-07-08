/*
Name: Amjad Qaher Sadek Adi
Student ID:1230800
Section number:3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FAULT_HANDLER 33
#define MAX_TASK_NAME_SIZE 201
#define MAX_TASK_DATE_SIZE 11
#define MAX_TASK_DESCRIPTION_LINE 231
#define MAX_TASK_ID_SIZE 11
#define MAX_TASK_DURATION_SIZE 11
struct TaskNode{
int taskId;
char taskName[MAX_TASK_NAME_SIZE];
char taskDate[MAX_TASK_DATE_SIZE];
double taskDuration;
int undoneStatus;
struct TaskNode* nextTask;
};
typedef struct TaskNode TaskNode;
typedef struct TaskNode* ptrToTaskNode;
typedef ptrToTaskNode LinkedList;
typedef ptrToTaskNode Stack;
LinkedList makeSingularEmpty(LinkedList );
void getFileInformation(LinkedList ,ptrToTaskNode);
int isEmptySingularList(LinkedList);
void disposeSingularListContents(LinkedList );
void deleteSingularList(LinkedList );
void insertInSingularAfter(int,char[],char[] ,double ,LinkedList,ptrToTaskNode );
void insertingPointerChanges(LinkedList ,ptrToTaskNode ,ptrToTaskNode );
ptrToTaskNode searchSingularById(int ,LinkedList );
ptrToTaskNode searchSingularByNameAndPrint(char [],LinkedList );
ptrToTaskNode searchSingularForPreviousById(int ,LinkedList );
ptrToTaskNode cutNextAndGet(ptrToTaskNode , LinkedList ,ptrToTaskNode);
void deleteNextInSingular(ptrToTaskNode,LinkedList ,ptrToTaskNode);
void viewUnperformedTasks(LinkedList );
void viewPerformedTasks(Stack );
void generateReport();
void writeUnperformedTasks(FILE* ,LinkedList );
void writePerformedTasks(FILE* ,Stack );
void writeUndoneTasks(FILE* ,LinkedList );
Stack createStack(Stack );
ptrToTaskNode pop(Stack );
void disposeStack(Stack );
void makeEmptyStack(Stack );
int isEmptyStack(Stack );
void push(ptrToTaskNode , Stack);
int main(){
    printf("Welcome to your Task Management System.");
    char selectedOption[FAULT_HANDLER];//used to detect false inputs that can cause Runtime error as entering string not a number
    short numericalRepresentationOfSelectedOption;
    LinkedList listOfUnperformedTasks=NULL;
    Stack stackOfPerformedTasks=NULL;
    ptrToTaskNode tail=NULL;
    do{
        printf("\n\nKindly, Choose an option from the following menu:\n1. Load Tasks File\n2. Add a New Task\n3. Delete a Task\n4. Search for a Task\n5. View Unperformed Tasks\n6. Perform a Task\n7. Undo Last Performed Task\n8. View Performed Tasks\n9. Generate Summary Report\n10. Exit\n");
        gets(selectedOption);
        numericalRepresentationOfSelectedOption=atoi(selectedOption);
        switch(numericalRepresentationOfSelectedOption){
        case 1:{
           listOfUnperformedTasks=makeSingularEmpty(listOfUnperformedTasks);//memory Allocating for the Head node which will have a next pointer that points to the first task node
            tail=(ptrToTaskNode) malloc(sizeof(struct TaskNode));
            if(!tail)
            printf("\nNo memory, Free memory and come again.");
            else {tail->nextTask=listOfUnperformedTasks;//tail is not the last node, it has a pointer to the last node, i did this so i dont need to return tail as i change it, specially in delete
            getFileInformation(listOfUnperformedTasks,tail);
            stackOfPerformedTasks=createStack(stackOfPerformedTasks);//memory Allocating for the Stack which will have a next pointer that points to Top task
            printf("\nList has been loaded with file tasks.");
            }
        break;
        }
        case 2:{
            if(listOfUnperformedTasks){// I did implement the check like this so it wont call id, name,....
        printf("\nEnter task ID: ");
        char stringId[MAX_TASK_ID_SIZE];
        gets(stringId);
        int taskId=atoi(stringId);
        ptrToTaskNode existIdInUnperformed=searchSingularById(taskId,listOfUnperformedTasks);//search if the id exist in unperformed, then dont add it because its a key value
          ptrToTaskNode existIdInPerformed=NULL;
        if(!existIdInUnperformed){//search if the id exist in performed also, then dont add it because its a key value, this is because if you undo the task that has the same id in performed it will cause problems
        ptrToTaskNode p;
        Stack tempStack=NULL;
        tempStack=createStack(tempStack);
          if(!tempStack)
            break;
            else{
        while(isEmptyStack(stackOfPerformedTasks)==0)
        push(pop(stackOfPerformedTasks),tempStack);
        while(isEmptyStack(tempStack)==0){
            p=pop(tempStack);
        push(p,stackOfPerformedTasks);
        if(p->taskId==taskId){
            existIdInPerformed=p;
            break;//if you find it there is no reason to continue checking
        }
    }
    }
        }
    if(!existIdInUnperformed&&!existIdInPerformed){
        printf("\nEnter task name: ");
        char taskName[MAX_TASK_NAME_SIZE];
        gets(taskName);
        printf("\nEnter task date: ");
        char taskDate[MAX_TASK_DATE_SIZE];
        gets(taskDate);
        printf("\nEnter task duration in hours: ");
        char stringDuration[MAX_TASK_DURATION_SIZE];
        gets(stringDuration);
        double taskDuration=atof(stringDuration);
        if(taskId&&taskDuration){//this is needed because if the id entered was string which will cause problems with reaching the same task and logic problems
        insertInSingularAfter(taskId,taskName,taskDate,taskDuration,listOfUnperformedTasks,tail);
        printf("\nTask with id %d has been inserted successfully.",taskId);
        }
        else printf("\nError in the enterd data.");
    }
    else printf("\nThe task id %d already exists in the system.",taskId);
            }
               else printf("\nNo existing unperformed task list, try loading the file list, or check if the loaded list exists.");
        break;
            }
        case 3:{
        char stringId[MAX_TASK_ID_SIZE];
        printf("\nEnter the ID of the task you want to delete: ");
        gets(stringId);
        int wantedId=atoi(stringId);
        ptrToTaskNode p=searchSingularForPreviousById(wantedId,listOfUnperformedTasks);
        if(p){// checks if list weren't null
            if(p->nextTask){//check if some parameters has error or if the task doesn't exist
            deleteNextInSingular(p,listOfUnperformedTasks,tail);
            printf("\nTask with ID %d has been deleted successfully.",wantedId);
            }
            else  printf("\nThe task with ID %d delete doesn't exist.",wantedId);
        }
            break;
        }
        case 4:{
            ptrToTaskNode wantedUnperformedTask=NULL;
             ptrToTaskNode wantedPerformedTask=NULL;
            do{
        printf("\nKindly, Choose the searching carteria\n1.search the task by its ID:\n2.search the task by its Name:\n");
        gets(selectedOption);
        numericalRepresentationOfSelectedOption=atoi(selectedOption);
        switch(numericalRepresentationOfSelectedOption){
        case 1:{
        char stringId[MAX_TASK_ID_SIZE];
        printf("\nEnter the ID of the task you want to search: ");
        gets(stringId);
        int taskId=atoi(stringId);
        wantedUnperformedTask=searchSingularById(taskId,listOfUnperformedTasks);//search id in unperformed
        if(wantedUnperformedTask)
             printf("\nThe task you searched is unperformed and has the following description:\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f", wantedUnperformedTask->taskId, wantedUnperformedTask->taskName, wantedUnperformedTask->taskDate, wantedUnperformedTask->taskDuration);
        else{
        ptrToTaskNode p;//search id in performed
        /* i did implement the search in performed because it will cause confusion to users who tries to add a task with the same id as a performed one but the console siad it wont work
            meanwhile when they searched it they found that there is no task with this id in the unperformed actually
        */
        Stack tempStack=NULL;
        tempStack=createStack(tempStack);
          if(tempStack==NULL)
            break;
            else{//traverse stack by popping and pushing to another stack to search in it
        while(isEmptyStack(stackOfPerformedTasks)==0)
        push(pop(stackOfPerformedTasks),tempStack);
        while(isEmptyStack(tempStack)==0){
            p=pop(tempStack);
        push(p,stackOfPerformedTasks);
        if(p->taskId==taskId){
            wantedPerformedTask=p;
          printf("\nThe task you searched is performed and has the following description:\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f", wantedPerformedTask->taskId, wantedPerformedTask->taskName, wantedPerformedTask->taskDate, wantedPerformedTask->taskDuration);
            break;
        }
    }
    }
        }
    if(!wantedPerformedTask&&!wantedUnperformedTask)
                printf("\nTask with the id %d hasn't been found.",taskId);//if both pointers are null then its clear that the task doesn't exist in the system
        break;
        }
        case 2:{
        char taskName[MAX_TASK_NAME_SIZE];
        printf("\nEnter the name of the task you want to search: ");
        gets(taskName);
        wantedUnperformedTask=searchSingularByNameAndPrint(taskName,listOfUnperformedTasks);
        ptrToTaskNode p;/* I implemented searching to name as its not a key, so there could be more than one task with the same name but not the same id,I also searched in unperformed and performed
        to not make confuse with search of id
        */
        Stack tempStack=NULL;
        tempStack=createStack(tempStack);
        if(!tempStack)
            break;
        else{
        while(isEmptyStack(stackOfPerformedTasks)==0)
        push(pop(stackOfPerformedTasks),tempStack);
        while(isEmptyStack(tempStack)==0){
            p=pop(tempStack);
        push(p,stackOfPerformedTasks);
        if(strcmp(p->taskName,taskName)==0){
                wantedPerformedTask=p;
                printf("\n\nThe tasks you searched is performed and has the following description:\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f", wantedPerformedTask->taskId, wantedPerformedTask->taskName, wantedPerformedTask->taskDate, wantedPerformedTask->taskDuration);
        }
    }
    }
        if(!wantedPerformedTask&&!wantedUnperformedTask)
        printf("\nTask with the name %s hasn't been found.",taskName);// if the tasks doesn't exist
        break;
        }
        default: printf("\nplease enter a correct number.");
        }
        }while(numericalRepresentationOfSelectedOption!=1&&numericalRepresentationOfSelectedOption!=2);
        break;
        }
        case 5:{
        viewUnperformedTasks(listOfUnperformedTasks);
        break;
        }
        case 6:{
        char stringId[MAX_TASK_ID_SIZE];
        printf("\nEnter the ID of the task you want to perform: ");
        gets(stringId);
        int wantedId=atoi(stringId);
        ptrToTaskNode p=searchSingularForPreviousById(wantedId,listOfUnperformedTasks);
        if(p){//checks if list is not null
        if(p->nextTask){
          ptrToTaskNode deletedUnperformedTask= cutNextAndGet(p,listOfUnperformedTasks,tail);/* I implemented a function called cut, this function cuts the task from the list without freeing it
          ,and we will push the pointer to that memory to the stack, because the same task cant be performed and unperformed at the same time
          */
            push(deletedUnperformedTask,stackOfPerformedTasks);
            printf("\nThe task with id %d has been performed.",wantedId);
        }
        else printf("\nThe task with id %d doesn't exist or it is being performed.",wantedId);
        }
            break;
        }
        case 7:{
            ptrToTaskNode p=pop(stackOfPerformedTasks);
            if(p){
            p->undoneStatus=1;
             insertingPointerChanges(listOfUnperformedTasks,tail,p);/*changing the pointer in insertion, I did it seperately because when inserting a pointer not task data we
             use the same memory allocated for the task because its more conventinal, so I will insert it by just changing pointers in the end of the list*/
            printf("\nThe task with id %d has been undone.",p->taskId);
            }
                    break;
        }
        case 8:{
        viewPerformedTasks(stackOfPerformedTasks);
        break;
        }
        case 9:{
        generateReport(listOfUnperformedTasks,stackOfPerformedTasks);
        break;
        }
        case 10:{
            disposeSingularListContents(listOfUnperformedTasks);
            disposeStack(stackOfPerformedTasks);
            free(tail);
        printf("\nThanks for using the task managment system, see you again.");
        break;
        }
        default: printf("\nplease enter a correct number.");
        }
    }while(numericalRepresentationOfSelectedOption!=10);
    return 0;
}

LinkedList makeSingularEmpty(LinkedList L){
    if(L!=NULL)
    deleteSingularList(L);
   else{
        L=(LinkedList) malloc(sizeof(TaskNode));
 if(L==NULL)
    printf("\nNo memory, Free memory and come again.");
 else
    L->nextTask=NULL;
   }
    return L;
}

void getFileInformation(LinkedList L,ptrToTaskNode tail){
    FILE *inputFile=fopen("tasks.txt","r");
    if (inputFile==NULL){//checking if the file we tried to open exists
        printf("\nError while opening the file, the file named tasks.txt may not exist.");
    }
    else{
            char dataFromFile[MAX_TASK_DESCRIPTION_LINE],taskName[MAX_TASK_NAME_SIZE],taskDate[MAX_TASK_DATE_SIZE];;
            int taskId;
            double taskDuration;
            for(int i=0,lineCount=1;fgets(dataFromFile,MAX_TASK_DESCRIPTION_LINE,inputFile)!=NULL;i=0,lineCount++){//read data till EOF is reached
                char* token=strtok(dataFromFile,"#");//cut dataFromFile into substrings based on #
                while(token!=NULL){
                        if(i==0)
                        taskId=atoi(token);
                     else if(i==3)
                        taskDuration=atof(token);
                   else strcpy((i==1)?taskName:taskDate,token);//assign taken to variables based on counter as they are arranged in file
                    token=strtok(NULL,"#");//cut based on # till NULL is reached
                i++;
                }
                if(i==4)
                insertInSingularAfter(taskId,taskName,taskDate,taskDuration,L,tail);
                else {
                printf("Invalid file data format in the line %d.",lineCount);
                break;
            }
            }
            fclose(inputFile);//closing the opened file after reading so the memory allocated with it is removed
}
}

int isEmptySingularList(LinkedList L){
    if(L==NULL)
        return -1;
    return L->nextTask==NULL;
}

void deleteSingularList(LinkedList L){
     if(L==NULL){
           printf("\nNo existing unperformed task list, try loading the file list, or check if the loaded list exists.");
     }
else if(!isEmptySingularList(L)){
ptrToTaskNode p=L->nextTask,temp;
L->nextTask=NULL;
while(p!=NULL){
temp=p->nextTask;
free(p);
p=temp;
}
}
}

void disposeSingularListContents(LinkedList L){
deleteSingularList(L);
free(L);
}

void insertInSingularAfter(int taskId,char taskName[],char taskDate[],double taskDuration,LinkedList L,ptrToTaskNode p){
            if(L==NULL)
           printf("\nNo existing unperformed task list, try loading the file list, or check if the loaded list exists.");
           else if(p==NULL)
           printf("\nThe unperformed task you want to add after doesn't exist.");
    else{
      ptrToTaskNode temp=(ptrToTaskNode) malloc(sizeof(TaskNode));
      if(temp==NULL){
          printf("\nNo memory, Free memory and come again.");
      }
      else{
            temp->taskId=taskId;
            strcpy(temp->taskName,taskName);
            strcpy(temp->taskDate,taskDate);
            temp->taskDuration=taskDuration;
            temp->undoneStatus=0;
            insertingPointerChanges(L,p,temp);
}
}
}

void insertingPointerChanges(LinkedList L,ptrToTaskNode p,ptrToTaskNode q){
    if(L==NULL){
        printf("\nNo existing unperformed task list, try loading the file list, or check if the loaded list exists.");
                 return;
    }
    if(p==NULL){
         printf("\nThe unperformed task you want to add after doesn't exist.");
                  return;
    }
    if(q==NULL){
         printf("\nThe unperformed task you want to add doesn't exist.");
         return;
    }
q->nextTask=p->nextTask->nextTask;
            p->nextTask->nextTask=q;
            p->nextTask=q;
}

ptrToTaskNode searchSingularById(int taskId,LinkedList L){
    if(L==NULL)
    printf("\nNo existing unperformed task list, try loading the file list, or check if the loaded list exists.");
    else if(!isEmptySingularList(L)){
   ptrToTaskNode p=L->nextTask;
    while(p!=NULL&&p->taskId!=taskId)
    p=p->nextTask;
    return p;
    }
    return NULL;
}

ptrToTaskNode searchSingularByNameAndPrint(char taskName[],LinkedList L){
    ptrToTaskNode wantedPerformedTask=NULL;
    if(L==NULL)
     printf("\nNo existing unperformed task list, try loading the file list, or check if the loaded list exists.");
    else if(!isEmptySingularList(L)){
   ptrToTaskNode p=L->nextTask;
    while(p!=NULL){
    if(strcmp(p->taskName,taskName)==0){
     printf("\n\nThe task you searched is unperformed and has the following description:\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f", p->taskId, p->taskName, p->taskDate, p->taskDuration);
    wantedPerformedTask=p;
    }p=p->nextTask;
    }
    }
    return wantedPerformedTask;
}

ptrToTaskNode searchSingularForPreviousById(int taskId,LinkedList L){
       ptrToTaskNode p=L;
      if(L==NULL){
    printf("\nNo existing unperformed task list, try loading the file list, or check if the loaded list exists.");
    return NULL;
      }
    while(p->nextTask!=NULL&&p->nextTask->taskId!=taskId)
    p=p->nextTask;
    return p;
}

ptrToTaskNode cutNextAndGet(ptrToTaskNode p,LinkedList L,ptrToTaskNode tail){
    ptrToTaskNode temp=NULL;
     if(L==NULL){
   printf("\nNo existing unperformed tasks, try loading the file list, or check if the loaded list exists.");
    return temp;
     }
    if(p==NULL){
    printf("\nThe unperformed task you wish to delete with its assistant doesn't exist.");
    return temp;
    }
    if(tail==NULL){
    printf("\nThe last unperformed task you may want to update dont exist.");
    return temp;
    }
    else if(p!=tail->nextTask){
             temp=p->nextTask;
            p->nextTask=temp->nextTask;
            if(tail->nextTask==temp)
                tail->nextTask=p;
    }
            return temp;
}

void deleteNextInSingular(ptrToTaskNode p,LinkedList L,ptrToTaskNode tail){
            ptrToTaskNode temp=cutNextAndGet(p,L,tail);
            free(temp);
}

void viewUnperformedTasks(LinkedList L){
if(L==NULL)
    printf("\nNo such unperformed tasks to print, the task data may not be loaded.");
    else if(!isEmptySingularList(L)){
        ptrToTaskNode p=L->nextTask;
        int i=1;
        printf("\nList of unperformed tasks:");
        while(p!=NULL){
        printf("\n\n%d.%s\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f",i++,(p->undoneStatus)?"(Undone Task)":"" ,p->taskId, p->taskName, p->taskDate, p->taskDuration);
        p=p->nextTask;
        }
    }
        else printf("\nThere is no unperformed tasks to show.");
}

void generateReport(LinkedList listOfUnperformedTasks,Stack stackOfPerdoemedTasks){
    FILE *outputFile=fopen("Report.txt","w");
    if(outputFile==NULL){
    printf("\nError opening the file");
    }
    else{
        writeUnperformedTasks(outputFile,listOfUnperformedTasks);
        writeUndoneTasks(outputFile,listOfUnperformedTasks);
        writePerformedTasks(outputFile,stackOfPerdoemedTasks);
        printf("\nTask data has been saved on the file.");
    }
    fclose(outputFile);
}

void writeUnperformedTasks(FILE* outputFile,LinkedList L){
        if(outputFile==NULL){
        printf("\nError while opening the file.");
            return;
        }
                fprintf(outputFile,"List of unperformed tasks:");
if(L==NULL)
    fprintf(outputFile,"\nNo such unperformed tasks to print, the task data may not be loaded.");
    else if(!isEmptySingularList(L)){
        ptrToTaskNode p=L->nextTask;
        int i=1;
        while(p!=NULL){
        fprintf(outputFile,"\n%d.%s\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f\n",i++,(p->undoneStatus)?"(Undone Task)":"" ,p->taskId, p->taskName, p->taskDate, p->taskDuration);
        p=p->nextTask;
        }
    }
        else fprintf(outputFile,"\nThere is no unperformed tasks to show.");
}

void writeUndoneTasks(FILE* outputFile,LinkedList L){
    int existUndoneTasks=0;
    if(outputFile==NULL){
        printf("\nError while opening the file.");
        return;
        }
fprintf(outputFile,"\n\nList of undone tasks:");
if(L==NULL)
    fprintf(outputFile,"\nNo such undone tasks to print, the task data may not be loaded.");
    else if(!isEmptySingularList(L)){
        ptrToTaskNode p=L->nextTask;
        int i=1;
        while(p!=NULL){
        if(p->undoneStatus==1){
        existUndoneTasks=1;
        fprintf(outputFile,"\n%d.\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f\n",i++, p->taskId, p->taskName, p->taskDate, p->taskDuration);
        }
        p=p->nextTask;
        }
            if(!existUndoneTasks)
          fprintf(outputFile,"\nThere is no undone tasks to show.");
        }
        else fprintf(outputFile,"\nThere is no undone tasks to show.");
}

void writePerformedTasks(FILE* outputFile,Stack stackOfPerformedTasks){
    if(outputFile==NULL){
        printf("\nError while opening the file.");
        return;
        }
fprintf(outputFile,"\n\nList of performed tasks:");
if(stackOfPerformedTasks==NULL)
    fprintf(outputFile,"\nNo such performed tasks to print, the task data may not be loaded.");
    else if(!isEmptyStack(stackOfPerformedTasks)){
            Stack tempStack=NULL;
     tempStack=createStack(tempStack);
    int i=1;
    ptrToTaskNode p;
    while(!isEmptyStack(stackOfPerformedTasks))
        push(pop(stackOfPerformedTasks),tempStack);
    while(!isEmptyStack(tempStack)){
            p=pop(tempStack);
        push(p,stackOfPerformedTasks);
     fprintf(outputFile,"\n%d.\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f\n",i++, p->taskId, p->taskName, p->taskDate, p->taskDuration);
        }
    }
    else fprintf(outputFile,"\nThere is no performed tasks to show.");
}

Stack createStack(Stack s){
    if(s!=NULL)
    makeEmptyStack(s);
    else{
        s=(Stack) malloc(sizeof(TaskNode));
 if(s==NULL)
    printf("\nNo memory, Free memory and come again.");
}
s->nextTask=NULL;
    return s;
}
void makeEmptyStack(Stack s){
if(isEmptyStack(s)==-1)
         printf("\nNo existing performed tasks, try loading the file list, or check if the loaded list exists.");
    else{
    while(!isEmptyStack(s))
    pop(s);
    }
}

int isEmptyStack(Stack s){
     if(s==NULL){
    return -1;
    }
return s->nextTask==NULL;
}

ptrToTaskNode pop(Stack s){
    ptrToTaskNode temp=NULL;
         if(s==NULL)
printf("\nNo existing performed tasks, try loading the file list, or check if the loaded list exists.");
    else if(isEmptyStack(s))
    printf("\nthere is No perforemd tasks.");
    else{
     temp=s->nextTask;
      s->nextTask=s->nextTask->nextTask;
}
    return temp;
}

void push(ptrToTaskNode p,Stack s){
         if(s==NULL)
printf("\nNo existing performed tasks, try loading the file list, or check if the loaded list exists.");
    else if(p==NULL)
            printf("\nNo such task to push into the performed task.");
    else{
            p->nextTask=s->nextTask;
            s->nextTask=p;
      }
}

void disposeStack(Stack S){
makeEmptyStack(S);
free(S);
}

void viewPerformedTasks(Stack mainStack){
    if(mainStack==NULL)
 printf("\nNo existing performed tasks, try loading the file list, or check if the loaded list exists.");
    else{Stack tempStack=NULL;
     tempStack=createStack(tempStack);
    int i=1;
    ptrToTaskNode p;
    if(!isEmptyStack(mainStack)){
    while(!isEmptyStack(mainStack))
        push(pop(mainStack),tempStack);
    while(!isEmptyStack(tempStack)){
            p=pop(tempStack);
        push(p,mainStack);
     printf("\n%d.\n-Task Id: %d\n-Task name: %s\n-Task date: %s\n-Task duration: %.5f",i++, p->taskId, p->taskName, p->taskDate, p->taskDuration);
    }
    }
    else printf("No performed tasks to show.");
}
}
