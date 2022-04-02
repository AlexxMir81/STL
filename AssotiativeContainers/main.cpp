#include<iostream>
#include<string>
#include<set>
#include<map>
#include<list>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

//#define STL_SET
//#define STL_MAP
#define STL_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_SET
	//std::set<int> set = { 50, 25, 75, 16, 32, 64, 80 };
//for (std::set<int>::iterator it = set.begin(); it != set.end(); ++it)
//{
//	cout << *it << tab;
//}
//cout << endl;
	int n;
	cout << "Введите размер контейнера: "; cin >> n;
	std::multiset<int> set;
	for (int i = 0; i < n; i++)
	{
		set.insert(rand() % 100);
	}
	for (int i : set)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << "Размер: " << set.size() << endl;

	//int value;
	//cout << "Введите удаляемое значение: "; cin >> value;
	//set.erase(value);
	int start_value;
	int stop_value;
	cout << "С какого значени удалить элементы: "; cin >> start_value;
	cout << "До какого значения удалить элементы: "; cin >> stop_value;
	//set.erase(set.find(start_value), set.find(stop_value));
	set.erase(set.lower_bound(start_value), set.upper_bound(stop_value));
	for (int i : set) cout << i << tab; cout << endl;
#endif // STL_SET

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(0, "sunday"),
		std::pair<int, std::string>(1, "monday"),
		std::pair<int, std::string>(2, "tuesday"),
		std::pair<int, std::string>(3, "wednesday"),
		{4, "thurtday"},
		{5, "friday"},
		{6, "saturday"}
	};

	for (std::pair<int, std::string> i : week)
	{
		cout << i.first << tab << i.second << endl;
	}
#endif // STL_MAP
#ifdef STL_LIST
	std::list<int> list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	int index;
	int value;
	cout << "Введите номер добавляемого элемента: "; cin >> index;
	cout << "Введите добавляемое число: "; cin >> value;

	if (index>=0&&index<list.size())
	{
		std::list<int>::iterator it;
		it = list.begin();
		for (int i = 0; i < index - 1; i++)
		{
			++it;
		}
		list.insert(it, value);
		for (int i : list)
		{
			cout << i << tab;
		}
	}else cout<< "Вы вышли за размер списка!";

#endif // STL_LIST


}