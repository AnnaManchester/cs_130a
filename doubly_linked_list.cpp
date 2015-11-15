#include "doubly_linked_list.h"
#include <iostream>
using namespace std;
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
	head = NULL;
	this->length = 0;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node<T>* tmp;
	while (head) {
		tmp = head;
		head = head->GetNext();
		delete tmp;
	}
}

template <class T>
void DoublyLinkedList<T>::Add(T& node) {
	Node<T>* tmp = head;
	if (!head)  {
	head = new Node<T>(node);
	this->length ++;
	return;
	}
	while (tmp->GetNext()) {
		 tmp = tmp->GetNext();
	}
	Node<T>* n = new Node<T>(node);
	tmp->SetNext(n);
	n->SetPrev(tmp);
	this->length ++;  
}

template <class T>
void DoublyLinkedList<T>::Remove(T& node) {
	Node<T>* tmp = head;
	while (tmp) {
		if (tmp->GetVal() == node) {
			Node<T>* prev = tmp->GetPrev();
			Node<T>* next = tmp->GetNext();
			if (prev) prev->SetNext(next);
			if (next) next->SetPrev(prev);
			if (tmp == head) head = head->GetNext();
			delete tmp;
			this->length --;
			return;
		}
		 tmp = tmp->GetNext();
	}
}



template <class T>
Node<T>* DoublyLinkedList<T>::GetHead(void) {
	if (head) return head;
	return NULL;  
}

template <class T>
bool DoublyLinkedList<T>::insert(int pos, const T & item) {
	if (pos < 0 || pos > this->length) return false;
	int count = 0;
	Node<T>* cur = head;
	Node<T>* node = new Node<T>;
	node->SetVal(item);
	if (pos == 0) {
		if (cur) {
			cur->SetPrev(node);
		}
		node->SetNext(cur);
                head = node;
		this->length ++;
		return true;
	}
	while (count < pos - 1) {
		cur = cur->GetNext();
		count ++;
	}
	Node<T>* tmp = cur->GetNext();
	cur->SetNext(node);
	node->SetPrev(cur);
	node->SetNext(tmp);
	if (tmp)
		tmp->SetPrev(node);
	this->length ++;
        
	return true;
}

template <class T>
bool DoublyLinkedList<T>::remove(int pos) {
	if (pos < 0 || pos >= this->length) return false;
	int count = 0;
	Node<T>* cur = head;
	if (pos == 0) {
		Node<T>* tmp = cur->GetNext();
		delete cur;
		if (tmp) {
			tmp->SetPrev(NULL);
		}
		head = tmp;
		this->length --;
		return true;
	}
	while (count < pos - 1) {
		cur = cur->GetNext();
		count ++;
	}
	Node<T>* tmp = cur->GetNext();
	Node<T>* tmp2 = tmp->GetNext();
	cur->SetNext(tmp2);
	if (tmp2) {
		tmp2->SetPrev(cur);
	}
	delete tmp;
	this->length --;
	return true;
}


template <class T>
bool DoublyLinkedList<T>::remove(iterator it) {
	Node<T>* node = it.GetNode();
	if (node == NULL) return false;
	Node<T>* prev = node->GetPrev();
	Node<T>* next = node->GetNext();
	if (prev) prev->SetNext(next);
	if (next) next->SetPrev(prev);
	if (node == head) head = head->GetNext();
	delete node;
	this->length --;
	return true;
}


template <class T>
bool DoublyLinkedList<T>::set(int pos, const T & item) {
	if (pos < 0 || pos >= this->length) return false;
	int count = 0;
	Node<T>* cur = head;
	while (count < pos) {
		cur = cur->GetNext();
		count ++;
	}
	cur->SetVal(item);
	return true;
}

template <class T>
T & DoublyLinkedList<T>::get(int pos) const {
	if (pos < 0 || pos >= this->length) {
		cout << "Invalid range!";
		exit(1);
	}
	int count = 0;
	Node<T>* cur = head;
	while (count < pos) {
		cur = cur->GetNext();
		count ++;
	}
	return cur->GetVal();
}
