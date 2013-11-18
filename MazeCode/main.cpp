#include <iostream>
#include "MazeGenerator.h"
#include "MovesStack.h"

using namespace std;

#define ROWS 24
#define COLS 79

void main(){
	ofstream fout;

	fout.open("test_data.txt");
	MazeGenerator M(24,79,-1);
	M.CreateMaze(1);
	M.SetStartAndExit();
	M.PrintMaze(0);
	M.PrintMaze(fout);
	system("pause>0");
}