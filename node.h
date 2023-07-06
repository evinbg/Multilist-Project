#ifndef NODE_H_EXISTS
#define NODE_H_EXISTS

#include <iostream>

class Node {
private:
	Node* sp;
	Node* cp;
	int stu;
	int cls;
	int grade;

public:
	Node();
	Node(int stuNum, int clsNum, int gradeNum);
	Node(int stuNum, int clsNum);
	~Node();

	void setNextStu(Node* next);
	Node* getNextStu();

	void setNextCls(Node* next);
	Node* getNextCls();

	void setStu(int stuNum);
	int getStu();

	void setCls(int clsNum);
	int getCls();

	void setGrade(int gradeNum);
	int getGrade();

	Node* searchStu(int stuNum);
	Node* searchCls(int clsNum);

	void insertStu(Node* student);
	void insertCls(Node* clas);

	void printClasses();
	void printStudents();
};

#endif