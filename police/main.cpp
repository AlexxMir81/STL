#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<list>

using namespace std;

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
	Crime(int id, std::string place) : id(id), place(place) {}
	~Crime() {}


};

void main()
{
	setlocale(LC_ALL, "");

}