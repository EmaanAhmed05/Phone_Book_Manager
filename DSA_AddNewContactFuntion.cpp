#include<iostream>
#include<string>
using namespace std;
//...linked list node
struct Node{
	string name ;
	string phone_number;
	string email;
	Node* next;
	Node* prev;
};

Node* head = NULL;

//...BST Node
struct BSTNode{
	string name ;
	string phone_number;
	string email;
	BSTNode* left;
	BSTNode* right;
	
};
//...root pointer 
BSTNode* root = NULL;

BSTNode* createBSTNode(string n, string number, string e){
	BSTNode* newNode = new BSTNode();
	newNode->name = n;
	newNode->phone_number = number;
	newNode->email = e;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

BSTNode* insertBST(BSTNode* root, string n,string number, string e ){
	if(root == NULL){
		return createBST(n,number,e);
	}
	if(n<root->name)
		root->left = insertBST(root->left,n,number,e);
	else if(n>root->name)
	root->right = insertBST(root->right, n , number ,e);
	
	else
	cout<<"Duplicate contact name not allowed!!!"<<endl;
	
	return root;
	
}


void addContact( string n, string number, string e){
	Node* newNode = new Node();
	newNode->name = n;
	newNode->phone_number = number;
	newNode->email = e;
	
	if (head == NULL){
	head = newNode;
	newNode->next = head;
	newNode->prev = head;
	}
	else{
		Node* last = head->prev;
		newNode->next = head;
		newNode->prev = last;
		last->next = newNode;
		head->prev = newNode;
	}
	cout<<"Contacts Added Successfully!!!"<<endl;
	
	// when u add a contact , first it will added in linked list and then in BSTNode
		root = insertBSTNode(root , n,e);
		cout<<"Contact Added to  BST successfully!!!"<<endl;
	
}
if (head == NULL){
	cout<<"No Contacts Found!!!"<<endl;
	return;
}
Node* temp = head ;
cout<<"\nContact "<<endl;
do{
	cout<<"Name"
}
	       

