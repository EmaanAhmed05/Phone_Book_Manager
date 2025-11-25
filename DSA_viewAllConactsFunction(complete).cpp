#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<limits>
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



void displayLinkedList(){
if (head == NULL){
	cout<<"No Contacts Found!!!"<<endl;
	return;
}
Node* temp = head ;
cout<<"\nContact "<<endl;
do{
	cout<<"Name:  "<<temp->name<<endl;
	cout<<"Phone: "<<temp->phone_number<<endl;
	cout<<"Email: "<<temp->email<<endl;
	temp= temp->next;
	
}while(temp!= head);}

//this function will display ontacts in alphabatical order(recursion is used to traverse the tree in correct order)
void inorderBST(BSTNode* root){
	//will vist left tree first , then current node , then right subtree
	if(root!=NULL){
		inorderBST(root->left);
		cout<< "Name  :  "<<root->name<<endl;
		cout<< "Phone : "<<root->phone_number<<endl;
		cout<< "Email : "<<root->email<<endl;
		    
		    inorderBST(root->right);}
	
	}
//search contacts in Bst(recursion is also used here to search )
void searchContact(BSTNode* root , string name){
	if (root == NULL){
		cout<<"Contact not Found!!"<<endl;
		return;
	}
	if (name==root->name){//if current node is equall to the existing node in BST then
		cout<<"Contact Found!!"<<endl;
		cout<<"Name  : "<<root->name;
		cout<<"Phone : "<<root->phone_number;
		cout<<"Email : "<<root->email<<endl;
	}
	else if(name < root->name){
		searchContact(root->left,name);}
		else{
		searchContact(root->right,name);
	}
}

//Heap Function
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
void minimumHeap(int i){
	int l = left(i);
	int r = right(i);
	int smallest = i;
	//will check if left or right child is smaller then the current node
	if (l<heapSizeMin() && minHeap[l]< minHeap[smallest])
	smallest = l;
	if (r<heapSizeMin() && minHeap[r]< minHeap[smallest])
	smallest = r;
	
	//if smallest value is not thr parent then swap parent and child
	if(smallest != i){
		swap(minHeap[i], minHeap[smallest]);
		minimumHeap(smallest);
	}}
	
void insertMinHeap(string x){
	minHeap.push_back(x);
	int i = heapSizeMin()-1;

	while(i>0&& minHeap[parent(i)]>minHeap[i]){
		swap(minHeap[i], minHeap[parent(i)]);
		i = parent(i);
	}}
	
string deleteMin(){
	if(heapSizeMin()==0)
	return" ";
	string minVal = minHeap[0];
	minHeap[0] = minHeap.back();
	minHeap.pop_back();
	minimumHeap(0);
	return minVal;
}


//Max Heap
void maximumHeap(int i){
	int l = left(i);
	int r = right(i);
	int largest = i;
	
	if(l <heapSizeMax()&& maxHeap[l]< maxHeap[largest])
	largest = l;//if left child exists and left child is alphabetically bigger then update te largest
	if(r<heapSizeMax()&& maxHeap[r]< maxHeap[largest])
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
		
		insertMinHeap(n);
		insertMaxHeap(n);
	
}
void saveContactsToFile(){
	ofstream file("contacts.txt");//will open or creates the file 
	if(!file){
		cout<<"Error opening file to save contacts!!\n";
		return;
	}
	if(head == NULL) 
	return;//if emty , nothing to save
	
	Node* temp = head;
	do{
		file<<temp->name<<endl;
		file<<temp->phone_number<<endl;
		file<<temp->email<<endl;
		
		temp = temp->next;
	}while(temp!= head);
	file.close();
	cout<<"Contacts Saved To File Successfully!!\n";
}

void loadContactsFromFile(){
	ifstream file("contacts.txt");
	if(!file){
		cout<<"No contacts file found. Starting fresh.\n";
		return;
	}

string name, phone,email;
while(getline(file, name)&& getline(file, phone)&& getline(file,email)){
	addContact(name,phone,email);
}
file.close();
cout<<"Contacts loaded form file successfully!!\n";
}

//.............VIEW ALL CONTACTS FUNCTION (2)...........
void viewAllContacts(){
	if(head==NULL){
		cout<<"No Contacts Found!"<<endl;
	}
	else{
		Node* temp = head;
		cout<<"\n____Contacts(Linked List)____\n";
		do{
			cout<<"Name  : "<<temp->name<<endl;
			cout<<"Phone : "<<temp->phone_number<<endl;
			cout<<"Email : "<<temp->email<<endl;
			cout<<" ______---______\n";
			
			temp= temp->next;
		}
		while(temp!= head);
	}
	cout<<"\n____Contacts (BST_order)____\n";
	inorderBST(root);
}

int main(){
	//load contacts from the file 
	loadContactsFromFile();
	
	int choice;
	do{
	cout<<"\n____Menu____\n";
	cout<<"\n1. Add Contacts \n";
	cout<<"\n2. View(display) All Contacts \n";
	cout<<"\n3. Search Contacts \n";
	cout<<"\n4. Exit \n";
	cout<<"\n Enter Choice: \n";
	cin>>choice;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	
	if(choice == 1){
		string n,p,e;
	
	cout<<"Enter name: "<<endl;
	getline(cin,n);
	
	cout<<"Enter phone number: "<<endl;
	getline(cin, p);
	
	cout<<"Enter Email: "<<endl;
	getline(cin,e);
	
	addContact(n,p,e);	
	}
	else if(choice == 2){
		viewAllContacts();
	}
	else if(choice == 3){
		string searchName;
		cout<<"Enter name to Search: "<<endl;
		getline(cin, searchName);
		searchContact(root, searchName);
	}
	else if (choice == 4){
		cout<<"Existing program!!!\n"<<endl;
		saveContactsToFile();//will save contacts before exit
	}
	else{
		cout<<"Invalid Choice!!\n"<<endl;
	}}
	while(choice != 4);
	
	return 0 ;


}
