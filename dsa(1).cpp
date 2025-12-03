#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<limits>
#include<stack>
#include<algorithm>
#include<cctype>
#include <unordered_map>
#include <queue>
using namespace std;
    queue<string> reminders;
    unordered_map<string, int> callCount;      // store number of calls per contact
    priority_queue<pair<int,string>> callHeap; // max heap (count, name)
//trim function
string trim(const string str){
	string s = str;
	s.erase(s.begin(),find_if(s.begin(),s.end(),[](unsigned char ch){return !isspace(ch);}));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch){ return !isspace(ch); }).base(), s.end());
	return s;
}
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

void addContact(string n, string number, string e, bool showMessage = true){
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

    if(showMessage){
        cout<<"Contacts Added Successfully!!!"<<endl;
        cout<<"Contact Added to  BST successfully!!!"<<endl;
    }

    // Add to BST and heaps
    root = insertBST(root, n, number, e);
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
        cout<<"Phone Book Initialized\n";
        return;
    }

    string name, phone, email;
    bool anyLoaded = false; // Track if any contact loaded
    while(getline(file, name) && getline(file, phone) && getline(file, email)){
        addContact(name, phone, email, false); // Don't show message for file loading
        anyLoaded = true;
    }

    file.close();

    if(anyLoaded){
        cout<<"Contacts loaded from file successfully!!\n";
    }
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
//..............EDIT CONTACTS FUNCTION(3)...............

stack<Node> undoStack;
Node* searchLinkedList(Node* head, const string& key)
{
    if (!head) return nullptr;
    
    string searchKey = trim(key);
    Node* temp = head;
    do {
        if (trim(temp->name) == searchKey || trim(temp->phone_number) == searchKey)
            return temp;
        temp = temp->next;
    } while (temp != head);

    return nullptr;
}
BSTNode* findMin(BSTNode* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

BSTNode* deleteFromBST(BSTNode* root, string key) {
    if (root == NULL) return root;

    if (key < root->name)
        root->left = deleteFromBST(root->left, key);

    else if (key > root->name)
        root->right = deleteFromBST(root->right, key);

    else {
        // Case 1 No child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }

        // Case 2 One child
        else if (root->left == NULL) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3 Two children
        BSTNode* temp = findMin(root->right);
        root->name = temp->name;
        root->phone_number = temp->phone_number;
        root->email = temp->email;

        root->right = deleteFromBST(root->right, temp->name);
    }

    return root;
}


void editContact() {
    string key;
    cout << "Enter name or number of contact to edit\n";
    getline(cin, key);

    Node* temp = searchLinkedList(head, key);

    if (!temp) {
        cout << "Contact not Found!!\n";
        return;
    }

    // save old name before modifying
    string oldName = temp->name;

    undoStack.push(*temp);

    cout << "\n What do you want to update?\n";
    cout << "1. Name\n";
    cout << "2. Number\n";
    cout << "3. Email\n";
    cout << "4. All Fields\n";
    cout << " Enter Choice\n";

    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string newName, newNumber, newEmail;

    switch (choice) {
        case 1:
            cout << "Enter new Name: ";
            getline(cin, newName);
            if (!newName.empty()) temp->name = newName;
            break;

        case 2:
            cout << "Enter new Number: ";
            getline(cin, newNumber);
            if (!newNumber.empty()) temp->phone_number = newNumber;
            break;

        case 3:
            cout << "Enter new Email: ";
            getline(cin, newEmail);
            if (!newEmail.empty()) temp->email = newEmail;
            break;

        case 4:
            cout << "Enter new Name: ";
            getline(cin, newName);
            if (!newName.empty()) temp->name = newName;

            cout << "Enter new Number: ";
            getline(cin, newNumber);
            if (!newNumber.empty()) temp->phone_number = newNumber;

            cout << "Enter new Email: ";
            getline(cin, newEmail);
            if (!newEmail.empty()) temp->email = newEmail;
            break;

        default:
            cout << "Invalid Choice!!!\n";
            return;
    }

    // remove old records from bst
    root = deleteFromBST(root, oldName);

    // Insert updated record
    root = insertBST(root, temp->name, temp->phone_number, temp->email);

    saveContactsToFile();
    cout << "Contact updated successfully!!!\n";
}
//..................DELETE CONTACT FUNCTION (4)....................

void deleteContact(){
    string key;
    cout << "Enter name or number of contact to delete:\n";
    getline(cin, key);

    // Find contact in Linked List
    Node* temp = searchLinkedList(head, key);

    if (!temp){
        cout << "Contact not found!\n";
        return;
    }
 // Save old data for undo
    undoStack.push(*temp);

    string delName = temp->name;

    // Removing from Linked List
    if (temp->next == temp && temp->prev == temp){
        head = NULL; 
    }
    else{
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        if (temp == head){
            head = temp->next;
        }
    }

    delete temp;
 // Removing from BST also
    root = deleteFromBST(root, delName);
 
    // Update file after deletion
    saveContactsToFile();

    cout << "Contact deleted successfully!\n";
}
//...................UNDO LAST OPERATION (5).....................

void undoLastOperation() {

    if (undoStack.empty()) {
        cout << "Nothing to undo!\n";
        return;
    }

    // Get last saved state
    Node last = undoStack.top();
    undoStack.pop();

    // Check if contact exists now ? means the last op was EDiT
    Node* found = searchLinkedList(head, last.name);

    if (found) {
        // Restore the old values (undo edit)
        found->name = last.name;
        found->phone_number = last.phone_number;
        found->email = last.email;

        // Update BST (remove new one ? insert old one)
        root = deleteFromBST(root, found->name);
        root = insertBST(root, last.name, last.phone_number, last.email);

        saveContactsToFile();
        cout << "Undo successful! (Edit restored)\n";
        return;
    }
    
    // If not found ? last operation was DELETE ? restore the deleted contact
    addContact(last.name, last.phone_number, last.email, false);
    saveContactsToFile();
    cout << "Undo successful! (Contact restored)\n";
}
// ===== REMINDER SYSTEM =====
void showReminderMenu() {
    cout << "\n=== Reminder System ===" << endl;
    cout << "1. Add New Reminder" << endl;
    cout << "2. View Next Reminder" << endl;
    cout << "3. Remove Current Reminder" << endl;
    cout << "4. View All Reminders" << endl;
    cout << "5. Exit Reminder Menu" << endl;
    cout << "Enter your choice: ";
}

void reminderSystem() {
    int choice;
    string reminder;

    do {
        showReminderMenu();
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                cout << "Enter reminder (Format: Name - Event - Date): ";
                getline(cin, reminder);
                reminders.push(reminder);
                cout << "Reminder added successfully!" << endl;
                break;

            case 2:
                if (!reminders.empty()) {
                    cout << "\nNext Reminder: " << reminders.front() << endl;
                } else {
                    cout << "No reminders available!" << endl;
                }
                break;

            case 3:
                if (!reminders.empty()) {
                    cout << "Removed: " << reminders.front() << endl;
                    reminders.pop();
                } else {
                    cout << "No reminders to remove!" << endl;
                }
                break;

            case 4:
                if (reminders.empty()) {
                    cout << "No reminders available!" << endl;
                } else {
                    cout << "\n=== All Reminders ===" << endl;
                    queue<string> temp = reminders;
                    int count = 1;
                    while (!temp.empty()) {
                        cout << count << ". " << temp.front() << endl;
                        temp.pop();
                        count++;
                    }
                }
                break;

            case 5:
                cout << "Returning to Main Menu..." << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);
}
// call and display top contacts
void callAContact() {
    if (head == NULL) {
        cout << "No contacts available to call!\n";
        return;
    }

    string name;
    cout << "Enter contact name to call: ";
    getline(cin, name);

    // search in Linked List
    Node* temp = searchLinkedList(head, name);
    if (!temp) {
        cout << "Contact not found!\n";
        return;
    }

    // increase count
    callCount[temp->name]++;

    // push into max heap
    callHeap.push({callCount[temp->name], temp->name});

    cout << "Called " << temp->name 
         << " (Total calls = " << callCount[temp->name] << ")\n";
}

void displayTopContacts() {
    if (callHeap.empty()) {
        cout << "No calls made yet!\n";
        return;
    }

    // make a temporary copy (so original heap stays unchanged)
    priority_queue<pair<int,string>> temp = callHeap;

    cout << "\n===== TOP CONTACTS (MOST CALLED) =====\n";

    while (!temp.empty()) {
        auto top = temp.top();
        temp.pop();
        cout << top.second << " ? " << top.first << " calls\n";
    }
}
int main(){
	//load contacts from the file 
	loadContactsFromFile();
	
	int choice;
	do{
	cout<<"\n____Menu____\n";
	cout<<"\n1. Add Contacts \n";
	cout<<"\n2. View All Contacts \n";
	cout<<"\n3. Search Contacts \n";
	cout<<"\n4. Edit Contact \n";
	cout<<"\n5. Delete Contact \n";
	cout<<"\n6. Undo last Operation \n";
	cout<<"\n7. Display Contacts Alphabetically \n";
	cout<<"\n8. Reminder System \n";
	cout<<"\n9. Call a contact \n";
	cout<<"\n10. Display top call contacts \n";
	cout<<"\n11. Exit \n";
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
	
	addContact(n,p,e,true);	
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
		editContact();
	}
	else if (choice == 5){
		deleteContact();
	}
	else if(choice == 6){
		undoLastOperation();
	}
	else if(choice == 7){
    if(root == NULL){
        cout << "No contacts available!\n";
    } else {
        cout << "\n--- Contacts (Alphabetical Order) ---\n";
        inorderBST(root);
        cout << "--------------------------------------\n";
    }
    }
    else if (choice == 8) {
    reminderSystem();
    }

	else if (choice == 9) {
        callAContact();
    }
	else if (choice == 10){	
		displayTopContacts();
	}
    else if (choice == 11) {
        cout<<"Existing program!!!\n"<<endl;
		saveContactsToFile();//will save contacts before exit
    }

	else{
		cout<<"Invalid Choice!!\n"<<endl;
	}}
	while(choice != 10);
	
	return 0 ;

}
