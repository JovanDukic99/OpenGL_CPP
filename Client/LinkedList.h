#pragma once
#include "List.h"
#define begin List<T>::begin
#define end List<T>::end
#define length List<T>::length
template <class T>
class LinkedList : public List<T>
{
public:
	LinkedList<T>();
	void add(T node);
};

template<class T>
inline LinkedList<T>::LinkedList()  {
}

template<class T>
inline void LinkedList<T>::add(T node) {
	if (begin == nullptr) {
		begin = new Element<T>(node);
		end = begin;
	}
	else {
		end->next = new Element<T>(node);
		end = end->next;
	}
	length++;
}