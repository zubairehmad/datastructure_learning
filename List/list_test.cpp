#include "List.hpp"
#include <iostream>

using namespace std;

template <typename T> std::ostream &operator<<(std::ostream &op, List<T> list) {
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

void inputList(List<int> &list) {
  int value = 0;

  do {
    cout << "\nEnter value to add in list (-1 to exit) : ";
    cin >> value;

    if (value != -1) {
      list.add(value);
    }
  } while (value != -1);
}

template <typename T> void printInReverse(List<int> myList) {

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

  inputList(myList);

  cout << "\nmyList = " << myList;
  printInReverse<int>(myList);

  myList.end();

  // Remove as many can be removed
  try {
    myList.remove();
    myList.remove();
    myList.remove();
  } catch (const exception &e) { /* Just silent the exception */ }

  cout << "\nMy list after some deletions from end: " << myList;
  printInReverse<int>(myList);

  int val;
  cout << "\nEnter any element to check whether its present: ";
  cin >> val;

  if (myList.find(val)) {
    cout << val << " is present in the list!\n";

    cout << "\nWith what value, you want to change it : ";
    cin >> val;

    myList.update(val);

    cout << "\nMy List: " << myList << endl;

  } else {
    cout << val << " is not present in the list!\n";
  }

  cout << "\nOn which index you want to jump to: ";
  cin >> val;

  try {

    myList.moveTo(val);

    cout << "\nAt index " << val << ", the value here is : " << myList[val]
         << endl;

  } catch (const exception &e) {
    cout << "\nException caught: " << e.what() << endl;
  }

  return 0;
}