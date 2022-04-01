#include<iostream>
#include<array>
#include<vector>
#include<deque>
using namespace std;
#define tab "\t"
//#define STL_ARRAY
//#define STL_VECTOR
#define STL_DEQUE
void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_ARRAY
	const int N = 5;
	std::array<int, N> arr = { 2,3,4,5 };
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY
#ifdef STL_VECTOR
	std::vector<int> vec = { 0,1,1,2,3,5,8,13,21,34 };

	cout << endl;
	cout << "Size: " << vec.size() << endl;
	cout << "Max_size: " << vec.max_size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	vec.push_back(55);
	//vec.reserve(25);
		try
	{
		for (int i = 0; i < vec.capacity(); i++)
		{
			cout << vec.at(i) << tab;
			//cout << vec[i] << tab;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	/*cout << "Size: " << vec.size() << endl;
	cout << "Max_size: " << vec.max_size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	int index;
	int count;
	int value;
	cout << "Ведите индекс добавлямого элемента: "; cin >> index;
	cout << "Ведите количество добавлений: "; cin >> count;
	cout << "Ведите значение добавлямого элемента: "; cin >> value;
	vec.insert(vec.begin()+index, count, value);*/
	vec.insert(vec.begin() + 3, { 1024, 2048, 3096 });
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_VECTOR
#ifdef STL_DEQUE
	std::deque<int> deque = { 3,5,8,13,21 };
	deque.push_back(34);
	deque.push_back(55);
	deque.push_back(89);

	deque.emplace_front(2);
	deque.emplace_front(1);
	deque.emplace_front(1);
	deque.emplace_front(0);

	for (int i : deque)
	{
		cout << i << tab;
	}
	cout << endl;
	
#endif // STL_DEQUE


}