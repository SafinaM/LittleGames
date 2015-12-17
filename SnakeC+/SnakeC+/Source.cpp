#pragma warning( disable: 4244)
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <list>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void SetCursorPosition(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Point
{

public:

	int x;             //the coordinate x
	int y;             //the coordinate y
	char sym;          //the symbol for any point

	Point(int _x, int _y, char _sym)    //the constructor with the coordinates and symbol
	{
		x = _x;
		y = _y;
		sym = _sym;
	}
	Point(const Point &p)           //the constructor with the point
	{
		x = p.x;
		y = p.y;
		sym = p.sym;
	}
	void Move(int offset, char direction)   // the coordinate changing depends on the direction
	{
		if (direction == 75)             //left
		{
			x = x - offset;
		}
		else if (direction == 77)             //right
		{
			x = x + offset;
		}
		else if (direction == 80)             //up
		{
			y = y + offset;
		}
		else if (direction == 72)            //down
		{
			y = y - offset;
		}


	}
	void Draw()                          //the drawint of the symbol in the definite coordinates
	{
		SetCursorPosition(x, y);
		cout << sym;
	}
	void pDraw(int tempx, int tempy)     //the erasing symbol in the definite coordinates
	{
		SetCursorPosition(x, y);
		cout << ' ';
	}

	friend bool operator ==(const Point &obj1, const Point &obj2);   //overloading of the == operator for Point class
	friend bool operator !=(const Point &obj1, const Point &obj2);   //overloading of the != operator for Point class
};
bool operator ==(const Point &obj1, const Point &obj2)
{
	if (obj1.x == obj2.x && obj1.y == obj2.y)
		return true;
	else
		return false;
}
bool operator !=(const Point &obj1, const Point &obj2)
{
	if (obj1.x != obj2.x || obj1.y != obj2.y)
		return true;
	else
		return false;
}

class Figure
{
public:
	vector <Point> pList;
	void Draw()
	{
		for (unsigned int i = 0; i<pList.size(); i++)
		{
			pList[i].Draw();
		}
	}
};
class HorizontalLines : public Figure                      //the class of the horizontal lines
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

class VerticalLines : public Figure                       //the class of the vertical lines
{
public:

	VerticalLines(int x, int yDown, int yUp, char sym)
	{
		for (int i = yDown; i<yUp; i++)
		{
			Point p(x, i, sym);
			pList.push_back(p);
		}
	}
};

class Snake : public Figure
{
public:

	char direction;
	Snake(Point Head, int len, char dir)
	{

		for (int i = 0; i<len; i++)
		{
			Point p(Head);
			p.Move(i, dir);
			pList.push_back(p);
		}
	}
	void Move()                                   //the move without parameter
	{
		Point Head = pList.front();
		Point Tail = pList.back();
		Head.Move(1, direction);
		pList.insert(pList.begin(), Head);
		pList.pop_back();
		Tail.pDraw(Tail.x, Tail.y);
	}
	void EraseTail()
	{
		while (pList.size() >= 4)
		{
			Point Tail = pList.back();
			pList.pop_back();
			Tail.pDraw(Tail.x, Tail.y);
		} 
	}

	bool Eat(Point Food)                           // if the coordinates of the food and the head are the same
	{                                              // the function will return true
		Point Head = pList.front();                // in other case it'll return false
		if (Head == Food)
		{
			Food.sym = Head.sym;
			pList.insert(pList.begin(), Food);
			return true;
		}
		else
			return false;
	}

	bool EatWithoutInsertion(Point Food)                           // if the coordinates of the food and the head are the same
	{                                              // the function will return true
		Point Head = pList.front();                // in other case it'll return false
		if (Head == Food)
		{
			return true;
		}
		else
			return false;
	}

	bool FoodOnSnake(Point Food)                    //if the coordinates of the next food are situated
	{                                               //on the snake  the function will return true

		if (find(pList.begin(), pList.end(), Food) != pList.end())
			return true;
		else
			return false;                            // in other case it'll return false
	}

	bool IntersectionWithTail()
	{
		Point Head = pList.front();                  // if the coordinates of the Head and of the snake body are the same
		for (unsigned int i = 2; i < pList.size(); i++)         //the function will return true
		{                                            //in other case it'll return false
			if (Head == pList[i])
			{
				for (unsigned int i = 2; i<pList.size(); i++)
				{
					if (pList[1] == pList[i])
						return false;
				}
				return true;
			}
		}
		return false;
	}

	void GameOver()                               //the Game Over function
	{
		SetCursorPosition(35, 10);
		cout << "GAME OVER!" << endl;
		SetCursorPosition(32, 11);
		cout << "To start - press Esc." << endl;
	}
	int SnakeLength()
	{
		return pList.size();
	}
};



class FoodCreator
{
	int _mapWidth;                                //the Width of the map
	int _mapHeight;                               //the Height of the map
	char _sym;                                     //the of the point

public:
	FoodCreator(int mapWidth, int mapHeight, char sym)  //constructor
	{
		_mapWidth = mapWidth - 2;
		_mapHeight = mapHeight - 2;
		_sym = sym;
	}
	Point CreateFood()               // the food is creating in the random coordinates on the map
	{
		srand(time(0));
		int x = (rand() % _mapWidth) + 2;
		int y = (rand() % _mapHeight) + 2;
		return Point(x, y, _sym);
	}
};
class Walls : public Figure                        // the class Walls for vertical and horizontal lines
{
public:
	vector <Figure> wList;
	Walls(int mapWidth, int mapHeight)
	{
		HorizontalLines downLine(0, mapWidth, 0, '*');
		HorizontalLines upLine(0, mapWidth, mapHeight, '*');
		VerticalLines leftLine(0, 0, mapHeight, '*');
		VerticalLines rightLine(mapWidth - 1, 0, mapHeight, '*');
		wList.push_back(downLine);
		wList.push_back(upLine);
		wList.push_back(leftLine);
		wList.push_back(rightLine);
	}
	void Draw()                                   // the draw fiunction of the Walls
	{
		for (unsigned int i = 0; i < wList.size(); i++)
		{
			wList[i].Draw();
		}
	}




	bool IntersectionWithWalls(Snake snake)         // if the coordinates of the Head Snake and of the walls are the same
	{                                               // the function will return true
		Point Head = snake.pList.front();           // in other case it'll return false
		for (unsigned int j = 0; j < wList.size(); j++)
		{
			for (unsigned int i = 0; i < wList[j].pList.size(); i++)
			{
				if (Head == wList[j].pList[i])
					return true;
			}
		}
		return false;
	}



};

void Cursor_Invis()
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);          //make the cursor is invisible
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void Start()
{
	system("cls");
	SetCursorPosition(10, 10);
	cout << "Snake. Please direct the snake by narrows Up, Down, Left and Right." << endl;
	Sleep(1000);
	system("cls");
	SetCursorPosition(32, 10);
	cout << "Are you ready?" << endl;
	Sleep(1000);

	system("cls");
	for (unsigned int i = 3; i != 0; i--)
	{
		SetCursorPosition(39, 10);
		cout << i << endl;
		Sleep(1000);
		system("cls");
	}
	SetCursorPosition(35, 10);
	cout << "START!" << endl;
	Sleep(1000);
	system("cls");
}

void Score(int &f, int &s, int &l)
{
	SetCursorPosition(26, 23);
	cout << "Score: " << endl;
	SetCursorPosition(34, 23);
	cout << f << endl;
	SetCursorPosition(37, 23);
	cout << "Stage: " << endl;
	SetCursorPosition(45, 23);
	cout << s << endl;
	SetCursorPosition(48, 23);
	cout << "Length: " << endl;
	SetCursorPosition(57, 23);
	cout << l << endl;
}



int main()
{
	Cursor_Invis();                         //the cursor become invisible
	char tumb = 27;

	do
	{
		Start();
		Walls walls(80, 22);                    //the class of the walls
		walls.Draw();                           //drawing of the wall class
		int nFoods = 0;
		int nStage = 0;
		int time = 200;
		Point Head(15, 10, 'O');                //the Head of the snake
		Snake snake(Head, 4, 77);               //the snake is coming to life by offset in the direction 77 (RIGHT)
		snake.Draw();                           //snake drawing
		int length = snake.SnakeLength();
		char key = 75;                          // the first direction of the movement 75 - LEFT
		FoodCreator F(79, 22, '&');             //the obj appearing in the map with Width 79 and Height 22, the symbol is &
		Point Food = F.CreateFood();            //creating of the food point     
		Food.Draw();                            //food drawing
		Score(nFoods, nStage, length);
		while (true)                      //while key != Esc
		{
			if (snake.EatWithoutInsertion(Food))
			{
				nFoods++;
				length = snake.SnakeLength();
				if (nFoods % 10 == 0)
				{
					nStage++;
					time -= 20;
				}
				if (nFoods % 60 == 0)
				{
					snake.EraseTail();
					length = snake.SnakeLength();
					SetCursorPosition(57, 23);               //erasing the number of previous length
					cout << " " << endl;
					SetCursorPosition(58, 23);               //erasing the number of previous length
					cout << " " << endl;
				}

				Score(nFoods, nStage, length);
			}

			if (snake.Eat(Food))  //if the snake have ate the food 
			{
				Food = F.CreateFood();                        //creating of the food point
				Food.Draw();                                  //food drawing
				length = snake.SnakeLength();
				Score(nFoods, nStage, length);
			}
			if(snake.FoodOnSnake(Food))  //if the food have appeared on the snake
			{
				Food = F.CreateFood();                        //creating of the food point
				Food.Draw();                                  //food drawing
			}

			if (snake.IntersectionWithTail() || walls.IntersectionWithWalls(snake)) //if the snake have met with the wall or with the Tail
			{
				snake.GameOver();       //the function of game over is calling
				break;
			}

			if (_kbhit())               //buffer keyboard not empty?
			{
				key = _getch();         //key gets ASCII code
			}
			snake.Draw();              
			Sleep(time);                 //interval time ms
			if (key == 72 || key == 75 || key == 77 || key == 80 || key == -32)  //if the key is LEFT, RIGHT, UP or DOWN    
			{
				snake.direction = key;                             // the snake change direction
			}
			snake.Move();
		}
		tumb = _getch();
	} while (tumb == 27);

	system("pause");
	return 0;
}
