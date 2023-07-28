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

	//ʹ��ԭ��ָ����Ϊ���������������󣬵������Ľ����ú�++��������list��������Ҫ��
	//�������ｫԭ��ָ����з�װ��Ȼ��ʹ����������شﵽ������Ҫ��Ч��
	//����list�ĵ�������һ���Զ������ͣ�����Զ������������ԭ��ָ��
	template <class T,class Ref>
	struct _list_iterator
	{
		typedef listNode<T> Node;
		typedef _list_iterator<T, Ref> Self;
		_list_iterator(Node* node)
			:_node(node)
		{}
		Ref& operator*()//����*�������Ϊԭ��ָ���еĽ����ò�����list����Ҫ��
		{
			return _node->val;
		}
		Self& operator++()//����++�����
		{
			_node = _node->next;
			return *this;
		}

		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}
		Node* _node;//ԭ��ָ��
	};

	//template <class T>
	//struct _list_iterator
	//{
	//	typedef listNode<T> Node;

	//	_list_iterator( Node* node)
	//		:_node(node)
	//	{}
	//   T& operator*()//����*�������Ϊԭ��ָ���еĽ����ò�����list����Ҫ��
	//	{
	//		return _node->val;
	//	}
	//	_list_iterator<T>& operator++()//����++�����
	//	{
	//		_node = _node->next;
	//		return *this;
	//	}

	//	bool operator!=(const _list_iterator<T>& it)
	//	{
	//		return _node != it._node;
	//	}
	//	Node* _node;//ԭ��ָ��
	//};


	template <class T>
	class list//��ͷ˫��ѭ���б�
	{
	public:
		typedef listNode<T> Node;
		//typedef _list_iterator<T> iterator;//���Զ���ĵ���������ͳһ����Ϊiterator
		typedef _list_iterator<T,T&> iterator;//��ͨ������

		typedef _list_iterator<T, const T&> const_iterator;//const������

		//const�����������ƣ�
		//����Ҫ���const�������ǣ�1.������ָ������ݲ��ܱ��޸�2.��������������޸�
		//1.const T* iterator     2.T* const iterator
		//typedef const _list_iterator<T> const_iterator;��������ǵڶ������const���ε��������װ�ĵ�������˵����������������ܱ��޸ģ���������ָ������ݲ����޸�

		//��ȷ�������ǣ�������ʱ���ʵ����ݣ�����ʱ����const T&���͵����ݣ��������ػ��������ݾ��޷��ٱ��޸�
		//�е��˻�ѡ�񿽱�һ�ݷ�װ�ĵ�������Ȼ����������ͬ���ͽ�������������غ����������Ͳ�ͬ����ͨ������������ֵ��T&,const����������������constT&.
		//��������ʵ��̫�����ˣ������������һ��ģ���������������ĵ������������͵ġ�

		iterator begin()
		{
			return _head->next;
			//return _list_iterator(_head->next)
			//�������Ĺ���֧����ʽ����ת��
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin()const
		{
			return _head->next;
			//return _list_iterator(_head->next)
			//�������Ĺ���֧����ʽ����ת��
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
			//β��������Ҫ�ҵ�β
			Node* tail = _head->prev;
			//�ҵ�β�����½������
			Node* newnode = new Node(x);
			tail->next = newnode;
			newnode->prev = tail;

			_head->prev = newnode;
			newnode->next = _head;
		}
	private:
		Node* _head;//��װ����һ��ָ�����ָ��
	};
	void test2(const list<int> lt)
	{

		list<int>::const_iterator cit = lt.begin();
		while (cit != lt.end())
		{
			//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
			cout << *cit << " ";
			++cit;
			//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
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
			//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
			cout << *it << " ";
			++it;
			//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
		}
		cout << endl;
		test2(lt);
	}
};