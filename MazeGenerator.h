#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include "AsciiDraw.h"
#include "MovesStack.h"


class MazeGenerator : public AsciiDraw
{
private:
	//Private Data Memebers
	int **MazeArray;						//2D array that holds the actual maze values
	int Rows;								//Number of rows in the array
	int Cols;								//Number of cols in the array
	COORD Current;							//Current location (like in the maze)
	COORD Start;							//Where the maze starts
	COORD Exit;								//Where the maze ends
	MovesStack *S;							//Stack to hold moves as they are taken, so we can backtrack
	int Moves[4];							//Given a Cell, this holds the number of available moves away
											//from that cell. 

	//Private Methods
	bool AvailableMoves();					//Get available moves at current location					
	void BuildMazeContainer();				//Builds dynamic 2D array
	void CompleteInit();					//Runs remainder of what was duplicated in constructors
	double Distance(int,int,int,int);		//Gets distance between two cells
	void GetMoves(COORD);					//Loads Moves array with any moves it finds
	COORD GetRandomEdgeCoord(int side);		//Used to assist in creating Start and Exit function
	void InitCells();						//Initializes MazeArray to 1's for walls and 2's for outer boundary
	bool NotVisited(COORD);					//Returns true if a given COORD == 1 (it's still a wall)
	COORD PickRandomMove();					//Given the Moves array, choose randomly one of the 1's
	void ResetMovesArray();					//Reset Moves[] to all zeros
	bool Reachable(COORD);					//Given a COORD, is there a neighbor that is empty (0)
	void SetCurrent(int,int);				//Function to set current COORD using 2 int's. Not used a lot.
	bool ValidHallway(COORD);				//Valid hallway means a cell has 1's on either N && S or E && W.
	bool WithinMaze(COORD);					//Is COORD not falling outside of array bounds.

public:
	MazeGenerator(void);					//Constructor
	MazeGenerator(int,int,int);				//Overloaded Constructor
	void CreateMaze(bool);					//Start Maze creation
	void SetStartAndExit();					//Randomly pick start and exit points for maze
	void SetStartAndExit(COORD,COORD);		//Specify start and exit points
	void PrintCell(COORD cell);				//Prints a single cell
	void PrintMaze(int);					//Print maze to screen
	void PrintMaze(ofstream &);				//Print maze to file
	~MazeGenerator(void);					//Destructor
};

