#include <stdio.h>
#include <stdlib.h>

struct node{
	int  data;
	struct node *next;
};

struct node*head = NULL;

struct list{
	int  count;
	struct node *head, *tail;
}list;

void insertFront(struct list *L, int x); 
void insertRear(struct list *L, int x);
void insertAt(struct list *L, int x, int p);
void deleteFront(struct list *L); 
void deleteRear(struct list *L);
void deleteAt(struct list *L, int p);
void displayAll(struct node *h);
int isEmpty(struct node *h);
int searchNode(struct list *h, int key);

int main(void){
	int x=0, p, choice = 1, n, data, index, searchKey;
	
	struct list *L = (struct list*)malloc(sizeof (struct list));
	
	L->head=NULL;
	L->tail=NULL;
	L->count=0;
	
	while(choice != 0){
        
         //Menu
        
        printf("============================================\n");
        printf("SINGLY LINKED LIST PROGRAM\n");
        printf("============================================\n");
        printf("1. Insert node - beginning\n");
        printf("2. Insert node - end\n");
        printf("3. Insert node - n position\n");
        printf("4. Delete node - beginning\n");
        printf("5. Delete node - end\n");
        printf("6. Delete node - n position\n");
        printf("7. Display list\n");
        printf("8. Check if empty\n");
		printf("9. Search for node\n");
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice: ");

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
                deleteFront(L);
                break;

            case 5:
                deleteRear(L);
                break;

            case 6:
                printf("Enter the node position which you want to delete: ");
                scanf("%d", &n);
                deleteAt(L, n);
                break;
            
            case 7:
                displayAll(L->head);
                break;
            
            case 8:
                isEmpty(L->head);
				break;

			case 9:
				printf("\nEnter element to search: ");
    			scanf("%d", &searchKey);

				// Call function to search first element by key
				index = searchNode(L, searchKey);
				
				// Element found in the list
				if (index == 0){
					printf("%d found in the list at node %d\n", searchKey, index+1);
				}else if(index>0){
					printf("%d found in the list at node %d\n", searchKey, index);
				}else{
					printf("%d not found.\n", searchKey);
				}
				break;
				
            case 0:
                break;

            default:
                printf("Invalid choice. Try again.");
        }

        printf("\n\n\n\n\n");
    }

    return 0;
}

void insertFront(struct list *L, int x)
{
	struct node *newNode=(struct node*)malloc(sizeof(struct node));
	
		if(L->count==0)
		{
			newNode->data = x;
			newNode->next = NULL;
			L->head = newNode;
			L->tail = newNode;
		}
		else
		{
			newNode->data = x;
			newNode->next = L->head;
			L->head = newNode;
		}
		
		L->count++;
}

void insertRear(struct list *L, int x)
{
	struct node *newNode=(struct node*)malloc(sizeof(struct node));
	
		if(L->count==0)
		{
			newNode->data = x;
			newNode->next = NULL;
			L->head = newNode;
			L->tail = newNode;
		}
		else
		{	
			newNode->data = x;
			L->tail->next = newNode;
			newNode->next = NULL;
			L->tail=newNode;
		}
		
		L->count++;
}

void insertAt(struct list *L, int x, int p)
{
	int c;	
	
		if(p==0)
		{
			insertFront(L, x);
	
		}
		else if(p==(L->count))
		{
			insertRear(L, x);

		}
		else if(p < 0 || p >= L->count)
		{
			printf("Invalid Position! Please try again.\n");
		}
		else
		{
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
				newNode->next = temp2;
				
				L->count++;
		}
		
}

void deleteFront(struct list *L)
{
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	
		if(L->count == 0)
		{
			printf("EMPTY LIST");
		}
		else
		{
			temp=L->head->next;
			free(L->head);
			L->head = temp;
			
			L->count--;
		}
}

void deleteRear(struct list *L)
{
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	
	temp= L->head;
	
		if(L->count == 0)
		{
			printf("EMPTY LIST");
		}
		else
		{
			while(temp->next!=L->tail)
			{
				temp = temp->next;
			}
			
				L->tail = temp;
				L->tail->next = NULL;
				
				L->count--;
		}
}

void deleteAt(struct list *L, int p)
{
	int c;
	
		if(p==0)
		{
			deleteFront(L);
	
		}
		else if(p==(L->count))
		{
			deleteRear(L);

		}
		else if(p < 0 || p >= L->count)
		{
			printf("Invalid Position! Please try again.\n");
		}
		else
		{
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
				
				temp1->next = temp2->next;
				temp2=NULL;
				free(temp2);
				
				L->count--;
		}
}
void displayAll(struct node *h)
{
	if(h==NULL){
		printf("EMPTY LIST");
	}else{
		while(h!=NULL)
		{
			printf("%d ", h->data);
			h = h->next;
		}
	}
	
	printf("\n");
	
	return;
}

int isEmpty(struct node *h){
	int count = 0;

	if(h==NULL){
		printf("STACK IS EMPTY");
	}else{
		while(h!=NULL){
        	count++;
        	h = h->next;
		}
			printf("%d node/s in stack", count);
    }
	
	printf("\n");
	
	return count;
}

int searchNode(struct list *h, int key){
    int index;
    struct node *curNode;

    index = 0;
    curNode = h;

    // Iterate till last element until key is not found
    while (curNode != NULL && curNode->data != key){
        index++;
        curNode = curNode->next;
    }


    return (curNode != NULL) ? index : -1;
}
