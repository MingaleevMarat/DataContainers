//ForwardList
#include<iostream>
#include<string>
using namespace std;

#define tab "\t"
#define DEBUG
template<typename T>class ForwardList;
template<typename T>class Iterator;
template<typename T>
class Element
{
	T Data;	//�������� ��������
	Element<T>* pNext;//����� ���������� ��������
	//Element<T>* - ��������� �� ��������� �������
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstrcutor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestrcutor:\t" << this << endl; 
#endif // DEBUG

	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
};

template<typename T>
int Element<T>::count = 0;
template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	Iterator<T> operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}

	T& operator*()
	{
		return Temp->Data;
	}

	operator bool()const
	{
		return Temp;
	}
};
template<typename T>
class ForwardList//����������� (����������������) ������
{
	Element<T>* Head;	//������ ������ - ��������� �� ��������� ������� ������.
	unsigned int size;//������ ������
public:
	Element<T>* getHead()const
	{
		return Head;
	}
	Iterator<T> begin()
	{
		return Head;
	}

	Iterator<T> end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;//���� ������ ��������� �� 0, �� ������ ����.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(unsigned int size):ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		for (int i = 0; i < size; i++)
		{
			push_front(T());
			//T() - �������� �� ��������� ��� ���������� ����.
		}
	}
	ForwardList(const initializer_list<T>& il): ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
	/*	for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}*/
		for (T const* it = il.end()-1; it != il.begin()-1; it--)
		{
			push_front(*it);
		}
	}

	ForwardList(const ForwardList<T>& other) : ForwardList()
	{
	/*	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		for (Iterator<T> it = other.Head; it != nullptr; ++it)
			push_back(*it);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//                      Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)
			return*this;
		while (Head)pop_front();
		for (Iterator<T> it = other.Head; it; ++it)
			push_back(*it);
		cout << "CopyAssignment:\t" << this << endl;
	}

	T& operator[](const int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}
	const T& operator[](const int index)const
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//					Addigng elements:
	void push_front(T Data)
	{
		//initializer_list<Element*>{ new Element(Data), New->pNext = Head, Head = New};
		
		//Element* New = new Element(Data);//������� ����� ������� � �������� � ���� �������� Data
		//New->pNext = Head;	//���������� ����� ������� � ������ ������
		//Head = New;	//��������� ������ �� ����� �������
		Head= new Element<T>(Data,Head);
		size++;
	}
	void push_back(T Data)
	{
		////0) ���������, �������� �� ������ ������:
		//if (Head == nullptr)return push_front(Data);
		////1) ������� ����� �������:
		//Element* New = new Element(Data);
		////2) ������� �� ����� ������:
		//Element* Temp = Head;
		//while (Temp->pNext)//����, pNext �������� �������� �� ����
		//	Temp = Temp->pNext;//��������� �� ��������� �������
		////������ �� ��������� � ��������� ��������, �.�. Temp->pNext == nullptr
		////3) ������������ ����� ������� � ����������:
		//Temp->pNext = New;

		
		/*if (Head == nullptr)return push_front(Data);
		Head = new Element(Data, Head);
		size++;*/
		if (Head == nullptr)return push_front(Data);
		Element<T>* Temp = Head;
		while (Temp->pNext)
		Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(int index, T Data)
	{
		//if (index == 0 || Head == nullptr)return push_front(Data);
		//if (index > size)return;
		//Element* New = new Element(Data);
		////1) ������� �� ������� ��������:
		//Element* Temp = Head;
		//for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		////3) �������� ����� ������� � ������:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		//size++;

		/*if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		Head = new Element(Data,Head);
		for (int i = 0; i < index - 1; i++)Head = Head;
		size++;*/

		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data,Temp->pNext);
		size++;

	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) ���������� ����� ����������� ��������:
		Element<T>* Erased = Head;
		//2) ��������� ��������� ������� �� ������:
		Head = Erased->pNext;
		//3) ������� ������ �� ������:
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) ������� �� �������������� ��������:
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) ������� ������� �� ������:
		delete Temp->pNext;
		//3) �������� ����� ���������� �������� �����:
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index >= size)return;
		if (index == 0)return pop_front();
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; ++i)
			Temp = Temp->pNext;
		Element<T>* Erased = Temp->pNext;
		//Temp->pNext = Temp->pNext->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
		size--;
	}
	//					Methods:
//#define OLD_PRINT
	void print()const
	{
#ifdef OLD_PRINT
		int a = 2;
		int* pa = &a;
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ 
		//� ��������� ��������� ������.
		while (Temp)//���� �������� �������� ��������� �����.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}
#endif // OLD_PRINT
		//for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			for (Element<T>* Temp = Head; Temp; Temp++)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� : " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define HOME_WORK_2
//#define RANGE_BASE_FOR_ARRAY
#define RANGE_BASE_FOR_LIST
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	list.pop_front();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();

	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;

	list.insert(index, value);
	list.print();
	cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

	/*ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/

#ifdef DESTRUCTOR_CHECK
	int n;
	cout << "������� ������ ������: ";
	cin >> n;
	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "������ ��������" << endl;
#endif // DESTRUCTOR_CHECK

#ifdef HOME_WORK_1
	int n;
	cout << "������� ������ ������: ";
	cin >> n;
	ForwardList list(n);
	for (int i = 0; i < n; i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < n; i++)
	{
		cout << list[i]<<tab;
	}
	cout << endl;
#endif // HOME_WORK_1
#ifdef HOME_WORK_2
	ForwardList list = { 3,5,8,13,21 };
	//list.print();
	for (Iterator it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // HOME_WORK_2

#ifdef  RANGE_BASE_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
	{
		cout << arr[i]<<tab;
	}
	cout << endl;*/
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	// ��� ���������� ���������� ���������, ������, ������ � �.�.
	// � ������ ������ ���������������� ��� �������� foreach  
#endif //  RANGE_BASE_FOR_ARRAY
#ifdef RANGE_BASE_FOR_LIST
			/*ForwardList<int> list = { 3,5,8,13,21 };
for (int i : list)
{
	cout << i << tab;
}
cout << endl;*/

	ForwardList<double> d_list = { 2.5,3.14,5.2,8.3 };
	for (double i : d_list)
		cout << i << tab;
	cout << endl;

	ForwardList<string> s_list = { "Have","a","nice","day" };
	for (string i : s_list)
		cout << i << tab;
	cout << endl;

	/*ForwardList<string> s_list2 = s_list;
	for (string i : s_list2)
		cout << i << tab;
	cout << endl;*/

	ForwardList<string> s_list2;
	s_list2 = s_list;
	for (string i : s_list2)
		cout << i << tab;
	cout << endl;
#endif // RANGE_BASE_FOR_LIST

	
}