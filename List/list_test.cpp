#include <exception>
#include <iostream>
#include <ostream>
#include <system_error>
#include "List.hpp"

using namespace std;

template <typename T>
std::ostream& operator << (std::ostream& op, List<T> list) {
    if (list.length() == 0) 
        op << "[]";
    else {
        op << "[" << list.get();

        while (list.next()) {
            op << ", " << list.get();
        }

        op << "]";
    }
    return op;
}

template <typename T>
void printInReverse(List<int> myList) {

    cout << "\nReversed List : ";

    // If list is empty then simply output this and return
    if (myList.length() == 0) {
        cout << "[]\n";
        return;
    }
    
    // Move to end
    myList.end();

    cout << "[" << myList.get();
    while (myList.back()) {
        cout << ", " << myList.get();
    }
    cout << "]\n";
}

int main() {

    List<int> myList;

    cout << "\nmyList = " << myList << endl;
    printInReverse<int>(myList);

    myList.add(52);
    myList.add(12);
    myList.add(3285);
    myList.add(628);

    cout << "\nMy list after some insertion : " << myList << endl;
    printInReverse<int>(myList);

    List<int> emptyList;

    try {
        cout << "\nTrying to move to start on empty list...\n";
        emptyList.start();
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    try {
        cout << "\nTrying to move to end on empty list...\n";
        emptyList.end();
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    try {
        cout << "\nTrying to move next in empty list...\n";
        emptyList.next();
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    try {
        cout << "\nTrying to move backward in empty list...\n";
        emptyList.back();
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    try {
        cout << "\nTrying to get element from empty list...\n";
        emptyList.get();
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    return 0;
}