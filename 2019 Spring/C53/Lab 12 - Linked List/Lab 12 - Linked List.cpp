/*File Name: Lab 12 - Linked List.cpp
Author: Trinity Caitlin Atayan Belen
Description: This program will created a to-do list that saves it using a double linked list and its operations.*/
#include<iostream>
#include<string>
using namespace std;

class Node {
public:
	string data; //stores a string
	Node* next = nullptr; //pointer to next node
	Node* previous = nullptr; //pointer to previous node

	//Constructor for creating new nodes in the int main
	Node (string d) {
		data = d;
	}
};

class List {
private:
	Node* head = nullptr; //pointer to first node
	Node* tail = nullptr; //pointer to last Node
public:

	//Appends a node
	void listAppend(Node* newNode) {
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}

		else {
			tail -> next = newNode;
			newNode -> previous = tail;
			tail = newNode;
		}
	}

	//Prepends (add to beginning) a node
	void listPrepend(Node* newNode) {
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}

		else {
			newNode -> next = head;
			head -> previous = newNode;
			head = newNode;
		}

	}

	//Inserts a node after another one
	void listInsertAfter(Node* curNode, Node* newNode) {
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}

		else if (curNode == tail) {
			tail->next = newNode;
				newNode->previous = tail;
				tail = newNode;
		}

		else {
			Node* sucNode = curNode->next;
			newNode->next = sucNode;
			newNode->previous = curNode;
			curNode->next = newNode;
			sucNode->previous = newNode;
		}
	}

	//Removes a node
	void listRemove(Node* curNode) {
		Node* sucNode = curNode->next;
		Node* predNode = curNode->previous;

		if (sucNode != NULL) {
			sucNode->previous = predNode;
		}

		if (predNode != NULL) {
			predNode->next = sucNode;
		}
		if (curNode == head) {
			head = sucNode;
		}
		if (curNode == tail) {
			tail = predNode;
		}

	}

	//Traverses the list
	void listTraverse() {
		Node* curNode = head;
		while (curNode != NULL) {
			cout << curNode->data << endl;
			curNode = curNode->next;
		}
	}

	//Traveses the list in reverse order
	void listTraverseReverse() {
		Node* curNode = tail;
		while (curNode != NULL) {
			cout << curNode->data << endl;
			curNode = curNode->previous;
		}
	}

	//Extra Credit
	//Insertion sorts the list
	void listInsertionSort() {
		Node* curNode = head->next;
		while (curNode != NULL) {
			Node* nextNode = curNode->next;
			Node* searchNode = curNode->previous;
				while (searchNode != NULL && searchNode->data > curNode->data) {
					searchNode = searchNode->previous;
					listRemove(curNode);
					if (searchNode == NULL) {
						curNode->previous = NULL;
						listPrepend(curNode);
						}
					else {
						listInsertAfter(searchNode, curNode);
					}
				}
				curNode = nextNode;
		}
	}
};
int main() {
	List varia; //List variable

	//Item number #1
	Node* teeth = new Node("Brush your teeth!");
	varia.listAppend(teeth);

	//Item number #2
	Node* face = new Node("Wash your face!");
	varia.listAppend(face);

	//Item number #3
	Node* eat = new Node("Eat breakfast!");
	varia.listAppend(eat);

	//Item number #4
	Node* school = new Node("Go to school!");
	varia.listAppend(school);

	//"wakeup" will be added to the beginning of the list
	Node* wakeup = new Node("Wake up!");
	varia.listPrepend(wakeup);

	//Prints in the following order so far
	varia.listTraverse();
	cout << endl;

	//Inserts "makebed" after "washface"
	Node* makebed = new Node("Make your bed!");
	varia.listInsertAfter(face, makebed);
	
	//Prints in reverse order
	varia.listTraverseReverse();
	cout << endl;

	//Extra Credit
	varia.listInsertionSort();
	varia.listTraverse();
	system("pause");
}