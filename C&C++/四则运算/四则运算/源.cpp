#include <iostream>
#include <time.h>
using namespace std;
const int MaxNum = 30;
const int MaxNum_p = 1000;
class Person
{
public:
	int ID = 0;
	int year = 0;
	void show() {
		cout << "people: id: " << ID << " year:" << year << endl;
	}
};
class Police
{
public:
	int ID = 0;
	int PoliceID = 0;
	int year = 0;
	void show() {
		cout << "people: id: " << ID << "year:" << year << " policeId" << PoliceID << endl;
	}
};
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
		head = new Node<T>;
		tail = new Node<T>;
		head->next = tail;
		head->pre = nullptr;
		tail->next = nullptr;
		tail->pre = head;

		len = 0;
	}
	bool isEmpty() {
		if (head->next == tail)
			return true;
		else return false;
	}
	void push(T value) {//add in the head
		Node<T>* temp = this->tail;
		tail->value = value;
		tail->next = new Node<T>;
		Node<T>* p = tail;
		tail = tail->next;
		tail->pre = p;
		tail->next = nullptr;
		len++;
	}
	T pop() {
		T temp = head->next->value;
		Node<T>* p = head->next;
		head->next = p->next;
		p->next->pre = head;
		delete p;
		len--;
		return temp;
	}
	int getSize() {
		return len;
	}

	void show() {
		cout << "共有" << len << "人" << endl;
		if (isEmpty() == true)
			return;
		Node<T>* itr = head->next;
		while (itr != tail)
		{
			itr->value.show();
			itr = itr->next;
		}
		return;
	}
};
class testingStation
{
public:
	List<Person> station[100];
	int CurNum = 1;
	void show() {
		cout << "共有" << CurNum << "个检查站" << endl;
		for (int i = 0; i < CurNum; i++) {
			cout << "检查站" << i << endl;
			cout << "**********************************" << endl;
			station[i].show();
		}
	}
};
int findMinNumTestingPoint(testingStation tS)
{
	int min = 0;
	for (int i = 0; i < tS.CurNum; i++)
	{
		if (tS.station[min].getSize() > tS.station[i].getSize())
			min = i;
	}
	return min;
};

int main()
{
	srand((unsigned)time(NULL));
	testingStation tS;
	List<Police> pS;
	for (int t = 0; t < 30; t++)
	{
		cout << "\n\n第" << t << "分钟\n";
		cout << "=========================\n";
		int comPeople = rand() % 40 + 10;
		int normal = (int)(comPeople * 10.0 / 11.0);
		int policeNum = (int)(comPeople * 1.0 / 11.0);
		cout << "来" << normal << "个普通人" << endl;
		cout << "来" << policeNum << "个警察" << endl;
		for (int i = 0; i < normal; i++)
		{
			Person p1;
			p1.ID = rand() % 100000 + 100000;
			p1.year = rand() % 150;
			int min = findMinNumTestingPoint(tS);
			if (tS.station[min].getSize() >= MaxNum)
			{
				tS.CurNum++;
				min = findMinNumTestingPoint(tS);
			}
			tS.station[min].push(p1);
		}
		for (int i = 0; i < policeNum; i++)
		{
			Police p1;
			p1.ID = rand() % 100000 + 100000;
			p1.year = rand() % 150;
			p1.PoliceID = rand() % 2000 + 1000;
			pS.push(p1);
		}
		int cnt = 0;
		for (int i = 0; i < tS.CurNum; i++)
		{ // 每分钟各个采集点采集5人
			for (int j = 0; j < 5; j++)
			{
				if (tS.station[i].getSize() > 0)
				{
					cnt++;
					tS.station[i].pop();
				}

			}
		};
		cout << "普通站点离开" << cnt << "人" << endl;
		cnt = 0;
		for (int j = 0; j < 5; j++)
		{
			if (pS.getSize() > 0)
			{
				cnt++;
				pS.pop();
			}
		}
		cout << "警察站点离开" << cnt << "人" << endl;
		tS.show();
		cout << "警察站点:" << endl;
		pS.show();
	}
}
