#include "AsciiDraw.h"

/** AsciiDraw constructor
* 
* This constructor simply initializes the following:
*		Forecolor = Gray;
*		BackColor = Black;
*		Top Left corner (where to start drawing) to 0,0 or top left of Dos window.
* @param    void
* @return   void
*
* GetConsoleCursorPosition(...)  // get the position X and Y of the cursor
* used SetConsoleCursorPosition(..)  // set the position X and Y of the cursor
* used SetConsoleTextAttribute(..)  // set attributes of console text , such as the color, font, dimension, ecc.
* ScrollConsoleScreenBuffer(...)  // move a part of the console in a new position 
*
*/
AsciiDraw::AsciiDraw(void)	//636-0014
{
    ForeColor=8;
    BackColor=0;
    BaseXY.X=0;
    BaseXY.Y=0;
    CurrXY.Y=0;
    CurrXY.X=0;
}

//Private Methods///////////////////////////////////////////////////////////////

/** BinToDecimal
* 
* @param    char * Binary - String of 0's and 1's to be converted to Decimal.
* @return   int - Decimal equivalent.
*/
int AsciiDraw::BinToDecimal(char * Binary){
        double total=0;
        for(int i=0,p=7;i<8;i++,p--){
                if(Binary[i]=='1')
                total += 1.0*pow(2.0,p);
        }
        return (int)total;
}

/** SetColors
* 
* Sets the Foreground and Background colors of the dos window, using the data
* members ForeColor and BackColor.
*
* @param    void
* @return   void
*/
void AsciiDraw::SetColors()
{
    int Buffer;                             //Buffer to hold both colors
    Buffer = BackColor*16;                  //Shift background left by 4 so 1001 would be 10010000
    Buffer =  Buffer + ForeColor;           //Add  BackGround with ForeGround color, so:
                                            //  1 0 0 1 0 0 0 0     (BRIGHT_BLUE background)
                                            //+ 0 0 0 0 1 1 1 0     (BRIGHT_YELLOW foreground)
                                            //---------------
                                            //  1 0 0 1 1 1 1 0     Combined foreground and background
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Buffer);
}

//Public Methods////////////////////////////////////////////////////////////////

//GETTERS///////////////////////////////////////////////////////////////////////

/** GetXY
* 
* Returns the current position of the cursor.
*
* @param    void
* @return   COORD
*/
COORD AsciiDraw::GetXY()
{
    return CurrXY;
}

/** GetX
* 
* Returns the current X coordinate.
*
* @param    void
* @return   int X - the X coordinate
*/
int AsciiDraw::GetX()
{
    return CurrXY.X;
}

/** GetY
* 
* Returns the current Y coordinate.
*
* @param    void
* @return   int Y - the Y coordinate
*/
int AsciiDraw::GetY()
{
    return CurrXY.Y;
}


//SETTERS///////////////////////////////////////////////////////////////////////
/** SetBaseXY
* 
* Sets the BaseXY of the current object. This is used to remember for example, the
* upper left corner of a box or something, so calculations can done based on this 
* location.
*
* @param    int X - new X coord
* @param    int Y - new Y coord
* @return   void
*/
void AsciiDraw::SetBaseXY(int x, int y)
{
    BaseXY.X = x;
    BaseXY.Y = y;
}

/** SetBaseXY
* 
* Sets the BaseXY of the current object. This is used to remember for example, the
* upper left corner of a box or something, so calculations can done based on this 
* location.
*
* @param    COORD P - new base XY position using P.X and P.Y
* @return   void
*/
void AsciiDraw::SetBaseXY(COORD P)
{
    BaseXY.X = P.X;
    BaseXY.Y = P.Y;
}

/** SetXY
* 
* Moves the cursor of the dos window to the specified X,Y where Top Left = 0,0 and
* X moves right and left and Y moves up and down.
*
* @param    int X - new X position
* @param    int Y - new Y position
* @return   void
*/
void AsciiDraw::SetXY(int x, int y)
{
    CurrXY.X = x;
    CurrXY.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CurrXY);
}

/** SetXY
* 
* Moves the cursor of the dos window to the specified X,Y where Top Left = 0,0 and
* X moves right and left and Y moves up and down.
*
* @param    COORD P - new XY position using P.X and P.Y
* @return   void
*/
void AsciiDraw::SetX(int x)
{
    CurrXY.X = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CurrXY);
}

/** SetXY
* 
* Moves the cursor of the dos window to the specified X,Y where Top Left = 0,0 and
* X moves right and left and Y moves up and down.
*
* @param    COORD P - new XY position using P.X and P.Y
* @return   void
*/
void AsciiDraw::SetY(int y)
{
    CurrXY.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CurrXY);
}

/** SetXY
* 
* Moves the cursor of the dos window to the specified X,Y where Top Left = 0,0 and
* X moves right and left and Y moves up and down.
*
* @param    COORD P - new XY position using P.X and P.Y
* @return   void
*/
void AsciiDraw::SetXY(COORD P)
{
    CurrXY.X = P.X;
    CurrXY.Y = P.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CurrXY);
}

/** SetBackgroundColor
*
* Uses a binary string to set the Background colors where bits are numbered from right to left 1 - 4.
* 
* Setting:       Bright Red Green Blue
* Bit:            4    3    2    1
* Example: "1001" would make the background Bright Blue
* @param    char * binary
* @return   void
*/
void AsciiDraw::SetBackgroundColor(char * binary)
{
    BackColor = BinToDecimal(binary);
    SetColors();
}

/** SetBackgroundColor
*
* Uses an int value to change the Background color
*
* Example: 13 would make the background Light Purple
* @param    int color
* @return   void
*/
void AsciiDraw::SetBackgroundColor(int color)
{   
    BackColor = color;
    SetColors();
}

/** SetColors
*
* Uses a binary string to set the Background and Foreground colors where bits 
* are numbered from right to left 1 - 8.
*                       Background          Foreground
* Setting:      Bright Red Green Blue Bright Red Green Blue
* Bit:             8    7    6     5     4    3    2    1
* Example: "11101010" would make the background Bright Yellow and the foreground Bright Green.
* @param    char * binary
* @return   void
*/
void AsciiDraw::SetColors(char * binary)
{
    int ColorVal = BinToDecimal(binary);
    BackColor = ColorVal >> 4;
    ForeColor = ColorVal & 0xF;
    SetColors();
}

/** SetColors
*
* Uses integer values to set foreground and background colors.
* 0 = Black     8 = Gray
* 1 = Blue      9 = Light Blue
* 2 = Green     10 = Light Green
* 3 = Aqua      11 = Light Aqua
* 4 = Red       12 = Light Red
* 5 = Purple    13 = Light Purple
* 6 = Yellow    14 = Light Yellow
* 7 = White     15 = Bright White
* @param    int BackGround
* @param    int ForeGround
* @return   void
*/
void AsciiDraw::SetColors(int BackGround,int ForeGround)
{
    ForeColor = ForeGround;
    BackColor = BackGround;
    SetColors();
}

/** SetForegroundColor
*
* Uses a binary string to set the Foreground colors where bits are numbered from right to left 1 - 4.
* 
* Setting:       Bright Red Green Blue
* Bit:             4    3    2    1
* Example: "1001" would make the Foregound Bright Blue
* @param    char * binary
* @return   void
*/
void AsciiDraw::SetForegroundColor(char * binary)
{
    ForeColor = BinToDecimal(binary);
    std::cout<<ForeColor<<std::endl;
    SetColors();
}

/** SetForegroundColor
*
* Uses an int value to change the Background color
*
* Example: 13 would make the foreground Light Purple
* @param    int color
* @return   void
*/
void AsciiDraw::SetForegroundColor(int color)
{
    ForeColor = color;
    SetColors();
}

/** PrintRotator
* 
* Prints a simple animation that mimics a rotator (usually for a waiting process).
*
* @param    int times - number of times to rotate
* @param    int x - x coord, where to start the rotation
* @param    int y - y coord, where to start the rotation
* @param    int speed - In milliseconds. How fast to "rotate". Smaller value = faster rotation. (e.g. 10 <= speed <= 100) 
* @return   void
*/
void AsciiDraw::PrintRotator(int times,int x,int y,int speed){
    for(int i=0;i<times;i++){
            SetXY(x,y);
            std::cout<<char(221);
            Sleep(speed);
            SetXY(x,y);
            std::cout<<char(220);
            Sleep(speed);
            SetXY(x,y);
            std::cout<<char(222);
            Sleep(speed);
            SetXY(x,y);
            std::cout<<char(223);
            Sleep(speed);
    }
}

/** Table
* 
* Creates an instance of a Table, where a table is really an 2D array of "Cells", along with the Ascii drawing that
* makes the table look nifty.
*
* @param    int rows - Number of rows in the table
* @param    int cols - Number of cols in the table
* @param    int color - Border color of table (see predefined colors in AsciiDraw.h)
* @param    int x - x coord of where to start the drawing
* @param    int y - y coord of where to start the drawing
* @return   void
*/
Table::Table(int rows, int cols, int color, int x, int y)
{
	//Initialize all the data members
    Rows = rows;
    Cols = cols;
    BaseX = x;
    BaseY = y;
    CurrentX = x;
    CurrentY = y;
    BorderColor = color;
    Padding=2;

	//Loop through the 2D array and setup all the colors.
    InitTableArray();

	//Set the border color of the table.
    SetForegroundColor(BorderColor);

	//Go to the x,y coordinate specified in the params.
    SetXY(CurrentX,CurrentY);

}

/** InitTableArray
* Dynamically creates and simultaniously Loops through the
* TableArray (that contains "cells" which are also objects) 
* and intializes each of them to the following:
*           BackgroundColor = black
*           ForeGroundColor = black
*           Character = space
*           Cell = UnOccupied
* @param    void
* @return   void
*/
void Table::InitTableArray(){
	//Create a single dimensional array of Cell pointers
    TableArray = new Cell *[Rows];

	//Loop through and attach a single dimensional array of Cells(s) of size Cols to 
	//each of the Cell pointers in the array above.
    for(int i=0;i<Rows;i++){
        TableArray[i] = new Cell[Cols];	//Attache the 1D array to TableArray[i]

		//Loop through the new row, and initialize each cell.
        for(int j=0;j<Cols;j++){
            TableArray[i][j].SetBackGroundColor(0);
            TableArray[i][j].SetForeGroundColor(0);
            TableArray[i][j].SetCharacter((char)255);
            TableArray[i][j].SetUnOccupied();
        }
    }

}

/** DrawTable
* 
* Actually dumps the table to the dos window.
*
* @param    void
* @return   void
*/
void Table::DrawTable(){
	
    ResetXY();					//Go to baseX and baseY

	//Not most efficient way to draw, but probably more readable for
	//intro CS students
    for(int c=0;c<Rows;c++){
        for(int r=0;r<Cols;r++){
            DrawCellBody(Padding);
            MoveUp(Padding+1);
        }
        MoveLeft(Padding*Cols+Cols);
        MoveDown(Padding+1);
    }
    DrawTableTopBorder();
    DrawTableMiddleBorders();
    DrawTableBottomBorder();
    DrawTableContents();
}

/** DrawTableTopBorder
* 
* Draws the top of the table
*
* @param    void
* @return   void
*/
void Table::DrawTableTopBorder(){
	
    ResetXY();					//Goback to baseX and baseY
    DrawTopLeftCorner();					
    for(int i=0;i<Cols-1;i++){
        MoveRight(Padding+1);	//Horizontal bar of cell is drawn seperately
        DrawTDown();			//Draw a downward "T"
    }
    MoveRight(Padding+1);
    DrawTopRightCorner();		
}

void Table::DrawTableMiddleBorders(){
    ResetXY();
    for(int j=0;j<Rows-1;j++){
        MoveDown(Padding*2-1);
        DrawTRight();
        for(int i=0;i<Cols-1;i++){
            MoveRight(Padding+1);
            DrawT();
        }
        MoveRight(Padding+1);
        DrawTLeft();
        CurrentX = BaseX;
        SetXY(CurrentX,CurrentY);
    }
}

void Table::DrawTableBottomBorder(){
    ResetXY();
    MoveDown(Rows*(Padding+1));
    DrawBottomLeftCorner();
    for(int i=0;i<Cols-1;i++){
        MoveRight(Padding+1);
        DrawInvertedT();
    }
    MoveRight(Padding+1);
    DrawBottomRightCorner();
}

void Table::DrawTableContents(){
    ResetXY();
    for(int i=1;i<=Rows;i++){
        for(int j=1;j<=Cols;j++){
            if(TableArray[i-1][j-1].IsOccupied()){
				SetBackgroundColor(TableArray[i-1][j-1].GetBackgroundColor());
				SetForegroundColor(TableArray[i-1][j-1].GetCharColor());
                SetXY( (BaseX+j*(Padding+1))-1,(BaseY+i*(Padding+1))-1);
                cout<<TableArray[i-1][j-1].GetCharacter();
                SetXY( (BaseX+j*(Padding+1))-2,(BaseY+i*(Padding+1))-2);
                cout<<TableArray[i-1][j-1].GetCharacter();
                SetXY( (BaseX+j*(Padding+1))-2,(BaseY+i*(Padding+1))-1);
                cout<<TableArray[i-1][j-1].GetCharacter();
                SetXY( (BaseX+j*(Padding+1))-1,(BaseY+i*(Padding+1))-2);
                cout<<TableArray[i-1][j-1].GetCharacter();
            }
        }
    }

	SetForegroundColor(BorderColor);
	SetBackgroundColor(0);

}

void Table::DrawCellBody(int size){
    MoveRight(1);
    DrawHorizontalLine(size);
    MoveDown(1);
    MoveLeft(size+1);
    DrawCellSides(size);
    DrawHorizontalLine(size);
}

void Table::DrawCellSides(int size){
    for(int i=0;i<size;i++){
        DrawVerticalLine(0);
        MoveRight(size+1);
        DrawVerticalLine(0);
        MoveLeft(size+1);
        MoveDown(1);
    }
    MoveRight(1);
}

void Table::DrawUpperLeftCell(){
    DrawTopLeftCorner();
    DrawHorizontalLine(3);
    DrawTDown();
    MoveDown(1);
    MoveLeft(3);
    DrawVerticalLine(1);
    MoveUp(1);
    MoveRight(3);
    DrawVerticalLine(1);
    MoveLeft(3);
    DrawVerticalLine(1);
    MoveUp(1);
    MoveRight(3);
    DrawVerticalLine(1);
    MoveLeft(3);
    DrawBottomLeftCorner();
    DrawHorizontalLine(3);
    DrawInvertedT();
}

void Table::MoveLeft(int x){
    CurrentX -= x;
    SetXY(CurrentX,CurrentY);
}

void Table::MoveRight(int x){
    CurrentX += x;
    SetXY(CurrentX,CurrentY);
}

void Table::MoveUp(int y){
    CurrentY -= y;
    SetXY(CurrentX,CurrentY);
}

void Table::MoveDown(int y){
    CurrentY += y;
    SetXY(CurrentX,CurrentY);
}

void Table::DrawTopRightCorner(){
    cout<<SURC;
}

void Table::DrawTopLeftCorner(){
    cout<<SULC;
}

void Table::DrawBottomRightCorner(){
    cout<<SBRC;
}

void Table::DrawBottomLeftCorner(){
    cout<<SBLC;
}

void Table::DrawTDown(){
    cout<<STD;
}

void Table::DrawTRight(){
    cout<<STR;
}

void Table::DrawTLeft(){
    cout<<STL;
}

void Table::DrawT(){
    cout<<ST;
}

void Table::DrawInvertedT(){
    cout<<STU;
}

void Table::DrawVerticalLine(int length){
    if(length == 0){
        cout<<SVB;
        return;
    }
    for(int i=0;i<length;i++){
        cout<<SVB;
        MoveDown(1);
    }
}

void Table::DrawHorizontalLine(int length){
    if(length == 0){
        cout<<SHB;
        return;
    }
    for(int i=0;i<length;i++){
        cout<<SHB;
        MoveRight(1);
    }
}

void Table::DrawMiddleTJunction(){
    cout<<ST;
}

void Table::ResetXY(){
    CurrentX = BaseX;
    CurrentY = BaseY;
    SetXY(CurrentX,CurrentY);
}


void Table::FillCell(int row,int col,char ch){
    TableArray[row][col].SetCharacter(ch);
}

void Table::FillCell(int row,int col,char ch,int color){
    TableArray[row][col].SetCharacter(ch);
	TableArray[row][col].SetForeGroundColor(color);
}

char Table::GetCellCharacter(int row, int col){
	return TableArray[row][col].GetCharacter();
}

int Table::GetBackGroundColor(int row, int col){
	return TableArray[row][col].GetBackgroundColor();
}

void Table::SetBackGroundColor(int row,int col,int color){
	TableArray[row][col].SetBackGroundColor(color);
}


