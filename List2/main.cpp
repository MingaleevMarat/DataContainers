#include"List.h"
#include"List.cpp"
//#define BASED_CHECK
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASED_CHECK
	int n;
	std::cout << "Введите размер списка: ";
	std::cin >> n;
	List list;

	for (int i = 0; i < n; i++)
	{
		/*list.push_front(rand()%100);*/
		list.push_back(rand() % 100);
	}
	//std::cout << "Список заполнен" <<std::endl;
	list.print();
	list.reverse_print();
	int index;
	int value;
	std::cout << "Введите индекс добавляемого элемента: " << std::endl;
	std::cin >> index;
	std::cout << "Введите значение добавляемого элемента: " << std::endl;
	std::cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK
	/*int arr[] = { 3,5,8,13,21 };
	print(arr);*/

#ifdef RANGE_BASED_FOR_LIST
	List<int> list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
	for (List<int>::ConstReverseIterator it = list.crbegin(); it; ++it)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
#endif // RANGE_BASED_FOR_LIST

	List<double> d_list = { 2.5,3.14,5.2,8.3 };
	for (double i : d_list)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it; ++it)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	List<std::string> s_list = { "Have","a","nice","day" };
	for (std::string i : s_list)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
}