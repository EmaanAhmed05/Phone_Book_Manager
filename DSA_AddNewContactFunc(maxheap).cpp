#include<iostream>
#include<vector>
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
//inserting contacst into BST...(recursion is used here..recursive call to left or right to add a new contacr in correct orderor position )
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

//this function will display ontacts in alphabatical order(recursion is used to traverse the tree in correct order)
void inorderBST(BSTNode* root){
	//will vist left tree first , then current node , then right subtree
	if(root!=NULL){
		inorderBST(root->left);
		cout<< "Name:"<<root->name
		    << "Phone:"<<root->phone_number
		    << "Email:"<<root->email<<endl;
		    
		    inorderBST(root->right);}
	
	}
//search contacts in Bst(recursion is also used here to search )
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

//miniHeap and MaxiHeap Function
vector<string> minHeap;//this will give us he alphabetically first contact quickly
vector<string> maxHeap;

int parent(int i){
return(i-1)/2;//gives index of parent of node 
 }
int left(int i){
return 2*i+1;//gives inddex of left child of node
}
int right(int i){
return 2*i+2;//gives index of right child of node
}


     int heapSizeMin(){
              return minHeap.size();
                   }
     int heapSizeMax(){
     	return maxHeap.size();
	 }              

//Mini Heap
void minimumHeap(int i)
 {
	int l = left(i);
	int r = right(i);
	int smallest = i;
	//will check if left or right child is smaller then the current node
	if (l<heapSizeMin() && minHeap[1]< minHeap[smallest])
	smallest = 1;
	if (r<heapSizeMin() && minHeap[r]< minHeap[smallest])
	smallest = 1;
	
	//if smallest value is not thr parent then swap parent and child
	if(smallest != i){
		swap(minHeap[i], minHeap[smallest]);
		minimumHeap(smallest);
	}	
}
void insertMinHeap(string x){
	minHeap.push_back(x);
	int i = heapSizeMin()-1;
	
	while(i>0&& minHeap[parent(i)]<minHeap[i]){
		swap(minHeap[i], minHeap[parent(i)]);
		i = parent(i);
	}
}
string deleteMin(){
	if(heapSizeMin()==0)
	return" ";
	string minVal = minHeap[0];
	minHeap[0] = minHeap.back();
	minHeap.pop_back();
	minimumHeap(0);
	return minVal;
}

//Maximum Heap
void maximumHeap(int i){
	int l = left(i);
	int r = left(i);
	int largest = i;
	
	if(l<heapSizeMax()&& maxHeap[l]> maxHeap[largest])
	largest = l;//if left child exists and left child is alphabetically bigger then update te largest
	if(r<heapSizeMax()&& maxHeap[r]> maxHeap[largest])
	largest = r;//same logic for right
	if(largest !=i){//if parent is NOT largest then swap the parent with largest
		swap(maxHeap[i],maxHeap[largest]);
		maximumHeap(largest);
	}	
}
void insertMaxHeap(string x){
	maxHeap.push_back(x);
	int i = heapSizeMax()-1;
	
while(i>0 && maxHeap[parent(i)]<maxHeap[i]){
	swap(maxHeap[i],maxHeap[parent(i)]);
	i = parent(i);
}
}
string deleteMax(){
	if(heapSizeMax()==0)
	return " ";
	string maxVal= maxHeap[0];
	maxHeap[0] = maxHeap.back();
	maxHeap.pop_back();
	maximumHeap(0);
	return maxVal;
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
	       