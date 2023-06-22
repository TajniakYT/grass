#ifndef  WEKTOR_H
#define WEKTOR_H

#include "komorka.h"

template<class T>
class Wektor{
private:
	Komorka<T>* first=nullptr;
	int wielkosc;
public:	
	void dodaj(T wartosc);
	Wektor operator[](int index);
	int rozmiar();
	T suma();
};
#endif