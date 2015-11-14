#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H
#include <stdlib.h>
#include "list.h"
#define MIN_LENGTH 2

template <class T>
class ListArray : List<T> {
private:
	T* list;
	int cur_size; //current size of array
	int length;
public:
	ListArray() {
		list = (T*)malloc(MIN_LENGTH  * sizeof(T));
		length = 0;
		cur_size = MIN_LENGTH;
	}
	~ListArray() {
		delete list;
	}	

	bool insert(int pos, const T & item);
	bool remove(int pos);
	bool set(int pos, const T & item);
	T & get(int pos) const;
	int size() const { return length; }
};
#include "list_array.cpp"
#endif
