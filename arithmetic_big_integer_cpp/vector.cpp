#include "vector.h"
#include <cstring>
Vector::Vector()
{
	size_mas = 1;
	mas = new LN[size_mas];
	size = 0;
}
void Vector::push(const LN& c)
{
	try
	{
		if (this->size == this->size_mas)
		{
			auto newMas = new LN[this->size_mas * 2];
			for (long long i = 0; i < this->size; i++)
			{
				newMas[i] = mas[i];
			}
			this->size_mas = this->size_mas * 2;
			delete[] mas;
			mas = newMas;
		}
		mas[this->size] = c;
		this->size++;
	}
	catch (std::bad_alloc e)
	{
		throw new Exceptions(ERROR_OUT_OF_MEMORY, "bad_alloc error");
	}
}
long long Vector::size_() const
{
	return size;
}
LN Vector::pop()
{
	this->size--;
	LN res = mas[this->size];
	return res;
}
