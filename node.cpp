#include <iostream>
#include "node.h"

Node::Node() {
	sp = NULL;
	cp = NULL;

	stu = 0;
	cls = 0;
	grade = 0;
}

Node::Node(int stuNum, int clsNum, int gradeNum) {
	sp = NULL;
	cp = NULL;

	stu = stuNum;
	cls = clsNum;
	grade = gradeNum;
}

Node::Node(int stuNum, int clsNum) {
	sp = NULL;
	cp = NULL;

	stu = stuNum;
	cls = clsNum;
	grade = 0;
}

Node::~Node() {
}

// getters and setters
void Node::setNextStu(Node* n) {
	sp = n;
}

Node* Node::getNextStu() {
	return sp;
}

void Node::setNextCls(Node* n) {
	cp = n;
}

Node* Node::getNextCls() {
	return cp;
}

void Node::setStu(int stuNum) {
	stu = stuNum;
}

int Node::getStu() {
	return stu;
}

void Node::setCls(int clsNum) {
	cls = clsNum;
}

int Node::getCls() {
	return cls;
}

void Node::setGrade(int gradeNum) {
	grade = gradeNum;
}

int Node::getGrade() {
	return grade;
}

Node* Node::searchStu(int stuNum) { // only used by the head node to check if an index node for this student number exists
	Node* next = sp;
	while (next != NULL) {
		if (next->getStu() == stuNum) {
			return next;
		}
		next = next->sp;
	}

	return NULL;
}

Node* Node::searchCls(int clsNum) { // only used by the head node to check if an index node for this class number exists
	Node* next = cp;
	while (next != NULL) {
		if (next->getCls() == clsNum) {
			return next;
		}
		next = next->cp;
	}

	return NULL;
}

void Node::insertStu(Node* student) { // inserts the given node in the list in the correct order
	Node* current = this;
	while (current->sp != NULL && current->sp->getStu() < student->getStu()) { // iterating until next is null or until inserted student number is larger than next student number
		current = current->sp;
	}
	student->sp = current->sp;
	current->sp = student;
}

void Node::insertCls(Node* clas) { // inserts the given node in the list in the correct order
	Node* current = this;
	while (current->cp != NULL && current->cp->getCls() < clas->getCls()) { // iterating until next is null or until inserted class number is larger than next class number
		current = current->cp;
	}
	clas->cp = current->cp;
	current->cp = clas;
}

void Node::printClasses() {
	Node* next = cp; // using cp will prevent index from printing
	while (next != NULL) {
		if (next->cp == NULL) { // if its the last class
			std::cout << next->getCls() << ";";
		}
		else {
			std::cout << next->getCls() << ", ";
		}
		next = next->cp;
	}
}

void Node::printStudents() {
	Node* next = sp; // using sp will prevent index from printing
	while (next != NULL) {
		if (next->sp == NULL) { // if its the last student
			std::cout << next->getStu() << ";";
		}
		else {
			std::cout << next->getStu() << ", ";
		}
		next = next->sp;
	}
}