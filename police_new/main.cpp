#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<list>
#include<windows.h>

using namespace std;
#define tab "\t"
const std::map<int, std::string> CRIMES =
{
	std::pair<int,std::string>(1, "������ �� ������� ����"),
	std::pair<int, std::string>(2, "���������� ��������"),
	std::pair<int, std::string>(3, "���� �� ��������� ������"),
	std::pair<int, std::string>(4, "����� �� �����������"),
	std::pair<int, std::string>(5, "�������� � ������������ �����"),
	std::pair<int, std::string>(6, "����������� �������"),
	std::pair<int, std::string>(7, "�������� � ��������� ���������"),
	std::pair<int, std::string>(8, "�������� ��� ����������"),
};

class Crime
{
	int id; //������
	std::string place; //����� �������������
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
std::string input_place();
void save(const map<std::string, std::list<Crime>>& base, std::string filename);

void main()
{
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::map<std::string, std::list<Crime>> base =
	{
		std::pair<std::string, std::list<Crime>>("a777bb", {Crime(1, "��.������"), Crime(2,"��.�����������"), Crime(3,"��.�����������"),Crime(6,"��.�������� ������")}),
		{"b123ca",{Crime(5,"��.������"), Crime(8,"��.�����������")}},
		{"b123ab",{Crime(4,"����������� ������ � �����������"), Crime(8,"��.�����������")}}

	};
	print(base);
	save(base, "base.txt");
#ifdef INPUT_BASE
	std::string licence_plate; //�������� ����
	cout << "������� ����� ����������: "; cin >> licence_plate;
	//int id;
	//cout << "������� ��������������: ";cin >> id;
	//std::string place;
	//cout << "������� ����� �������������: ";
	//cin.ignore();
	//std::getline(cin, place);
	base[licence_plate].push_back(Crime(check_crime(), input_place()));
	print(base);
#endif // INPUT_BASE


}

void print(const map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << "\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt << "\n";
		}
		cout << "\n--------------------------------------\n";
	}
}

int check_crime()
{
	system("CLS");
	for (std::pair<int, std::string>i : CRIMES)
	{
		cout << i.first << tab << i.second << endl;
	}
	int id;
	cout << "�������� ��������������: "; cin >> id;
	return id;
}
std::string input_place()
{
	std::string place;
	cout << "������� ����� �������������: ";
	cin.ignore();
	std::getline(cin, place);
	return place;
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
		fout.seekp(-1, std::ios::cur); //cur - current (�������)
		fout << ";\n";
	}
	fout.close();
	std::string command = "notepad ";
	command += filename;
	system(command.c_str()); //c_str - ���������� ���������� ������� std::string � ���� ������� ��������� char(c-string)
}