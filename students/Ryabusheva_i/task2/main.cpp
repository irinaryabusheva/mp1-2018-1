#include <iostream>
#include <math.h>
using namespace std;
class Polynom
{
	int deg;
	double *koef;;
public:
	Polynom();
	Polynom(int k, double arr[]);
	~Polynom();
	Polynom& operator = (const Polynom &);
	int GetDeg();
	double GetKoef(int);
	double Calculate(double);
	void Print();
	Polynom derivative();
};

Polynom::Polynom() {
	deg = 0;
	for (int i = 0; i <= deg; i++)
		koef[i] = 0;
}

Polynom::Polynom(int k, double arr[]) {
	koef = new double[k + 1];
	deg = k;
	for (int i = 0; i <= k; i++)
		koef[i] = arr[i];
}

Polynom::~Polynom()
{
	delete[] koef;
}

Polynom& Polynom::operator = (const Polynom &s)
{
	if (this == &s)
		return *this;
	if (this != &s) {
		delete[] koef;
		koef = new double[deg + 1];
	}
	for (int i = 0; i <= deg; i++)
		koef[i] = s.koef[i];
	koef = s.koef;
	return *this;
}

int Polynom::GetDeg()
{
	return deg;
}

double Polynom::GetKoef(int i) {
	if (i <= deg)
		return koef[i];
	else
		return 0.0;
}

double Polynom::Calculate(double x)
{
	double sum = 0;
	for (int i = 0; i <= deg; i++)
		sum += koef[i] * pow(x, deg - i);
	return sum;
}

Polynom Polynom::derivative() {
	int i;
	Polynom Z(deg - 1);
	for (i = 0; i <= deg - 1; i++)
	{
		Z.koef[i] = (i + 1)*koef[i + 1];
	}
	returne Z;
}

void Polynom::Print()
{
	cout << koef[0] << "*(x^" << deg << ")";
	for (int i = 1; i < deg; i++)
	{
		if (koef[i]>0)
			cout << "+" << koef[i] << "*(x^" << deg - i << ")";
		else
			cout << koef[i] << "*(x^" << deg - i << ")";
	}
	if (koef[deg] > 0)
		cout << "+" << koef[deg] << "\n";
	else
		cout << koef[deg] << "\n";
}

void main()
{
	int n;
	double a[12];
	cout << "deg=";
	cin >> n;
	for (int i = 0; i <= n; i++) {
		cout << "koef[" << i << "] = ";
		cin >> a[i];
	}
	Polynom P(n, a);
	P.Print();
	double x;
	cout << "x=";
	cin >> x;
	cout << P.Calculate(x) << "\n";
	P.derivative();
	P.Print();
	system("pause");
}