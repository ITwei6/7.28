#pragma once
#include<iostream>
using namespace std;
namespace tao
{

	template <class T>
	struct listNode
	{
		listNode<T>* next;
		listNode<T>* prev;
		T val;
		listNode(const T& val = T())
			:next(nullptr)
			, prev(nullptr)
			, val(val)
		{}
	};

	//使用原生指针作为迭代器不符合需求，迭代器的解引用和++都不符合list迭代器的要求
	//所以这里将原生指针进行封装，然后使用运算符重载达到我们想要的效果
	//所以list的迭代器是一个自定义类型，这个自定义类型里存着原生指针
	template <class T,class Ref>
	struct _list_iterator
	{
		typedef listNode<T> Node;
		typedef _list_iterator<T, Ref> Self;
		_list_iterator(Node* node)
			:_node(node)
		{}
		Ref& operator*()//重载*运算符因为原生指针中的解引用不符合list迭代要求
		{
			return _node->val;
		}
		Self& operator++()//重载++运算符
		{
			_node = _node->next;
			return *this;
		}

		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}
		Node* _node;//原生指针
	};

	//template <class T>
	//struct _list_iterator
	//{
	//	typedef listNode<T> Node;

	//	_list_iterator( Node* node)
	//		:_node(node)
	//	{}
	//   T& operator*()//重载*运算符因为原生指针中的解引用不符合list迭代要求
	//	{
	//		return _node->val;
	//	}
	//	_list_iterator<T>& operator++()//重载++运算符
	//	{
	//		_node = _node->next;
	//		return *this;
	//	}

	//	bool operator!=(const _list_iterator<T>& it)
	//	{
	//		return _node != it._node;
	//	}
	//	Node* _node;//原生指针
	//};


	template <class T>
	class list//带头双向循环列表
	{
	public:
		typedef listNode<T> Node;
		//typedef _list_iterator<T> iterator;//将自定义的迭代器名字统一命名为iterator
		typedef _list_iterator<T,T&> iterator;//普通迭代器

		typedef _list_iterator<T, const T&> const_iterator;//const迭代器

		//const迭代器如何设计？
		//我们要求的const迭代器是：1.迭代器指向的内容不能被修改2.迭代器本身可以修改
		//1.const T* iterator     2.T* const iterator
		//typedef const _list_iterator<T> const_iterator;这种情况是第二种情况const修饰的是这个封装的迭代器，说明是这个迭代器不能被修改，而不是它指向的内容不能修改

		//正确的做法是，解引用时访问到数据，返回时返回const T&类型的数据，这样返回回来的数据就无法再被修改
		//有的人会选择拷贝一份封装的迭代器，然后其他都相同，就解引用运算符重载函数返回类型不同，普通迭代器，返回值是T&,const迭代器返回类型是constT&.
		//但这样做实在太冗余了，大佬是再添加一个模板参数来控制这里的迭代器返回类型的。

		iterator begin()
		{
			return _head->next;
			//return _list_iterator(_head->next)
			//单参数的构造支持隐式类型转化
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin()const
		{
			return _head->next;
			//return _list_iterator(_head->next)
			//单参数的构造支持隐式类型转化
		}
		const_iterator end()const
		{
			return _head;
		}
		list()
		{
			_head = new Node;
			_head->prev = _head;
			_head->next = _head;
		}
		void push_back(const T& x)
		{
			//尾插首先需要找到尾
			Node* tail = _head->prev;
			//找到尾部后将新结点连接
			Node* newnode = new Node(x);
			tail->next = newnode;
			newnode->prev = tail;

			_head->prev = newnode;
			newnode->next = _head;
		}
	private:
		Node* _head;//封装的是一个指向结点的指针
	};
	void test2(const list<int> lt)
	{

		list<int>::const_iterator cit = lt.begin();
		while (cit != lt.end())
		{
			//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
			cout << *cit << " ";
			++cit;
			//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
		}
		cout << endl;
	}
	void test1()
	{
		list<int>  lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
			cout << *it << " ";
			++it;
			//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
		}
		cout << endl;
		test2(lt);
	}
};