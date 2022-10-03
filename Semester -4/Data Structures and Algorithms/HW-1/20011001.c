#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int value;
	struct node *next, *down;
}NODE;

void printTablo(NODE*);
int *createRandom(int);
NODE *insertNode(NODE*, NODE*);
NODE *createList(int);
NODE *fastLinkedList(int*, int, NODE*, int*);
NODE *searchValue(NODE*, int*,int);
void search(NODE*, int);
void addNode(NODE*,NODE*);
int deleteNode(NODE*, int);
int getMenu();			//menüyü print edip seçimi döndürüyor
NODE *cleanPastTablo(NODE*, int*);		//önceki fast linked list tablosunu freeliyor

int main(){
	NODE *head = (NODE*)malloc(sizeof(NODE));
	NODE *newNode;
	int level, option;
	int N, element;
	int *random;
	printf("Enter number of elements: ");
	scanf("%d",&N);
	head->down = createList(N);
	random = (int*)malloc(((N+1)/2)*sizeof(int));
	random = createRandom(N);	
	level = 1;
	head->down = fastLinkedList(random,(N+1)/2,head->down,&level);
	head->next = NULL;
	printTablo(head);
	do{
		option = getMenu();
		if(option == 1)
			printTablo(head);
		else if(option == 2)
			search(head,level);
		else if(option == 3){
			newNode = (NODE*)malloc(sizeof(NODE));
			printf("Enter value of new element: ");
			scanf("%d",&newNode->value);
			addNode(head, newNode);
			N++;
			head = cleanPastTablo(head,&level);
			printTablo(head);
			random = createRandom(N);
			head->down = fastLinkedList(random,(N+1)/2,head->down,&level);
			printTablo(head);
		}
		else if(option == 4){
			if(deleteNode(head,level)){
				N--;
				head = cleanPastTablo(head,&level);
				printTablo(head);
				random = createRandom(N);
				head->down = fastLinkedList(random,(N+1)/2,head->down,&level);
			}
			printTablo(head);
		}
	}while(option!=-1);
	free(random);	free(head);
	return 0;
}

int getMenu(){
	int option;
	printf("\n----- MENU -----\n");
	printf("1  - Print all levels\n");
	printf("2  - Search an element\n");
	printf("3  - Add an element\n");
	printf("4  - Delete an element\n");
	printf("-1 - Exit\n");
	printf("Created by 20011001 Buse Nur Pekmezci\n\n");
	printf("Enter your option: ");
	scanf("%d",&option);
	return option;
}

void printTablo(NODE *head){
	NODE *tmp = head, *temp;
	printf("\nALL LEVELS:\n");
	while(tmp->down!=NULL){
		temp = tmp;
		while(temp->next!=NULL){
			printf("%d	",temp->value);
			temp = temp->next;
		}
		printf("%d\n",temp->value);
		tmp = tmp->down;
	}
	temp = tmp;
	while(temp->next!=NULL){
		printf("%d	",temp->value);
		temp = temp->next;
	}
	printf("%d\n",temp->value);
}

int *createRandom(int len){
	int i, temp, unique, j;
	int *random = (int*)malloc(len*sizeof(int));
	for(i=0;i<len;i++){
		unique = 0;
		while(unique == 0){
			temp = rand() % len;
			j = 0;
			while(j<i && random[j] != temp){
				j++;
			}
			if(j==i){
				unique = 1;
			}
		}
		random[i] = temp;
	}
	return random;
}

NODE *insertNode(NODE *temp, NODE *head){		//en baþta listeyi oluþturmak için ve eklemeler için
	NODE *prev, *curr;
	if(head == NULL){
		head = temp;
		head->next = NULL;
	}
	else if(temp->value < head->value){
		temp->next = head;
		head = temp;
	}
	else{
		prev = head;
		curr = head->next;
		while(curr!=NULL && curr->value < temp->value){
			prev = curr;
			curr = curr->next;
		}
		prev->next = temp;
		temp->next = curr;
	}
	return head;		//aslýnda head node u olan head i deðil
}						//listenin data tutan ilk node unu döndürüyor

NODE *createList(int N){
	int i;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	NODE *temp=NULL;
	head->next = temp;
	printf("Enter elements: ");
	for(i=0;i<N;i++){
		temp = (NODE*)malloc(sizeof(NODE));
		scanf("%d",&temp->value);
		temp->down = NULL;
		head->next = insertNode(temp,head->next);	//data tutan ilk nodu döndürdüðüm için next'e atýyor
	}
	head->down=NULL;
	return head;
}

NODE *fastLinkedList(int *random, int n, NODE *prev_head, int *level){
	(*level)++;
	int i;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	NODE *curr, *newNode;
	head->down = prev_head;
	head->next = NULL;
	if(n==1){
		newNode = (NODE*)malloc(sizeof(NODE));
		curr = prev_head;
		while(random[0]>-1){
			curr=curr->next;
			random[0]--;
		}
		newNode->value = curr->value;
		newNode->down = curr;
		head->next = insertNode(newNode,head->next);
		return head;
	}
	else{
		for(i=0;i<n;i++){
			newNode = (NODE*)malloc(sizeof(NODE));
			curr = prev_head;
			while(random[i]>-1){
				curr=curr->next;
				random[i]--;
			}
			newNode->value = curr->value;
			newNode->down = curr;
			head->next = insertNode(newNode,head->next);
		}
		random = createRandom((n+1)/2);
	}
	return fastLinkedList(random, (n+1)/2, head, level);
}

NODE *searchValue(NODE *head, int *level, int value){		//Eleman silmek için de aramayý bu
	NODE *curr, *prev;									//yöntemle yaptýðým için hem node un 0.
	int found = 0, level2 = *level;						//seviyedeki yerinden önceki node u
	prev = head->down;							//hem de bulunduðu seviyenin levelini döndürüyor
	curr = prev;
	while(prev != NULL && found == 0){
		level2--;
		curr = curr->next;
		while(curr!=NULL && value > curr->value){
			prev = curr;
			curr = curr->next;
		}
		if(curr!=NULL && value == curr->value){
			found = 1;
		}
		else{
			prev = prev->down;
			curr = prev;
		}
	}
	if(found == 1){
		(*level) = level2;		
		while(curr->down != NULL){
			prev = prev->down;
			curr = curr->down;
			while(prev->next!=curr){
				prev = prev->next;
			}
		}
		return prev;
	}
	else{
		return NULL;
	}
}

void search(NODE *head, int level){
	int value;
	printf("Enter value of element: ");
	scanf("%d",&value);
	if(searchValue(head,&level,value) != NULL){		//eðer node varsa levelini
		printf("Element found at %d\n",level+1);	//bu fonksiyonla yazdýrýyor
	}
	else{
		printf("Element not found\n");
	}
}

void addNode(NODE *head, NODE *newNode){
	NODE *curr, *prev;
	prev = head->down;
	curr = prev->next;
	while(prev->down!=NULL){
		if(curr == NULL){
			prev = prev->down;
			curr = prev->next;
		}
		else{
			if(curr->value > newNode->value){
				prev = prev->down;
				curr = prev->next;
			}
			else{
				prev = curr;
				curr = curr->next;
			}
		}
	}
	prev->next = insertNode(newNode,curr);
}

int deleteNode(NODE *head, int level){
	NODE *prev, *curr;
	int value;
	printf("Enter value of element: ");
	scanf("%d",&value);
	prev = searchValue(head,&level,value);		//0. seviyedeki nodu siliyor.
	if(prev != NULL){							//sonra liste temizlenip baþtan
		curr = prev->next;						//oluþturulur
		prev->next = curr->next;
		free(curr);
		return 1;
	}
	else{
		printf("There is no element with this value.\n");
		return 0;
	}
}
NODE *cleanPastTablo(NODE *head, int *level){
	NODE *tmp, *tmp2;
	while(head->down != NULL){
		tmp = head;
		while(tmp != NULL){
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
		head = head->down;
	}
	(*level) = 1;
	tmp = (NODE*)malloc(sizeof(NODE));
	tmp->next = NULL;
	tmp->down = head;	//hiçbir node bulundurmayan
	return tmp;			//son seviye headini de oluþturup döndürüyor
}
