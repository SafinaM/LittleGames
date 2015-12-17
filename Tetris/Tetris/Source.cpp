//Simbols of Unicode are switch off. 

#pragma warning (disable : 4018)
#pragma warning (disable : 4244)
#pragma warning (disable : 4715)

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <cmath>
#include <conio.h>
#include <map>
#include <ctime>

#define PI 3.14159265   


using namespace std;

void SetCursor(int x, int y)                               //this function set the cursor to the definite coordinates
{                                                          //the origin is situated in the right up angel
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hConsole, coord);
}

class Point                             //the class point    
{

public:
	int x;
	int y;
	char sym;

	Point()
	{

	}
	Point(int _x, int _y, char _sym)   //the constructor with parameteres
	{
		x = _x;
		y = _y;
		sym = _sym;
	}
	Point(const Point &p)    //the constructor with object
	{
		x = p.x;
		y = p.y;
		sym = p.sym;
	}

	void SetCursor()                                //this function set the cursor to the definite inside coordinates 
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(hConsole, coord);
	}
	void Draw()                      //draw point in the console on the definite place by definite symbol
	{
		SetCursor();
		cout << sym;
	}
	void pDraw()                    //erase point in the console on the definite place 
	{
		SetCursor();
		cout << ' ';
	}
};


class zPoint        //class zPoint without symbol
{

public:
	int x;
	int y;


	zPoint()
	{

	}
	zPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	zPoint(const zPoint &p)
	{
		x = p.x;
		y = p.y;
	}
};


class Figure           //the parent class for all figures in the program
{
public:

	vector <Point> pList;      //vector for the figure array
	vector <Point> outputMatr; //vector for the output matrix which we'll see inside the walls after figures falling
	int tempCursorX;           //the temporary value for the coordinate X
	int tempCursorY;           //the temporary value for the coordinate Y


	void EraseAll()           //Clearing the pList
	{
		pList.clear();
	}

	void DrawGlass()            //showing of the ouput matrix in the console
	{
		for (int i = 0; i < outputMatr.size(); i++)
		{
			outputMatr[i].Draw();
		}
	}
	void pDrawGlass()         //erasing of the ouput matrix from the console
	{
		for (int i = 0; i < outputMatr.size(); i++)
		{
			outputMatr[i].pDraw();
		}
	}

	void Draw()         //drawing of the figure in the console
	{
		for (int i = 0; i < pList.size(); i++)
		{
			pList[i].Draw();
		}
	}
	void pDraw()     //drawing of the figure from the console
	{
		for (int i = 0; i < pList.size(); i++)
		{
			pList[i].pDraw();
		}
	}
	void AddToGlass(vector<Point> &pList)   //adding the elements of the figure-vector to the output matrix vector
	{
		for (int i = 0; i<pList.size(); i++)
			outputMatr.push_back(pList[i]);
	}
	bool verificationDown()          //verification of the intersection with the border
	{
		char tempSym = ' ';
		int tempX = 0;
		int tempY = 0;
		vector <zPoint> zList;


		for (int i = 0; i < pList.size(); i++)
		{
			tempX = pList[i].x;
			tempY = pList[i].y + 1;
			zPoint p(tempX, tempY);
			zList.push_back(p);
		}

		for (int i = 0; i < pList.size(); i++)
		{
			for (int j = 0; j < zList.size(); j++)
			{
				if (pList[i].x == zList[j].x && pList[i].y == zList[j].y)
				{
					zList.erase(zList.begin() + j);
					if (j>0)
					j--;
					if (i>0)
					i--;
				}
			}
		}

		for (int i = 0; i < zList.size(); i++)
		{
			if (!ReadFromConsole(zList[i].x, zList[i].y))
				return false;
		}
		return true;
	}

	bool virtual verificationLeft()   //virtual function for verificaction of the intersection with left border
	{

		char tempSym = ' ';
		int tempX = 0;
		int tempY = 0;
		vector <zPoint> zList;


		for (int i = 0; i < pList.size(); i++)
		{
			tempX = pList[i].x - 1;
			tempY = pList[i].y;
			zPoint p(tempX, tempY);
			zList.push_back(p);
		}

		for (int i = 0; i < pList.size(); i++)
		{
			for (int j = 0; j < zList.size(); j++)
			{
				if (pList[i].x == zList[j].x && pList[i].y == zList[j].y)
				{
					zList.erase(zList.begin() + j);
					if (j>0)
					j--;
					if (i>0)
					i--;
				}
			}
		}

		for (int i = 0; i < zList.size(); i++)
		{
			if (!ReadFromConsole(zList[i].x, zList[i].y))
				return false;
		}
		return true;
	}



	virtual bool verificationRight()         //virtual function for verificaction of the intersection with ricght border
	{

		int tempX = 0;
		int tempY = 0;
		vector <zPoint> zList;


		for (int i = 0; i < pList.size(); i++)
		{
			tempX = pList[i].x + 1;
			tempY = pList[i].y;
			zPoint p(tempX, tempY);
			zList.push_back(p);
		}

		for (int i = 0; i < pList.size(); i++)
		{
			for (int j = 0; j < zList.size(); j++)
			{
				if (pList[i].x == zList[j].x && pList[i].y == zList[j].y)
				{
					zList.erase(zList.begin() + j);
					if (j>0)
						j--;
					if( i>0 )
						i--;
				}
			}
		}

		for (int i = 0; i < zList.size(); i++)
		{
			if (!ReadFromConsole(zList[i].x, zList[i].y))
				return false;
		}
		return true;
	}

	bool ReadFromConsole(short int x, short int y)     //the function which is reading the symbol in the definite coordinates
	{
		const int sz = 1;
		char buff[sz];
		DWORD cbRead = 0;
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord = { x, y };
		ReadConsoleOutputCharacter(hStdout, buff, sz, coord, &cbRead);

		if (buff[0] == ' ')       //if the place on the coord plate is free the function will return the true
		{
			return true;
		}
		return false; // if the place on the coord plate is NOT free the function will return the false
	}
	bool ReadFromConsole2(short int x, short int y) //the function which is reading the symbol in the definite coordinates
	{
		const int sz = 1;
		char buff[sz];
		DWORD cbRead = 0;
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord = { x, y };
		ReadConsoleOutputCharacter(hStdout, buff, sz, coord, &cbRead);

		if (buff[0] == '*')
		{
			return true;       //if the place on the coord plate is * the function will return the true
		}
		return false;      //if the place on the coord plate is NOT * the function will return the false
	}

	void Move()
	{
		for (int i = 0; i< pList.size(); i++)
		{
			pList[i].y += 1;
		}
	}
	bool verificationOfLines(int glassBegin, int glassEnd, int glassHeight) //verification of the matrix on the comlete lines
	{
		bool tumb = false;

		int tempY = 0;
		for (int i = glassHeight - 1; i >= 0; i--)
		{
			for (int j = glassBegin; j < glassEnd; j++)
			{
				if (ReadFromConsole2(j, i))
				{

					if (j == glassEnd - 1)
					{
						tumb = true;
						tempY = i;
						SetCursor(60, 18);


						SetCursor(outputMatr[0].x, outputMatr[0].y);
						cout << " ";
						for (int k = 0; k < outputMatr.size(); k++)
						{

							if (outputMatr[k].y == tempY)
							{
								SetCursor(60, 10);


								outputMatr.erase(outputMatr.begin() + k);
								k--;
							}
							pDrawGlass();
						}
						for (int f = 0; f < outputMatr.size(); f++)
						{
							if (outputMatr[f].y < tempY)
							{
								outputMatr[f].y += 1;
							}
						}
						i++;
						pDrawGlass();
					}
				}
				else
					break;
			}
		}
		return tumb;
	}

	bool GameOver()          //the function of Game Over
	{
		for (int i = 0; i < outputMatr.size(); i++)
		{
			if (outputMatr[i].y == 0)
			{
				SetCursor(39, 12);
				cout << "GAME OVER" << endl;
				return true;
			}

		} return  false;

	}



	void MoveKey(char direction)            //moving figure to the left to the right and to down
	{
		if (direction == 75)
		{
			if (verificationLeft())
			{
				for (int i = 0; i< pList.size(); i++)
				{
					pList[i].x -= 1;
				}
			}
		}
		else if (direction == 77)
		{

			if (verificationRight())
			{
				for (int i = 0; i < pList.size(); i++)
				{
					pList[i].x += 1;
				}
			}
		}
		else if (direction == 80)
		{
			int i = 0;
			while (verificationDown())
			{
				for (int i = 0; i < pList.size(); i++)
				{
					pList[i].y += 1;
				}
			}
		}
	}


	void ChangeXY(int diffX, int diffY)       //changing of the coordinates for figure showing in another place of the console
	{
		for (int i = 0; i< pList.size(); i++)  //afinn's transform
 		{
			pList[i].x += diffX;
			pList[i].y += diffY;
		}
	}

	void virtual setBaseRotationPoint()      //setting of the rotation center
	{
		tempCursorX = pList[1].x;            //
		tempCursorY = pList[1].y;
	}

	void virtual Rotate()                  //rotating of the figure
	{
		if (abs(pList[2].x - pList[0].x) < abs(pList[2].y - pList[0].y))        //if the figure in the hor state...
		{
			if (verificationRight() && verificationLeft() && verificationDown())
			{
				setBaseRotationPoint();
				for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
				{
					pList[i].x -= tempCursorX;      
					pList[i].y -= tempCursorY;
				}
				for (int i = 0; i < pList.size(); i++)                //the matrix of rotation
				{
					int tempx, tempy;
					tempx = -pList[i].y;
					tempy = pList[i].x;
					pList[i].x = tempx;
					pList[i].y = tempy;
				}
				for (int i = 0; i< pList.size(); i++)              //return the figure to the beginning coordinates
				{
					pList[i].x += tempCursorX;
					pList[i].y += tempCursorY;
				}
			}
		}
		else            //if the figure in the vertical state
		{
			if (verificationDown())
			{
				setBaseRotationPoint();
				for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
				{
					pList[i].x -= tempCursorX;
					pList[i].y -= tempCursorY;
				}
				for (int i = 0; i < pList.size(); i++)              //the matrix of rotation
				{
					int tempx, tempy;
					tempx = -pList[i].y;
					tempy = pList[i].x;
					pList[i].x = tempx;
					pList[i].y = tempy;
				}

				for (int i = 0; i< pList.size(); i++)              //return the figure to the beginning coordinates
				{
					pList[i].x += tempCursorX;
					pList[i].y += tempCursorY;
				}
			}
		}
	}
};

class Line : public Figure
{
public:
	Line()
	{

		for (int i = 0; i < 4; i++)          //generating of the line
		{
			Point p(i, 0, '*');
			pList.push_back(p);
		}
	}

	bool verificationRightForLine()   //for line we write definite function for verification with right border
	{

		int tempX = 0;                 //the right point from the line
		int tempXNext = 0;             //the next right point from the line
		int tempY = 0;
		vector <zPoint> zList;
		int p = 0;
		for (int i = 0; i < pList.size(); i++)
		{
			tempX = pList[i].x + 1;          //take the value of the line x+1
			tempXNext = pList[i].x + 2;      //take the value of the line x+2
			tempY = pList[i].y;              //the value of y are the same
			zPoint p(tempX, tempY);
			zList.push_back(p);
			zPoint p1(tempXNext, tempY);
			zList.push_back(p1);             //the vector with two right and next points near line
		}

		for (int i = 0; i < pList.size(); i++)
		{
			for (int j = 0; j < zList.size(); j++)
			{
				if (pList[i].x == zList[j].x && pList[i].y == zList[j].y)  //comparing of the coordinates
				{
					zList.erase(zList.begin() + j);        //erasing points which are the same with the line
					if(j>0)
						j--;
					if(i>0)
						i--;
				}
			}
		}

		for (int i = 0; i < zList.size(); i++)
		{
			if (!ReadFromConsole(zList[i].x, zList[i].y))     //if the point near line is NOT emty return false 
				return false;                                //we cannot rotate
		}
		return true;                  //if the point near line is emty return true (we can rotate)
	}

	void Rotate() 
	{
		if (abs(pList[3].x - pList[0].x) < abs(pList[3].y - pList[0].y))   //if the line in the vertical state
		{
			if (verificationRightForLine() && verificationLeft() && verificationDown()) //all verification return true
			{
				setBaseRotationPoint();                            //setting the base point of the rotation
				for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
				{
					pList[i].x -= tempCursorX;                      //affin's transform
					pList[i].y -= tempCursorY;
				}
				for (int i = 0; i < pList.size(); i++)              //the matrix of rotation
				{
					int tempx, tempy;
					tempx = -pList[i].y;                      //put the line in the coordinate origin
					tempy = pList[i].x;
					pList[i].x = tempx;                      
					pList[i].y = tempy;
				}
				for (int i = 0; i< pList.size(); i++)              //return the figure to the beginning coordinates
				{
					pList[i].x += tempCursorX;
					pList[i].y += tempCursorY;
				}
			}
		}
		else                               //if the line in the horizontal state
		{
			if (verificationRight() && verificationDown())
			{
				setBaseRotationPoint();
				for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
				{
					pList[i].x -= tempCursorX;
					pList[i].y -= tempCursorY;
				}
				for (int i = 0; i < pList.size(); i++)                //the matrix of rotation
				{
					int tempx, tempy;
					tempx = pList[i].y;
					tempy = -pList[i].x;
					pList[i].x = tempx;
					pList[i].y = tempy;
				}

				for (int i = 0; i< pList.size(); i++)              //return the figure to the coordinate origin
				{
					pList[i].x += tempCursorX;
					pList[i].y += tempCursorY;
				}
			}
		}
	}


};
class figureT : public Figure           //T-figure
{
public:
	figureT()
	{
		for (int i = 0; i < 3; i++)
		{
			Point p(i, 0, '*');
			pList.push_back(p);
		}
		Point p(1, 1, '*');
		pList.push_back(p);
	}

	bool verificationLeftForFigureTRotation()
	{

		if (ReadFromConsole(pList[1].x - 1, pList[1].y))    //verification of the left point
			return true;                                    //if the point is empty return true
		else
			return false;                                  //else return false
	}
	bool verificationRightForFigureTRotation()              //verification of the right point
	{

		if (ReadFromConsole(pList[1].x + 1, pList[1].y))
			return true;
		else
			return false;
	}

	void Rotate()
	{
		if (verificationRightForFigureTRotation() && verificationLeftForFigureTRotation() && verificationDown())
		{
			setBaseRotationPoint();
			for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
			{
				pList[i].x -= tempCursorX;
				pList[i].y -= tempCursorY;
			}
			for (int i = 0; i < pList.size(); i++)               //the matrix of rotation
			{
				int tempx, tempy;
				tempx = -pList[i].y;
				tempy = pList[i].x;
				pList[i].x = tempx;
				pList[i].y = tempy;
			}
			for (int i = 0; i< pList.size(); i++)              //return the figure to the origin coordinates
			{
				pList[i].x += tempCursorX;
				pList[i].y += tempCursorY;
			}
		}

	}


};
class Quadrant : public Figure
{
public:
	Quadrant()
	{
		int j = 0;
		for (int i = 0; i < 2; i++)
		{
			Point p(i, j, '*');
			for (int j = 0; j < 2; j++)
			{
				Point p(i, j, '*');
				pList.push_back(p);
			}
		}
	}

	void Rotate()
	{
	}
};
class  figureGr : public Figure
{
public:
	figureGr()
	{
		int j = 0;
		for (int i = 1; i < 3; i++)
		{
			Point p(i, j, '*');
			pList.push_back(p);
		}
		j++;
		for (int i = 0; i < 2; i++)
		{
			Point p(i, j, '*');
			pList.push_back(p);
		}
	}

	void setBaseRotationPoint()
	{
		tempCursorX = pList[0].x;
		tempCursorY = pList[0].y;
	}

	void Rotate()
	{
		if (abs(pList[3].x - pList[0].x) > abs(pList[3].y - pList[0].y))   //if the figure in the horizontal state
		{
			if (verificationRight() && verificationDown())
			{
				setBaseRotationPoint();
				for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
				{
					pList[i].x -= tempCursorX;
					pList[i].y -= tempCursorY;
				}
				for (int i = 0; i < pList.size(); i++)                //the matrix of rotation
				{
					int tempx, tempy;
					tempx = pList[i].y;
					tempy = -pList[i].x;
					pList[i].x = tempx;
					pList[i].y = tempy;
				}
				for (int i = 0; i< pList.size(); i++)              //return the figure to the coordinate origin
				{
					pList[i].x += tempCursorX;
					pList[i].y += tempCursorY;
				}
			}
		}
		else                                                    //if the figure in the vertical state  
		{

			setBaseRotationPoint();              
			for (int i = 0; i < pList.size(); i++)              //put the figure to the coordinate origin
			{
				pList[i].x -= tempCursorX;
				pList[i].y -= tempCursorY;
			}
			for (int i = 0; i < pList.size(); i++)              //the matrix of rotation
			{
				int tempx, tempy;
				tempx = -pList[i].y;
				tempy = pList[i].x;
				pList[i].x = tempx;
				pList[i].y = tempy;
			}

			for (int i = 0; i< pList.size(); i++)              //return the figure to the coordinate origin
			{
				pList[i].x += tempCursorX;
				pList[i].y += tempCursorY;
			}

		}
	}

};
class figureGl : public Figure
{
public:
	figureGl()
	{
		int j = 0;
		for (int i = 0; i < 2; i++)
		{
			Point p(i, j, '*');
			pList.push_back(p);
		}
		j++;
		for (int i = 1; i < 3; i++)
		{
			Point p(i, j, '*');
			pList.push_back(p);
		}
	}

	void setBaseRotationPoint()
	{
		tempCursorX = pList[1].x;
		tempCursorY = pList[1].y;
	}


	void Rotate()
	{
		if (abs(pList[3].x - pList[0].x) < abs(pList[3].y - pList[0].y))    //if the figure in the vertical state  
		{
			if (verificationLeft() && verificationDown())
			{
				setBaseRotationPoint();
				for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
				{
					pList[i].x -= tempCursorX;
					pList[i].y -= tempCursorY;
				}
				for (int i = 0; i < pList.size(); i++)                //the matrix of rotation
				{
					int tempx, tempy;
					tempx = -pList[i].y;
					tempy = pList[i].x;
					pList[i].x = tempx;
					pList[i].y = tempy;
				}
				for (int i = 0; i< pList.size(); i++)              //teturn the figure to the beginning coordinates
				{
					pList[i].x += tempCursorX;
					pList[i].y += tempCursorY;
				}
			}
		}
		else                                                     //if the figure in the horizontal state  
		{

			setBaseRotationPoint();
			for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
			{
				pList[i].x -= tempCursorX;
				pList[i].y -= tempCursorY;
			}
			for (int i = 0; i < pList.size(); i++)                //the matrix of rotation
			{
				int tempx, tempy;
				tempx = pList[i].y;
				tempy = -pList[i].x;
				pList[i].x = tempx;
				pList[i].y = tempy;
			}

			for (int i = 0; i< pList.size(); i++)              //return the figure to the beginning coordinates
			{
				pList[i].x += tempCursorX;
				pList[i].y += tempCursorY;
			}
		}
	}


};
class figureLr : public Figure
{
public:
	figureLr()
	{
		for (int i = 0; i < 3; i++)
		{
			Point p(0, i, '*');
			pList.push_back(p);
		}

		Point p(1, 2, '*');
		pList.push_back(p);

	}
	bool verificationLeftForFigureLrRotation()
	{

		if (ReadFromConsole(pList[1].x - 1, pList[1].y))
			return true;
		else
			return false;
	}
	bool verificationRightForFigureLrRotation()
	{

		if (ReadFromConsole(pList[1].x + 1, pList[1].y))
			return true;
		else
			return false;
	}

	void Rotate()
	{
		if (verificationRightForFigureLrRotation() && verificationLeftForFigureLrRotation() && verificationDown())
		{
			setBaseRotationPoint();
			for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
			{
				pList[i].x -= tempCursorX;
				pList[i].y -= tempCursorY;
			}
			for (int i = 0; i < pList.size(); i++)                //the matrix of rotation
			{
				int tempx, tempy;
				tempx = -pList[i].y;
				tempy = pList[i].x;
				pList[i].x = tempx;
				pList[i].y = tempy;
			}
			for (int i = 0; i< pList.size(); i++)              //return the figure to the beginning coordinates
			{
				pList[i].x += tempCursorX;
				pList[i].y += tempCursorY;
			}
		}

	}
};
class figureLl : public Figure
{
public:
	figureLl()
	{

		for (int i = 0; i < 3; i++)
		{
			Point p(1, i, '*');
			pList.push_back(p);
		}
		Point p(0, 2, '*');
		pList.push_back(p);
	}

	bool verificationLeftForFigureLlRotation()
	{

		if (ReadFromConsole(pList[1].x - 1, pList[1].y))
			return true;
		else
			return false;
	}
	bool verificationRightForFigureLlRotation()
	{

		if (ReadFromConsole(pList[1].x + 1, pList[1].y))
			return true;
		else
			return false;
	}

	void Rotate()
	{
		if (verificationRightForFigureLlRotation() && verificationLeftForFigureLlRotation() && verificationDown())
		{
			setBaseRotationPoint();
			for (int i = 0; i < pList.size(); i++)               //put the figure to the coordinate origin
			{
				pList[i].x -= tempCursorX;
				pList[i].y -= tempCursorY;
			}
			for (int i = 0; i < pList.size(); ++i)                //the matrix of rotation
			{
				int tempx = 0, tempy = 0;
				tempy = pList[i].x;
				tempx = -pList[i].y;
				pList[i].x = tempx;
				pList[i].y = tempy;
			}
			for (int i = 0; i< pList.size(); i++)              //return the figure to the beginning coordinates
			{
				pList[i].x += tempCursorX;
				pList[i].y += tempCursorY;
			}
		}

	}

};

class VerticalLines : public Figure
{
	public:
	VerticalLines(int x, int yDown, int yUp, char sym)
	{
		for (int i = yDown; i < yUp; i++)
		{
			Point p(x, i, sym);
			pList.push_back(p);
		}
	}
};

class HorizontalLines : public Figure
{
	public:
	HorizontalLines(int xLeft, int xRight, int y, char sym)
	{
		for (int i = xLeft; i<xRight; i++)
		{
			Point p(i, y, sym);
			pList.push_back(p);
		}
	}
};


void Cursor_Invis()                                   //make the cursor is invisible
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

Figure* FigureGenerating()                       //generating firure
{
	int NoFig = rand() % 7 + 1;

	Figure *temp;
	switch (NoFig)
	{
		case 1:
		{
			temp = (Figure*) new Quadrant;      //casting of the Figure pointer to the hereditary class pointer
			return temp;
		}
		case 2:
		{
			temp = (Figure*) new Line;
			return temp;
		}
		case 3:
		{
			temp = (Figure*) new figureGr;
			return temp;
		}
		case 4:
		{
			temp = (Figure*) new figureGl;
			return temp;
		}
		case 5:
		{
			temp = (Figure*) new figureLr;
			return temp;
		}
		case 6:
		{
			temp = (Figure*) new figureLl;
			return temp;
		}
		case 7:
		{
			temp = (Figure*) new figureT;
			return temp;
		}
	} 
}


int main()
{

	char reStart = '0';

	Cursor_Invis();
	while (reStart != 27)            //while key != Esc
	{
		HorizontalLines bottom(35, 46, 21, '#');     //drawing bottom border of the glass
		bottom.Draw();
		VerticalLines leftLine(35, 0, 22, '#');      //drawing left border of the glass
		leftLine.Draw();
		VerticalLines rightLine(46, 0, 22, '#');     //drawing right border of the glass
		rightLine.Draw();

		Figure Out;
		srand(time(0));                              // randomizing
		Figure *t1;                                  //creating the pointer for the figure 1
		Figure *t2;                                  //creating the pointer for the figure 2
		int nLines = 0, nStage = 0;                  //counters for the lines and stages
		int time = 400;                              //first speed

		t1 = FigureGenerating();                     //generating the first figure

		while (true)
		{
			SetCursor(48, 0);                        //set cursor to the definite coordinates
			cout << "Next figure:";
			SetCursor(48, 5);
			cout << "Lines:" << " " << nLines;
			SetCursor(48, 7);
			cout << "Stage:" << " " << nStage;
			t2 = FigureGenerating();               //calling the second generating figure
			t2->ChangeXY(50, 2);                   //replacement of the second figure to the right from the glass
			t2->Draw();
			t1->ChangeXY(39, 0);                    //replacement of the first figure to the center of the glass
			t2->ChangeXY(-50, -2);                  //returning the second figure to the origin coodinates for following processing

			char key;
			while (true)
			{
				while (_kbhit())                   //if buffer keyboard is not empty
				{
					key = _getch();                //get the key code
					t1->pDraw();                   //erasing of the step of the first figure
					t1->MoveKey(key);              //the function of the keypressing
					t1->Draw();                    //redrawing of the first figure
					Sleep(27);                     //
					t1->pDraw();                   // erasing
					if (key == 32) t1->Rotate();    // if we press the backspace the figure is rotating
					t1->Draw();
				}
				Sleep(time);                      //long delay
				t1->pDraw();
				if (t1->verificationDown())        //verification of the figure intersection with the bottom border
				{
					t1->Move();
					t1->Draw();
				}
				else                             // in other case
				{
					while (_kbhit())             //if keyboard buffer is not empty
					{
						key = _getch();        //get the key code
						Sleep(30);             //short delay
						t1->pDraw();
						t1->MoveKey(key);
						t1->Draw();
						while (t1->verificationDown())
						{
							t1->pDraw();       //drawing
							t1->Move();        //erasing
							t1->Draw();        //re-drawing
						}
					}

					Out.AddToGlass(t1->pList);   //adding the figure to the output  matrix
					Out.DrawGlass();             //drawing the output matrix        

					while (Out.verificationOfLines(36, 46, 21))  //verification of the line completing    
					{
						nLines++;                  //line counter
						if (nLines % 20 == 0)
						{
							time -= 25;
							nStage++;             //Stage counter
						}
						Out.pDrawGlass();         //erasing output matrix
						Out.DrawGlass();          //re-drawing output matrix
					}

					Out.pDrawGlass();            //erasing output matrix
					Out.DrawGlass();             //re-drawing output matrix

					t1->EraseAll();             //clearing t1
					break;
				}
			}
			if (Out.GameOver())
			{
				SetCursor(30, 14);
				cout << "Do you want to restart the game? " << endl;
				SetCursor(30, 15);
				cout << "Press any key... No - Esc" << endl;
				reStart = _getch();
				break;
			}

			t2->ChangeXY(50, 2);
			t2->pDraw();
			t2->ChangeXY(-50, -2);
			t1 = t2;
		}
		system("cls");
	}
	system("pause");
	return 0;
}