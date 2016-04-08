#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#define BLOCK 2
#define LINESIZE 256
#define NAMESIZE 32

/*C:/Users/admin/Desktop/CST_Term_2/COMP_2510_C/midterm2*/


typedef struct record record;
struct record {
	char name[32];
	int score;
};

typedef struct node node;
struct node{
	record data;
	node *next;
};

/*Scans the inputs for the records from standard input, and saves them within the strcture of one record.*/
int scan(char * name, int * score){
	
	/*The first name, last name, and scores for the records are stored as local string variables.*/
	char line[LINESIZE];
	
	/*nscore is the int version of strscore, and scorecheck indicates wheteher or not the score is valid.*/
	size_t i = 0;
	
	printf("Enter a First name and Score separated by spaces:\n");
	if(!fgets(line, LINESIZE, stdin)){
		clearerr(stdin);
		return -1;
	}
	/*Format all input to lowercase*/
	for(i=0; line[i]!='\0'; i++){
		line[i] = tolower((int)line[i]);
	}
	
	if(sscanf(line,"%s %d", name, score)!=2){
		printf("Your name and score  not assigned.\n");
		return 0;
	}
	
	if(*score>=0 && *score<=100 && strlen(name)<NAMESIZE){
		printf("Valid input. \n");
		
		return 1;
	}else{
		printf("Your input was invalid.\n");
	}
	return -1;
}

int insert(node ** plist, const char *a_name, int a_score){
	node * newnode = malloc(sizeof(node));
	if (newnode == 0)
		return 0;
	newnode->data.score = a_score;
	strcpy(newnode->data.name, a_name);
	newnode ->next = *plist;
	*plist = newnode;
	return 1;
}

void fprint(node * list){
if (list!=0){ /*If the list isn't empty*/
	node * p;
	for (p= list; p!= 0; p=p->next)
	printf("%s %d\n", list->data.name, list->data.score);
	}
}

char scan2(){
	char line[LINESIZE];
	char yn = 'n';
	if(!fgets(line, LINESIZE, stdin)){
		clearerr(stdin);
	}
	if(sscanf(line,"%c", &yn)==1){
		return yn;
	}
	return 'n';
}

int scan3(char * findname){
	char line[LINESIZE];
	if(!fgets(line, LINESIZE, stdin)){
		clearerr(stdin);
	}
	if(sscanf(line,"%s", findname )==1){
		return 1;
	}
	return 0;
}

node * find(node *lst, const char * name){
	node * p;
	for (p=lst; p!=0; p=p->next)
		if(strcmp(name,p->data.name)==0){
			return p;
		}
	return 0;
}

/*Deletes all the nodes in the linked list.*/
void destroy(node ** list){
	node * p, *q;
	for (p=*list; p!=0; p=q){
		q=p->next;
		free(p);
	}
	*list = 0;
}

/*Deletes all instances of a specified name from the list.*/
size_t delete_all(node **plist, const char * name){
	node ** tracer;
	size_t count = 0;
	
	for (tracer = plist; *tracer!=0; ){
		if(strcmp(name, (*tracer)->data.name)==0){
			node * p = *tracer;
			*tracer = p->next;
			free(p);
			count++;
		}else{
			tracer = &(*tracer)->next;
		}
	}
	return count;
	
}

int main(void){
	
	node * head;
	node * p;
	char keepreading;
	char name[NAMESIZE], findname[NAMESIZE];
	int score = 0, scancheck =0;
	
	do{
	scancheck = scan(name, &score);
	if(scancheck == 1 && insert(&head, name, score))
		printf("record created and added to the linked list.\n");
	
	printf("Do you you want to add more records? Y/N\n");
	keepreading = scan2();
	}while (keepreading == 'y');
	
	printf("Printing the linked list\n");
	fprint(head);
	
	printf("Which person do you want to find?\n");
	scancheck = scan3(findname);
	if(scancheck)
		(p = find(head, findname))? printf("%s %d\n", p->data.name, p->data.score) : printf("Could not find that name.\n");
	
	fprint(head);
	printf("Deleting the list.\n");
	destroy(&head);
	fprint(head);
	
	printf("Attempted to print head, there should be no list above.\n");
	printf("Attempting to delete all instances of bryn.\n");
	delete_all(&head, "bryn");
	fprint(head);
	
	
	
	
	return 0;
}
