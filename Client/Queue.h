#pragma once
#include "List.h"
template <class T>
class Queue : public List<T>
{
public:
	Queue<T>();
	virtual void push(T node);
	T pop();
};

template<class T>
inline Queue<T>::Queue() : List<T>() {

}

template<class T>
inline void Queue<T>::push(T node) {
	if (List<T>::begin == nullptr) {
		List<T>::begin = new Element<T>(node);
		List<T>::end = List<T>::begin;
	}
	else {
		List<T>::end->next = new Element<T>(node);
		List<T>::end = List<T>::end->next;
	}
	List<T>::increment();
}

template<class T>
inline T Queue<T>::pop() {
	T val = List<T>::begin->data;
	List<T>::remove(val);
	return val;
}
