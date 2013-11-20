#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;

struct CellNode{
	COORD Cell;
	CellNode *Next;
};

class MovesStack{
private:
	CellNode *Top;
	int Size;
public:
	MovesStack();
	//Push a coordinate onto the stack
	void Push(COORD);
	//Turn a row and col into a coordinate, then push it on the stack
	void Push(int,int);
	void Push(COORD*);
	//Get the last move from top of stack
	bool Pop(COORD&);
	//Look at the top of the stack
	bool Peek(COORD&);
	//Is the stack empty
	bool Empty(void);
	void Print();
	~MovesStack();
};

