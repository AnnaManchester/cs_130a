#include "doubly_linked_list.h"

#include <string>
#include <iostream>
using namespace std;

int main() {
	DoublyLinkedList<string> test_list;
	string *a = new string("This is my first tweet.");
	string *b = new string("Hello Bryce.");
	string *c = new string("Hello Anna.");
	test_list.Add(a);
	test_list.Add(b);
	test_list.Add(c);	
	test_list.Remove(a);
	cout << *(test_list.Traverse()) << endl;
	test_list.Remove(b);
	cout << *(test_list.Traverse()) << endl;
	return 0;	
}
