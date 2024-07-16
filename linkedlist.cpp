//============================================================================
// Name         : Polynomial Calculator 
// Author       : Aysa Binte Masud
// Version      : 1.0
// Date Created : 25-08-2022
// Date Modified: 10-05-2023
// Description  : Linked List class methods used for Polynomial Calculator
//============================================================================
#include "linkedlist.h" //including the header file that contains the definition of the class LinkedList


//create the constructor class
LinkedList::LinkedList(){

    //creates an empty list that means point the head to nullptr
    this->head=nullptr;
}

//create the constructor class
LinkedList::~LinkedList(){

    //call removeAll() function to remove all the nodes and free up spaces
    removeAll();
}

//create a function for inserting nodes(terms) into a list(polynomial expression)
void LinkedList::insert(int coef,int expo){

    //create a temporary node 
    Node* n = new Node(coef, expo);

    // if head is pointing at nothing, the list is empty
    if (head == nullptr) {

        //insert the temporary node in the empty list and make it  head
        head = n;
        return;
    }

    //make two pointers for reading a whole linkedlist 
    Node* previous = nullptr; //make a pointer and initialize as a nullptr
    Node* current = head;//make another pointer and assign head to it
    
    // traverse the list and loop as long as 'current' pointer is not nullptr
    while(current) {

        // if exponents match, add the coefficients
        if(current->expo == expo){
            current->coef += coef;
            
            // if the coefficient becomes zero, remove the node from the list
            if(current->coef == 0){
                if(previous){ //if previous is not nullptr

                    //point the next of previous to next of current, skipping current
                    previous->next = current->next; 

                    //delete the current term with coefficient zero
                    delete current;

                    //move the current pointer to the next node
                    current = previous->next;

                } else { //if 'current' is the first node

                    //mpoint head to the next node
                    head = current->next;

                    //delete the first node
                    delete current;

                    //update 'current' pointer to point to the next node
                    current = head;
                }
            }

            //delete dynamically created node and return 
            delete n;
            return;
        } 

        // if current node's exponent is less, insert the new node before it
        else if(current->expo < expo){

            // Point the 'next' of the new node 'n' to the current node
            n->next = current;

            if(previous){//if previous is not nullptr
                previous->next = n; //Update the 'next' pointer of the previous node to point to 'n', thus inserting 'n' between previous and current
            
            } else {//if current is head

                // Update the head of the list to point to 'n', making 'n' the new head
                head = n;
            }
            return;
        }

        // Move to the next node in the list for the next iteration
        previous = current;
        current = current->next;
    }
    
    // if the term's exponent is larger than all nodes, insert at the end
    if(previous) { //if previous is not nullptr
        previous->next = n; //Update the 'next' pointer of the previous node to point to 'n',
    }
    else {
    head = n;   // set the head of the list to 'n', making 'n' the first node
    }
}

//create a function to print the polynomial
void LinkedList::print(ostream& os) const {

    // Start from the beginning of the list
    Node* current = head;

    // If the list is empty
    if (current == nullptr) {
        os << "Empty polynomial" << endl; //print a meassage saying it is empty
        return;
    }
    
    //continue as long as current is not nullptr
    while (current != nullptr) {

        //continue if the coefficient is not zero
        if (current->coef != 0) {

            if (current->coef > 0) {//if coefficient is positive, print a plus sign
                os << "+";
            }
            os << current->coef;
            
            // This is the change to ensure terms with exponent 0 are displayed with x^0
            if (current->expo == 0) {
                os << "x^0";
            } else {
                os << "x^" << current->expo;
            }
        }
        
        //forward the pointer to the next node
        current = current->next;
    }
    //print endline
    os << endl;
}



void LinkedList::removeAll(){
    //create a pointer of type node and store the value of the head
    Node* current = head;

    //shift the value of pointer current until the end of the pointer
    while (current != nullptr) {

        //store the current node in a temporary node del
        Node* del = current;
        current=current->next;//shift current to one step right

        //delete the value of the temporary pointer
        delete del;
        
    }
    head=nullptr;// point the head to nullptr, since the list is empty.

}