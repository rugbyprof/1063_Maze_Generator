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
	fout.close();

	//////////////////////////////////////////////////////////
	//ifstream fin;
	//fin.open("test_data.txt");
	//int rows;
	//int cols;
	//int **MazeArray;
	//char ch;
	//fin>>rows>>cols;
	//
	//MazeArray = new int*[cols];
	//for(int i=0;i<rows;i++){
	//	MazeArray[i] = new int[cols];
	//	for(int j=0;j<cols;j++){
	//		MazeArray[i][j] = 0;
	//	}
	//}

	//COORD Start;
	//COORD Exit;

	//fin.get(ch);
	//for(int i=0;i<rows;i++){
	//	for(int j=0;j<cols;j++){
	//		fin.get(ch);
	//		if(ch=='S'){
	//			Start.X = j;
	//			Start.Y = i;
	//			ch='0';
	//		}
	//		if(ch=='E'){
	//			Exit.X = j;
	//			Exit.Y = i;
	//			ch='0';
	//		}
	//		MazeArray[i][j] = ch-48;
	//	}
	//	fin.get(ch);
	//}

	//for(int i=0;i<rows;i++){
	//	for(int j=0;j<cols;j++){
	//		cout<<MazeArray[i][j];
	//	}
	//	cout<<endl;
	//}
	//system("pause>0");

}