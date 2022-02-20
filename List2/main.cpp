#include<iostream>

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			std::cout << "EConstructor:" << this << std::endl;
		}
		~Element()
		{
			std::cout << "EDestructor:" << this << std::endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			std::cout << "ItConstructor:\t" << this << std::endl;
		}
		~Iterator()
		{
			std::cout << "ItDestructor:\t" << this << std::endl;
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

		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
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
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			std::cout << "RItConstructor:\t" << this << std::endl;
		}

		~ReverseIterator()
		{
			std::cout << "RItDestructor:\t" << this << std::endl;
		}
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}

		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}

		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const ReverseIterator& other)const
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
		operator bool()const
		{
			return Temp;
		}
	};
	ReverseIterator rbegin()
	{
		
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		std::cout << typeid(il.begin()).name() << std::endl;
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	~List()
	{
		/*while (Head)
		{
			pop_front();
		}*/
		while (Tail)
		{
			pop_back();
		}
		std::cout << "LDestructor:\t" << this << std::endl;
	}

	//                 Adding elements:
	void push_front(int Data)
	{
		/*Tail = Head = new Element(Data, Head, Tail);
		size++;*/
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}

	void insert(int index, int Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - 1 - index; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	// Removing elements:

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)
			return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	//           Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
		std::cout << "Количество элементов списка: \t" << size << std::endl;
	}

	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
		std::cout << "Количество элементов списка: \t" << size << std::endl;
	}
};

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
	List list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
	for (List::ReverseIterator it = list.rbegin(); it; ++it)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
#endif // RANGE_BASED_FOR_LIST

	/*const int size = 100;
	int arr[size] = {};
	for (int i = 0; i < size; ++i)
	{
		std::cout << arr[i] << std::endl;
	}*/
}