//Implementation of Pre-order Traversal 
#include <bits/stdc++.h> 

using namespace std; 

//Structure of node with pointers to left and right.
struct node{
    int data;
    struct node* left; //for left;
    struct node* right; //for right;
    node(int value){ //create a node using new node;
        data=value;
        left=NULL;
        right=NULL;
    }
};

//Function to print preorder of the given tree 
void preOrder(node* root){
    if(root==NULL){
        return;
    }
    cout<<root->data<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

int main(){ 
    //constructing tree
    node* root= new node(1); //root node of tree;
    root->left= new node(2);
    root->right= new node(3);
    root->left->left= new node(4);
    root->left->right= new node(5);
    root->right->left= new node(6);
    cout<<"Pre-order traversal: ";
    preOrder(root);
    return 0; 
}
