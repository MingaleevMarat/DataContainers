#pragma once
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
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List <T>;
	}*Head, * Tail;
	size_t size;

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp);
		~BaseIterator();
		virtual BaseIterator& operator++() = 0;
		/*virtual BaseIterator operator++(int) = 0;*/
		virtual BaseIterator& operator--() = 0;
		/*	virtual BaseIterator operator--(int) = 0;*/
		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const T& operator*()const;
		operator bool()const;
	};
public:
	class ConstIterator :public BaseIterator
	{

	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();

		ConstIterator operator++(int);

		ConstIterator& operator--();

		ConstIterator operator--(int);
	};
	ConstIterator cbegin()const;
	ConstIterator cend()const;


	class ConstReverseIterator :public BaseIterator
	{

	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();

		ConstReverseIterator operator++(int);

		ConstReverseIterator& operator--();

		ConstReverseIterator operator--(int);
	};
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator*();
	};

	Iterator begin();
	Iterator end();

	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		T& operator*();
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
