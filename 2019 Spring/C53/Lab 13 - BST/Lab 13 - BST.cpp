/*File Name:Lab 13 - BST.cpp
Author: Trinity Caitlin Atayan Belen
Description: The program stores students' information into a tree*/

#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int grade;
	string fullName;
	Node* left = nullptr; //Pointer to Left child node
	Node* right = nullptr; //Pointer to Right child node

	Node(string fN, int g) //Constructor
	{
		fullName = fN;
		grade = g;
	}

	void print() 
	{
		cout << "Student Info" << endl;
		cout << "Name: " << fullName << endl;
		cout << "Grade: " << grade << endl;
		cout << endl;
	}

};

class BST {
public:
	Node* root = nullptr; //Pointer to first node

	Node* search(string studentName) //searches for a student's name and then prints out the information of that student
	{
		Node* cur = root;
		while (cur != NULL) {
			if (studentName == cur->fullName) {
				cur->print();
				return cur;
			}
			else if (studentName < cur->fullName) {
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}
		}
		return NULL;
	}

	void insert(Node* newNode) //Inserts a node into the tree
	{
		int grade;
		if (root == NULL) {
			root = newNode;
			newNode->left = NULL;
			newNode->right = NULL;
		}

		else {
			Node*cur = root;
			while (cur != NULL) {
				if (newNode->grade < cur->grade) {
					if (cur->left == NULL) {
						cur->left = newNode;
						cur = NULL;
					}

					else {
						cur = cur->left;
					}
				}
				else {
					if (cur->right == NULL) {
						cur->right = newNode;
						cur = NULL;
					}
					else {
						cur = cur->right;
					}
				}
			}
		}
		newNode->left = NULL;
		newNode->right = NULL;
	}

	//traverses the tree from the left, then root, and then the right
	//it needs to be recursive to check the right and left sides of the nodes of the left side first
	//Then, it does the same to the right side after it prints the root once it finds the left side to be null
	void traverse(Node *cur)
	{
		if (cur == NULL) 
		{
			return;
		}

		traverse(cur->left);
		cur->print();
		traverse(cur->right);
	}

	void remove(string studentName) //removes a student from the tree
	{
		Node*par = NULL;
		Node*cur = root;
		while (cur != NULL) {
			if (cur->fullName == studentName) {
				if (!cur->left && !cur->right) {       
					if (!par) {
						root = NULL;
					}
					else if (par->left == cur) {
						par->left = NULL;
					}
					else
						par->right = NULL;
					}
				else if (cur->left && !cur->right) {  
					if (!par) {
						root = cur->left;
					}
					else if (par->left == cur) {
						par->left = cur->left;
					}
					else {
						par->right = cur->left;
					}
				}
				else if (!cur->left && cur->right) {    
					if (!par) {
						root = cur->right;
					}
					else if (par->left == cur) {
						par->left = cur->right;
					}
					else {
						par->right = cur->right;
					}
				}
				else {                                  
					Node* suc = cur->right;
					while (suc->left != NULL) {
						suc = suc->left;
						Node* successorData = suc;
						remove(studentName);
						cur = successorData;
					}
				}
				return;
			}
			else if (cur->fullName < studentName) {
				par = cur;
				cur = cur->right;
			}
			else {                    
				par = cur;
				cur = cur->left;
			}
		}
		return;
	}
};

int main() {
	BST student;

	Node* Bob= new Node("Bob", 87);
	student.insert(Bob);
	
	Node* Ted = new Node("Ted", 97);
	student.insert(Ted);

	Node* Andy = new Node("Andy", 63);
	student.insert(Andy);

	Node* Eva = new Node("Eva", 89);
	student.insert(Eva);

	Node* Sue = new Node("Sue", 96);
	student.insert(Sue);

	student.traverse(student.root);
	cout << "______________" << endl;
	student.search("Sue");
	cout << "______________" << endl;
	student.remove("Andy");
	student.traverse(student.root);

	system("pause");
}