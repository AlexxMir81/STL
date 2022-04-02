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
		cout << tab << "���� ������ ���." << endl << "1 - �������� ��������������" << endl << "2 - ����������� ������ ������ ��������������" << endl
			<< "3 - ���������� ������ �������������� �� ������ ����" << endl << "4 - ����������� ������ �������������� �� ��������� �������" << endl
		<< "5 - ��������� ���������" << endl << "0 - �����" << endl;
		cin >> n;
		switch (n)
		{
		case 1: add(adding); break;
		case 2: print(adding, 0, 0); break;
		case 3: cout << "������� ����� ����: "; cin >> first; print(adding, first, 0); break;
		case 4: cout << "������� ����� �: "; cin >> first; cout << "������� ����� ��: "; cin >> second; print(adding, first, second); break;
		case 5: save(adding); break;
		case 0: cout << "������ ���������!" << endl; break;
		default:;
		}
	}
}

void add(std::multimap<int, std::string>& adding)
{
	int nomer;
	std::string	offense;
	cout << "������� ����� ������: "; cin >> nomer;
	cout << "������� ��������������: "; cin >> offense;
	adding.insert(std::pair<int, std::string>(nomer, offense));
	cout << "�������������� ���������!" << endl;
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
	if (!file)cout << "���� �� ������!" << endl;
	else cout << "���� ������!" << endl;
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