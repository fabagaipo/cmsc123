#include <stdio.h>
#include <stdlib.h>

struct node{
	int  data;
	struct node *prev, *next;
};

struct list{
	int  count;
	struct node *head, *tail;
}list;

void insertFront(struct list *, int); 
void insertRear(struct list *, int);
void insertAt(struct list *, int, int);
void removeFront(struct list *); 
void removeRear(struct list *);
void removeAt(struct list *, int);
void printList(struct node *);
void isEmpty(struct node *);

int main(){
	int x=0, p, choice = 1, n, data;
	
	struct list *L = (struct list*)malloc(sizeof (struct list));
	
	L->head=NULL;
	L->tail=NULL;
	L->count=0;
	
	while(choice != 0){
        
         //Menu
        
        printf("============================================\n");
        printf("DOUBLY LINKED LIST PROGRAM\n");
        printf("============================================\n");
        printf("1. Insert node - at beginning\n");
        printf("2. Insert node - at end\n");
        printf("3. Insert node - at N\n");
        printf("4. Delete node - from beginning\n");
        printf("5. Delete node - from end\n");
        printf("6. Delete node - from N\n");
        printf("7. Display list\n");
        printf("8. Check if node is empty\n");
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice : ");

        scanf("%d", &choice);

        
         // Choose from different menu operation
        
        switch(choice){

            case 1:
                printf("Enter data of first node : ");
                scanf("%d", &data);

                insertFront(L, data);
                break;

            case 2:
                printf("Enter data of last node : ");
                scanf("%d", &data);

                insertRear(L, data);
                break;

            case 3:
                printf("Enter the position where you want to insert new node: ");
                scanf("%d", &n);
                printf("Enter data of %d node : ", n);
                scanf("%d", &data);

                insertAt(L, data, n);
                break;
            
            case 4:
                removeFront(L);
                break;

            case 5:
                removeRear(L);
                break;

            case 6:
                printf("Enter the node position which you want to delete: ");
                scanf("%d", &n);
                removeAt(L, n);
                break;
            
            case 7:
                printList(L->head);
                break;
            
            case 8:
                isEmpty(L->head);

            case 0:
                break;

            default:
                printf("Invalid choice. Try again.");
        }

        printf("\n\n\n\n\n");
    }

    return 0;
}

void insertFront(struct list *L, int x){
	struct node *newNode=(struct node*)malloc(sizeof(struct node));
	
		if(L->count==0){
			newNode->data = x;
			newNode->next = NULL;
			newNode->prev = NULL;
			L->head = newNode;
			L->tail = newNode;
		}
		else{
			newNode->data = x;
			newNode->prev = NULL;
			newNode->next = L->head;
			L->head->prev = newNode;
			L->head = newNode;
		}
		
		L->count++;
}

void insertRear(struct list *L, int x){
	struct node *newNode=(struct node*)malloc(sizeof(struct node));
	
		if(L->count==0){
			newNode->data = x;
			newNode->prev = NULL;
			newNode->next = NULL;
			L->head = newNode;
			L->tail = newNode;
		}
		else{	
			newNode->data = x;
			L->tail->next = newNode;
			newNode->next = NULL;
			newNode->prev = L->tail;
			L->tail=newNode;
		}
		
		L->count++;
}

void insertAt(struct list *L, int x, int p){
	int c;	
	
		if(p==0){
			insertFront(L, x);
	
		}
		else if(p==(L->count)){
			insertRear(L, x);

		}
		else if(p < 0 || p >= L->count){
			printf("Invalid Position! Please try again.\n");
		}
		else{
			struct node *newNode=(struct node*)malloc(sizeof(struct node));
			struct node *temp1=(struct node*)malloc(sizeof(struct node));
			struct node *temp2=(struct node*)malloc(sizeof(struct node));
			newNode->data = x;
			newNode->next = NULL;
			temp1 = L->head;
			temp2 = L->head;
				
				for(c=0; c!=(p-1); c++)
				{
					temp1=temp1->next;
				
				}
				
				for(c=0; c!=p; c++)
				{
					temp2=temp2->next;
				}
				
				temp1->next = newNode;
				newNode->prev = temp1;
				newNode->next = temp2;
				temp2->prev = newNode;
				
				L->count++;
		}
		
}

void removeFront(struct list *L){
		if(L->count == 0){
			printf("EMPTY LIST");
		}
		else{
			L->head = L->head->next;
			L->head->prev = NULL;
			
			L->count--;
		}
}

void removeRear(struct list *L){
		if(L->count == 0){
			printf("EMPTY LIST");
		}
		else{
		 	L->tail = L->tail->prev;
		 	L->tail->next = NULL;
		 	
		 	L->count--;
		}
}

void removeAt(struct list *L, int p){
	int c;
	
		if(p==0){
			removeFront(L);
	
		}
		else if(p==(L->count)){
			removeRear(L);

		}
		else if(p < 0 || p >= L->count){
			printf("Invalid Position! Please try again.\n");
		}
		else{
			struct node *temp1=(struct node*)malloc(sizeof(struct node));
			struct node *temp2=(struct node*)malloc(sizeof(struct node));
			
			temp1=L->head;
			temp2=L->head;
			
				for(c=0; c!=(p-1); c++)
				{
					temp1= temp1->next;
				}
				
				for(c=0; c!=p; c++)
				{
					temp2=temp2->next;
				}
				
				temp2 = temp2->next;
				temp1->next = temp2;
				temp2->prev = temp1;
				
				L->count--;
		}
}

void printList(struct node *h){
	if(h==NULL){
		printf("EMPTY LIST");
	}
	else{
		while(h!=NULL){
			printf("%d ", h->data);
			h = h->next;
		}
	}
	
	printf("\n");
	
	return;
}


void deleteFront(struct list *L){
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	
		if(L->count == 0){
			printf("EMPTY LIST");
		}
		else{
			temp=L->head->next;
			free(L->head);
			L->head = temp;
			
			L->count--;
		}
}

void deleteRear(struct list *L){
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	
	temp= L->head;
	
		if(L->count == 0){
			printf("EMPTY LIST");
		}
		else{
			while(temp->next!=L->tail){
				temp = temp->next;
			}
			
				L->tail = temp;
				L->tail->next = NULL;
				
				L->count--;
		}
}

void deleteAt(struct list *L, int p){
	int c;
	
		if(p==0){
			deleteFront(L);
	
		}
		else if(p==(L->count)){
			deleteRear(L);

		}
		else if(p < 0 || p >= L->count){
			printf("Invalid Position! Please try again.\n");
		}
		else{
			struct node *temp1=(struct node*)malloc(sizeof(struct node));
			struct node *temp2=(struct node*)malloc(sizeof(struct node));
			
			temp1=L->head;
			temp2=L->head;
			
				for(c=0; c!=(p-1); c++){
					temp1= temp1->next;
				}
				
				for(c=0; c!=p; c++){
					temp2=temp2->next;
				}
				
				temp1->next = temp2->next;
				temp2=NULL;
				free(temp2);
				
				L->count--;
		}
}

void isEmpty(struct node *h){
	if(h==NULL){
		printf("EMPTY LIST");
	}
	else{
		printf("LIST CONTAINS NODES. DISPLAYING NODES...\n");
		while(h!=NULL){
			printf("%d ", h->data);
			h = h->next;
		}
	}
	
	printf("\n");
	
	return;
}