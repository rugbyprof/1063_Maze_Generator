#include "MazeGenerator.h"

////////////////////////////////////////////////////////////////////////////////////////////
//Public Methods
////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------
// Constructor that will build a maximum sized maze seeding the 
// random number generator with time.
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
MazeGenerator::MazeGenerator(void)
{
	srand(time(0));
	Rows = 24;
	Cols = 79;
	CompleteInit();
}

//-----------------------------------------------------------------
// Constructor that will build a specified sized maze seeding the 
// random number generator with time if seed is less than zero,
// otherwise seed it with the parameter
//
// @Param: int rows
// @Param: int cols
// @Param: int seed (-1 = time(0), otherwise it's your seed)
// @Returns: void
//-----------------------------------------------------------------
MazeGenerator::MazeGenerator(int rows,int cols,int seed)
{
	if(seed < 0)
		srand(time(0));
	else
		srand(seed);
	Rows = rows;
	Cols = cols;
	CompleteInit();

}

//-----------------------------------------------------------------
// Should start at some given point and then proceed to build walls
// and hallways. 
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::CreateMaze(bool watch_progress){

	ResetMovesArray();
	PrintMaze(0);
	COORD Previous;
	do{
		MazeArray[Current.Y][Current.X] = 0;	//Set current location to 0 (where we are starting to create)
		SetXY(Current.X,Current.Y);
		SetForegroundColor(12);
		cout<<'.';
		SetForegroundColor(7);

		GetMoves(Current);						//Get all moves from our current location

		if(AvailableMoves()){					//If we have moves, good, pick one randomly to go to
			Previous = Current;
			Current = PickRandomMove();			//Getting a random move 
			S->Push(Current);					//Push that move onto our stack
		}else{
			S->Pop(Current);					//Else, there are NO moves so pop current off the stack
		}										//and try to go somewhere from a previous location

		if(watch_progress){						//If watch_progress > 0, then print out the creation process
			//PrintMaze(0);						//to the screen
			PrintCell(Previous);
			PrintCell(Current);
			Sleep(10);
		}

	}while(!S->Empty());						//Keep going until the stack is empty (no more moves to make).

}

//-----------------------------------------------------------------
// Creates the Start of the maze, and the exit of the maze using 
// pre-chosen coordinates.
// @Param: COORD start
// @Param: COORD exit
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::SetStartAndExit(COORD start,COORD exit){
	Start = start;
	Exit = exit;
}

//-----------------------------------------------------------------
// Randomly chooses the start and exit of the maze
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::SetStartAndExit(){
	int Side;				//0-3 (N,S,E,W)
	bool found = 0;			//Did we find a spot that isn't blocked

	double MaxDistance = Distance(0,0,Cols,Rows);	//Used to make sure start
													//and exit aren't too close
	while(!found){
		ResetMovesArray();					//Reset out Moves[] to all 0's
		Side = rand() % 4;					//Generate random # from 0-3
		Start = GetRandomEdgeCoord(Side);	//Get a COORD on edge of maze
		if(Reachable(Start)){				//Reachable = not blocked by wall.
			found=true;
		}
	}

	found = false;

	while(!found){							//Same as above for exit
		ResetMovesArray();
		Side = rand() % 4;
		Exit = GetRandomEdgeCoord(Side);
		//The distance test is to make sure the start and exit are at least 75% of MaxDistance apart.
		if(Reachable(Exit) && (Distance(Start.X,Start.Y,Exit.X,Exit.Y)/MaxDistance) > .75){
			found=true;
		}
	}
}

//-----------------------------------------------------------------
// Only prints a single cell, not entire array.
//
// @Param: COORD cell
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::PrintCell(COORD cell){
	SetXY(cell.X,cell.Y);
	if(cell.X == Start.X && cell.Y == Start.Y){
		cout<<'S';
	}else if(cell.X == Exit.X && cell.Y == Exit.Y){
		cout<<'E';
	}else if(MazeArray[cell.Y][cell.X]>=1){
		cout<<char(178);
	}else{
		cout<<char(32);
	}
}
//-----------------------------------------------------------------
// Prints maze to standard out
//
// @Param: int debug -  If set to 1, then actual values are printed to screen, 
//						not extended dos characters
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::PrintMaze(int debug){
	SetXY(0,0);
	if(debug){
		for(int i=0;i<Rows;i++){
			for(int j=0;j<Cols;j++){
				std::cout<<MazeArray[i][j];
			}
			std::cout<<std::endl;
		}
	}else{
		for(int i=0;i<Rows;i++){
			for(int j=0;j<Cols;j++){
				if(i==Start.Y && j==Start.X){
					SetBackgroundColor(12);
					cout<<'S';
					SetBackgroundColor(0);
				}else if(i==Exit.Y && j==Exit.X){
					SetBackgroundColor(12);
					cout<<'E';
					SetBackgroundColor(0);
				}else if(MazeArray[i][j]>=1){
					cout<<char(178);
				}else{
					cout<<char(32);
				}
			}
			std::cout<<std::endl;
		}
	}
}

//-----------------------------------------------------------------
// Prints maze to a file
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::PrintMaze(ofstream &fout){
	fout<<Rows<<" "<<Cols<<endl;
	for(int i=0;i<Rows;i++){
		for(int j=0;j<Cols;j++){
			if(i==Start.Y && j==Start.X)
				fout<<'S';
			else if(i==Exit.Y && j==Exit.X)
				fout<<'E';
			else if(MazeArray[i][j]>=1)
				fout<<1;
			else
				fout<<0;
		}
		if(i<Rows-1)
			fout<<endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//Private Methods
////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------
// Checks to see if there are any available moves within the moves array 
//
// @Param: int* Array[4]
// @Returns: bool- true if any location has a 1
//-----------------------------------------------------------------
bool MazeGenerator::AvailableMoves(){
	return (Moves[0]>0 || Moves[1]>0 || Moves[2]>0 || Moves[3]>0);
}

//-----------------------------------------------------------------
// Generates a dynamic 2D array that will hold our maze values
// Using 0 for initial values
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::BuildMazeContainer(){
	MazeArray = new int*[Cols];
	for(int i=0;i<Rows;i++){
		MazeArray[i] = new int[Cols];
		for(int j=0;j<Cols;j++){
			MazeArray[i][j] = 0;
		}
	}
}

//-----------------------------------------------------------------
// Finishes up the initialization of the maze
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::CompleteInit(){

	SetCurrent(1,1);		//Start at top left corner of array
	S = new MovesStack();	//Create a new stack to hold COORD's
	S->Push(Current);		//Push our Current local onto the stack
	BuildMazeContainer();	//Build dynamic 2D array to hold our values
	InitCells();			//Init the cells to their appropriate vals
}

//-----------------------------------------------------------------
// Gets euclidian distance between two cells
//
// @Param: COORD P
// @Param: COORD Q
// @Returns: double distance
//-----------------------------------------------------------------
double MazeGenerator::Distance(int P1,int P2,int Q1,int Q2){

	return sqrt(pow(double(P1 - Q1),2) + pow(double((P2 - Q2)),2));
}

//-----------------------------------------------------------------
// Gets all available moves given a COORD / location
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::GetMoves(COORD cell){

	ResetMovesArray();			//Make all moves 0

	COORD North = cell;			//Create 4 COORD values mostly 
	COORD South = cell;			//just for readability
	COORD East = cell;
	COORD West = cell;

	//Each of the following test for:
	//1) Is the move inside the array representing the maze
	//2) Has that location been visited already
	//3) Is it a "ValidHallway". This is my heuristic for helping with the maze creation.
	//   Basically a "ValidHallway" is a cell that has 1's on opposite sides of it. (East and West or North and South)
	North.Y--;
	if(WithinMaze(North) && NotVisited(North) && ValidHallway(North)){
		Moves[0]=1;
	}

	South.Y++;
	if(WithinMaze(South) && NotVisited(South) && ValidHallway(South)){
		Moves[1]=1;
	}

	East.X++;
	if(WithinMaze(East) && NotVisited(East) && ValidHallway(East)){
		Moves[2]=1;
	}
	
	West.X--;
	if(WithinMaze(West) && NotVisited(West) && ValidHallway(West)){
		Moves[3]=1;
	}

}

//-----------------------------------------------------------------
// Returns a random COORD somewhere along the edge of the maze
// @Param: int side - 0=North, 1=South, 2=East, 3=West
// @Returns: COORD
//-----------------------------------------------------------------
COORD MazeGenerator::GetRandomEdgeCoord(int side){

	COORD C;

	switch(side){
	case 0: C.X = (rand() % (Cols));
		    C.Y = 0;
			break;
	case 1: C.X = (rand() % (Cols));
		    C.Y = Rows-1;
			break;
	case 2: C.X = Cols-1;
		    C.Y = (rand() % (Rows));
			break;
	case 3: C.X = 0;
		    C.Y = (rand() % (Rows));
			break;
	}
	return C;
}

//-----------------------------------------------------------------
// Method that dynamically builds a 2D int array that represents our
// walls and hallways. 1's = wall, and 0's = hallway.
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::InitCells(){
	int i,j,val;
	for(i=0;i<Rows;i++){
		for(j=0;j<Cols;j++){
			if(i==0 || j==0 || j==Cols-1 || i==Rows-1)
				val=2;	//Impenetrable wall (outer wall) 
			else
				val=1;  //A wall we can knock down if needed when building the maze

			MazeArray[i][j] = val;
		}
	}
}

//-----------------------------------------------------------------
// Any cell with a value 1 is a wall to start. Anything with a value
// greater than 1, is a boundary (like the around the maze).
//
// @Param: COORD
// @Returns: bool
//-----------------------------------------------------------------
bool MazeGenerator::NotVisited(COORD c){
	return (MazeArray[c.Y][c.X] == 1);
}

//-----------------------------------------------------------------
// Picks a random move, from available moves 
//
// @Param: void
// @Returns: COORD C - The chosen move
//-----------------------------------------------------------------
COORD MazeGenerator::PickRandomMove(){

	COORD C;	//Create a COORD and initialize it.
	C.X = -1;
	C.Y = -1;

	int r = rand()%4;		//Generate a random number from 0 to 3

	while(Moves[r]==0){		//Each time Moves[r] equals 0, then we loop and choose again.
		r = rand()%4;
	}						//This loop should never fail because "AvailableMoves" 
							//should have been called first.

	//Depending on "r" we choose a move to make
	switch(r){
		case 0: C.X = Current.X; C.Y = Current.Y-1; return C;	//r = 0, go North
		case 1: C.X = Current.X; C.Y = Current.Y+1; return C;	//r = 1, go South
		case 2: C.X = Current.X+1; C.Y = Current.Y; return C;	//r = 2, go East
		case 3: C.X = Current.X-1; C.Y = Current.Y; return C;	//r = 3, go West
	}
}

//-----------------------------------------------------------------
// Re-sets the Moves array to zeros. So [N,S,E,W] are now 0.
//
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::ResetMovesArray(){
	for(int i=0;i<4;i++){	//Holds available moves from current location
		Moves[i]=0;			//Example: [1,0,1,0] = You can move North and East, but not South and West.
	}						//		   [N,S,E,W]
							//Used in multiple functions checking for available moves.
}

//-----------------------------------------------------------------
// This returns true if there is an "open" cell, like a hallway which
// basically has 0 in the MazeArray, next two the COORD passed in
//
// @Param: COORD cell - The cell to be checked
// @Returns: void
//-----------------------------------------------------------------
bool MazeGenerator::Reachable(COORD cell){
	COORD North = cell;			//Create 4 COORD values mostly 
	COORD South = cell;			//just for readability
	COORD East = cell;
	COORD West = cell;

	//Each of the following test for:
	//1) Is the move inside the array representing the maze
	//2) Is there an opening (0) next to the cell (making it reachable)
	North.Y--;
	if(WithinMaze(North) && MazeArray[North.Y][North.X]==0){
		return true;
	}

	South.Y++;
	if(WithinMaze(South) && MazeArray[South.Y][South.X]==0){
		return true;
	}

	East.X++;
	if(WithinMaze(East) && MazeArray[East.Y][East.X]==0){
		return true;
	}
	
	West.X--;
	if(WithinMaze(West) && MazeArray[West.Y][West.X]==0){
		return true;
	}	
}

//-----------------------------------------------------------------
// Sets current position in maze
//
// @Param: int row
// @Param: int col
// @Returns: void
//-----------------------------------------------------------------
void MazeGenerator::SetCurrent(int x,int y){
	Current.X = x;
	Current.Y = y;
}

//-----------------------------------------------------------------
// Any cell with two opposite walls (east and west or north and south) is valid (for now)
//
// @Param: COORD
// @Returns: bool
//-----------------------------------------------------------------
bool MazeGenerator::ValidHallway(COORD c){

	return (
		//This top boolean just makes sure that there are walls on oppossite sides of the cell we might choose
		(MazeArray[c.Y][c.X-1] != 0 && MazeArray[c.Y][c.X+1] != 0) || (MazeArray[c.Y-1][c.X] != 0 && MazeArray[c.Y+1][c.X] != 0) 
		&&
		//This boolean makes sure that there are walls on 3 sides of that same choice. Why? Change
		//it to 1 and look at the type of maze it creates. Can you see a difference?
		(MazeArray[c.Y][c.X-1] + MazeArray[c.Y][c.X+1] + MazeArray[c.Y-1][c.X] + MazeArray[c.Y+1][c.X] > 2)
		);
}

//-----------------------------------------------------------------
// Method receives a row and a column and returns wether or not it
// its within the maze boundaries.
//
// @Param: int row
// @Param: int col
// @Returns: bool
//-----------------------------------------------------------------
bool MazeGenerator::WithinMaze(COORD c){
	return ((c.Y>0) && (c.X>0) && (c.Y<Rows-1) && (c.X<Cols-1));
}

MazeGenerator::~MazeGenerator(void)
{
}
