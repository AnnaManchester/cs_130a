#include "list_array.h"
#include <iostream>
using namespace std;

int main(){
	ListArray<int>* list = new ListArray<int>;
	list->insert(0,1);
	list->insert(0,2);
	cout << list->get(0);
	cout << list->get(1) << endl;
	list->insert(2,5);
	list->insert(1,10);
	cout << list->get(0);
	cout << list->get(1) << endl;
	cout << list->get(2);
	cout << list->get(3) << endl;
	list -> insert(5,4);
	cout << list->get(0);
	cout << list->get(1) << endl;
	cout << list->get(2);
	cout << list->get(3) << endl;
	list->remove(0);
	list->remove(2);	
	list->remove(2);
	cout << list->get(0);
	cout << list->get(1) << endl;
	return 0;
}
