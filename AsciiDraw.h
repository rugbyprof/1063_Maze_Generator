#pragma once

#include <Windows.h>
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;
/*
//http://pastebin.com/MRp6RZbp

class ConsoleCursorPosition
{
private:
    static COORD GetConsoleCursorPosition(HANDLE hHandle)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo( hHandle , &info );
        return info.dwCursorPosition;
    }
 
    struct _X
    {
        _X(): hConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE)) {}
        _X& operator =(short rhs)
        {
            COORD coord(GetConsoleCursorPosition(hConsoleOutput));
            coord.X=rhs;
            SetConsoleCursorPosition(hConsoleOutput, coord);
            return *this;
        }
        operator short()
        {
            return GetConsoleCursorPosition(hConsoleOutput).X;
        }
private:
        const HANDLE hConsoleOutput;
    };
 
    struct _Y
    {
        _Y(): hConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE)) {}
        _Y& operator =(short rhs)
        {
            COORD coord(GetConsoleCursorPosition(hConsoleOutput));
            coord.Y=rhs;
            SetConsoleCursorPosition(hConsoleOutput, coord);
            return *this;
        }
        operator short()
        {
            return GetConsoleCursorPosition(hConsoleOutput).Y;
        }
private:
        const HANDLE hConsoleOutput;
    };
 
public:
    _X X;
    _Y Y;
 
    ConsoleCursorPosition(): X(), Y() {}
} CCP;
*/


//Table borders using extended ascii and predefined constants
////////////////////////////////////////////////////////////////////////////////
const char DULC = char(201);        //double Upper Left Corner
const char DURC = char(187);        //double Upper Right Corner
const char DBLC = char(200);        //double Bottom Left Corner
const char DBRC = char(188);        //double Bottom Right Corner
const char DHTB = char(205);        //double Horizontal Top Bar
const char DVB  = char(186);        //double Verticle Size Bar
const char DT   = char(206);        //Double T Junction
const char DTD  = char(203);        //Double T Down
const char DTU  = char(202);        //Double T Up
const char DTR  = char(204);        //Double T Right
const char DTL  = char(185);        //Double T Left
const char SULC = char(218);        //Single Upper Left Corner
const char SURC = char(191);        //Single upper Right Corner
const char SBLC = char(192);        //Single Bottom Left Corner
const char SBRC = char(217);        //Single Bottom Right Corner
const char SVB  = char(179);        //Single Verticle Bar
const char SHB  = char(196);        //Single Horizontal Bar
const char ST   = char(197);        //Single T Junction
const char STD  = char(194);        //Single T Points Down
const char STU  = char(193);        //Single T Points Up
const char STR  = char(195);        //Single T Points Right
const char STL  = char(180);        //Single T Points Left

//Colors as pre-defined constants
////////////////////////////////////////////////////////////////////////////////
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define AQUA            3
#define RED             4
#define PURPLE          5
#define YELLOW          6
#define WHITE           7
#define GRAY            8
#define BRIGHT_BLUE     9
#define BRIGHT_GREEN    10
#define BRIGHT_AQUA     11
#define BRIGHT_RED      12
#define BRIGHT_PURPLE   13
#define BRIGHT_YELLOW   14
#define BRIGHT_WHITE    15

class AsciiDraw
{
private:
    int     BinToDecimal(char *);
    void    SetColors();
    COORD   BaseXY;
    COORD   CurrXY;
    int     ForeColor;
    int     BackColor;
public:
            AsciiDraw(void);
    COORD   GetXY();
    int     GetX();
    int     GetY();
    COORD   GetBaseXY();
    int     GetBaseX();
    int     GetBaseY();

    void    SetBaseXY(int,int);
    void    SetBaseXY(COORD);
    void    SetXY(int,int);
    void    SetXY(COORD);
    void    SetX(int);
    void    SetY(int);

    void    SetBackgroundColor(char *);     
    void    SetBackgroundColor(int);        
    void    SetColors(char *);                  
    void    SetColors(int,int);     
    void    SetForegroundColor(char *);
    void    SetForegroundColor(int);

    void    PrintRotator(int ,int ,int ,int);
};

//---------------------------------------------------------------------
// Dependancies:
//		None
// This class represents a single entry in a table (aka Cell). It has 
// data members to keep track of contents, colors, and it's own location.
//---------------------------------------------------------------------
class Cell{
private:
    int ForeGroundColor;
    int BackGroundColor;
    char Ch;
    bool Occupied;
public:
	Cell(){
		ForeGroundColor = 8;	// Gray
		BackGroundColor = 4;	// Black
		Ch = ' ';				// Space (empty);
		Occupied = false;		// Set to unoccupied
	}

	//Public Methods////////////////////////////////////////////////////////////////

	//GETTERS/////////////////////////////////////////////////////////////////////// 

	/** GetCharacter
	* 
	* Returns a copy of the character in the cell.
	*
	* @param    void
	* @return   char
	*/
	char GetCharacter(){
        return Ch;
    }

	/** IsOccupied
	* 
	* Returns true if cell is being occupied.
	*
	* @param    void
	* @return   bool
	*/
	bool IsOccupied(){
        return Occupied;
    }

	/** GetCharColor
	* 
	* Returns color of character in cell.
	*
	* @param    void
	* @return   int  - color
	*/
	int GetCharColor(){
		return ForeGroundColor;
	}

	/** GetBackgroundColor
	* 
	* Returns color of background in cell.
	*
	* @param    void
	* @return   int  - color
	*/
	int GetBackgroundColor(){
		return BackGroundColor;
	}

	//SETTERS/////////////////////////////////////////////////////////////////////// 

	/** SetForeGroundColor
	* 
	* Sets the foreground color of the table cell (e.g. character color).
	*
	* @param    int Color - See predefined constants above.
	* @return   void
	*/
    void SetForeGroundColor(int Color){
        ForeGroundColor = Color;
    }

	/** SetBackGroundColor
	* 
	* Sets the background color of the table cell (not necessarily the whole table cell, but the background of the character).
	*
	* @param    int Color - See predefined constants above.
	* @return   void
	*/
    void SetBackGroundColor(int Color){
        BackGroundColor = Color;
    }

	/** SetBackGroundColor
	* 
	* Sets the character to be held in the table. Also sets cell to be occupied, since a character is being placed in the cell.
	*
	* @param    char ch - Ascii character.
	* @return   void
	*/
    void SetCharacter(char ch){
        Ch = ch;
		Occupied = true;
    }

	/** SetOccupied
	* 
	* Sets the character to be held in the table.
	*
	* @param    char ch - Ascii character.
	* @return   void
	*/
    void SetOccupied(){
        Occupied=true;
    }

	/** SetUnOccupied
	* 
	* Makes the Cell "unoccupied", but doesn't change the character (if any) that is in the cell. That must be explicitly done.
	*
	* @param    void
	* @return   void
	*/
    void SetUnOccupied(){
        Occupied=false;
    }

	/** Overloaded = operator
	* 
	* This method will be called when one cell is being assigned to another. 
	*
	* @param    Cell param 
	* @return   Cell Temp
	*/
	Cell& operator= (Cell param){
		Cell Temp;
		Temp.BackGroundColor = param.GetBackgroundColor();
		Temp.Ch = param.GetCharacter();
		Temp.ForeGroundColor = param.GetCharColor();
		return Temp;
	}

};


//---------------------------------------------------------------------
// Dependancies:
//		class AsciiDraw
//		class Cell
// This class is a bloated 2D array representation. It uses "AsciiDraw" to
// draw the table borders etc., and uses the class "Cell" to add functionality
// to each array location. See description of Cell class.
//---------------------------------------------------------------------
class Table : public AsciiDraw{
private:
    int Rows;
    int Cols;
    Cell **TableArray;
    int CurrentRow;
    int CurrentCol;
    int BaseX;
    int BaseY;
    int CurrentX;
    int CurrentY;
    int Padding;
    int BorderColor;
    void DrawCellBody(int);
    void DrawCellSides(int);
    void DrawUpperLeftCell();
    void DrawTopRightCorner();
    void DrawTopLeftCorner();
    void DrawBottomRightCorner();
    void DrawBottomLeftCorner();
    void DrawVerticalLine(int);
    void DrawHorizontalLine(int);
    void DrawTableTopBorder();
    void DrawTableMiddleBorders();
    void DrawTableBottomBorder();
    void DrawMiddleTJunction();
	void DrawTRight();
	void DrawTLeft();
	void DrawT();
    void DrawTDown();
    void DrawInvertedT();
    void MoveLeft(int);
    void MoveRight(int);
    void MoveUp(int);
    void MoveDown(int);
    void ResetXY();
    void DrawTableContents();
    void InitTableArray();
public:
    Table(int, int, int,int, int);
	void FillCell(int row, int col, char ch);
	void FillCell(int row, int col, char ch,int color);
	bool SwapCells(int row, int col, char direction);
	void SetBackGroundColor(int row,int col,int color);
	char GetCellCharacter(int row, int col);
	int  GetCharacterColor(int row,int col);
	int  GetBackGroundColor(int row, int col);
    void DrawTable();
	void ExplodeCell(int row,int col,int speed);
};

class ProgressBar : public AsciiDraw{
private:
	COORD BaseXY;
	int Length;
	int Color;
	int PercentDone;
	int Total;
	int Progress;
public:
	ProgressBar(){
		//Gets the current console position
		BaseXY.X = 0;
		BaseXY.Y = 5;
		Length = 40;
		Color = BRIGHT_GREEN;
		PercentDone = 0;
		Total = 0;
		Progress = 0;
	}

	ProgressBar(COORD base_xy,int color,int length){
		BaseXY = base_xy;
		Color = color;
		Length = length;
		PercentDone = 0;
	}

	void SetBaseXY(COORD basexy){
		BaseXY = basexy;
	}

	void InitProgressBar(int total,int x,int y,int length){
		BaseXY.X = x;
		BaseXY.Y = y;
		Total = total;
		Length = length;
		Progress = 0;
		PercentDone = 0;
		PrintShell();
	}

	void PrintShell(){
		double p = double(PercentDone)/100.0;
		SetForegroundColor(Color);
		SetXY(BaseXY);
		std::cout<<"[";
		for(int i=0;i<(Length*p);i++){
			cout<<char(176);
		}
		SetX(BaseXY.X + Length);
		std::cout<<"]";
	}

	void SetColor(int color){
		Color = color;
	}

	void PrintPercentDone(){
		SetX(BaseXY.X + Length+1);
		std::cout<<PercentDone<<"%";
	}

	void UpdateProgress(){
		Progress+=1;
		PercentDone = (double(Progress)/double(Total))*100;
		PrintPercentDone();
		PrintShell();
		if(PercentDone == 100){
			SetForegroundColor(WHITE);
			cout<<endl;
		}
	}
};

