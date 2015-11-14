#include "list_array.h"
#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
void copy(T* src, T* dest, int size) {
	for (int i = 0; i < size; i++) {
		dest[i] = src[i];
	}
}

template <class T>
bool ListArray<T>::insert(int pos, const T & item) {
	if (pos < 0 || pos > length) return false;
	if (length == cur_size) {
		T* tmp = (T*) malloc(cur_size * 2 * sizeof(T));  
		copy(list, tmp, length);
		free(list);
		list = tmp;
		cur_size *= 2;
	}
	for (int j = length; j > pos; j--) {
		list[j] = list[j-1];
	}
	list[pos] = item;
	length ++;
	return true;	
}

template <class T>
bool ListArray<T>::remove(int pos) {
	if (pos < 0 || pos >= length) return false;
	for (int i = pos; i < length; i++) {
		list[i] = list[i+1];
	}
	length --;
	if (length <= cur_size / 2 && length > MIN_LENGTH) {
		T* tmp = (T*) malloc(cur_size / 2 * sizeof(T));
		copy(list, tmp, length);
		free(list);
		list = tmp;
		cur_size /= 2;
	}
	return true;
}

template <class T>
bool ListArray<T>::set(int pos, const T & item) {
	if (pos < 0 || pos >= length) return false;
	list[pos] = item;
	return true;
}

template <class T>
T & ListArray<T>::get(int pos) const {
	if (pos < 0 || pos >= length) {
		cout << "Invalid range!";
		exit(1);
	}
	return list[pos];
}
