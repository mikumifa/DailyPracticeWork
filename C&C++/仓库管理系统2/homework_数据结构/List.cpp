#include"List.h"
template<typename T>
class Node {
public:
	Node<T>* next;
	Node<T>* pre;
	T value;
	Node(T value, Node<T>* pre = nullptr, Node<T>* next = nullptr) {
		this->next = next;
		this->value = value;
		this->pre = pre;
	}
	Node(Node<T>* pre = nullptr, Node<T>* next = nullptr) {
		this->next = next;
		this->pre = pre;
	}
};
template<typename T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
public:
	int len = 0;
	List() {
		head = new Node<T>();
		tail = new Node<T>();
		head->next = tail;
		tail->next = nullptr;
		head->pre = nullptr;
		tail->pre = head;
		len = 0;
	}
	List(List<T>& copy) {

		head = new Node<T>();
		tail = new Node<T>();
		head->next = tail;
		tail->next = nullptr;
		head->pre = nullptr;
		tail->pre = head;
		len = 0;

		Node<T>* itr = copy.head->next;
		while (itr != copy.tail)
		{
			Node<T>* p = tail->pre;
			tail->pre = new Node<T>(itr->value, p, tail);
			p->next = tail->pre;
			itr = itr->next;
		}
		len = copy.len;
	}
	~List() {
		Node<T>* itr = head;
		while (itr != nullptr)
		{
			Node<T>* p = itr;
			itr = itr->next;
			delete p;
		}
		len = 0;
		head = nullptr;
		tail = nullptr;
	}
	bool isEmpty() {
		if (head->next == tail)
			return true;
		else return false;
	}
	void pushFront(T value) {
		Node<T>* p = head->next;
		head->next = new Node<T>(value, head, head->next);
		p->pre = head->next;
		len++;
	}
	void pushBack(T value) {
		Node<T>* p = tail->pre;
		tail->pre = new Node<T>(value, p, tail);
		p->next = tail->pre;
		len++;
	}
	T popFront() {
		T temp = head->next->value;
		Node<T>* p = head->next;
		head->next = p->next;
		p->next->pre = head;
		delete p;
		len--;
		return temp;
	}
	T popBack() {
		T temp = tail->pre->value;
		Node<T>* p = tail->pre;
		tail->pre = p->pre;
		p->pre->next = tail;
		delete p;
		len--;
		return temp;
	}
	void remove(T value) {
		Node<T>* itr = head->next;
		while (itr != tail)
		{
			if (itr->value == value) {
				Node<T>* p = itr->pre;
				p->next = itr->next;
				itr->next->pre = p;
				delete itr;
				len--;
				return;
			}
			itr = itr->next;
		}

	}
	string toString() {
		if (isEmpty() == true)
			return "null";
		string ans;
		stringstream ss;
		Node<T>* itr = head->next;
		while (itr->next != tail)
		{
			ss << itr->value << "->";
			itr = itr->next;
		}
		ss << itr->value;
		ss >> ans;
		return ans;
	}
	void show() {
		if (isEmpty() == true)
		{
			cout << "null" << endl;
			return;
		}
		Node<T>* itr = head->next;
		while (itr->next != tail)
		{
			cout << itr->value << "->";
			itr = itr->next;
		}
		cout << itr->value << endl;
	}
	void sort() {
		Node<T>* end = tail;
		for (int i = 0; i < len - 1; i++) {
			Node<T>* itr = head->next;
			while (itr->next != end)
			{
				Node<T>* itrNext = itr->next;
				if (itr->value > itrNext->value)
				{
					swap(itr->value, itrNext->value);
				}
				itr = itr->next;
			}
			end = end->pre;
		}
	}
};