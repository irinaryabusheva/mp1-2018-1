#include<iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>  
using namespace std;

enum Direction { RIGHT, LEFT, UP, DOWN };

class Game
{
	bool GameOver;
	bool Win;
	int x, y;
	int foodX, foodY;
	int tailX[100];
	int tailY[100];
	int nTail = 5;
	Direction dir;
	int  width, height;
	int speed;
	int lengthToWin;
	void GetRandFood()
	{
		srand(time(NULL));
		foodX = rand() % width;
		foodY = rand() % height;
	}
	void GetRandSnake() {
		x = rand() % (width - 4) + 1;
		y = rand() % height + 1;
		int m = x;
		for (int i = 0; i < 4; i++) {
			m++;
			tailX[i] = m;
			tailY[i] = y;
		}
	}
public:
	Game(int _width, int _height, int _speed, int _lengthToWin)
	{
		GameOver = false;
		Win = false;
		width = _width;
		height = _height;
		speed = _speed;
		lengthToWin = _lengthToWin;
		dir = LEFT;
		GetRandSnake();
		GetRandFood();
	};

	void Map()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		system("cls");
		for (int i = 0; i < width + 2; i++)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
			cout << "#";
		}
		cout << endl;

		for (int i = 0; i < height + 1; i++) {
			for (int j = 0; j < width + 2; j++)
			{
				if (j == 0 || j == width) {
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
					cout << "#";
				}
				if (i == y && j == x) {
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
					cout << "0";
				}
				else if (i == foodY && j == foodX) {
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
					cout << "@";
				}
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
							cout << "o";
						}
					}
					if (!print)
						cout << " ";
				}
			}
			cout << endl;
		}
		for (int i = 0; i < width + 2; i++)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
			cout << "#";
		}
		cout << endl;
		cout << "You lendth: " << nTail << endl;
		cout << "Length to win:" << lengthToWin << endl;
	}
	void Control() {
		Sleep(speed);
		if (_kbhit())
		{
			switch (_getch())
			{
			case 75:
				if (dir != RIGHT)
					dir = LEFT;
				break;
			case 77:
				if (dir != LEFT)
					dir = RIGHT;
				break;
			case 72:
				if (dir != DOWN)
					dir = UP;
				break;
			case 80:
				if (dir != UP)
					dir = DOWN;
				break;
			case 'x':
				GameOver = true;
				break;
			}
		}
	}
	void Move()
	{
		int prX = tailX[0];
		int prY = tailY[0];
		int pr2X, pr2Y;
		tailX[0] = x;
		tailY[0] = y;
		for (int i = 1; i < nTail; i++)
		{
			pr2X = tailX[i];
			pr2Y = tailY[i];
			tailX[i] = prX;
			tailY[i] = prY;
			prX = pr2X;
			prY = pr2Y;
		}
		switch (dir)
		{
		case RIGHT:
			x++;
			break;
		case LEFT:
			x--;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		}

		if (x > width || x < 0 || y > height || y < 0)
		{
			GameOver = true;
		}
		for (int i = 2; i < nTail; i++)
		{
			if (tailX[i] == x && y == tailY[0])
				GameOver = true;
		}
		if (x == foodX && y == foodY)
		{
			bool tmp = true;
			while (tmp)
			{
				tmp = false;
				GetRandFood();
				for (int i = 0; i <= nTail; i++)
					if (tailX[i] == foodX && tailY[i] == foodY)
					{
						tmp = true;
						break;
					}
			}
			nTail++;
		}
		if (lengthToWin == nTail)
			Win = true;
	}
	bool Over()
	{
		return GameOver;
	};
	bool GameWin()
	{
		return Win;
	};
};
int main()
{
	HWND hWnd = GetForegroundWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	srand(time(NULL));
	/*int _width;
	int _height;
	int _speed;
	int _lengthToWin;
	cout << "Enter width" << endl;
	cin >> _width;
	cout << "Enter height" << endl;
	cin >> _height;
	cout << "Enter speed" << endl;
	cin >> _speed;
	cout << "Enter length to win" << endl;
	cin >> _lengthToWin;

	//Game game(_width, _height, _speed, _lengthToWin);*/
	Game game(30, 30, 150, 10);
	//system("cls");

	while (!game.Over() && !game.GameWin())
	{
		game.Map();
		game.Control();
		game.Move();
	}

	if (game.Over())
	{
		cout << "GAME OVER" << endl;
		cout << "YOU LOSE" << endl;
	}

	if (game.GameWin())
	{
		cout << "YOU WON" << endl;
	}
	system("pause");
	return 0;
}
