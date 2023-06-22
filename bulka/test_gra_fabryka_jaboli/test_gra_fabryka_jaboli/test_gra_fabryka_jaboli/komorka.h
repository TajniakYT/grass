#ifndef KOMORKA_H
#define KOMORKA_H

template<class Type>
class Komorka {
public:
	Type value;
	Type* next;
	Komorka<Type>(Type cellvalue);
};
#endif

