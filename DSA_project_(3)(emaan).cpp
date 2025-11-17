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
//inserting contacst into BST
BSTNode* insertBST(BSTNode* root, string n,string number, string e ){
	if(root == NULL){
		return createBSTNode(n,number,e);
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
		root = insertBST(root , n,number,e);
		cout<<"Contact Added to  BST successfully!!!"<<endl;
	
}

void displayLnkedList(){
if (head == NULL){
	cout<<"No Contacts Found!!!"<<endl;
	return;
}
Node* temp = head ;
cout<<"\nContact "<<endl;
do{
	cout<<"Name"<<temp->name;
	cout<<"Phone"<<temp->phone_number;
	cout<<"Email"<<temp->email;
	temp= temp->next;
	
}while(temp!= head);}

//this function will display ontacts in alphabatical order
void inorderBST(BSTNode* root){
	//will vist left tree first , then current node , then right subtree
	if(root!=NULL){
		inorderBST(root->left);
		cout<< "Name:"<<root->name
		    << "Phone:"<<root->phone_number
		    << "Email:"<<root->email<<endl;
		    
		    inorderBST(root->right);}
	
	}
//search contacts in Bst
void searchContact(BSTNode* root , string name){
	if (root == NULL){
		cout<<"Contact not Found!!"<<endl;
	}
	if (name==root->name){//if current node is equall to the existing node in BST then
		cout<<"Contact Found!!"<<endl;
		cout<<"Name: "<<root->name;
		cout<<"Phone Number: "<<root->phone_number;
		cout<<"Email: "<<root->email<<endl;
	}
	else if(name < root->name){
		searchContact(root->left,name);}
		else{
		searchContact(root->right,name);
	}
}

int main(){
	//add some contacts to check 
	addContact("Ali","   00000000000 ","ali@example.com");
	addContact("Sara","  00000000000 ","sara@example.com");
	addContact("Ahmed"," 00000000000 ","ahmed@example.com");
	
	void displayLinkedList();
	
	cout<<"\n Contacts (BST):\n"<<endl;
	inorderBST(root);
	
	cout<<"\n Searcing for 'Sara' : \n";
	searchContact(root, "Sara");
	return 0 ;
}
	       