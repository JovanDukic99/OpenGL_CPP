#pragma once
template <class T>
class Element
{
private:
	Element<T>* next;
	T data;
	template <typename T>
	friend class List;
	template <typename T>
	friend class LinkedList;
public:
	Element<T>(T data);
};

template<class T>
inline Element<T>::Element(T data) : next(nullptr) {
	this->data = data;
}
