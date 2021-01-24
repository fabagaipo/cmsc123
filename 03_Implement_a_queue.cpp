//QUEUE IMPLEMENTATION FOR SINGLY LINKED LIST AND CIRCULAR ARRAY 

#include <iostream>
using namespace std;

//for circular array
#define SIZE 5
int A[SIZE];
int f = -1;
int r = -1;

//for singly linked list
struct node {
   int data;
   struct node *next;
};
struct node* front = NULL;
struct node* rear = NULL;
struct node* temp;

void Insert(); //queue for singly linked list
void Delete(); //dequeue for singly linked list
void Display(); //display elements for singly linked list
bool isempty(); //checks if queue is empty for circular array
void enqueue (int); //enqueue for circular array
void dequeue(); //dequeue for circular array
void displayQueue(); //display elements for circular array

//Main Function
int main(){
 int choice, flag=1, value;
 while( flag == 1){
     cout<<"\n============================================\n";
     cout<<"IMPLEMENTING QUEUES\n";
     cout<<"============================================\n";
     cout<<"1. ENQUEUE - SINGLY LINKED LIST\n";
     cout<<"2. DEQUEUE - SINGLY LINKED LIST\n";
     cout<<"3. ENQUEUE - CIRCULAR ARRAY\n";
     cout<<"4. DEQUEUE - CIRCULAR ARRAY\n";
     cout<<"5. Display all the elements of queue - SINGLY LINKED LIST\n";
     cout<<"6. Display all the elements of queue - CIRCULAR ARRAY\n";
     cout<<"0. Exit\n";
     cout<<"--------------------------------------------\n";
     cout<<"Enter your choice: \n";
     cin>>choice;
  switch (choice){

      case 1: 
        Insert();
        break;

      case 2:
        Delete();
        break;

      case 3: 
        cout<<"Enter value to insert:\n";
        cin>>value;
        enqueue(value);
        break;

      case 4: 
        dequeue();
        break;

      case 5:
        Display();
        break;

      case 6: 
        displayQueue();
        break;

      case 7:
        flag = 0;
        break;
  }
 }

 return 0;
}

//SINGLY LINKED LIST FUNCTIONS:
void Insert() {
   int val;
   cout<<"Insert the element in queue: "<<endl;
   cin>>val;
   if (rear == NULL) {
      rear = (struct node *)malloc(sizeof(struct node));
      rear->next = NULL;
      rear->data = val;
      front = rear;
   }else{
      temp=(struct node *)malloc(sizeof(struct node));
      rear->next = temp;
      temp->data = val;
      temp->next = NULL;
      rear = temp;
   }
}
void Delete() {
   temp = front;
   if (front == NULL) {
      cout<<"Underflow"<<endl;
      return;
   }
   else
   if (temp->next != NULL) {
      temp = temp->next;
      cout<<"Element deleted from queue is: "<<front->data<<endl;
      free(front);
      front = temp;
   } else {
      cout<<"Element deleted from queue is: "<<front->data<<endl;
      free(front);
      front = NULL;
      rear = NULL;
   }
}
void Display() {
   temp = front;
   if ((front == NULL) && (rear == NULL)) {
      cout<<"Queue is empty"<<endl;
      return;
   }
   cout<<"Singly Linked List Queue elements are: ";
   while (temp != NULL) {
      cout<<temp->data<<" ";
      temp = temp->next;
   }
   cout<<endl;
}

//CIRCULAR ARRAY QUEUE FUNCTIONS:
//Function to check if queue is empty or not
bool isempty(){
 if(f == -1 && r == -1)
 return true;
 else
 return false;
}

//function to enter elements in queue
void enqueue (int value){
 //queue is full
 if((r + 1)%SIZE == f){
    cout<<"Queue is full \n";
 }else{
  //first element inserted
  if( f == -1)
     f = 0;
 //insert element at rear
    r = (r+1)%SIZE;
   A[r] = value;
 }
}

//function to remove element from queue
void dequeue(){
 if(isempty()){
  cout<<"Queue is empty\n";
 }else{
 //only one element
    if(f == r){
        cout<<"Element deleted from queue is: "<<A[f];
        f = r = -1;
    }else{
        cout<<"Element deleted from queue is: "<<A[f];
        f = (f + 1)%SIZE;
    }
  }
}

//function to display queue for singly linked list
void displayQueue(){
 if(isempty()){
  cout<<"Queue is empty\n";
 }else{
     cout<<"Circular array Queue elements are: ";
  int i;
  if( f <= r ){
   for( i=f ; i<= r ; i++)
   cout<<A[i]<<" ";
  }else{
   i=f;
   while( i < SIZE){
   cout<<A[i]<<" ";
   i++;
   }
   i=0;
   while( i <= r){
   cout<<A[i]<<" ";
   i++;
   }
  }
 }
}
