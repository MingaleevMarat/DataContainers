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
	}*Head,*Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
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
		if (Head == nullptr && Tail ==nullptr)
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
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
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
			for (int i = 0; i < size-1-index; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
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
		std::cout << "���������� ��������� ������: \t" << size << std::endl;
	}

	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
		std::cout << "���������� ��������� ������: \t"<<size << std::endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	std::cout << "������� ������ ������: ";
	std::cin >> n;
	List list;

	for (int i = 0; i < n; i++)
	{
		/*list.push_front(rand()%100);*/
		list.push_back(rand() % 100);
	}
	//std::cout << "������ ��������" <<std::endl;
	list.print();
	list.reverse_print();
	int index;
	int value;
	std::cout << "������� ������ ������������ ��������: " << std::endl;
	std::cin >> index;
	std::cout << "������� �������� ������������ ��������: " << std::endl;
	std::cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
}