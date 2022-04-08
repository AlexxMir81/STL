#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<list>

using namespace std;

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
	Crime(int id, std::string place) : id(id), place(place) {}
	~Crime() {}


};

void main()
{
	setlocale(LC_ALL, "");

}