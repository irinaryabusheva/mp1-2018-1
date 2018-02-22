#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;
class Rational
{
	int p; //числитель
	int q; //знаменатель
	int Nod(int a, int b);
public:
	Rational(int _p = 0, int _q = 1) : p(_p), q(_q) {};
	Rational Sum(const Rational &s)
	{
		int c;
		Rational tmp;
		tmp.p = p*s.q + q*s.p;
		tmp.q = q*s.q;
		if (tmp.p>tmp.q)
			c = Nod(tmp.p, tmp.q);
		else
			c = Nod(tmp.q, tmp.p);
		tmp.p = tmp.p / c;
		tmp.q = tmp.q / c;
		return tmp;
	};// сумма
	Rational Sub(const Rational &s)
	{
		int c;
		Rational tmp;
		tmp.p = p*s.q - q*s.p;
		tmp.q = q*s.q;
		if (tmp.p > tmp.q)
			c = Nod(tmp.p, tmp.q);
		else
			c = Nod(tmp.q, tmp.p);
		tmp.p = tmp.p / c;
		tmp.q = tmp.q / c;
		return tmp;
	};// вычитание
	Rational Mult(const Rational&s)
	{
		int c;
		Rational tmp;
		tmp.p = p*s.p;
		tmp.q = q*s.q;
		if (tmp.p>tmp.q)
			c = Nod(tmp.p, tmp.q);
		else
			c = Nod(tmp.q, tmp.p);
		tmp.p = tmp.p / c;
		tmp.q = tmp.q / c;
		return tmp;
	};// умножение
	Rational Div(const Rational &s)
	{
		int c;
		Rational tmp;
		tmp.p = p*s.q;
		tmp.q = q*s.p;
		if (tmp.p>tmp.q)
			c = Nod(tmp.p, tmp.q);
		else
			c = Nod(tmp.q, tmp.p);
		tmp.p = tmp.p / c;
		tmp.q = tmp.q / c;
		return tmp;
	};// деление
	void Print() const
	{
		cout << "(" << p << "/" << q << ")" "\n";
	};
	Rational operator=(const Rational &s)
	{
		p = s.p;
		q = s.q;
		return *this;
	};
};

int Rational::Nod(int a, int b)
{
	int nod = 1;
	for (int i = a; i > 0; i--)
	{
		if (a % i == 0 && b % i == 0)
		{
			nod = i;
			break;
		}
	}
	return nod;
}// нод

void main()
{
	Rational R1(5, 9), R2(4, 6), R3;
	R1.Print();
	R2.Print();

	R3 = R1.Sum(R2);
	cout << "sum = ";
	R3.Print();

	R3 = R1.Sub(R2);
	cout << "sub =";
	R3.Print();

	R3 = R1.Mult(R2);
	cout << "mult = ";
	R3.Print();

	R3 = R1.Div(R2);
	cout << "div = ";
	R3.Print();

	system("pause");
}