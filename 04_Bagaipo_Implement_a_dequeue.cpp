//DEQUEUE IMPLEMENTATION FOR DOUBLY LINKED LIST AND CIRCULAR ARRAY 

#include <iostream>
using namespace std;

//for circular array
#define SIZE 5
int A[SIZE];
int f = -1;
int r = -1;

//Node of a doubly linked list 
struct Node{ 
    int data; 
    Node *prev, *next; 
    // Function to get a new node 
    static Node* getnode(int data) { 
        Node* newNode = (Node*)malloc(sizeof(Node)); 
        newNode->data = data; 
        newNode->prev = newNode->next = NULL; 
        return newNode; 
    } 
}; 
  
//structure for DLL
class doubly{ 
    Node* front; 
    Node* rear; 
    Node* temp;
    int Size;
  
public: 
    doubly(){ 
        front = rear = NULL;
        Size = 0; 
    } 
  
    // Function Calls for DLL
    void insertFront(int data); //enqueues element at front
    void deleteFront(); //dequeues element at front
    void Display(); //displays list of elements in queue
    int getFront(); //shows front element in queue
    int sizeDLL(); //returns the number of elements in queue
    bool isEmpty(); //checks if dll queue is empty
};

//DOUBLY LINKED LIST FUNCTIONS:
// Function to return the number of elements in the queue 
int doubly::sizeDLL(){ 
    return Size; 
} 

// Function to check whether queue is empty or not 
bool doubly::isEmpty(){ 
    return (front == NULL); 
} 
   
// Function to enqueue at the front end 
void doubly::insertFront(int data){ 
    Node* newNode = Node::getnode(data); 
    // If true then new element cannot be added 
    // and it is an 'Overflow' condition 
    if (newNode == NULL){
        cout << "Queue is full\n"; 
    }else{ 
        // If dequeue is empty 
        if (front == NULL){ 
            rear = front = newNode; 
  
        // Inserts node at the front end 
        }else{ 
            newNode->next = front; 
            front->prev = newNode; 
            front = newNode; 
        }
        Size++; 
    } 
} 
  
// Function to delete the element from the front end 
void doubly::deleteFront(){ 
    // If dequeue is empty then return empty 
    if (isEmpty()){
        cout << "Queue is empty\n"; 
  
    // Deletes the node from the front end and makes 
    // the adjustment in the links 
    }else{ 
        Node* temp = front; 
        front = front->next; 
  
        // If only one element was present 
        if (front == NULL){
            rear = NULL; 
        }else{
            front->prev = NULL; 
        free(temp);
        }
        Size--;
    } 
} 

// Function to return the element at the front
int doubly::getFront(){ 
    if (isEmpty()){
        cout<<"Queue is empty";
    }else{
    cout<<"Element at front is: "<<front->data;
    }
}

void doubly::Display() {
   temp = front;
   if ((front == NULL) && (rear == NULL)) {
      cout<<"Queue is empty"<<endl;
      return;
   }
   cout<<"Doubly Linked List Queue elements are: ";
   while (temp != NULL) {
      cout<<temp->data<<" ";
      temp = temp->next;
   }
   cout<<endl;
}

//structure for circular array
class circular{
    int count;

public:
    circular(){
        count = 0;
    }
    //FUNCTION CALLS FOR CIRCULAR ARRAY:
    bool isempty(); //checks if queue is empty for circular array
    void enqueue (int); //enqueue for circular array
    void dequeue(); //dequeue for circular array
    void displayQueue(); //display elements for circular array
    void showfront(); //shows the front of queue for circular array
    int counter(); //counts size of queue for circular array
};


//CIRCULAR ARRAY QUEUE FUNCTIONS:
//Function to check if queue is empty or not
bool circular::isempty(){
    if(f == -1 && r == -1){
        return true;
    }else{
        return false;
    }
}

//function to enter elements in queue
void circular::enqueue (int value){
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
 count++;
}

//function to remove element from queue
void circular::dequeue(){
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
  count--;
}

//function to display queue for circular array
void circular::displayQueue(){
 if(isempty()){
  cout<<"Queue is empty";
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

//function to count nummber of elements in queue for circular array
int circular::counter(){
    return count;
}

//function to show front element in queue for circular array
void circular::showfront(){
 if(isempty()){
 cout<<"Queue is empty\n";
 }else{
 cout<<"Element at front is: "<<A[f];
 }
}

//Main Function
int main(){
 int choice, flag=1, value;
 doubly dll;
 circular cc;

 while(flag == 1){
     cout<<"\n============================================\n";
     cout<<"\tIMPLEMENTING DEQUEUES\n";
     cout<<"============================================\n";
     cout<<"1. ENQUEUE - DOUBLY LINKED LIST\n";
     cout<<"2. DEQUEUE - DOUBLY LINKED LIST\n";
     cout<<"3. SHOW FRONT - DOUBLY LINKED LIST\n";
     cout<<"4. IF EMPTY - DOUBLY LINKED LIST\n";
     cout<<"5. ENQUEUE - CIRCULAR ARRAY\n";
     cout<<"6. DEQUEUE - CIRCULAR ARRAY\n";
     cout<<"7. SHOW FRONT - CIRCULAR ARRAY\n";
     cout<<"8. IF EMPTY - CIRCULAR ARRAY\n";
     cout<<"9. DISPLAY - DOUBLY LINKED LIST\n";
     cout<<"10. DISPLAY - CIRCULAR ARRAY\n";
     cout<<"11. SIZE OF QUEUE - DOUBLY LINKED LIST ARRAY\n";
     cout<<"12. SIZE OF QUEUE - CIRCULAR ARRAY\n";
     cout<<"0. EXIT\n";
     cout<<"--------------------------------------------\n";
     cout<<"Enter your choice: \n";
     cin>>choice;

  switch(choice){

      case 1: 
        cout<<"Enter value to enqueue: \n";
        cin>>value;
        dll.insertFront(value);
        break;

      case 2:
        dll.deleteFront();
        break;

      case 3:
        dll.getFront(); 
        break;

      case 4:
        if(dll.isEmpty()){
            cout<<"Doubly Linked List Queue is empty";
        }else{
            cout<<"Doubly Linked List Queue has elements";
        }
        break;

      case 5:
        cout<<"Enter value to enqueue: \n";
        cin>>value;
        cc.enqueue(value);
        break;

      case 6: 
        cc.dequeue();
        break;

      case 7:
        cc.showfront();
        break;

      case 8:
        if (cc.isempty()){
            cout<<"Circular Array Queue is empty";
        }else{
            cout<<"Circular Array Queue has elements";
        }
        break;

      case 9:
        dll.Display();
        break;

      case 10: 
        cc.displayQueue();
        break;

      case 11:
        cout<<"Number of elements in DLL queue: "<<dll.sizeDLL()<<endl;
        break;

      case 12:
        cout<<"Number of elements in Circular Array queue: "<<cc.counter();
        break;

      case 0:
        flag = 0;
        break;
  }
 }

 return 0;
}

