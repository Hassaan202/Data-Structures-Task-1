#pragma once
#include <iostream>
using namespace std;


template<class T>
class DList {
public:
	struct DNode;

private:
	class listIterator;
	DNode* head, * tail;
	bool isPrime(T&);

public:
	typedef listIterator iterators;
	iterators begin() {
		iterators I(head);
		return I;
	}
	iterators end() {
		iterators I(tail);
		return I;
	}

	DList();
	DList(T, DNode* = nullptr, DNode* = nullptr);
	DNode* getHead() { return head; }
	bool isEmpty();
	void insertAtStart(T&);
	void insertAtEnd(T&);
	bool insert(T&, T&);
	void insertAtMiddle(T&);
	void printList();
	void deleteAtStart();
	void deleteAtEnd();
	void deleteByValue(T&);
	void deleteNode(DNode*);
	void deleteNode(iterators);
	void printReverse();
	int deletePrimeNumbers();
	T getMax();
	T getMin();
	void sort();
	DList<T> merge(const DList<T>&);
	void swapDNodes(DNode*&, DNode*&);
	DList& operator=(const DList<T>&);
	/*DList(DList<T>&);*/
	/*~DList();*/
};




//NODE CLASS
template<class T>
struct DList<T>::DNode {
	friend class DList;
	DNode* next, * prev;
	T data;
	DNode();
	DNode(T, DNode* = nullptr, DNode* = nullptr);
};

template<class T>
inline DList<T>::DNode::DNode() {
	next = prev = nullptr;
}

template<class T>
inline DList<T>::DNode::DNode(T val, DNode* p, DNode* n) {
	data = val;
	next = n;
	prev = p;
}




//LISTITERATOR CLASS
template<class T>
class DList<T>::listIterator {
	friend class DList;
	DNode* iPtr;

public:
	listIterator(DNode* = nullptr);
	listIterator& operator++();
	listIterator operator++(int);
	listIterator& operator--();
	listIterator operator--(int);
	T& operator*();
	bool operator==(const listIterator);
	bool operator!=(const listIterator);
};

template<class T>
inline DList<T>::listIterator::listIterator(DNode* p) {
	iPtr = p;
}

template<class T>
typename DList<T>::listIterator& DList<T>::listIterator::operator++()
{
	if (iPtr != nullptr) {
		iPtr = iPtr->next;
	}
	return (*this);
}

template<class T>
typename DList<T>::listIterator DList<T>::listIterator::operator++(int) {
	//typename keyword tells the compiler that the following is type/declaration
	//depends upon a template type
	listIterator tmp = *this;
	if (iPtr!=nullptr)
	    iPtr = iPtr->next;
	return tmp;
}

template<class T>
typename DList<T>::listIterator& DList<T>::listIterator::operator--()
{
	if (iPtr != nullptr) {
		iPtr = iPtr->prev;
	}
	return (*this);
}

template<class T>
typename DList<T>::listIterator DList<T>::listIterator::operator--(int) {
	listIterator tmp = *this;
	--(*this);
	return tmp;
}

template<class T>
T& DList<T>::listIterator::operator*() {
	return (iPtr->data);
}

template<class T>
bool DList<T>::listIterator::operator==(const listIterator l) {
	return (iPtr == l.iPtr);
}

template<class T>
bool DList<T>::listIterator::operator!=(const listIterator l) {
	return (iPtr != l.iPtr);
}




//DLIST CLASS
template<class T>
inline bool DList<T>::isPrime(T& num)
{
	if (num == 1) {
		return false;
	}
	else {
		for (int i = 2; i <= num / 2; i++) {
			if (num % i == 0) {
				return false;
			}
		}
		return true;
	}
}

template<class T>
inline DList<T>::DList() {
	head = tail = nullptr;
}

template<class T>
inline DList<T>::DList(T val, DNode* h, DNode* t)
{
	data = val;
	head = h;
	tail = t;
}

template<class T>
inline bool DList<T>::isEmpty()
{
	return (head==nullptr);
}

template<class T>
inline void DList<T>::insertAtStart(T& val) {
	if (head != nullptr) { //non-empty list
		head = new DNode(val, nullptr, head);
		head->next->prev = head;
	}
	else {
		head = tail = new DNode(val);
	}
}

template<class T>
inline void DList<T>::insertAtEnd(T& val) {
	if (head != nullptr) { //non-empty list
		tail->next = new DNode(val, tail, nullptr);
		tail = tail->next;
	}
	else {
		head = tail = new DNode(val);
	}
}

template<class T>
inline bool DList<T>::insert(T& key, T& element) {
	if (head != nullptr) { //non-empty list
		if (head != tail) {  //more than one element
			DNode* tmp = head;
			while (tmp->data != key && tmp->next != nullptr) {
				tmp = tmp->next;
			}
			if (tmp->data == key) { //if element found
				if (tmp == head) {
					head->next = new DNode(element, head, head->next);
					head->next->next->prev = head->next;
				}
				else if (tmp == tail) {
					insertAtEnd(element);
				}
				else {
					tmp->next = new DNode(element, tmp, tmp->next);
					tmp->next->next->prev = tmp->next;
				}
				return true;
			}
			return false;
		}
		else {
			if (head->data == key) { //insert after head
				insertAtEnd(element);
				return true;
			}
		}
	}
	return false;
}

template<class T>
inline void DList<T>::insertAtMiddle(T& element) {
	DNode* tmp = head;
	int count = 0;
	while (tmp != nullptr) {
		tmp = tmp->next;
		count++;
	}
	tmp = head;

	if (tmp != nullptr) {
		for (int i = 0; i != count / 2 - 1; i++) {
			tmp = tmp->next;
		}
		insert(tmp->data, element);
	}
	else {
		insertAtStart(element);
	}
}

template<class T>
inline void DList<T>::printList() {
	DNode* tmp = head;
	while (tmp != nullptr) {
		if (tmp->next != nullptr) {
			cout << tmp->data;
		}
		else {
			cout << tmp->data;
		}
		tmp = tmp->next;
	}
	cout << endl;
}

template<class T>
inline void DList<T>::deleteAtStart() {
	if (head != nullptr) { //non-empty list
		if (head != tail) { //more than one element
			DNode* tmp = head;
			head = head->next;
			head->prev = nullptr;
			delete tmp;
		}
		else {
			delete head;
			head = tail = nullptr;
		}
	}
}

template<class T>
inline void DList<T>::deleteAtEnd() {
	if (head != nullptr) { //non-empty list
		if (head != tail) { //more than one element
			DNode* tmp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete tmp;
		}
		else {
			delete head;
			head = tail = nullptr;
		}
	}
}

template<class T>
inline void DList<T>::deleteByValue(T& k) {
	if (head != nullptr) { //non-empty
		if (head != tail) { //more than one element
			DNode* tmp = head;
			while (tmp->data != k && tmp->next != nullptr) {
				tmp = tmp->next;
			}
			if (tmp->data == k) { //if found
				if (tmp == head) {
					deleteAtStart();
				}
				else if (tmp == tail) {
					deleteAtEnd();
				}
				else {
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					delete tmp;
				}
			}
		}
		else {
			if (head->data == k) {
				delete head;
				head = tail = nullptr;
			}
		}
	}

}

template<class T>
inline void DList<T>::deleteNode(DNode* ptr)
{
	if (head != nullptr) { //non-empty list
		if (ptr != nullptr) {
			if (head != tail) { //more than one element
				if (ptr != head) {  //if not the first element
					/*deleteFromStart();*/
					ptr->prev->next = ptr->next;
				}
				else {
					head = ptr->next;
				}
				if (ptr != tail) { //if not the last element
					/*deletefromtail();*/
					ptr->next->prev = ptr->prev;
				}
				else {
					tail = ptr->prev;
				}
			}
			else {
				head = tail = nullptr;
			}
			delete ptr;
		}
	}
}

template<class T>
inline void DList<T>::deleteNode(iterators it)
{
	DNode* ptr = it.iPtr;
	if (head != nullptr) { //non-empty list
		if (ptr != nullptr) {
			if (head != tail) { //more than one element
				if (ptr != head) {  //if not the first element
					/*deleteFromStart();*/
					ptr->prev->next = ptr->next;
				}
				else {
					head = ptr->next;
				}
				if (ptr != tail) { //if not the last element
					/*deletefromtail();*/
					ptr->next->prev = ptr->prev;
				}
				else {
					tail = ptr->prev;
				}
			}
			else {
				head = tail = nullptr;
			}
			delete ptr;
		}
	}
}

template<class T>
inline void DList<T>::printReverse()
{
	DNode* tmp = tail;
	while (tmp != nullptr) {
		if (tmp->prev != nullptr) {
			cout << tmp->data << " , ";
		}
		else {
			cout << tmp->data << endl;
		}
		tmp = tmp->prev;
	}
}

template<class T>
inline int DList<T>::deletePrimeNumbers()
{
	int count = 0;
	DNode* tmp = head;
	while (tmp != nullptr) {
		if (isPrime(tmp->data) == true) {
			DNode* t = tmp->next;
			deleteNode(tmp);
			tmp = t;
			count++;
		}
		else {
			tmp = tmp->next;
		}
	}
	return count;
}

template<class T>
inline T DList<T>::getMax() {
	T maxNum = INT16_MIN;
	DNode* tmp = head;
	while (tmp != nullptr) {
		maxNum = max(maxNum, tmp->data);
		tmp = tmp->next;
	}
	return maxNum;
}

template<class T>
inline T DList<T>::getMin() {
	T minNum = INT16_MAX;
	DNode* tmp = head;
	while (tmp != nullptr) {
		minNum = min(minNum, tmp->data);
		tmp = tmp->next;
	}
	return minNum;
}

template<class T>
DList<T>& DList<T>::operator=(const DList<T>& t1)
{
	//deep copy implemented
	if (this != &t1) {
		if (t1.head != nullptr) {
			DNode* tmp = t1.head;
			while (tmp != nullptr) {
				insertAtEnd(tmp->data);
				tmp = tmp->next;
			}
		}
	}
	return *this;
}

template<class T>
void DList<T>::sort() {
	DNode* tmp = head, * innerTemp, * innerTempNext, * finalVal = nullptr;
	bool noMoreSwaps = false;

	while (tmp != tail && !noMoreSwaps) {
		noMoreSwaps = true;
		innerTemp = head;
		while (innerTemp->next != finalVal) {
			if ((innerTemp->data) > (innerTemp->next->data)) { //swap
				if (tmp == innerTemp) {
					tmp = tmp->next;
				}
				else if (tmp == innerTemp->next) {
					tmp = innerTemp;
				}
				innerTempNext = innerTemp->next;
				swapDNodes(innerTemp, innerTempNext); //ineertemp->next modify by temp
				noMoreSwaps = false;
			}
			else { //noswap
				innerTemp = innerTemp->next;
			}
		}
		if (!finalVal)
			finalVal = tail;
		else
			finalVal = finalVal->prev;
		tmp = tmp->next;
	}
}

template<class T>
DList<T> DList<T>::merge(const DList<T>& D1) {
	DList<T> tmpList;
	tmpList = *this;
	DNode* tmp = D1.head;
	while (tmp != nullptr) {
		tmpList.insertAtEnd(tmp->data);
		tmp = tmp->next;
	}
	return tmpList;
}

template<class T>
void DList<T>::swapDNodes(DNode*& d1, DNode*& d2) {
	//works when d1 points to an element before d2,sufficient for sorting
	DNode* tmp = nullptr;
	if (d1 != nullptr && d2 != nullptr) {
		if (d1 != d2) {
			if (d1 == head) { //swap first element
				head = d2;

				d2->prev = nullptr;
				d1->prev = d2;
				d1->next = d2->next;
				d2->next = d1;
				d1->next->prev = d1;
			}
			else if (d2 == tail) { //swap last element
				tail = d1;

				d1->next = nullptr;
				d2->next = d1;
				d2->prev = d1->prev;
				d1->prev = d2;
				d2->prev->next = d2;
			}
			else { //swap nodes in between the list
				d1->next = d2->next;
				d2->next = d1;
				d2->prev = d1->prev;
				d1->prev = d2;
				d2->prev->next = d2;
				d1->next->prev = d1;
			}
		}
	}
}

//template<class T>
//inline DList<T>::DList(DList<T>& t1)
//{
//	//deep copy implemented
//	if (t1.head != nullptr) {
//		DNode* tmp = t1.head;
//		while (tmp != nullptr) {
//			this->insertAtEnd(tmp->data);
//			tmp = tmp->next;
//		}
//	}
//}

//template<class T>
//inline DList<T>::~DList()
//{
//	if (head != nullptr) {
//		DNode* tmp = head;
//		while (tmp != nullptr) {
//			head = tmp->next;
//			delete tmp;
//			tmp = head;
//		}
//	}
//}
