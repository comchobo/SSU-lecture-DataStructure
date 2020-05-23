#include<iostream>
using namespace std;

template <class T> class Chain;

template <class T>
class ChainNode {
	friend class Chain<T>;

public:
	ChainNode(T element = 0, ChainNode* next = 0);
private:
	T data;
	ChainNode<T> *link;
};

template <class T>
class Chain {
public:
	Chain();
	~Chain();
	void Insert_First(const T& e);
	void Insert_Last(const T& e);

	T return_Front();
	T return_End();
	T Get(int i) throw (const char*);
	void Delete_First() throw (const char*);
	void Delete_Last() throw (const char*);

	void InsertAt(int i, T value) throw (const char*);
	void DeleteAt(int i) throw (const char*);

	class ChainIterator {
	public:
		// constructor   
		ChainIterator(ChainNode<T>* startNode = 0) {
			current = startNode;
		}
		// dereferencing operators   
		ChainNode<T>& operator*() const {return current->link;} 
		ChainNode<T>* operator->() const {return current;} 

		ChainIterator& operator++() {	//전위증감연산자 
			current = current->link;
			return *this;
		}
		ChainIterator operator++(int) { //후위증감연산자  
			ChainIterator old = *this;
			current = current->link;
			return old;
		}
		bool operator!=(const ChainIterator right) const {
			return current != right.current;
		}
		bool operator==(const ChainIterator right)const {
			return current == right.current;
		}
		ChainNode<T>* current;
	};
	void PrintChain();

private:
	ChainNode<T> *first;
	ChainNode<T> *last;
	int size;
};

int main() {
	Chain<int> test;
	for (int i = 1; i < 10; i++) test.Insert_Last(i); //1
	test.PrintChain();		// 2

	test.Insert_First(0);	// 3
	test.PrintChain();		// 4
	test.Insert_Last(10);	// 5
	test.PrintChain();		// 6

	try { cout << test.return_Front() << endl; }
	catch (const char *ex) {
		cout << "예외가 발생하였습니다 : " << ex << endl;
	}	//7 
	try { cout << test.return_End() << endl; }
	catch (const char *ex) {
		cout << "예외가 발생하였습니다 : " << ex << endl;
	}	//8
	try { cout << test.Get(2) << endl; }
	catch (const char *ex) {
		cout << "예외가 발생하였습니다 : " << ex << endl;
	} 	//9 (3번째 원소 출력)

	try { test.Delete_First(); }
	catch (const char *ex) {
		cout << "예외가 발생하였습니다 : " << ex << endl;
	}			//10 
	test.PrintChain();		//11
	try {	test.Delete_Last();	}
	catch (const char *ex) {
		cout << "예외가 발생하였습니다 : " << ex << endl;
	}			//12 
	test.PrintChain();		//13

	try { test.InsertAt(2, 100);}
	catch (const char *ex) {
		cout << "예외가 발생하였습니다 : " << ex << endl;
	}			//14 
	test.PrintChain();		//15
	try { test.DeleteAt(6); }
	catch (const char *ex) {
		cout << "예외가 발생하였습니다 : " << ex << endl;
	}			//16
	test.PrintChain();		//17
}

//chainnode constructor
template <class T>
ChainNode<T>::ChainNode(T element, ChainNode<T>* next) {
	data = element;
	link = next;
}

//chain constructor
template <class T>
Chain<T>::Chain() {
	first = 0;
	last = 0;
	size = 0;
}

//Chain destructor
template <class T>
Chain<T>::~Chain() {
	ChainNode<T> *temp = first;
	ChainNode<T> *temp2;
	for (int i = 0; i < size - 1; i++) {
		temp2 = temp->link;
		delete temp;
		temp = temp2;
	}
	size = 0;
}

//insert node at first index
template <class T>
void Chain<T>::Insert_First(const T& e) {
	if (first) {
		ChainNode<T>* temp = new ChainNode<T>(e);
		temp->link = first;
		first = temp;
	}
	else first = last = new ChainNode<T>(e);
	size++;
}

//insert node at last index
template <class T>
void Chain<T>::Insert_Last(const T& e) {
	if (first) {
		last->link = new ChainNode<T>(e);
		last = last->link;
	}
	else first = last = new ChainNode<T>(e);
	size++;
}

//return front node data
template <class T>
T Chain<T>::return_Front() {
	return first->data;
}

//return last node data
template <class T>
T Chain<T>::return_End() {
	return last->data;
}

//return i index node data
template <class T>
T Chain<T>::Get(int i) throw (const char*) {
	if (i<0 || i>size) throw "index was not proper";

	ChainIterator temp = ChainIterator(first);
	for (int j = 0; j<i; j++) temp++;
	return temp->data;
}

template <class T>
void Chain<T>::Delete_First() throw (const char*) {
	if (size < 1) throw "Cannot delete node";

	if (size == 1) {
		delete first->link;
		first = 0;
	}
	else {
		ChainIterator temp = first->link;
		delete first;
		first = temp.current;
	}
	size--;
}

template <class T>
void Chain<T>::Delete_Last() throw (const char*) {
	if (size < 1) throw "Cannot delete node";

	if (size == 1) {
		delete first->link;
		first = 0;
	}
	else {
		ChainIterator temp = ChainIterator(first);
		for (int i = 0; i < size - 1; i++) temp++;
		delete temp->link;
		temp->link = 0;
		last = temp.current;
	}
	size--;
}

//insert at node i
template <class T>
void Chain<T>::InsertAt(int i, T value) throw (const char*) {
	if (i<0 || i>size) throw "index was not proper";

	ChainIterator temp = ChainIterator(first);
	for (int j = 0; j<i; j++) temp++;

	ChainNode<T>* tempNode = new ChainNode<T>(value, temp->link);
	temp->link = tempNode;
	size++;
}

//delete at node i
template <class T>
void Chain<T>::DeleteAt(int i) throw (const char*) {
	if (i<0 || i>size) throw "index was not proper";

	ChainIterator temp = ChainIterator(first);
	for (int j = 0; j<i - 1; j++) temp++;

	ChainIterator temp2 = ChainIterator(temp->link);
	temp->link = temp2->link;
	delete temp2.current;
	size--;
}

//print whole chainNodes
template <class T>
void Chain<T>::PrintChain() {
	if (size == 0) {}
	else {
		ChainIterator temp = ChainIterator(first);
		for (int i = 0; i < size; i++) {
			cout << temp->data << " ";
			temp++;
		}
		cout << endl;
	}
}

