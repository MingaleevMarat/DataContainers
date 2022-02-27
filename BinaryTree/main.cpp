#include<iostream>
class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft=nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			std::cout << "Econstructor: \t" << this << std::endl;
		}
		~Element()
		{
			std::cout << "EDestructor: \t" << this << std::endl;
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;
		std::cout << "TConstructor: \t" << this << std::endl;
	}
	~Tree()
	{
		std::cout << "TDestructor: \t" << this << std::endl;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
				Root->pLeft = new Element(Data);
			else
				insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)
				Root->pRight = new Element(Data);
			else
				insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		std::cout << Root->Data << "\t";
		print(Root->pRight);
	}
};
void main()
{
	setlocale(LC_ALL, "");
	int n;
	std::cout << "¬ведите размер дерева: ";
	std::cin >> n;
	Tree tree;
	for (int i = 0; i < n; ++i)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	std::cout << std::endl;
}