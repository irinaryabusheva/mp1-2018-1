#include <iostream>
#include <math.h>
#include <conio.h>
using namespace std;

class Integral
{
	double left;
	double right;
	int Func;
	double Calculate(double x)
	{
		switch (Func)
		{
		case 0:
		{
			return sin(x);
			break;
		}
		case 1:
		{
			return cos(x);
			break;
		}
		case 2:
		{
			return exp(x);
			break;
		}
		}
		return 0;
	}

public:
	Integral(double _left = 0, double _right = 0, int _Func = 0) : left(_left), right(_right), Func(_Func) {};
	~Integral() {};

	Integral(const Integral &s)
	{
		left = s.left;
		right = s.right;
		Func = s.Func;
	}

	void SetBounds(double _left, double _right)
	{
		left = _left;
		right = _right;
	};
	void SetFuncNumber(int _Func)
	{
		Func = _Func;
	};

	double GetLeftBound()
	{
		return left;
	};
	double GetRightBound()
	{
		return right;
	};
	int GetFuncNumber()
	{
		return Func;
	};

	double RectangleLeft(int n)
	{
		int i;
		double result, h;
		result = 0;
		h = (right - left) / n;
		for (i = 0; i < n; i++)
		{
			result += Calculate(left + h * i);
		}
		result *= h;
		return result;
	};

	double RectangleRight(int n)
	{
		int i;
		double result, h;

		result = 0;
		h = (right - left) / n;
		for (i = 1; i <= n; i++)
		{
			result += Calculate(left + h * i);
		}
		result *= h;
		return result;
	};

	double RectangleMiddle(int n)
	{
		int i;
		double result, h;

		result = 0;
		h = (right - left) / n;
		for (i = 0; i < n; i++)
		{
			result += Calculate(left + h * (i + 0.5));
		}
		result *= h;
		return result;
	};

	Integral& operator=(const Integral &s)
	{
		left = s.left;
		right = s.right;
		Func = s.Func;
		return *this;
	}
};

int main()
{
	Integral i;
	int n;

	double left;
	double right;

	cout << "Input left and right bounds \n";
	cin >> left >> right;
	i.SetBounds(left, right);

	int Func;

	cout << "Input FuncNumber:\n";
	cout << "0 - sin\n";
	cout << "1 - cos\n";
	cout << "2 - exp\n";
	cin >> Func;
	i.SetFuncNumber(Func);

	int op;
	bool integral = 1;
	while (integral)
	{
		system("cls");
		cout << "1 - RectangleLeft\n";
		cout << "2 - RectangleRight\n";
		cout << "3 - RectangleMiddle\n";
		cout << "4 - Set new bounds\n";
		cout << "5 - Set new function\n";
		cout << "6 - Show bounds\n";
		cout << "7 - Show function\n";
		cout << "8 - Exit\n";
		cin >> op;
		switch (op)
		{
		case 1:
		{
			cout << "Input n \n";
			cin >> n;
			cout << i.RectangleLeft(n);
			_getch();
			break;
		}
		case 2:
		{
			cout << "Input n \n";
			cin >> n;
			cout << i.RectangleRight(n);
			_getch();
			break;
		}
		case 3:
		{
			cout << "Input n \n";
			cin >> n;
			cout << i.RectangleMiddle(n);
			_getch();
			break;
		}
		case 4:
		{
			cout << "Input left and right bounds \n";
			cin >> left >> right;
			i.SetBounds(left, right);
			break;
		}
		case 5:
		{
			cout << "0 - sin\n";
			cout << "1 - cos\n";
			cout << "2 - exp\n";
			cin >> Func;
			i.SetFuncNumber(Func);
			break;
		}
		case 6:
		{
			cout << "Left = " << i.GetLeftBound() << "\n";
			cout << "Right = " << i.GetRightBound();
			_getch();
			break;
		}
		case 7:
		{
			if (i.GetFuncNumber() == 0)
				cout << "sin";
			if (i.GetFuncNumber() == 1)
				cout << "cos";
			if (i.GetFuncNumber() == 2)
				cout << "exp";
			_getch();
			break;
		}
		case 8:
		{
			integral = 0;
			break;
		}
		}
	}
	system("pause");
	return 0;
}