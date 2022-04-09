#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<list>
#include<windows.h>
#include<conio.h>
#include<time.h>

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
std::string currentDateTime(const std::time_t curtime);
class Crime
{
	int id; //статья
	std::string place; //место происшествоия
	std::time_t date_time;
public:
	int get_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::time_t get_date_time()const
	{
		return date_time;
	}
	Crime(int id, std::string place, std::time_t date_time) : id(id), place(place), date_time(date_time) {}
	~Crime() {}

};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << CRIMES.at(obj.get_id()) << " - " << obj.get_place() << "|" << currentDateTime(obj.get_date_time());
};
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_id() << obj.get_place() << obj.get_date_time();
	return ofs;
}

void print(const map<std::string, std::list<Crime>>& base);
int check_crime();
void save(const map<std::string, std::list<Crime>>& base, std::string filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string filename);
std::string input_place();
std::string input_plate();
void menu(std::map<std::string, std::list<Crime>>& base, std::string filename);
void search(const std::map<std::string, std::list<Crime>>& base, std::string target);
void search2(const std::map<std::string, std::list<Crime>>& base, std::string target, std::string target2);
void search3(const std::map<std::string, std::list<Crime>>& base, int id);
void search4(const std::map<std::string, std::list<Crime>>& base, std::string place);

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
			fout << *jt << "|" << time(NULL) << ",";
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
			int date_time;
			std::getline(fin, licence_plate, ':');
			std::getline(fin, all_crimes);
			if (licence_plate.empty() || all_crimes.empty())continue;
			all_crimes.erase(all_crimes.find_last_of(';'));
			for (int start = -1, end = 0; end != std::string::npos; start = end)
			{
				start++;
				end = all_crimes.find(',', start);
				std::string place = all_crimes.substr(start, end - start);
				date_time = stoi(place.substr(place.find("|")+1, std::string::npos));
				place.erase(place.find("|"), std::string::npos);
				int id = std::stoi(place);
				place.erase(0, 1);
				base[licence_plate].push_back(Crime(id, place, date_time));
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
		case '2': search(base, input_plate()); break;
		case '3': search2(base, input_plate(), input_plate()); break;
		case '4': //cout << "Эта опция еще не добавлена, постараемся включить ее в следующее обновление\n";
			system("PAUSE");
			break;
		case '5': search3(base, check_crime()); break;
		case '6': search4(base, input_place());			
		case '7': save(base, filename); break;
		case '8': load(base, filename); break;
		case '9': base[input_plate()].push_back(Crime(check_crime(), input_place(), (time(NULL)))); break;
		}

	} while (key != 27);

}

void search(const std::map<std::string, std::list<Crime>>& base, std::string target)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		if (it->first == target)
		{
			cout << it->first << "\n";
			for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
			{
				cout << *jt << ";\n";
			}
		}
	}
	system("PAUSE");
}
void search2(const std::map<std::string, std::list<Crime>>& base, std::string target, std::string target2)
{
	std::map<std::string, std::list<Crime>>::const_iterator it, itlow, itup;
	itlow = base.lower_bound(target2);
	itup = base.upper_bound(target);
	for (it = itlow; it != itup; ++it)
	{
		cout << it->first << "\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt << ";\n";
		}
	}
	system("PAUSE");
}
void search3(const std::map<std::string, std::list<Crime>>& base, int id)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		for(std::list<Crime>::const_iterator jt=it->second.begin();jt!=it->second.end();++jt)
			if (jt->get_id() == id)
			{
				cout << it->first << "\n";
				cout << *jt << ";\n";
			}
	}
	system("PAUSE");
}
void search4(const std::map<std::string, std::list<Crime>>& base, std::string place)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			std::size_t found = jt->get_place().find(place, 0);
			if(found!=std::string::npos)
			{
				cout << it->first << "\n";
				cout << *jt << ";\n";
			}
		}
	}
	system("PAUSE");
}

std::string currentDateTime(const std::time_t curtime)
{
	tm* ptm = nullptr;
	time_t t = curtime;//std::time(nullptr);
	ptm = std::localtime(&t);
	std::string day;
	std::string mon;
	std::string year;
	std::string hours;
	std::string min;
	std::string sec;
	(ptm->tm_mday < 10) ? day = "0" + std::to_string(ptm->tm_wday) : day = std::to_string(ptm->tm_wday);
	(ptm->tm_mon < 10) ? mon = "0" + std::to_string(ptm->tm_mon) : mon = std::to_string(ptm->tm_mon);
	(ptm->tm_hour < 10) ? hours = "0" + std::to_string(ptm->tm_hour) : hours = std::to_string(ptm->tm_hour);
	(ptm->tm_min < 10) ? min = "0" + std::to_string(ptm->tm_min) : min = std::to_string(ptm->tm_min);
	(ptm->tm_sec < 10) ? sec = "0" + std::to_string(ptm->tm_sec) : sec = std::to_string(ptm->tm_sec);
	year = std::to_string(1900 + ptm->tm_year);
	return day + "." + mon + "." + year + " " + hours + ":" + min + ":" + sec;
}