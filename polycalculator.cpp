//============================================================================
// Name         : Polynomial Calculator 
// Author       : Aysa Binte Masud
// Version      : 1.0
// Date Created : 25-08-2022
// Date Modified: 10-05-2023
// Description  : Polycalculator class methods 
//============================================================================
#include<iostream>
#include "polycalculator.h"
using namespace std;

// function for taking user input
void PolyCalculator::input(){
    // String to hold the input for the first polynomial expression.
    string str1;
    cout << "Enter first Polynomial expression: ";
    getline(cin, str1);

    //if parsing fails, print an error message and make the list empty
    if (!parse(str1, list1)){ 
        cout << "Invalid Polynomial expression: "  << endl;
        list1.removeAll();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore until newline
    }

    // String to hold the input for the second polynomial expression.
    string str2;
    cout << "Enter second Polynomial expression: ";
    getline(cin, str2);

    //if parsing fails, print an error message and make the list empty
    if (!parse(str2, list2)){
        cout << "Invalid Polynomial expression: " << str2 << endl;
        list2.removeAll();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore until newline
    }
}


//function to display the expressions 
void PolyCalculator::display(ostream& os){
	cout<<"Exp1: ";
	list1.print(os); // call the print function for the list

	cout<<"Exp2: ";
	list2.print(os); // call the print function for the list
}

void PolyCalculator::add(){

   //clear the values of the result list, list3
	list3.removeAll();

	//declare two pointers to go through two expressions given by the user
	for (Node* p1 = list1.head; p1 != nullptr; p1 = p1->next) {//continue from head until the end(null)
        list3.insert(p1->coef, p1->expo);
    }
    for (Node* p2 = list2.head; p2 != nullptr; p2 = p2->next) {//continue from head until the end(null)
        list3.insert(p2->coef, p2->expo);
    }
    
    //print the result
    cout<<"Exp1+Exp2: "; 
    list3.print();
    cout<<endl;
}
void PolyCalculator::sub(){

	//clear the values of the result list, list3
	list3.removeAll();

	//declare two pointers to go through two expressions given by the user
	for (Node* p1 = list1.head; p1 != nullptr; p1 = p1->next) {//continue from head until the end(null)
        list3.insert(p1->coef, p1->expo);
    }
    for (Node* p2 = list2.head; p2 != nullptr; p2 = p2->next) {//continue from head until the end(null)
        list3.insert(-p2->coef, p2->expo);//inset the node with negative coefficients since we are subtracting
    }
	cout<<"Exp1-Exp2: ";
	list3.print(); // print the result
	cout<<endl;
}

void PolyCalculator::mul() {
    //clear the values of the result list, list3
    list3.removeAll();

    // For each term in the first polynomial
    Node* p1 = list1.head;
    while (p1 != nullptr) {

        // Multiply it with each term in the second polynomial
        Node* p2 = list2.head;
        while (p2 != nullptr) {

            int coefmul = p1->coef * p2->coef;//new coefficient will be the product of the coefficients
            int exposum = p1->expo + p2->expo;//new exponent will be the sum of the exponents
            list3.insert(coefmul, exposum);
            p2 = p2->next;//forward to next term
        }
        p1 = p1->next;//forward to next term
    }
    cout << "Exp1*Exp2: ";
    if(list3.head == nullptr) {
        cout << "0";  // If the result is empty, print 0
    } else {
        list3.print();
    }
    cout << endl;
}

void PolyCalculator::readData(string path){

	ifstream infile(path); // declare a file variable to store the file name
	if(!infile.is_open()){ //if the file doesn't open, show the error message
		cerr<<"Unable to open the file "<<endl;
		return;
	}
	string str1;
	if(getline(infile,str1)){
		list1.removeAll(); //clear the data that already existed
		if(!parse(str1,list1)){ //if invalid format, show error message
			cout<<"Invalid polynomial"<<endl;
			return;
		}
	}
	string str2;
	if(getline(infile,str2)){
		list2.removeAll();//clear the data that already existed
		if(!parse(str2,list2)){//if invalid format, show error message
			cout<<"Invalid polynomial"<<endl;
			return;
		}
	}
	infile.close();//close the file

}
void PolyCalculator::writeData(string path){
	ofstream outfile(path); // declare a file variable to store the file name
	if(!outfile.is_open()){ //if the file doesn't open, show the error message
		cerr<<"Unable to open the file "<<endl;
		return;
	}
	outfile<<"Exp1: "; //write the first expression into the file
	list1.print(outfile);


	outfile<<"Exp2: "; //write the second expression into the file
	list2.print(outfile);


	list3.removeAll();//delete the existed data
	add();
	outfile<<"Exp1+Exp2: "; //write the sum of the expressions into the file
	list3.print(outfile);


	list3.removeAll();//delete the existed data
	sub();
	outfile<<"Exp1-Exp2: ";//write the result of the subtraction
	list3.print(outfile);


	list3.removeAll();//delete the existed data
	mul();
	outfile<<"Exp1*Exp2: ";//write the product in the file
	list3.print(outfile);


	outfile.close(); //close the file
}

// create a function to parse a polynomial expression from a string format
bool PolyCalculator::parse(string expr, LinkedList& list){
    int index = 0;// Initialize the starting index of the string expression.

    // Loop through the expression string until its end.
    while (index < expr.length()){
        int coef = 0; //initialize the coefficient
        int expo = 0; //initialize the exponent
        int sign_coef = 1; //initialize the sign of the coefficient

        // Check for a negative sign and update the coefficient sign
        if (expr[index] == '-'){
            sign_coef = -1;
            index++; //move to the next character
        }
        else if (expr[index] == '+'){//check for a positive 
            index++;//move to the next character
        }

        // Extract the coefficient by processing continuous digits.
        while (index < expr.length() && isdigit(expr[index])){

            // Construct the coefficient digit by digit.
            coef = coef * 10 + (expr[index] - '0');//subtract '0' to subtract the ASCII code of 0
            index++;//move to the next character
        }
        coef *= sign_coef;// Apply the sign to the coefficient.

        // Check if the next character isn't 'x' or the end of the expression
        if (index >= expr.length() || expr[index] != 'x'){
            return false;
        }
        index++;

        if (index >= expr.length() || expr[index] != '^'){// Check if the next character isn't '^' or the end of the expression
            return false;
        }
        index++;

        // Extract the exponent by processing continuous digits.
        while (index < expr.length() && isdigit(expr[index])){

            // Construct the exponent digit by digit.
            expo = expo * 10 + (expr[index] - '0');//subtract '0' to subtract the ASCII code of 0
            index++;//move to the next character
        }

        //  the explicit handling of 0x^0 or any 0 coefficient term
        if (coef == 0){
            continue;  // Skip adding the term to the list
        }
        
        list.insert(coef, expo);
    }

    //return true if every term follows correct format
    return true;
}