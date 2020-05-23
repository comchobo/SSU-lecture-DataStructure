#pragma once
#include<iostream>
#include<cstring>
#include<stdlib.h>

class Bizcard;
template <class T> class Bag;

class Bizcard{
	private:
		char *name;
		char *phone;
	public:
		Bizcard();
		Bizcard(const char* input, const char* phinput);
		Bizcard& operator=(const Bizcard& sub);
		Bizcard(const Bizcard& copy); 
		~Bizcard();
		void ShowInfo() throw (char);
};

template <class T> class Bag {
	public: 
		Bag (int bagCapacity = 3);
	       ~Bag();
	        int Size() const;
		bool IsEmpty() const;
		T& Element() const;        
		void Push(const T&);    
		void Pop();   
	private:   
		T *array;   
		int capacity;    
		int top;  
}; 

// Bizcard class definition
using namespace std;

Bizcard::Bizcard(){
	name = NULL;		// 포인터가 할당받았는지 검사하기 위해 널로 초기화
	phone = NULL;
}

Bizcard::Bizcard(const char* input, const char* phinput){
	name = new char[strlen(input)+1];
	phone = new char[strlen(phinput)+1];
	strcpy(name, input);
	strcpy(phone,phinput);
}
// 무난하게 입력받은 파라미터를 통해 name과 phone을 복사한다.

Bizcard& Bizcard::operator=(const Bizcard& sub) {
	name = new char[strlen(sub.name)+1];
	phone = new char[strlen(sub.phone)+1];
	strcpy(name,sub.name);
	strcpy(phone,sub.phone);
	return *this;
}
//대입연산자 또한 생성자와 유사하다.

Bizcard::Bizcard(const Bizcard& copy) {
	name = new char[strlen(copy.name)+1];
	phone = new char[strlen(copy.phone)+1];
	strcpy(name, copy.name);
	strcpy(phone, copy.phone);
}
// 복사생성자 또한 생성자와 유사하다.

Bizcard::~Bizcard() {
	int error = -1;
	if (name) {
		delete[] name;
		name = NULL;		//포인터변수를 해제하면 널로 초기화한다.
	}
	if (phone) {
		delete[] phone;
		phone = NULL;
	}
}

void Bizcard::ShowInfo() throw (char) {
	int error = -1;
	if (name != NULL && phone != NULL){
		cout << "name is " << name << endl;
		cout << "phone number is " << phone << endl;
	}
// 포인터 멤버변수가 할당받았을 때만 출력한다.
}

//bag class definition

template <typename T> 
int Bag<T>::Size() const {
	return top+1;
	}

template <typename T> 
bool Bag<T>::IsEmpty() const {
	return (top == -1);
}

template <typename T> 
Bag<T>::Bag (int bagCapacity): capacity ( bagCapacity ) {
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];   top = -1; 
}
	   	   
template <typename T>
Bag<T>::~Bag() {
	int i;
	for (i=top;i>-1; i--) {
		array[i].~T();   // array에 쌓인 스택을 차례차례 해제한다.
	}
	if (array != NULL) {
		delete[] array;  // 이 또한 마찬가지로 해제한 뒤 널로 초기화해 
		array = NULL;  // 해제된 메모리를 다시 해제하는 것을 방지한다.
	}
}

template <typename T> 
T& Bag<T>::Element() const {
	int a=rand();
	if(IsEmpty()) throw "Bag is empty";
	return array[a%top];
}
// rand 함수를 통해 랜덤한 값을 출력한다.

template <typename T> 
void Bag<T>::Push(const T& x) {
   if (capacity ==top+1){
        ChangeSize1D(array, capacity, 2 * capacity);
	    capacity *=2;   
	}   
	array[++top] = x; 
} 

template <typename T>
void Bag<T>::Pop() {
   if (IsEmpty()) throw "Bag is empty, cannot delete";
   int deletePos = top / 2;
   copy(array+deletePos+1,array+top+1,array+deletePos);
   array[top--].~T();
}

int min(int a, int b){
	if(a>b) return b;
	else return a;
}

template <typename T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "New length must be >= 0";
    T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete [] a; 
	a = temp; 
}
