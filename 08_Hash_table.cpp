//IMPLEMENTING AN ELEMENTARY ENROLLMENT SYSTEM WITH HASH TABLE
#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <array>
#include <algorithm>

#define MAXHASH 1000

using namespace std;


//Using closed hash or open addressing over separate chaining or open hashing
//Collisions are dealt with by searching for another empty buckets within the hash table array itself.
//One key per bucket at most

//Reason for closed hash:
//-No size overhead apart from the hash table array.
//-Better memory locality and cache performance. All elements laid out linearly in memory.
//-Performs better than open hashing when the number of keys is known in advance and the churn is low.

enum SlotType {normalSlot, emptySlot, tombstone}; //declaring three types of closed hash

//Each record holds an integer key and a value of any type (hence the need for a template).
//The value type must be printable using << or code won't work.

//In this implementation, the value is stored directly in the record. If the value is large, it would be more
//efficient to have the records hold pointers to the values. In this case, we need to ensure that deep copies
//are made upon assignment, and that any values allocated properly deleted in the Record destructor.

//Slot Class
template <class T> class Slot{
private:
	int key;
	T value;
	SlotType type;

public:
	//The default constructor produces an empty record.
	//A possibly better way to keep track of tombstones and emtpy
	//records would be to use inheritance, similar to the way we
	//avoided having null pointers in leaf nodes for binary trees.
	Slot(){
		key = 0;
		type = emptySlot;
	}
	Slot(int newkey, T newvalue)
		: key(newkey), value(newvalue){
		type = normalSlot;
	}
	//Convert a record to a tombstone
	void kill(){
		type = tombstone;
	}
	//Get the integer key of a record
	int getKey() const{
		return key;
	}
	//Get the value of a record
	T getValue() const{
		return value;
	}
	//Check if a record is empty
	bool isEmpty() const{
		return(type == emptySlot);
	}
	//Check if a record is a normal record
	bool isNormal() const{
		return(type == normalSlot);
	}
	//Check if a record is a tombstone
	bool isTombstone() const{
		return (type == tombstone);
	}
	//Overload the << operator for printing records
	friend ostream& operator<<(ostream& os, const Slot& me){
		if (me.isTombstone())
			os << "<<Tombstone>>";
		else if (me.isEmpty())
			os << "<<Empty>>";
		else
			os << "Key: " << me.key << ", Value: " << me.value;
		return os;
	}
	~Slot(){
	}
};
//End of Slot Class Functions

//HashTable Class Functions
//This class is used as the main hash table. Uses class T so type of values it holds can be changed.
template <class T> class HashTable{
private:
	float itemCount = 0; 	//Keeps track of the items to see if its full
	int perm[MAXHASH];		//Creates a permutation array for the random probing

	
	unsigned int hash(unsigned int x){ 			//An integer hash function that accepts an integer hash key
		x = ((x >> 16) ^ x) * 0x45d9f3b; 		//algorithm that provides good statistical distribution
		x = ((x >> 16) ^ x) * 0x45d9f3b; 		//Each input bit affects each output bit with about 50% probability.
		x = (x >> 16) ^ x; 						//There are no collisions (each input results in a different output).
		return x % MAXHASH;
	}

public:
	Slot<T> arr[MAXHASH]; //This is where all of the values and key pairs are stored

	//Default constructor that fills the permutation array
	HashTable(){
		for (int i = 0; i < MAXHASH; i++){
			perm[i] = i;
		}
		random_shuffle(&perm[0], &perm[MAXHASH]); //calls the random algorithm to randomize whats in the array
	}

	//Inserts a key value pair and keeps track of collisions. Returns if its successful or not.
	bool insert(int key, T value, int& collisions){
		int spot = hash(key); //hashes the key for a spot on the array
		int home = spot;
		int inserted = 0, temp = 0;
		if (itemCount == 1000){ //if its full then return false
			return false;
		}
		while (!inserted){ //loop until you find where to put it
			if (arr[spot].isEmpty() || arr[spot].isTombstone()){ //if the slot type is empty or dead (practically empty), places it there
				arr[spot] = Slot<T>(key, value); //Creates a new slot to put there
				itemCount++; //increase the total items of the array
				return true;
			}else if (arr[spot].isNormal()){
				if (arr[spot].getKey() == key){ //If the slot is full or keys are equal then returns false
					return false;
				}else{ //random probing
					collisions++; //increases collisions
					spot = (home + perm[temp]) % MAXHASH; //this uses the permutation array for the random probing and mods it to loop around
					temp++; //Adds one to the slot of permutations incase we have to keep looking
				}
			}
		}
		return false;
	}

	//This removes something from the table with a given key. Returns if its successful or not.
	bool remove(int key){
		int spot = hash(key); //Gets a spot from the hash of the key
		int home = spot;
		int removed = 0, temp = 0;
		while (!removed){
			if (arr[spot].getKey() == key) { //If successfully found then deletion takes place
				arr[spot] = Slot<T>(); //Replace the spot with an empty slot
				arr[spot].kill(); //Call the kill function to replace the value type with a tombstone
				itemCount--; //Remove one from total count
				return true;
			}if (arr[spot].isTombstone() || arr[spot].isEmpty()){ //If the spot it finds is empty or a tombstone then that key doesn't exist
				return false;
			}if (arr[spot].isNormal()){ //If it does exist then we need to random probe
				if (temp == 1000){ //If it loops around 1000 times and doesn't find it then it for sure doesn't exist
					return false;
				}
				spot = (home + perm[temp]) % MAXHASH; //this uses the permutation array for the random probing and mods it to loop around
				temp++; //Adds one to the slot of permutations incase we have to keep looking
			}
		}
		return false;
	}

	//Locates the given key and sets it equal to a value to be able to return it. Returns if its successful or not.
	bool find(int key, T& value){
		int spot = hash(key); //Gets a spot from the hash of the key
		int home = spot;
		int found = 0, temp = 0;
		while (!found){
			if (arr[spot].getKey() == key){ //If the key is found then we are good and value is set to equal as indication
				value = arr[spot].getValue();
				return true;
			}if (arr[spot].isTombstone() || arr[spot].isEmpty()){ //If the spot we end up in is empty or is a tombstone then return false
				return false;
			}if (arr[spot].isNormal()){
				if (temp == 1000){ //If we have iterated 1000 times then record does not exist
					return false;
				}
				spot = (home + perm[temp]) % MAXHASH; //this uses the permutation array for the random probing and mods it to loop around
				temp++; //Adds one to the slot of permutations incase we have to keep looking
			}
		}
		return false;
	}

	//Overloads the << operator. Returns what we want to print
	friend ostream& operator<<(ostream& os, const HashTable& me){
		for (int i = 0; i < MAXHASH; i++){ //iterate over the table to print stuff out
			if (me.arr[i].isNormal()){ //As long as something is there we are good to print it out
				os << "Slot: " << i << " Key: " << me.arr[i].getKey(); //Prints out the basic info of what the slot and key is for the given table value
				os << me.arr[i].getValue(); //Calls the value overloaded print. This is used to keep things generic.
			}
		}
		return os;
	}
};
//End of HashTable Class Functions

//Student Function
class Student{
public:
	int studID;
	int age;
	int contact;
	string firstName;
	string lastName;
	string middleName;
	string gender;
	string address;

	//Default constructor
	Student(){}

	//This is a constructor for the student class to set all the values.
	Student(int newStudID, int newAge, int newContact, string newFirst, string newLast, string newMiddle, string newGender, string newAddress){
		studID = newStudID;
		age = newAge;
		firstName = newFirst;
		lastName = newLast;
		middleName = newMiddle;
		gender = newGender;
		contact = newContact;
		address = newAddress;
	}
	//This overloads the << operator. This is used to keep the overloaded << in hash table generic so it can be reused for different classes
	friend ostream& operator<<(ostream& os, const Student& me){
		os << " Student ID: " << me.studID << " First name: " << me.firstName << " Last name: " << me.lastName << " Middle name: " << me.middleName << " Age: " << me.age << " Gender: " << me.gender << " Contact: " << me.contact << " Address: " << me.address << endl; // prints out all of the info
		return os; //Returns it for printing
	}
};
//End of Student Class

//TEST FUNCTIONS:
//Test for filling the array with random values
void fillIt(HashTable<Student> &table){
	int col = 0, n1 = 10, n2 = 123456;
	for (int i = 0; i < 1000; i++){
		Student stud = Student(i, n1, n2, "A", "A", "A", "A", "A");
		table.insert(i, stud, col);
	}
}
//Test for checking insert, delete, and search instead of user inputs
void test(){
	HashTable<Student> h1;
	int a = 0;
	int testID = 834611;
	int testID2 = 834612;
	int failID = 834613;
	Student stud = Student(testID, 20, 4236313, "Peter", "Parker", "Benjamin", "Male", "New York");

	//Insert testing
	cout << "\nInsert test:" << endl;
	cout << "Should work since it doesn't exist." << endl;
	cout << h1.insert(testID, stud, a) << endl;
	cout << "Shouldn't work since it does exist." << endl;
	cout << h1.insert(testID, stud, a) << endl;
	cout << "Should work since it doesn't exist." << endl;
	cout << h1.insert(testID2, stud, a) << endl;
	cout << endl;

	//Search testing
	cout << "Search test:" << endl;
	Student value;
	cout << "Should work since it does exist." << endl;
	cout << h1.find(testID, value) << endl;
	cout << "Should work since it does exist." << endl;
	cout << h1.find(testID2, value) << endl;
	cout << "Shouldn't work since it doesn't exist." << endl;
	cout << h1.find(failID, value) << endl;
	cout << endl;

	//Delete testing
	cout << "Delete test:" << endl;
	cout << "Should work since it does exist." << endl;
	cout << h1.remove(testID) << endl;
	cout << "Should work since it does exist." << endl;
	cout << h1.remove(testID2) << endl;
	cout << "Shouldn't work since it doesn't exist." << endl;
	cout << h1.remove(failID) << endl;
	system("PAUSE"); //goes back to menu
}

//Main elementary enrollment system
int main(){
	HashTable<Student> table; //intializes the table for the class Student
	int choice, flag=1, value;
	while( flag == 1){ //If input is not within the choices, menu will keep displaying until user chooses a valid input or exits
		cout<<"\n============================================\n";
		cout<<"\tELEMENTARY ENROLLMENT SYSTEM\n";
		cout<<"============================================\n";
		cout<<"1. INSERT\n";
		cout<<"2. DELETE\n";
		cout<<"3. SEARCH\n";
		cout<<"4. DISPLAY\n";
		cout<<"5. TEST RUN - INSERT, DELETE, and SEARCH\n";
		cout<<"6. TEST RUN - TABLE FILLING\n";
		cout<<"0. Exit\n";
		cout<<"--------------------------------------------\n";
		cout<<"Enter your choice: ";
		cin>>choice;
		switch (choice){
			case 1:{ //Insert
				cout << "-----------Inserting a new record-----------" << endl;
				string last, first, middle, gender, address; //strings for inputs
				int studID, age, contact, collisions = 0; //int variables for inputs and collision variable
				cout << "Family name: ";
				cin >> last; //family name
				cout << "First name: ";
				cin >> first; //first name
				cout << "Middle name: ";
				cin >> middle; //middle name
				cout << "Student ID: ";
				cin >> studID; //student ID
				while (cin.fail()){ //Checks for valid int input
					cout << "Student ID entered was not valid." << endl;
					cin.clear(); //Empty cin
					cin.ignore(256,'\n');
					cout << "Re-enter Student ID: ";
					cin >> studID; //asks to re-enter a valid id
				}
				cout << "Age: ";
				cin >> age; //age
				while (cin.fail()){
					cout << "Age entered was not valid." << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cout << "Re-enter Age: ";
					cin >> age;
				}
				cout << "Gender: ";
				cin >> gender; //gender
				cout << "Contact Number: ";
				cin >> contact; //contact
				while (cin.fail()){ 
					cout << "Input entered was not valid." << endl;
					cin.clear(); 
					cin.ignore(256,'\n'); 
					cout << "Re-enter Contact number: ";
					cin >> contact; 
				}
				cout << "Address: ";
				cin >> address; //address
				Student student = Student(studID, age, contact, first, last, middle, gender, address); //Create a student with all of the given info using class student
				if (table.insert(studID, student, collisions)){
					cout << "Record inserted." << endl;
				}else{ //If it failed to insert then the record either already exists or the table is full
					cout << "Record failed to insert. Already exists or full table." << endl;
				}
				break;
			}
			case 2:{ //Delete
				int studID;
				cout << "--------------Deleting a record-------------" << endl;
				cout << "Enter Student ID to delete: "; //Asks for student ID to delete
				cin >> studID; 
				while (cin.fail()){
					cout << "Student ID entered was not valid." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Re-enter Student ID: ";
					cin >> studID;
				}
				cout << "Searching...";
				if (table.remove(studID)){ //If removal is successful, print successful deletion prompt
					cout << "Record found" << endl;
					cout << "Deleting...Complete" << endl;
				}else{ //If unsuccessful then file does not exist
					cout << "Record not found" << endl;
				}
				break;
			}
			case 3:{ //Search
				int studID;
				cout << "--------------Searching records-------------" << endl;
				Student returned; //value to pass if something is found that is equal to what is being searched
				cout << "Enter Student ID to search for: ";
				cin >> studID; //Input student ID
				while (cin.fail()){
					cout << "Student ID entered was not valid." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Re-enter Student ID: ";
					cin >> studID;
				}
				cout << "Searching...";
				if (table.find(studID, returned)){ //Successful search, print out the other details
					cout << "Record found" << endl;
					cout << "----------------------------" << endl;
					cout << "Last name: " << returned.lastName << endl;
					cout << "First name: " << returned.firstName << endl;
					cout << "Middle name: " << returned.middleName << endl;
					cout << "Age: " << returned.age << endl;
					cout << "Gender: " << returned.gender << endl;
					cout << "Student ID: " << returned.studID << endl;
					cout << "Contact Number: " << returned.contact << endl;
					cout << "Address: " << returned.address << endl;
					cout << "----------------------------" << endl;
				}else{
					cout << "Record not found" << endl;
				}
				break;
			}
			case 4:{ //Print List
				cout << "----------------Displaying...---------------" << endl;
				cout << table << endl;
				break;
			}
			case 5:{ //Test function for insert, delete, and search
				cout << "----------------Testing...------------------" << endl;
				test();
				break;
			}
			case 6:{ //Test function for filling table
				cout << "----------------Testing...------------------" << endl;
				fillIt(table);
				cout << table << endl;
				break;
			}
			case 0:{ //Exit
				cout << "-----------------Exiting...-----------------" << endl;
				flag = 0; //Breaks the while loop
				break;
			}
		cout << endl;
		}
	}
	return 0;
}
