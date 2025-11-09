#include<iostream>
#include<string>
using namespace std;

struct Node{
	string name ;
	string phone_number;
	string email;
	Node* next;
	Node* prev;
};

Node* head = NULL;
//....1st function
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
		
	}
	cout<<"Contacts Added Successfully!!!"<<endl;
	
}
