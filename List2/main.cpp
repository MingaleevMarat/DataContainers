#include<iostream>

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			std::cout << "EConstructor:" << this << std::endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			std::cout << "EDestructor:" << this << std::endl;
#endif // DEBUG

		}
		friend class List <T>;
	}*Head, *Tail;
	size_t size;

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp) : Temp(Temp)
		{
#ifdef DEBUG
			std::cout << "BItConstructor:" << this << std::endl;
#endif // DEBUG

		}
		~BaseIterator()
		{
#ifdef DEBUG
			std::cout << "BItDestructor:" << this << std::endl;
#endif // DEBUG

		}
		virtual BaseIterator& operator++() = 0;
		/*virtual BaseIterator operator++(int) = 0;*/
		virtual BaseIterator& operator--() = 0;
	/*	virtual BaseIterator operator--(int) = 0;*/
		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const T& operator*()const
		{
			return Temp->Data;
		}
		operator bool()const
		{
			return Temp;
		}
	};
public:
	class ConstIterator:public BaseIterator
	{
	
	public:
		ConstIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			std::cout << "CItConstructor:\t" << this << std::endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			std::cout << "CItDestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		ConstIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}

		ConstIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}

		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
	};
	ConstIterator cbegin()const;
	ConstIterator cend()const;


	class ConstReverseIterator:public BaseIterator
	{

	public:
		ConstReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			std::cout << "CRItConstructor:\t" << this << std::endl;
#endif // DEBUG

		}

		~ConstReverseIterator()
		{
#ifdef DEBUG
			std::cout << "CRItDestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		ConstReverseIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}

		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}

		ConstReverseIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}

		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
	};
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp)
		{
#ifdef DEBUG
			std::cout << "ItConstructor:\t" << this << std::endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			std::cout << "ItDestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};

	Iterator begin();
	Iterator end();

	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp)
		{
#ifdef DEBUG
			std::cout << "RItConstructor:\t" << this << std::endl;
#endif // DEBUG

		}
		~ReverseIterator()
		{
#ifdef DEBUG
			std::cout << "RItDestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};

	ReverseIterator rbegin();
	ReverseIterator rend();
	
	List();
	List(const std::initializer_list<T>& il);
	~List();

	//                 Adding elements:
	void push_front(T Data);

	void push_back(T Data);

	void insert(int index, T Data);
	// Removing elements:

	void pop_front();
	void pop_back();
	//           Methods:
	void print()const;

	void reverse_print()const;
};

template<typename T>
typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}

template<typename T>
typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}

template<typename T>
typename List<T>::ConstReverseIterator List<T>::crbegin()const
{

	return Tail;
}

template<typename T>
typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}

template<typename T>
typename List<T>::Iterator List<T>::begin()
{
	return Head;
}

template<typename T>
typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rbegin()
{

	return Tail;
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>
List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	std::cout << "LConstructor:\t" << this << std::endl;
#endif // DEBUG

}

template<typename T>
List<T>::List(const std::initializer_list<T>& il) :List()
{
	std::cout << typeid(il.begin()).name() << std::endl;
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
}

template<typename T>
List<T>::~List()
{
	/*while (Head)
	{
		pop_front();
	}*/
	while (Tail)
	{
		pop_back();
	}
#ifdef DEBUG
	std::cout << "LDestructor:\t" << this << std::endl;
#endif // DEBUG

}

template<typename T>
void List<T>::push_front(T Data)
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

template<typename T>
void List<T>::push_back(T Data)
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

template<typename T>
void List<T>::insert(int index, T Data)
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

template<typename T>
void List<T>::pop_front()
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

template<typename T>
void List<T>::pop_back()
{
	if (Head == Tail)
		return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

//           Methods:

template<typename T>
void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	std::cout << "Количество элементов списка: \t" << size << std::endl;
}

template<typename T>
void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	std::cout << "Количество элементов списка: \t" << size << std::endl;
}

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
	for (List<double>::ReverseIterator it= d_list.rbegin();it;++it)
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