//============================================================================
// Name         : Polynomial Calculator 
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-08-2022
// Date Modified: 15-02-2022
// Description  : Linked List class used for Polynomial Calculagtor
//============================================================================
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<iostream>
#include<fstream>
using namespace std;

class Node
{
	private:
		int coef; //variable to store coefficient of a term
		int expo; //variable to store exponent of a term
		Node* next; //Pointer pointing to the next Node
		
	public:
		Node(int coef, int expo) : coef(coef), expo(expo), next(NULL)
		{} // initialize the node with different attributes
		friend class LinkedList;
		friend class PolyCalculator;
};
class LinkedList
{
	private:
		Node* head; // pointer to the head 
	public:
		LinkedList (); // empty list constructor
		void insert(int coef,int expo); // add a new Node at the right place in the Linked List
		void print(ostream& os=cout) const;
		void removeAll();	 // remove all nodes
		~LinkedList (); // destructor to clean up all nodes
	
		friend class PolyCalculator;
};

            
    
#endif