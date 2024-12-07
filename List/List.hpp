#pragma once

#include <stdexcept>
template <typename T>
class List {
	private:
		
		T* list; // It is the array which will store all the list elements
		int current; // It is the current marker
		int size; // Size of the list

	public:
		
		List();

		// A copy constructor to ensure deep copy
		List(const List<T>&);

		// Adds the given element to the current position in list.
		void add(const T&);

		// Returns the size of the list
		int length() const;

		// Returns the value at current index
		T get() const;

		// Moves the current pointer to the start of the list, throws exception if list don't have any elements
		void start();

		// Moves the current pointer to the end of the list, throws exception if list don't have any elements
		void end();

		// Moves the current pointer/marker 1 step forward. If it can't move next (i.e, at the end of list) 
		// then false is returned otherwise true. If list don't have any elements, then exception is thrown
		bool next();

		// Moves the current pointer/marker 1 step backward. If it can't move backward (i.e, at the start of list) 
		// then false is returned otherwise true. If list don't have any elements, then exception is thrown
		bool back();
		
		// Destrutor to deallocate the allocated memory
		~List();
};

template <typename T>
List<T>::List() : list(nullptr), current(-1), size(0) {}

template <typename T>
List<T>::List(const List<T>& other) {

	size = other.size;
	
	list = new T[size];

	for (int i = 0; i < other.size; i++) {
		list[i] = other.list[i];
	}

	// Initalize current to the start of the list
	current = 0;
}

template <typename T>
int List<T>::length() const {
	// Return the length/size of the list
	return size;
}

template <typename T>
void List<T>::add(const T& elem) {
	if (list == nullptr) {
		// If list is has no element, then simply create a new one.
		list = new T[1];
		list[0] = elem;
		current = 0;
	} else {
		// Store current list in temporary array
		T* temp = list;

		// Reallocate list with increased size
		list = new T[size+1];

		int i,j;
		i=j=0;

		while (i < size) {
			if (i == current) {
				list[j] = elem;
				++j;
			}
			list[j] = temp[i];
			++i;
			++j;
		}

		// Free the memory
		delete[] temp;
	}

	// Increment the size
	size++;
}

template <typename T>
T List<T>::get() const {
	if (current == -1) {
		throw std::runtime_error("The list don't have any elements!");
	}
	return list[current];
}

template <typename T>
void List<T>::start() {
	if (current == -1) throw std::runtime_error("The list don't have any elements! Can't move to start!");
	current = 0;
}

template <typename T>
void List<T>::end() {
	if (current == -1) throw std::runtime_error("The list don't have any elements! Can't move to end!");
	current = size - 1;
}

template <typename T>
bool List<T>::next() {

	if (current == -1) throw std::runtime_error("The list don't have any element! Can't move forward!");

	if (current == size-1) {
		return false;
	} else {
		current += 1;
		return true;
	}
}

template <typename T>
bool List<T>::back() {

	if (current == -1) throw std::runtime_error("The list don't have any element! Can't move backward!");

	if (current == 0) {
		return false;
	} else {
		current -= 1;
		return true;
	}
}

template <typename T>
List<T>::~List() {
	if (list != nullptr) {
		// Free the memory allocated for list
		delete[] list;
	}
}