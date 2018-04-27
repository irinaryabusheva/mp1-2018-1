#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Person
{
private:
	string Numb;
	string FullName;
	int Sum;
	string Pin;
	bool Block;
public:
	Person() {};
	Person(string _Numb, string _FullName, int _Sum, string _Pin, bool _Block = false) :Numb(_Numb), FullName(_FullName), Sum(_Sum), Pin(_Pin) {};
	string GetNumb()
	{
		return Numb;
	}
	int GetSum()
	{
		return Sum;
	}
	bool AddSum(int _Sum)
	{
		if (!Block || _Sum < 0)
		{
			return false;
		}
		Sum += _Sum;
		return true;
	}
	bool  LooseSum(int _Sum)
	{
		if (!Block || ((_Sum < 0) && (Sum < _Sum)))
		{
			return false;
		}
		Sum -= _Sum;
		return true;
	}
	string GetPin()
	{
		return Pin;
	}
	bool CheckPin(string _pin)
	{
		return _pin == Pin;
	}
	void SetBlock(bool _block)
	{
		Block = _block;
	}
	bool GetBlock()
	{
		return Block;
	}

	Person &operator=(const Person &s)
	{
		Numb = s.Numb;
		FullName = s.FullName;
		Pin = s.Pin;
		Sum = s.Sum;
		Block = s.Block;
	}
};


class PC
{
private:
	vector <Person> persons;
public:
	PC() {}
	PC(vector <Person> cp) { persons = cp; }
	void AddClient(string Numb, string FullName, int Sum, string Pin)
	{
		Person c(Numb, FullName, Sum, Pin);
		persons.push_back(c);
	}
	int CheckSum(int i)
	{
		return persons[i].GetSum();
	}
	int FindByNumb(string _numb)
	{
		for (size_t i = 0; i < persons.size(); i++)
			if (persons[i].GetNumb() == _numb)
				return i;
		return -1;
	}
	bool CheckByNumb(string _numb)
	{
		for (size_t i = 0; i < persons.size(); i++)
			if (persons[i].GetNumb() == _numb)
				return 1;
		return 0;
	}
	bool CheckByPin(int i, string _pin)
	{
		if (persons[i].CheckPin(_pin))
			return 1;
		return 0;
	}
	bool LooseCash(int i, int _sum)
	{
		return  persons[i].LooseSum(_sum);
	}
	bool AddCash(int i, int _sum)
	{
		return  persons[i].AddSum(_sum);
	}
	bool GetStatus(int i)
	{
		return  persons[i].GetBlock();
	}
	void SetBlock(int i, bool _block)
	{
		persons[i].SetBlock(_block);
	}
};

class ATM
{
private:
	int case100;
	int case200;
	int case500;
	int case1000;
	int case2000;
	int case5000;
	PC *center;
	int i;
public:
	ATM(PC *_center) {
		case100 = 1600000;
		case200 = 1600000;
		case500 = 1600000;
		case1000 = 1600000;
		case2000 = 1600000;
		case5000 = 1600000;
		center = _center;
	}
	bool BlockPerson()
	{
		center->SetBlock(i, false);
		return true;
	}
	bool CheckStatus()
	{
		return center->GetStatus(i);
	}
	bool FindPerson(string _Numb)
	{
		i = center->FindByNumb(_Numb);
		return center->CheckByNumb(_Numb);
	}
	bool CheckPinCode(string _pin)
	{
		return center->CheckByPin(i, _pin);
	}
	int CheckBalance()
	{
		return center->CheckSum(i);
	}
	bool WithdrawMoney(int _case100, int _case200, int _case500, int _case1000, int _case2000, int _case5000)
	{
		bool tmp = 0;
		if ((case100 >= _case100) && (case200 >= _case200) && (case500 >= _case500) && (case1000 >= _case1000) && (case2000 >= _case2000) && (case5000 >= _case5000))
		{
			int s = 100 * _case100 + 200 * _case200 + 500 * _case500 + 1000 * _case1000 + 2000 * _case2000 + 5000 * _case5000;
			if (center->CheckSum(i) >= s)
			{
				case100 -= _case100;
				case200 -= _case200;
				case500 -= _case500;
				case1000 -= _case1000;
				case2000 -= _case2000;
				case5000 -= _case5000;
				if (center->LooseCash(i, s))
					tmp = 1;
			}
		}
		return tmp;
	}
	bool DepositMoney(int _case100, int _case200, int _case500, int _case1000, int _case2000, int _case5000)
	{
		bool tmp = 0;
		if ((case100 + _case100 <= 2000000) && (case200 + _case200 <= 2000000) && (case500 + _case500 <= 2000000) && (case1000 + _case1000 <= 2000000) && (case2000 + _case2000 <= 2000000) && (case5000 + _case5000 <= 2000000))
		{
			int s = 100 * _case100 + 200 * _case200 + 500 * _case500 + 1000 * _case1000 + 2000 * _case2000 + 5000 * _case5000;
			if (center->CheckSum(i) >= s)
			{
				case100 += _case100;
				case200 += _case200;
				case500 += _case500;
				case1000 += _case1000;
				case2000 += _case2000;
				case5000 += _case5000;
				if (center->AddCash(i, s))
					tmp = 1;
			}
		}
		return tmp;
	}
};

int main()
{
	PC center;
	center.AddClient("0001", "Иванов Антон Павлович", 10000, "1111");
	center.AddClient("0002", "Петров Сергей Иванович", 25000, "2222");
	center.AddClient("0003", "Асадов Егор Владимирович", 50000, "3333");
	ATM atm(&center);
	int op;
	string s;
	string p;
	bool pin = 0,
		cash = 0,
		menu1 = 1,
		menu2 = 1;
	int _case100;
	int _case200;
	int _case500;
	int _case1000;
	int _case2000;
	int _case5000;
	while (menu1)
	{
		system("cls");
		cout << "Enter the card number: " << endl;
		cin >> s;
		if (!atm.FindPerson(s))
		{
			while (!atm.FindPerson(s))
			{
				cout << "Your card is not accepted!\n" << endl;
				cout << "Enter the card: \n" << endl;
				cin >> s;
			}
		}
		if (!atm.CheckStatus())
		{
			cout << "The operation was not performed. Your card is locked! \n" << endl;
			break;
		}

		while (menu2)
		{
			for (int i = 0; i < 3; i++)
			{
				cout << "Enter the PIN" << endl;
				cin >> p;
				if (atm.CheckPinCode(p))
				{
					cout << "Your card adopted! \n" << endl;
					pin = 1;
					break;
				}
				else
				{
					cout << "The PIN is incorrect!\n" << endl;
				}
			}
			if (!pin)
			{
				cout << "Your card is locked! \n" << endl;
				atm.BlockPerson();
				break;
			}
			cout << "Your card has been accepted\n" << endl;
			cout << "Choose an operation\n" << endl;
			cout << "1 - Withdraw money from the account" << "\n" << endl;
			cout << "2 - Deposit money to the account" << "\n" << endl;
			cout << "3 - Check balance" << "\n" << endl;
			cout << "4 - Exit" << "\n" << endl;
			cin >> op;
			switch (op)
			{
			case 1:
			{
				cout << "Enter 100: " << endl;
				cin >> _case100;
				cout << "Enter 200: " << endl;
				cin >> _case200;
				cout << "Enter 500: " << endl;
				cin >> _case500;
				cout << "Enter 1000: " << endl;
				cin >> _case1000;
				cout << "Enter 2000: " << endl;
				cin >> _case2000;
				cout << "Enter 5000: " << endl;
				cin >> _case5000;
				if (atm.WithdrawMoney(_case100, _case200, _case500, _case1000, _case2000, _case5000))
				{
					cout << "Success\n" << endl;
				}
				else
				{
					cout << "Sorry. The operation is currently unavailable!" << endl;
				}
				break;
			}
			case 2:
			{
				cout << "Enter 100: " << endl;
				cin >> _case100;
				cout << "Enter 200: " << endl;
				cin >> _case200;
				cout << "Enter 500: " << endl;
				cin >> _case500;
				cout << "Enter 1000: " << endl;
				cin >> _case1000;
				cout << "Enter 2000: " << endl;
				cin >> _case2000;
				cout << "Enter 5000: " << endl;
				cin >> _case5000;
				if (atm.DepositMoney(_case100, _case200, _case500, _case1000, _case2000, _case5000))
				{
					cout << "Success\n" << endl;
				}
				else
				{
					cout << "Sorry. The operation is currently unavailable!" << endl;
				}
				break;
			}
			case 3:
			{
				cout << atm.CheckBalance() << endl;
				break;
			}
			case 4:
			{
				menu2 = 0;
			}
			}
		}
	}
}