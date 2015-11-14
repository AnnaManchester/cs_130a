#ifndef LIST_H
#define LIST_H

template <class T>
class List {
protected:
	int length;

public:	
	List() {length = 0;}
	~List() {}
	virtual bool insert(int pos, const T & item) = 0;
	virtual bool remove(int pos) = 0;
	virtual bool set(int pos, const T & item) = 0;
	virtual T & get(int pos) const = 0;
	int size() const { return length; }
};
#endif
