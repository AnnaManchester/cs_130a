#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <stddef.h>
#include <iostream>
#include "list.h"

using namespace std;

template <class T>
class Node {
private:
	Node* prev;
	Node* next;
	T val;
public:
	Node(T &value) {
		val = value;
		prev = NULL;
		next = NULL;
	}
	Node() {}
	~Node() {}

	void SetPrev(Node* node) {prev = node;};
	Node* GetPrev() {return prev;};
	void SetNext(Node* node) {next = node;};
	Node* GetNext() {return next;};
	void SetVal(const T &value) {val = value;};
	T& GetVal() {return val;};
};

template <class T>
class DoublyLinkedList : public List<T> {
private:
	Node<T>* head; // May need tail, depending on what 2.d asks for.
public:
	class iterator
        {
            public:
		iterator() {};
                iterator(Node<T>* ptr) {
			node_ = ptr;
		}
                iterator operator++() {
			iterator i = *this;
			node_=node_->GetNext();
			return i;
		}
		iterator operator++(int junk) { node_ = node_->GetNext(); return *this; }
		T& operator*() {
		    if (node_)
			return node_->GetVal();
		    cout  <<  "Error: accessing null pointer"  <<  endl;
		    exit(1);
		}
                T* operator->() {
		    if (node_)
			return &(node_->GetVal());
		    cout  <<  "Error: accessing null pointer"  <<  endl;
		    exit(1);
		}
                bool operator==(const iterator& rhs) { return node_ == rhs.node_; }
                bool operator!=(const iterator& rhs) { return node_ != rhs.node_; }
        	Node<T>* GetNode() { return node_; }   
	private:
		Node<T>* node_;
        };

	DoublyLinkedList();
	~DoublyLinkedList();
	
	void Add(T& node);
	void Remove(T& node);
	Node<T>* GetHead(void); // Get head
	void SetHead(Node<T>* node) {
		head = node;
	}
	bool remove(iterator it);	
	bool insert(int pos, const T & item);
	bool remove(int pos);
	bool set(int pos, const T & item);
	T& get(int pos) const;
	iterator begin() {return iterator(head);}
	iterator end() {return iterator(NULL);}
};
#include "doubly_linked_list.cpp"
#endif
