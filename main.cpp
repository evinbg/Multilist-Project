#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "node.h"

void printMenu(); // prints the main menu
int checkInput(int options, std::string text); // checks if the user's input is valid
void doAction(int action); // does the action of the user input
void insertFromFile(); // reads and inserts the nodes from the file
void searchStudent(); // searches for a student from the user's input
void searchClass(); // searches for a class from the user's input
void printStudents(); // prints all of the students and their respective classes
void printClasses(); // prints all of the classes and their respective students
void addStudent(); // gets a student and class number from the user and inserts the node into the multilist

bool fileCheck; // checks if the file has already been read and inputted
Node* head; // keeps track of the head of the multilist

int main() {
	bool keepGoing = true;
	int action;
	fileCheck = false;

	Node* newHead = new Node(0, 0, 0); // head of the multilist
	head = newHead;

	while (keepGoing == true) { // loop to keep the application running
		printMenu();
		action = checkInput(6, "Enter an option: ");
		doAction(action);
	}

	return 0;
}

void printMenu() {
	std::cout << "[Multilist]" << std::endl;
	std::cout << "1: Insert data from multilist_input.txt" << std::endl;
	std::cout << "2: Add/Create a student" << std::endl;
	std::cout << "3: Search for student" << std::endl;
	std::cout << "4: Search for class" << std::endl;
	std::cout << "5: Print all students" << std::endl;
	std::cout << "6: Print all classes" << std::endl;
	std::cout << "0: Exit" << std::endl;
}

int checkInput(int options, std::string text) {
	bool keepGoing = true;
	bool intCheck;
	int num;
	std::string strInput;

	while (keepGoing == true) { // loops until valid input is given
		std::cout << text;
		std::getline(std::cin, strInput);
		intCheck = true;

		for (int i = 0; i < strInput.length(); i++) { // checks if the input is an integer
			if (std::isdigit(strInput[i]) == false) {
				std::cout << "Please enter an integer" << std::endl;
				intCheck = false;
				break;
			}
		}

		if (intCheck == true) {
			num = std::stoi(strInput);
			if (num > options) { // checks if the integer input is within the given range
				std::cout << "Please enter an option within the range 0 - " << options << std::endl;
			}
			else {
				keepGoing = false;
			}
		}
	}

	return num;
}

void doAction(int action) {

	switch (action) {
	case (1):
		insertFromFile();
		break;

	case (2):
		addStudent();
		break;

	case (3):
		searchStudent();
		break;

	case (4):
		searchClass();
		break;

	case (5):
		printStudents();
		break;

	case (6):
		printClasses();
		break;

	case (0):
		exit(1);
		break;

	default:
		std::cout << "Something went wrong..." << std::endl;
		break;
	}
}

void insertFromFile() {
	if (fileCheck == true) {
		std::cout << "The file has already been inserted" << std::endl << std::endl;
		return;
	}

	fileCheck = true;

	std::ifstream inputFile;
	inputFile.open("multilist_input.txt");

	if (!inputFile) { // checks if the file exists in the directory
		std::cout << "File not found. Check if the file is in the project's directory" << std::endl << std::endl;
		return;
	}

	std::cout << "Nodes read from file:" << std::endl;

	std::string inputLine;

	while (std::getline(inputFile, inputLine)) { // reads each line in the file
		std::string stuStr = "";
		std::string clsStr = "";
		std::string gradeStr = "";
		int where = 1; // variable to check what piece of data it is on

		for (int i = 0; i < inputLine.size(); i++) { // iterates through the characters in the line
			if (inputLine[i] == '(' || inputLine[i] == ')') { // ignores the parentheses
				continue;
			}
			if (inputLine[i] == ',') { // detects when a new number starts
				where++;
				continue;
			}
			if (where == 1) { // for the student number
				stuStr += inputLine[i];
			}
			if (where == 2) { // for the class number
				clsStr += inputLine[i];
			}
			if (where == 3) { // for the grade number
				gradeStr += inputLine[i];
			}
		}

		// converting all of the strings to integers
		int stuNum = stoi(stuStr);
		int clsNum = stoi(clsStr);
		int gradeNum = stoi(gradeStr);

		std::cout << stuNum << ", " << clsNum << ", " << gradeNum << std::endl;

		Node* student = new Node(stuNum, clsNum, gradeNum); // creating new node for the line

		Node* existingStudent = head->searchStu(stuNum); // checks if there is an index for the student number
		Node* existingClass = head->searchCls(clsNum); // checks if there is an index for the class number

		if (existingStudent == NULL) { // if there isnt an index for the student yet
			Node* newStudent = new Node(stuNum, 0, 0); // creating the student index
			head->insertStu(newStudent); // inserting the student index
			newStudent->insertCls(student); // inserting the new node into the student's index
		}
		else { // if there is an index for the student already
			existingStudent->insertCls(student); // inserting the new node into the student's index
		}

		if (existingClass == NULL) { // if there isnt an index for the class yet
			Node* newClass = new Node(0, clsNum, 0); // creating the class index
			head->insertCls(newClass); // inserting the class index
			newClass->insertStu(student); // inserting the new node into the class' index
		}
		else { // if there is an index for the class already
			existingClass->insertStu(student); // inserting the new node into the class' index
		}
	}

	std::cout << std::endl;
}

void printStudents() {
	Node* current = head;
	while (current != NULL) { // looping through all student indexes
		current = current->getNextStu(); // skips the index node
		if (current == NULL) {
			break;
		}
		std::cout << "student ";
		std::cout << current->getStu() << ": classes ";
		current->printClasses(); // prints the current student's classes
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void printClasses() {
	Node* current = head;
	while (current != NULL) { // looping through all class indexes
		current = current->getNextCls(); // skips the index node
		if (current == NULL) {
			break;
		}
		std::cout << "class ";
		std::cout << current->getCls() << ": students ";
		current->printStudents(); // prints the current class' students
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void searchStudent() {
	int num = checkInput(10000, "Enter a student number: ");

	Node* existingStudent = head->searchStu(num); // searches for an index with the student number

	if (existingStudent == NULL) {
		std::cout << "Student doesn't exist" << std::endl << std::endl;
	}
	else { // if there is an index for the student number
		std::cout << "student " << existingStudent->getStu() << ": classes ";
		existingStudent->printClasses(); // prints all of the student's classes
		std::cout << std::endl << std::endl;
	}
}

void searchClass() {
	int num = checkInput(3000, "Enter a class number: ");

	Node* existingClass = head->searchCls(num); // searches for an index with the class number

	if (existingClass == NULL) {
		std::cout << "Class doesn't exist" << std::endl << std::endl;
	}
	else { // if there is an index for the class number
		std::cout << "class " << existingClass->getCls() << ": students ";
		existingClass->printStudents(); // prints all of the class' students
		std::cout << std::endl << std::endl;
	}
}

void addStudent() {
	std::string strInput;

	std::cout << "Enter the student and class number number e.g. \"(4, 130)\": ";
	std::getline(std::cin, strInput);

	std::string strStudent, strClass;
	int intStudent, intClass;
	int numSwitch = 0; // keeps track of what number it is on
	bool numCheck = false;

	for (int i = 0; i < strInput.size(); i++) { // iterating through the input
		if (strInput[i] == '(' || strInput[i] == ')') { // skips the parentheses
			continue;
		}
		if (strInput[i] == ',') { // uses comma to tell when the class number starts
			numSwitch = 1;
			if (strInput[i + 1] == ' ') { // checks for the space after the comma
				i = i + 1;
			}
			continue;
		}
		else {
			if (numSwitch == 0) { // concatenates the characters for the student number
				strStudent += strInput[i];
			}
			else if (numSwitch == 1) { // concatenates the characters for the class number
				strClass += strInput[i];
			}
		}
	}

	try { // tries to convert the strings to integers
		intStudent = std::stoi(strStudent);
		intClass = std::stoi(strClass);
	}
	catch (...) { // will catch the error if the strings are not integers
		std::cout << "Please use the correct format" << std::endl << std::endl;
		return;
	}

	if (intStudent > 10000 || intClass > 3000) { // checks if the inputted integers are within range
		numCheck = false;
		std::cout << "Please enter numbers within the range" << std::endl << std::endl;
	}
	else {
		Node* student = new Node(intStudent, intClass); // creating new node for the input

		Node* existingStudent = head->searchStu(intStudent); // checks if there is an index for the student number
		Node* existingClass = head->searchCls(intClass); // checks if there is an index for the class number

		if (existingStudent == NULL) { // if there isnt an index for the student yet
			Node* newStudent = new Node(intStudent, 0, 0); // creating the student index
			head->insertStu(newStudent); // inserting the student index
			newStudent->insertCls(student); // inserting the new node into the student's index
		}
		else { // if there is an index for the student already
			existingStudent->insertCls(student); // inserting the new node into the student's index
		}

		if (existingClass == NULL) { // if there isnt an index for the class yet
			Node* newClass = new Node(0, intClass, 0); // creating the class index
			head->insertCls(newClass); // inserting the class index
			newClass->insertStu(student); // inserting the new node into the class' index
		}
		else { // if there is an index for the class already
			existingClass->insertStu(student); // inserting the new node into the class' index
		}

		std::cout << "Added student " << intStudent << " to class " << intClass << std::endl << std::endl;
	}
}
