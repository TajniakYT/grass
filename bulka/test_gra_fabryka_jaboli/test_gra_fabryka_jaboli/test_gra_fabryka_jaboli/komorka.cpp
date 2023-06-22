#include "komorka.h"

template<class Type>
Komorka<Type>::Komorka<Type>(Type cellvalue)
{
	value = cellvalue;
	next = nullptr;
}