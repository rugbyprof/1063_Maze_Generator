#include "MovesStack.h"



//-----------------------------------------------------------------
//Initialize (construct) our list based stack
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
MovesStack::MovesStack(void)
{
	Top=NULL;
	Size=0;
}

//-----------------------------------------------------------------
//Push a coordinate onto the top of the stack stack.
//So, everything is just a front-sert.
// @Param: COORD
// @Returns: void
//-----------------------------------------------------------------
void MovesStack::Push(COORD cell){
	CellNode *C = new CellNode;
	C->Cell = cell;
	C->Next = NULL;

	if(Top==NULL){
		Top=C;
	}else{
		C->Next = Top;
		Top = C;
	}
	Size++;
}

//-----------------------------------------------------------------
//Turn a COORD* into a COORD, then push it on the stack
//
// @Param: COORD*
// @Returns: void
//-----------------------------------------------------------------
void MovesStack::Push(COORD* cell){
	COORD Temp;
	Temp.X = cell->X;
	Temp.Y = cell->Y;
	Push(Temp);
}

//-----------------------------------------------------------------
//Turn a row and col into a coordinate, then push it on the stack
//
// @Param: COORD
// @Returns: void
//-----------------------------------------------------------------
void MovesStack::Push(int row,int col){
	COORD Temp;
	Temp.X = col;
	Temp.Y = row;
	Push(Temp);
}

//-----------------------------------------------------------------
//Get the last move from top of stack
//
// @Param: void
// @Returns: COORD
//-----------------------------------------------------------------
bool MovesStack::Pop(COORD& cell){

	if(!Empty()){
		CellNode *TempPtr = Top;
		cell.X = TempPtr->Cell.X;
		cell.Y = TempPtr->Cell.Y;

		Top = TempPtr->Next;
		delete TempPtr;
		Size--;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------
//Look at the top of the stack, without altering the stack
//
// @Param: void
// @Returns: COORD
//-----------------------------------------------------------------
bool MovesStack::Peek(COORD& cell){
	if(!Empty()){
		cell = Top->Cell;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------
//Checks for empty stack
//
// @Param: void
// @Returns: bool
//-----------------------------------------------------------------
bool MovesStack::Empty(void){
	return Size == 0;
}

void MovesStack::Print(){
	CellNode* H = Top;
	while(H){
		cout<<"["<<H->Cell.X<<","<<H->Cell.Y<<"]";
		H = H->Next; 
	}
	cout<<endl;
}

MovesStack::~MovesStack(void)
{
	//add code to delete remaining nodes in stack if you want.
}
