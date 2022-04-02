#include<iostream>
#include<map>
#include<string>
#include<fstream>
using namespace std;

#define tab "\t"
#define delimter "\n---------------------------------\n"
void add(std::multimap<int, std::string>& adding);
void print(std::multimap<int, std::string>& adding, int first, int second);
void save(std::multimap<int, std::string>& adding);
void load();
void main()
{
	setlocale(LC_ALL, "");
	load();
	std::multimap<int, std::string> adding = {};
	int n, first, second;
	n = 10;
	while (n)
	{	
		cout << tab << "База данных ГАИ." << endl << "1 - Добавить правонарушение" << endl << "2 - Распечатать полный список правонарушений" << endl
			<< "3 - Распечатаь список правонарушений по номеру авто" << endl << "4 - рапсечатать список правонарушений по диапазону номеров" << endl
		<< "5 - Сохранить изменения" << endl << "0 - Выход" << endl;
		cin >> n;
		switch (n)
		{
		case 1: add(adding); break;
		case 2: print(adding, 0, 0); break;
		case 3: cout << "Введите номер авто: "; cin >> first; print(adding, first, 0); break;
		case 4: cout << "Введите номер с: "; cin >> first; cout << "Введите номер по: "; cin >> second; print(adding, first, second); break;
		case 5: save(adding); break;
		case 0: cout << "Работа завершена!" << endl; break;
		default:;
		}
	}
}

void add(std::multimap<int, std::string>& adding)
{
	int nomer;
	std::string	offense;
	cout << "Ввежите номер машины: "; cin >> nomer;
	cout << "Ввежите правонарушение: "; cin >> offense;
	adding.insert(std::pair<int, std::string>(nomer, offense));
	cout << "Правонарушение добавлено!" << endl;
}

void print(std::multimap<int, std::string>& adding, int first, int second)
{
		int temp = 0;
		if (second == 0)
		{
			for (std::pair<int, std::string> i : adding)
			{
				if (first == 0)
				{
					if (temp != i.first)cout << i.first << endl; cout << i.second << endl;
					temp = i.first;

				}else if (first == i.first)cout << i.first << endl << i.second << endl;
			}
		}
		else
		{
			std::multimap<int, std::string>::iterator it, itlow, itup;
			itlow = adding.lower_bound(first);
			itup = adding.upper_bound(second);
			for (it = itlow; it != itup; ++it)
			{
				if (temp != it->first) cout << it->first << endl; cout << it->second << endl;
				temp = it->first;
			}
		}
}

void save(std::multimap<int, std::string>& adding)
{
	ofstream file;
	file.open("c:\\test\\test.txt", ios::app);
	for (std::pair<int, std::string> i : adding)
		file << i.first << " " << i.second << endl;
	file.close();
}
void load()
{
	ifstream file("c:\\test\\test.txt");
	if (!file)cout << "Файл не открыт!" << endl;
	else cout << "Фалй открыт!" << endl;
	int n = 10;
	char* buffer = new char[n] {};
	std::string number;
	std::string offense;
	while(!file.eof())
	{ 	
		file.getline(buffer, n, ' ');
		cout << buffer << endl;
	}
	delete[] buffer;
}