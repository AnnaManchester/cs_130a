#include "doubly_linked_list.h"
#include "list_array.h"
#include <ctime>
#include <iostream>
using namespace std;

void TestInsert(int num) {
    DoublyLinkedList<int>* list1 = new DoublyLinkedList<int>();
    ListArray<int>* list2 = new ListArray<int>();
    clock_t begin = clock();
    for (int i = 0; i < num; i++) {
	list1->insert(i/2, i);
    }
    double secs = double(clock() - begin)/CLOCKS_PER_SEC;
    cout  <<  "Doubly linked list based, insert number: "  <<  num  <<  "  time: "  <<  secs  <<  endl;
    begin = clock();
    for (int i = 0; i < num; i++) {
	list2->insert(i/2, i);
    }
    secs = double(clock() - begin)/CLOCKS_PER_SEC;
    cout  <<  "Array based, insert number: "  <<  num  <<  "  time: "  <<  secs  <<  endl;
    
    delete list1;
    delete list2;
}

int main() {
    for (int i = 2000; i<=10000; i+=2000) {
	TestInsert(i);
    }
    return 0;
}
