#pragma once
#include "Element.h"
template <class T>
class List
{
protected:
	Element<T>* begin;
	Element<T>* end;
	int length;
public:
	List<T>();
	T operator[](int index);
	int size();
	T first();
	T last();
	bool remove(T node);
	bool contains(T node);
	void clear();
	bool empty();
private:
	void removebegin();
};

template<class T>
inline List<T>::List() : begin(nullptr), end(nullptr), length(0) {

}

template<class T>
inline T List<T>::operator[](int index) {
	if (empty()) {
		return -1;
	}

	int t = 0;

	Element<T>* temp = begin;
	while (temp != nullptr) {
		if (t == index) {
			return temp->data;
		}
		t++;
		temp = temp->next;
	}

	return -1;
}

template<class T>
inline int List<T>::size() {
	return length;
}

template<class T>
inline T List<T>::first() {
	return begin->data;
}

template<class T>
inline T List<T>::last() {
	return end->data;
}

template<class T>
inline bool List<T>::remove(T node) { // 1 2 3 4 5
	if (empty()) {
		return false;
	}

	Element<T>* stepBack = begin;
	Element<T>* current = begin->next;

	if (stepBack->data == node) {
		removebegin();
		length--;
		return true;
	}

	while (current != nullptr) {
		if (current->data == node) {
			Element<T>* temp = current->next;
			delete current;
			stepBack->next = temp;

			if (stepBack->next == nullptr) {
				end = stepBack;
			}

			length--;
			return true;
		}
		stepBack = current;
		current = current->next;
	}
	return false;
}

template<class T>
inline bool List<T>::contains(T node) {
	Element<T>* temp = begin;
	while (temp != nullptr) {
		if (temp->data == node) {
			return true;
		}
		temp = temp->next;
	}
	return false;
}

template<class T>
inline void List<T>::clear() {
	Element<T>* current = begin;
	while (current != nullptr) {
		Element<T>* temp = current->next;
		delete current;
		current = temp;
	}
	begin = nullptr;
	end = nullptr;
}

template<class T>
inline bool List<T>::empty() {
	return begin == nullptr;
}

template<class T>
inline void List<T>::removebegin() {
	Element<T>* temp = begin->next;
	delete begin;
	begin = temp;
}


