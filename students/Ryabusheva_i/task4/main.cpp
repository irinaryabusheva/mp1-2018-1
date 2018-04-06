#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

struct Date {
	int day;
	int month;
	int year;
	Date(int _year = 0, int _month = 0, int _day = 0) : year(_year), month(_month), day(_day) {}
	Date& operator=(const Date& d)
	{
		day = d.day;
		month = d.month;
		year = d.year;
		return *this;
	}
	friend ostream &operator<<(ostream& os, const Date &obj);
}weightStartDate;

ostream &operator<<(ostream& os, const Date &obj)
{
	os << obj.day << '.' << obj.month << '.' << obj.year;
	return os;
}

struct Weight
{
	Date date;
	double weight;
	Weight(Date d = 0, double w = 0) : date(d), weight(w) { }
	Weight& operator=(const Weight& n)
	{
		date = n.date;
		weight = n.weight;
		return *this;
	}

	friend ostream& operator<<(ostream& os, Weight& obj);
};
ostream& operator<<(ostream& os, Weight& obj)
{
	os << obj.date.day << '.' << obj.date.month << '.' << obj.date.year;
	os << ' ' << obj.weight << '\n ' << endl;
	return os;
}

struct Person
{
	string name;
	vector <Weight> obs;
	Person(string _name) : name(_name) {};
	Person(string _name, vector <Weight> n) {
		name = _name;
		obs = n;
	};
	Person& operator=(const Person& n)
	{
		obs = n.obs;
		name = n.name;
		return *this;
	}
	int Search(int _day, int _month, int _year)
	{
		for (unsigned int j = 0; j < obs.size(); j++)
		{
			if (obs[j].date.day == _day && obs[j].date.month == _month && obs[j].date.year == _year)
			{
				return j;
			}
		}
		return -1;
	}
	void observation(int _day, int _month, int _year, double _weight)
	{
		if (Search(_day, _month, _year) == -1)
		{
			Date d(_day, _month, _year);
			Weight w(d, _weight);
			obs.push_back(w);
		}
		else
		{
			obs[Search(_day, _month, _year)].weight = _weight;
		}

	}
	friend ostream& operator<<(ostream& os, Person& obj);
};
ostream& operator<<(ostream& os, Person& obj)
{
	os << obj.name << "\t" << endl;
	for (unsigned int i = 0; i < obj.obs.size(); i++)
	{
		os << obj.obs[i] << endl;
	}
	return os;
}

class Scales
{
	vector <Person> scale;
public:
	Scales() {};
	Scales(vector <Person> cl) { scale = cl;}

	~Scales() {};
	
	void SetWeight( int _day, int _month, int _year, double _weight, string _name)
	{
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			if (scale[i].name == _name)
				scale[i].observation(_day, _month, _year, _weight);
		}
	}

	void SetStartDate(int _day, int _month, int _year)
	{
		weightStartDate.day = _day;
		weightStartDate.month = _month;
		weightStartDate.year = _year;
	};

	Date GetStartDate()
	{
		return weightStartDate;
	};

	double GetWeight(int _day, int _month, int _year, string _name)
	{
		if (scale.size() > 0)
		{
			for (unsigned int i = 0; i < scale.size(); i++)
			{
				if (scale[i].name == _name)
				{
					return scale[i].obs[scale[i].Search( _day,  _month, _year)].weight;
				}
			}
		}
		else
			return 0;
	};

	void AddName(string name)
	{
		Person p(name);
		scale.push_back(p);
	};

	double AvgWeightAll(string _name)
	{
		double avg = 0;
		int count = 0;
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			if (scale[i].name == _name)
			{
				for (unsigned int j = 0; j < scale[i].obs.size(); j++)
				{
					avg += scale[i].obs[j].weight;
					count++;
				}

			}
		}
		return avg / count;
	};
	double AvgWeightMonth(string _name, int _month, int _year)
	{
		double avg = 0;
		int count = 0;
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			if (scale[i].name == _name)
			{
				for (unsigned int j = 0; j < scale[i].obs.size(); j++)
				{
					if ((scale[i].obs[j].date.month == _month) && (scale[i].obs[j].date.year == _year))
					{
						avg += scale[i].obs[j].weight;
						count++;
					}
				}
			}
		}
		return avg / count;
	};

	double MinWeightAll(string _name)
	{
		double min = 1000;
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			if (scale[i].name == _name)
			{
				for (unsigned int j = 0; j < scale[i].obs.size(); j++)
				{
					if (scale[i].obs[j].weight < min)
						min = scale[i].obs[j].weight;
				}
			}
		}
		return min;
	};
	double MinWeightMonth(string _name, int _month, int _year)
	{
		double min = 1000;
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			if (scale[i].name == _name)
			{
				for (unsigned int j = 0; j < scale[i].obs.size(); j++)
				{
					if ((scale[i].obs[j].date.month == _month) && (scale[i].obs[j].date.year == _year))
					{
						if (scale[i].obs[j].weight < min)
							min = scale[i].obs[j].weight;
					}
				}
			}
		}
		return min;
	};

	double MaxWeightAll(string _name)
	{
		double max = 0;
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			if (scale[i].name == _name)
			{
				for (unsigned int j = 0; j < scale[i].obs.size(); j++)
				{
					if (scale[i].obs[j].weight > max)
						max = scale[i].obs[j].weight;
				}
			}
		}
		return max;
	};
	double MaxWeightMonth(string _name, int _month, int _year)
	{
		double max = 0;
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			if (scale[i].name == _name)
			{
				for (unsigned int j = 0; j < scale[i].obs.size(); j++)
				{
					if ((scale[i].obs[j].date.month == _month) && (scale[i].obs[j].date.year == _year))
					{
						if (scale[i].obs[j].weight > max)
							max = scale[i].obs[j].weight;
					}
				}
			}
		}
		return max;
	};

	void InputFile()
	{
		ofstream file;
		file.open("Scales.txt");
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			file << scale[i].name << endl;
			for (unsigned int j = 0; j < scale[i].obs.size(); j++)
			{
				file << scale[i].obs[j] << endl;
			}
		}
		file.close();
	};

	void OutputFile()
	{
		ifstream file;
		char str[100];
		file.open("Scales.txt");
		for (unsigned int i = 0; i < scale.size(); i++)
		{
			file.getline(str, 40, '\t');
			scale[i].name = atoi(str);
			for (unsigned int j = 0; j < scale[i].obs.size(); j++)
			{
				file.getline(str, 10, '.');
				scale[i].obs[j].date.day = atoi(str);
				file.getline(str, 10, '.');
				scale[i].obs[j].date.month = atoi(str);
				file.getline(str, 10, ' ');
				scale[i].obs[j].date.year = atoi(str);
				file.getline(str, 10, '\n');
				scale[i].obs[j].weight = atoi(str);
			}
		}
		file.close();
	};
};


int main()
{
	Scales W;
	int day;
	int month;
	int year;
	double weight;
	int op, a;
	bool menu = 1;
	string name;
	while (menu)
	{
		system("cls");
		cout << "1 - Add new person\n" << endl;
		cout << "2 - Set Start Date\n" << endl;
		cout << "3 - Get Start Date\n" << endl;
		cout << "4 - Set Weight\n" << endl;
		cout << "5 - Get Weight\n" << endl;
		cout << "6 - Average Weight\n" << endl;
		cout << "7 - Min Weight\n" << endl;
		cout << "8 - Max Weight\n" << endl;
		cout << "9 - Input File\n" << endl;
		cout << "10 - Output File\n" << endl;
		cout << "11 - Exit\n" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
		{
			cout << "Add name: ";
			cin >> name;
			W.AddName(name);
			break;
		}
		case 2:
		{
			cout << "Enter day: ";
			cin >> day;
			cout << "Enter month: ";
			cin >> month;
			cout << "Enter year: ";
			cin >> year;
			W.SetStartDate(day, month, year);
			break;
		}
		case 3:
		{
			cout << W.GetStartDate() << endl;
			_getch();
			break;
		}
		case 4:
		{
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter day: ";
			cin >> day;
			cout << "Enter month: ";
			cin >> month;
			cout << "Enter year: ";
			cin >> year;
			cout << "Enter weight: ";
			cin >> weight;
			W.SetWeight(day, month, year, weight, name);
			break;
		}
		case 5:
		{
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter day: ";
			cin >> day;
			cout << "Enter month: ";
			cin >> month;
			cout << "Enter year: ";
			cin >> year;
			cout << W.GetWeight(day, month, year, name) << endl;
			_getch();
			break;
		}
		case 6:
		{
			cout << "Enter name: " << endl;
			cin >> name;
			cout << "1 - all observation" << endl;
			cout << "2 - in chosen month" << endl;
			cin >> a;
			switch (a)
			{
			case 1:
			{
				cout << "Average Weight =" << W.AvgWeightAll(name) << endl;
				break;
			}
			case 2:
			{
				cout << "Enter month: ";
				cin >> month;
				cout << "Enter year: ";
				cin >> year;
				if (W.AvgWeightMonth(name, month, year))
					cout << "Average Weight =" << W.AvgWeightMonth(name, month, year) << endl;
				else
					cout << "No observation in this month" << endl;
				break;
			}
			default:
			{
				cout << "Incorrect input" << endl;
			}
			}
			_getch();
			break;
		}
		case 7:
		{
			cout << "Enter name: " << endl;
			cin >> name;
			cout << "1 - all observation" << endl;
			cout << "2 - in chosen month" << endl;
			cin >> a;
			switch (a)
			{
			case 1:
			{
				cout << "Min Weight =" << W.MinWeightAll(name) << endl;
				break;
			}
			case 2:
			{
				cout << "Enter month: ";
				cin >> month;
				cout << "Enter year: ";
				cin >> year;
				if (W.MinWeightMonth(name, month, year))
					cout << "Min Weight =" << W.MinWeightMonth(name, month, year) << endl;
				else
					cout << "No observation in this month" << endl;
				break;
			}
			default:
			{
				cout << "Incorrect input" << endl;
			}
			}
			_getch();
			break;
		}
		case 8:
		{
			cout << "Enter name: " << endl;
			cin >> name;
			cout << "1 - all observation" << endl;
			cout << "2 - in chosen month" << endl;
			cin >> a;
			switch (a)
			{
			case 1:
			{
				cout << "Max Weight =" << W.MaxWeightAll(name) << endl;
				break;
			}
			case 2:
			{
				cout << "Enter month: ";
				cin >> month;
				cout << "Enter year: ";
				cin >> year;
				if (W.MaxWeightMonth(name, month, year))
					cout << "Max Weight =" << W.MaxWeightMonth(name, month, year) << endl;
				else
					cout << "No observation in this month" << endl;
				break;
			}
			default:
			{
				cout << "Incorrect input" << endl;
			}
			}
			_getch();
			break;
		}
		case 9:
		{
			W.InputFile();
			break;
		}
		case 10:
		{
			W.OutputFile();
			break;
		}
		case 11:
		{
			menu = 0;
			break;
		}
		}
	}
	system("pause");
	return 0;
}