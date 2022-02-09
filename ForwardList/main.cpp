//ForwardList
#include<iostream>
using namespace std;

#define tab "\t"
#define DEBUG
class Element
{
	int Data;	//Значение элемента
	Element* pNext;//Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
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
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}

	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList//Односвязный (однонаправленный) список
{
	Element* Head;	//Голова списка - указывает на начальный элемент списка.
	unsigned int size;//Размер списка
public:
	Element* getHead()const
	{
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;//Если голова указывает на 0, то список пуст.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(unsigned int size):ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		for (int i = 0; i < size; i++)
		{
			push_front(0);
		}
	}
	ForwardList(const initializer_list<int>& il): ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
	/*	for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}*/
		for (int const* it = il.end()-1; it != il.begin()-1; it--)
		{
			push_front(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//                      Operators:
	
	int& operator[](const int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}
	const int& operator[](const int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//					Addigng elements:
	void push_front(int Data)
	{
		//initializer_list<Element*>{ new Element(Data), New->pNext = Head, Head = New};
		
		//Element* New = new Element(Data);//Создаем новый элемент и помещаем в него значение Data
		//New->pNext = Head;	//Привязывем новый элемент к началу списка
		//Head = New;	//Переводим Голову на новый элемент
		Head= new Element(Data,Head);
		size++;
	}
	void push_back(int Data)
	{
		////0) Проверяем, является ли список пустым:
		//if (Head == nullptr)return push_front(Data);
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);
		////2) Доходим до конца списка:
		//Element* Temp = Head;
		//while (Temp->pNext)//Пока, pNext текущего элемента НЕ ноль
		//	Temp = Temp->pNext;//переходим на следующий элемент
		////Теперь мы находимся в последнем элементе, т.е. Temp->pNext == nullptr
		////3) Присоединяем новый элемент к последнему:
		//Temp->pNext = New;

		
		/*if (Head == nullptr)return push_front(Data);
		Head = new Element(Data, Head);
		size++;*/
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int index, int Data)
	{
		//if (index == 0 || Head == nullptr)return push_front(Data);
		//if (index > size)return;
		//Element* New = new Element(Data);
		////1) Доходим до нужного элемента:
		//Element* Temp = Head;
		//for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		////3) Включаем новый элемент в список:
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
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data,Temp->pNext);
		size++;

	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) Запоминаем адрес удавляемого элемента:
		Element* Erased = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Erased->pNext;
		//3) Удаляем элемен из памяти:
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) Удаляем элемент из памяти:
		delete Temp->pNext;
		//3) Затираем адрес удаленного элемента нулем:
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index >= size)return;
		if (index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; ++i)
			Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
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
		Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ 
		//к элементам структуры данных.
		while (Temp)//Пока Итератор содержит ненулевой адрес.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//переход на следующий элемент
		}
#endif // OLD_PRINT
		//for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			for (Element* Temp = Head; Temp; Temp++)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов : " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define HOME_WORK_2
//#define RANGE_BASE_FOR_ARRAY
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
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
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	list.insert(index, value);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
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
	cout << "Введите размер списка: ";
	cin >> n;
	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "Список заполнен" << endl;
#endif // DESTRUCTOR_CHECK

#ifdef HOME_WORK_1
	int n;
	cout << "Введите размер списка: ";
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
	// Под диапазоном понимается контейнер, массив, список и т.д.
	// В других языках программирования это называют foreach  
#endif //  RANGE_BASE_FOR_ARRAY
	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}