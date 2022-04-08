#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<list>
#include<windows.h>
#include<conio.h>

using namespace std;
#define tab "\t"
const std::map<int, std::string> CRIMES =
{
	std::pair<int,std::string>(1, "проезд на красный свет"),
	std::pair<int, std::string>(2, "превышение скорости"),
	std::pair<int, std::string>(3, "езда по встречной полосе"),
	std::pair<int, std::string>(4, "дрифт на перекрестке"),
	std::pair<int, std::string>(5, "парковка в неположенном месте"),
	std::pair<int, std::string>(6, "оскорбление офицера"),
	std::pair<int, std::string>(7, "вождение в нетрезвом состоянии"),
	std::pair<int, std::string>(8, "вождение без документов"),
};

class Crime
{
	int id; //статья
	std::string place; //место происшествоия
public:
	int get_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
	}
	Crime(int id, std::string place) : id(id), place(place) {}
	~Crime() {}

};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << CRIMES.at(obj.get_id()) << " - " << obj.get_place();
};
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_id() << obj.get_place();
	return ofs;
}

void print(const map<std::string, std::list<Crime>>& base);
int check_crime();
void save(const map<std::string, std::list<Crime>>& base, std::string filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string filename);
std::string input_place();
std::string input_plate();
void menu(std::map<std::string, std::list<Crime>>& base, std::string filename);
//#define INPUT_BASE

void main()
{
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::map<std::string, std::list<Crime>> base /*=
	{
		std::pair<std::string, std::list<Crime>>("a777bb", {Crime(1, "ул.Ленина"), Crime(2,"ул.Октябрьская"), Crime(3,"ул.Октябрьская"),Crime(6,"ул.Степного Фронта")}),
		{"b123ca",{Crime(5,"ул.Ленина"), Crime(8,"ул.Октябрьская")}},
		{"b123ab",{Crime(4,"перекресток Ленина и Октябрьской"), Crime(8,"ул.Октябрьская")}}

	}*/;
	load(base, "base.txt");
	print(base);

#ifdef INPUT_BASE
	std::string licence_plate; //номерной знак
	cout << "Введите номер автомобиля: "; cin >> licence_plate;
	//int id;
	//cout << "Введите правонарушение: ";cin >> id;
	//std::string place;
	//cout << "Введите место правнарушения: ";
	//cin.ignore();
	//std::getline(cin, place);
	base[licence_plate].push_back(Crime(check_crime(), input_place()));
	print(base);
#endif // INPUT_BASE
	menu(base, "base.txt");
	save(base, "base.txt");

}

void print(const map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << "\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt << ";\n";
		}
		cout << "\n--------------------------------------\n";
	}
	system("PAUSE");
}

int check_crime()
{
	system("CLS");
	for (std::pair<int, std::string>i : CRIMES)
	{
		cout << i.first << tab << i.second << endl;
	}
	int id;
	cout << "Выберите правонарушение: "; cin >> id;
	return id;
}
std::string input_place()
{
	std::string place;
	cout << "Введите место правнарушения: ";
	cin.ignore();
	std::getline(cin, place);
	return place;
}
std::string input_plate()
{
	std::string licence_plate; //номерной знак
	cout << "Введите номер автомобиля: "; cin >> licence_plate;
	return licence_plate;
}

void save(const map<std::string, std::list<Crime>>& base, std::string filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		fout << it->first << ":";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			fout << *jt << ",";
		}
		fout.seekp(-1, std::ios::cur); //cur - current (текущий)
		fout << ";\n";
	}
	fout.close();
	std::string command = "notepad ";
	command += filename;
	system(command.c_str()); //c_str - возвращает содержимое объекта std::string в виде массива элементов char(c-string)
}

void load(std::map<std::string, std::list<Crime>>& base, const std::string filename)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string licence_plate;
			std::string all_crimes; //этот буфер будет хранить все правонарушения заданного номера
			std::getline(fin, licence_plate, ':');
			std::getline(fin, all_crimes);
			if (licence_plate.empty() || all_crimes.empty())continue;
			all_crimes.erase(all_crimes.find_last_of(';'));
			for (int start = -1, end = 0; end != std::string::npos; start = end)
			{
				start++;
				end = all_crimes.find(',', start);
				std::string place = all_crimes.substr(start, end - start);
				int id = std::stoi(place);
				place.erase(0, 1);
				base[licence_plate].push_back(Crime(id, place));
			}
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found!" << endl;
	}

}

void menu(std::map<std::string, std::list<Crime>>& base, std::string filename)
{
	char key;
	do
	{
		system("CLS");
		cout << "1. Вывод всей базы;" << endl;
		cout << "2. Вывод по номерному знаку;" << endl;
		cout << "3. Вывод по диапазону номеров;" << endl;
		cout << "4. Вывод по шаблону;" << endl;
		cout << "5. Вывод по правонарушению;" << endl;
		cout << "6. Вывод по адресам" << endl;
		cout << "7. Сохранение базы;" << endl;
		cout << "8. Загрузка базы;" << endl;
		cout << "9. Добавление записи;" << endl;
		cout << "Esc - Выход из программы;" << endl;
		key = _getch();
		switch (key)
		{
		case '1': print(base); break;
		case '2': //cout << "empty\n"; break;
		case '3': //cout << "empty\n"; break;
		case '4': //cout << "empty\n"; break;
		case '5': //cout << "empty\n"; break;
		case '6': cout << "empty\n"; 
			system("PAUSE");
			break;
		case '7': save(base, filename); break;
		case '8': load(base, filename); break;
		case '9': base[input_plate()].push_back(Crime(check_crime(), input_place())); break;
		}

	} while (key != 27);

}