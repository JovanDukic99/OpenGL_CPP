#pragma once
#include "Queue.h"
template <class T, class F>
class PriorityQueue : public Queue<T>
{
private:
	F test;
public:
	PriorityQueue<T, F>();
	void push(T node);
private:
	void insertAtBegin(T node);
	void insertAtEnd(T node);
	void insertBetween(Element<T>* temp, Element<T>* current, T node);
};

template<class T, class F>
inline PriorityQueue<T, F>::PriorityQueue() : Queue<T>() {

}

template<class T, class F>
inline void PriorityQueue<T, F>::push(T node) {
	if (List<T>::begin == nullptr) {
		List<T>::begin = new Element<T>(node);
		List<T>::end = List<T>::begin;
		List<T>::increment();
		return;
	}
	else {
		if (test(List<T>::begin->data, node)) { // 1 3
			insertAtBegin(node);
			return;
		}
		Element<T>* temp = List<T>::begin;
		Element<T>* current = List<T>::begin->next;

		while (current != nullptr) {
			if (test(current->data, node)) {
				insertBetween(temp, current, node);
				return;
			}
			temp = current;
			current = current->next;
		}
		
		insertAtEnd(node);
	}
}

template<class T, class F>
inline void PriorityQueue<T, F>::insertAtBegin(T node) {
	Element<T>* temp = new Element<T>(node);
	temp->next = List<T>::begin;
	List<T>::begin = temp;
	List<T>::increment();
}

template<class T, class F>
inline void PriorityQueue<T, F>::insertAtEnd(T node) {
	Element<T>* temp = new Element<T>(node);
	List<T>::end->next = temp;
	List<T>::end = temp;
	List<T>::increment();
}

template<class T, class F>
inline void PriorityQueue<T, F>::insertBetween(Element<T>* temp, Element<T>* current, T node) {
	Element<T>* p = new Element<T>(node);
	p->next = current;
	temp->next = p;
	List<T>::increment();
}
