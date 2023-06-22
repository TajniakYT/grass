#include <iostream>
#include <stdexcept>
#include "komorka.h"
#include "wektor.h"

template<class T>
void Wektor<T>::dodaj(T wartosc) {
	if (first == nullptr)
	{
		first = new Komorka<T>(wartosc);
	}
	Komorka<T>* current = first;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	current->next = new Komorka<T>(wartosc);
}

template <class T>
Wektor<T> Wektor<T>::operator[](int index) {
	Komorka<T>* current = first;
	for (int i = 0; i < index; i++) {
		if (current.next != nullptr) {
			current = current->next;
		}
		else {
			throw std::out_of_range("Index out of range");
		}
	}
	return current->value;
}

template <class T>
T Wektor<T>::suma() {
	T* suma;
	if (first == nullptr)
	{
		return((T)0);
	}
	else {
		suma += first->value;
	}
	Komorka<T>* current = first;

	while (true) {
		if (current.next != nullptr) {
			current = current->next;
			suma += current->value;
		}
		else {
			break;
		}
	}
	return suma;
}

