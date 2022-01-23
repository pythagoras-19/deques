/*
Notes:
1. When doing the first add ( pushFront() or pushBack() )to either the bottom or top make sure to set the top->value and bottom->value to the value, separately.
*/
#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include<string.h>
#include <vector>
using namespace std;
struct Node
{
    int value;
    Node* next;
    Node* prev;
};
//DEQUES
int getLengthOfDeque(Node *&top, Node *&bottom)
{
	std::cout << "getLengthOfDeque() called\n";
	Node* current = new Node;
	if (!top)
	{
		std::cout << "It is now an empty deque.\n";
		return 0;
	}
	int i = 0;
	for (current = top; current; current = current->next, i++); // missing semicolon here caused weird bug that was hard to solve!
	//std::cout << "i: " << i << std::endl;
	delete current;
	return i;
	
}
void printDeque(Node *&top, Node *&bottom)
{
	std::cout << "In printDeque()\n";
	Node* current = top;
	for(; current; current = current->next) 
	{
		std::cout << current->value << std::endl;
	}
	std::cout << "bottom->value: " << bottom->value << std::endl;
	delete current;
}
void pushFront(Node *&top, Node *& bottom, int value)
{
	std::cout << "pushFront() called\n";
	Node* newNode = new Node;
	Node* temp = new Node;
	if (!top)//if top is NULL
	{
		top = newNode;        //top is now a new node
		bottom = newNode;     //bottom is now a new node
		//bottom = top; 
		top->value = value;   //top = value passed in function header
		bottom->value = value;//bottom = value passed in function header
		top->prev = NULL;     //since there are no other nodes in our deque we set prev pointer to null
		top->next = NULL;     ////since there are no other nodes in our deque we set next pointer to null
	}
	else
	{
		std::cout << top->value << std::endl;
		temp = top; // temp node = previous top
		top = newNode; // give top a new node 
		top->value = value; // new top node gets new value
		top->prev = NULL; // 0
		top->next = temp; // top->next = previous top node
		bottom = bottom; // bottom stays bottom (1)
	}
}
void pushBack(Node *&top, Node *&bottom, int value)
{
	std::cout << "pushBack() called\n";
	Node* newNode = new Node;
	Node* temp = new Node;
	if(!bottom) // empty deque (no elements)
	{
		bottom = newNode;        // bottom is now a new node
		top = newNode;           // top is now a new node
		top->value = value;      // top = value passed in function header
		bottom->value = value;   // bottom = value passed function header
		bottom->prev = NULL;     // since this is the only node in our deque prev pointer will be null
		bottom->next = NULL;     // since this is the only node in our deque next pointer will be null
	}
	else
	{
		std::cout << "bottom value was : " << bottom->value << std::endl;
		temp->value = value; // temp->value = 13
		temp->prev = bottom; // temp->prev = 1
		temp->next = NULL;   // temp->next = null
		bottom->next = temp; // bottom->next = 13
		bottom = temp;       // bottom = 13
		std::cout << "new bottom value: " << bottom->value << std::endl;
	}
}
int popFront(Node *&top, Node *&bottom)
{
	Node* temp = new Node; // used to hold the value of top so we can then delete that node after top becomes top->next
	int nodeValue = -999;
	if (getLengthOfDeque(top, bottom) == 0)
	{
		std::cout << "Deque is empty! You are trying to pop a value from an empty deque!\n";
		return 0;
	}
	else
	{
		//std::cout << top->value << " popped from deque." << std::endl;
		nodeValue = top->value;
		temp = top;
		top = top->next;
		delete temp;
		return nodeValue;
	}
}
int popBack(Node *&top, Node *&bottom)
{
	Node* temp = new Node;
	int nodeValue = -999;
	if (getLengthOfDeque(top, bottom) == 0)
	{
		std::cout << "Deque is empty! You are trying to pop a value from an empty deque!\n";
		return 0;
	}
	else
	{
		std::cout << bottom->value << " popped from deque.\n";
		nodeValue = bottom->value;
		temp = bottom;
		bottom = bottom->prev;
		delete temp;
		return nodeValue;
	}
	
}
int main()
{
	FILE* filePtr = NULL;
	Node* top = NULL;
	Node* bottom = NULL;
	int number[50];//allows 49 characters and the null character in each of our numbers
	int i = 0;
	//DEQUES (double ended queues)
	std::cout << "Beginning deque operations.\n";
	filePtr = fopen("input.txt", "r");
	if(filePtr == NULL)
	{
		std::cout << "Error! Nothing in file!" << std::endl;
		exit(1); // exit the program if we can't open the file
	}
	//top, bottom = NULL;
	top = NULL;
	bottom = NULL;
	while (fscanf(filePtr,"%d", &number[i]) != EOF) // while we keep reading from the file and read in a number and we haven't reached the end of file (EOF)
	{
		if (number[i] >= 10)
		{
			pushBack(top, bottom, number[i]);
		}
		else pushFront(top, bottom, number[i]);
		i++;
	}
	int lengthOfTheDeque = getLengthOfDeque(top, bottom);
	std::cout << "The length of the deque is: " << lengthOfTheDeque << std::endl;
	int dequePoppedValue = -999;
	std::cout << "Top: " << top->value << "\nBottom: " << bottom->value << std::endl;
	printDeque(top, bottom);
	//searching
	


	//poppiing all data from deque
	for(i=0; i < lengthOfTheDeque; i++)
	{
		//poppedValue = popFront(top);
		//dequePoppedValue = popFront(top, bottom);
		dequePoppedValue = popFront(top,bottom);
		std::cout << dequePoppedValue << " popped from deque!\n";
	}
	lengthOfTheDeque = getLengthOfDeque(top, bottom);
	std::cout <<  lengthOfTheDeque << std::endl;
	fclose(filePtr);
}
	/*
		//old
		temp = bottom; //temp = old bottom 
		bottom = newNode;
		temp->next = bottom;
		bottom->value = value; // new bottom = new value
		bottom->prev = temp; // new bottom->prev = old bottom
		bottom->next = NULL; // new bottom-> next = NULL (end of deque)
		top = top;
		*/