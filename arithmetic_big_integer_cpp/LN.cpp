#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include "LN.h"

LN::LN()
{
	is_Nan = false;
	m_size = 0;
	m_sign = false;
	m_number = nullptr;
}
LN::LN(const LN &b)
{
	is_Nan = false;
	try
	{
		this->m_number = new std::uint8_t[b.m_size];
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "bad_alloc error");
	}
	for (long long i = 0; i < b.m_size; i++)
	{
		this->m_number[i] = b.m_number[i];
	}
	this->m_size = b.m_size;
	this->m_sign = b.m_sign;
}
LN::LN(LN&& b)
{
	is_Nan = false;
	b.m_number = nullptr;
	b.m_size = 0;
	b.m_sign = false;
}
LN::LN(long long num)
{
	is_Nan = false;
	if (num < 0)
	{
		this->m_size = true;
		num = -num;
	}
	else
	{
		this->m_sign = false;
	}
	this->m_number = new std::uint8_t[19];
	int k = 0;
	while (num != 0)
	{
		m_number[k] = num % 256;
		num = num / 256;
		k++;
	}
	if (k == 0)
	{
		this->m_size = 1;
		m_number[0] = 0;
	}
	else
	{
		this->m_size = k;
	}
}
LN::LN(const char *a)
{
	is_Nan = false;
	if (a[0] == '-')
	{
		this->m_sign = true;
		this->m_size = LN::len(a) - 1;
	}
	else
	{
		this->m_sign = false;
		this->m_size = LN::len(a);
	}
	try
	{
		this->m_number = new std::uint8_t[(this->m_size + 1) / 2];
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "bad_alloc error");
	}
	long long r = 0;
	for (long long i = len(a) - 1; i > len(a) - 1 - this->m_size; i -= 2)
	{
		if (i != len(a) - this->m_size)
		{
			m_number[r] = convert_to_int(a[i]) + 16 * convert_to_int(a[i - 1]);
		}
		else
		{
			m_number[r] = convert_to_int(a[i]);
		}
		r++;
	}
	this->m_size = (this->m_size + 1) / 2;
	if (this->m_size == 1 && this->m_number[0] == 0)
	{
		this->m_sign = false;
	}
}
LN::LN(std::string str)
{
	is_Nan = false;
	long long c = str.length();
	if (str[0] == '-')
	{
		this->m_sign = true;
		this->m_size = c - 1;
	}
	else
	{
		this->m_sign = false;
		this->m_size = c;
	}
	try
	{
		this->m_number = new std::uint8_t[(this->m_size + 1) / 2];
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "bad_alloc error");
	}
	long long  r = 0;
	for (long long i = c - 1; i > c - this->m_size - 1; i-= 2)
	{
		if (i != c - this->m_size)
		{
			m_number[r] = convert_to_int(str.substr(i, 1)[0]) + 16 * convert_to_int(str.substr(i - 1, 1)[0]);
		}
		else
		{
			m_number[r] = convert_to_int(str.substr(i, 1)[0]);
		}
		r++;
	}
	this->m_size = (this->m_size + 1) / 2;
	if (m_size == 1 && m_number[0] == 0)
	{
		this->m_sign = false;
	}
}
LN& LN::operator = (LN&& b)
{
	delete[] this->m_number;
	this->m_number = b.m_number;
	this->m_size = b.m_size;
	this->m_sign = b.m_sign;
	b.m_number = nullptr;
	b.m_size = 0;
	b.m_sign = false;
	return *this;
}
LN& LN::operator = (const LN &b)
{
	this->m_size = b.m_size;
	delete[] this->m_number;
	this->m_sign = b.m_sign;
	try
	{
		this->m_number = new std::uint8_t[this->m_size];
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "bad_alloc error");
	}
	for (long long i = 0; i < this->m_size; i++)
	{
		this->m_number[i] = b.m_number[i];
	}
	return *this;
}
LN::~LN()
{
	m_size = 0;
	m_sign = false;
	is_Nan = false;
	delete[] m_number;
}
bool LN::operator == (const LN &b) const
{
	if (this->is_Nan || b.is_Nan)
	{
		return false;
	}
	if (b.m_sign != this->m_sign)
	{
		return false;
	}
	if (this->m_size != b.m_size)
	{
		return false;
	}
	if (bigger(this->m_number, b.m_number, this->m_size, b.m_size, &this->m_sign) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LN::operator !=(const LN &b) const
{
	if (this->is_Nan || b.is_Nan)
	{
		return true;
	}
	return !(*this == b);
}
bool LN::operator >(const LN &b) const
{
	if (this->is_Nan || b.is_Nan)
	{
		return false;
	}
	if (this->m_sign != b.m_sign)
	{
		return this->m_sign < b.m_sign;
	}
	if (this->m_size != b.m_size)
	{
		return this->m_size > b.m_size;
	}
	if (bigger(this->m_number, b.m_number, this->m_size, b.m_size, &this->m_sign) == 1)
	{
		return true;
	}
	else
	{
	return false;
	}
}
bool LN::operator <(const LN &b) const
{
	if (this->is_Nan || b.is_Nan)
	{
		return false;
	}
	if (this->m_sign != b.m_sign)
	{
		return this->m_sign > b.m_sign;
	}
	if (this->m_size != b.m_size)
	{
		return this->m_size < b.m_size;
	}
	if (bigger(this->m_number, b.m_number, this->m_size, b.m_size, &this->m_sign) == -1)
	{
	  return true;
	}
	else
	{
		return false;
	}
}
bool LN::operator >=(const LN &b) const
{
	if (this->is_Nan || b.is_Nan)
	{
		return false;
	}
	return !(*this < b);
}
bool LN::operator <=(const LN &b) const
{
	if (this->is_Nan || b.is_Nan)
	{
		return false;
	}
	return !(*this > b);
}
LN LN::operator +(const LN &b) const
{
		LN res{};
		if (this->is_Nan || b.is_Nan)
		{
			res.is_Nan = true;
			return res;
		}
		bool pBoolean = true;
		try
		{
			if (this->m_sign == b.m_sign)
			{
				res.m_sign = b.m_sign;
				res.m_number = sum(this->m_number, b.m_number, this->m_size, b.m_size, &pBoolean);
				res.m_size = std::max(this->m_size, b.m_size) + pBoolean;
			}
			else
			{
				if (this->m_sign < b.m_sign)
				{
					res.m_number = sub(this->m_number, b.m_number, this->m_size, b.m_size, &pBoolean, &res.m_size, &res.m_sign);
				}
				else
				{
					res.m_number = sub(b.m_number, this->m_number, b.m_size, this->m_size, &pBoolean, &res.m_size, &res.m_sign);
				}
			}
		}
		catch (Exceptions e)
		{
			throw;
		}
		res.is_Nan = false;
		return res;
}
LN& LN::operator +=(const LN& b)
{
	if (this->is_Nan || b.is_Nan)
	{
		this->is_Nan = true;
		return *this;
	}
	try
	{
		*this = *this + b;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return *this;
}
LN LN::operator -(const LN &b) const
{
		LN res{};
		if (this->is_Nan || b.is_Nan)
		{
			res.is_Nan = true;
			return res;
		}
		bool pBoolean = true;
		try
		{
			if (this->m_sign != b.m_sign)
			{
				res.m_sign = this->m_sign;
				res.m_number = sum(this->m_number, b.m_number, this->m_size, b.m_size, &pBoolean);
				res.m_size = std::max(this->m_size, b.m_size) + pBoolean;
			}
			else
			{
				res.m_number = sub(this->m_number, b.m_number, this->m_size, b.m_size, &pBoolean, &res.m_size, &res.m_sign);
			}
		}
		catch (Exceptions e)
		{
			throw;
		}
		res.is_Nan = false;
		return res;
}
LN& LN::operator -=(const LN& b)
{
	if (this->is_Nan || b.is_Nan)
	{
    	this->is_Nan = true;
		return *this;
	}
	try
	{
		*this = *this - b;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return *this;
}
LN LN::operator *(const LN& b) const
{
	LN res{};
	if (this->is_Nan || b.is_Nan)
	{
		res.is_Nan = true;
		return res;
	}
	if (this->m_sign == b.m_sign)
	{
		res.m_sign = false;
	}
	else
	{
		res.m_sign = true;
	}
	try
	{
		res.m_number = mult(this->m_number, b.m_number, this->m_size, b.m_size, &res.m_size);
	}
	catch (Exceptions e)
	{
		throw;
	}
	res.is_Nan = false;
	return res;
}
LN& LN::operator *=(const LN& b)
{
	if (this->is_Nan || b.is_Nan)
	{
		this->is_Nan = true;
		return *this;
	}
	try
	{
		*this = *this * b;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return *this;
}
LN LN::operator /(LN& b)
{
	LN res{};
	if (b == LN("0"))
	{
		res.is_Nan = true;
		return res;
	}
	if (this->is_Nan || b.is_Nan)
	{
		res.is_Nan = true;
		return res;
	}
	int t = this->m_sign;
	int k = b.m_sign;
	this->m_sign = false;
	b.m_sign = false;
	LN right = *this;
	LN left = LN("0");
	LN mid{};
	while (right - left > LN("1"))
	{
		mid = right + left;
		try
		{
			mid.m_number = LN::divide_to_two(mid.m_number, mid.m_size, &mid.m_size);
		}
		catch (Exceptions e)
		{
			throw;
		}
		if (mid * b < *this)
		{
			left = mid;
		}
		else if (mid * b > *this)
		{
			right = mid;
		}
		else
		{
			res = mid;
			if (t != k)
			{
				res.m_sign = true;
			}
			else
			{
				res.m_sign = false;
			}
			this->m_sign = t;
			b.m_sign = k;
			return res;
		}
	}
	res = left;
	if (t != k)
	{
		res.m_sign = true;
	}
	else
	{
		res.m_sign = false;
	}
	this->m_sign = t;
	b.m_sign = k;
	res.is_Nan = false;
	return res;
}
LN& LN::operator /=(LN& b)
{
	if (this->is_Nan || b.is_Nan)
	{
		this->is_Nan = true;
		return *this;
	}
	try
	{
		*this = *this / b;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return *this;
}
LN LN::operator %(LN& b)
{
	if (this->is_Nan || b.is_Nan)
	{
		this->is_Nan = true;
		return *this;
	}
	return *this - *this / b;
}
LN& LN::operator %=(LN& b)
{
	if (this->is_Nan || b.is_Nan)
	{
		this->is_Nan = true;
		return *this;
	}
	try
	{
		*this = *this % b;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return *this;
}
LN LN::operator ~()
{
	try
	{
		LN res{};
		if (this->m_sign)
		{
			res.is_Nan = true;
			return res;
		}
		LN right = *this;
		LN left = LN("0");
		LN mid{};
		while (right - left > LN("1"))
		{
			mid = left + right;
			mid.m_number = LN::divide_to_two(mid.m_number, mid.m_size, &mid.m_size);
			LN sqr = mid * mid;
			if (sqr < *this)
			{
				left = mid;
			}
			else if (sqr > *this)
			{
				right = mid;
			}
			else
			{
				res = mid;
				return res;
			}
		}
		res = left;
		return res;
	}
	catch (Exceptions e)
	{
		throw;
	}
}
LN LN::operator -()
{
	if (this->is_Nan)
	{
		return *this;
	}
	this->m_sign = !this->m_sign;
	return *this;
}
LN LN::operator +()
{
	if (this->is_Nan)
	{
		return *this;
	}
	this->m_sign = false;
	return *this;
}
LN::operator long long() const
{
	long long res = 0;
	if (!this->is_Nan)
	{
		for (long long i = m_size - 1; i > -1; i--)
		{
			res = 256 * res + m_number[i];
		}
		if (m_sign)
		{
			res = -res;
		}
	}
	return res;
}
LN::operator bool() const
{
	if (!this->is_Nan)
	{
		for (long long i = 0; i < m_size; i++)
		{
			if (m_number[i] != 0)
			{
				return true;
			}
		}
	}
	return false;
}
LN operator"" _ln(const char *a)
{
	LN res = LN(a);
	return res;
}
LN& LN::operator ++()
{
	if (this->is_Nan)
	{
		return *this;
	}
	LN one = LN("1");
	try
	{
		*this = *this + one;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return *this;
}
LN& LN::operator --()
{
	if (this->is_Nan)
	{
		return *this;
	}
	LN one = LN("1");
	try
	{
		*this = *this - one;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return *this;
}
LN LN::operator ++(int)
{
	if (this->is_Nan)
	{
		return *this;
	}
	LN res = *this;
	LN one = LN("1");
	try
	{
		*this = *this + one;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return res;
}
LN LN::operator --(int)
{
	if (this->is_Nan)
	{
		return *this;
	}
	LN res = *this;
	LN one = LN("1");
	try
	{
		*this = *this - one;
	}
	catch (Exceptions e)
	{
		throw;
	}
	return res;
}
int LN::bigger(const std::uint8_t* a, const std::uint8_t*b, const unsigned int size_a, const unsigned int size_b, const bool* sign)
{
	for (long long i = std::min(size_a, size_b) - 1; i > -1; i--)
	{
		if (a[i] > b[i])
		{
			if (*sign == 0)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
		if (a[i] < b[i])
		{
			if (*sign == 0)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}
std::uint8_t* LN::divide_to_two(const std::uint8_t* a, long long size_a, long long *size)
{
	try
	{
		std::uint8_t *res;
		res = new std::uint8_t[size_a];
		int trans = 0;
		for (long long i = size_a - 1; i > -1; i--)
		{
			res[i] = (a[i] >> 1) + 128 * trans;
			if (a[i] % 2 == 1)
			{
				trans = 1;
			}
			else
			{
				trans = 0;
			}
		}
		res = LN::delete_extra_zeros(res, size_a, size);
		return res;
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "");
	}
	catch (Exceptions e)
	{
		throw;
	}
}
std::uint8_t* LN::mult(const std::uint8_t* a, const std::uint8_t* b, long long size_a, long long size_b, long long* size)
{
	try
	{
		auto *res = new std::uint8_t[size_a + size_b];
		for (long long i = 0; i < size_a + size_b; i++)
		{
			res[i] = 0;
		}
		auto res1 = new std::uint8_t[size_a + size_b];
		for (long long t = 0; t < size_a + size_b; t++)
		{
			res1[t] = 0;
		}
		for (long long i = 0; i < size_b; i++)
		{
			int translate = 0;
			for (long long k = 0; k < i; k++)
			{
				res1[k] = 0;
			}
			for (long long j = 0; j < size_a; j++)
			{
				res1[i + j] = (a[j] * b[i] + translate) % 256;
				translate = (a[j] * b[i] + translate) / 256;
			}
			res1[i + size_a] = translate;
			bool bul = true;
			res = LN::sum(res, res1, size_a + size_b, size_a + size_b, &bul);
		}
		delete[] res1;
		res = LN::delete_extra_zeros(res, size_a + size_b, size);
		return res;
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "");
	}
	catch (Exceptions e)
	{
		throw;
	}
}
std::uint8_t *LN::sum(const std::uint8_t* a, const std::uint8_t* b, long long size_a, long long size_b, bool* pBoolean)
{
	try
	{
		auto *res = new std::uint8_t[std::max(size_a, size_b)];
		int translatebit = 0;
		for (long long i = 0; i < std::min(size_a, size_b); i++)
		{
			int ourbit = 1;
			std::uint8_t s = 0;
			for (int j = 0; j < 8; j++)
			{
				s |= a[i] & ourbit ^ b[i] & ourbit ^ translatebit;
				translatebit = ((a[i] & b[i] & ourbit) | (a[i] & ourbit & translatebit) | (b[i] & ourbit & translatebit)) << 1;
				ourbit <<= 1;
			}
			if (translatebit == 256)
			{
				translatebit = 1;
			}
			else
			{
				translatebit = 0;
			}
			res[i] = s;
		}
		if (size_a == std::max(size_a, size_b))
		{
			for (long long i = size_b; i < size_a; i++)
			{
				int ourbit = 1;
				std::uint8_t s = 0;
				for (int j = 0; j < 8; j++)
				{
					s |= a[i] & ourbit ^ !*pBoolean & ourbit ^ translatebit;
					translatebit = ((a[i] & !*pBoolean & ourbit) | (a[i] & ourbit & translatebit) | (!*pBoolean & ourbit & translatebit)) << 1;
					ourbit <<= 1;
				}
				if (translatebit == 256)
				{
					translatebit = 1;
				}
				else
				{
					translatebit = 0;
				}
				res[i] = s;
			}
		}
		else
		{
			for (long long i = size_a; i < size_b; i++)
			{
				int ourbit = 1;
				std::uint8_t s = 0;
				for (int j = 0; j < 8; j++)
				{
					s |= !*pBoolean & ourbit ^ b[i] & ourbit ^ translatebit;
					translatebit = ((!*pBoolean & b[i] & ourbit) | (!*pBoolean & ourbit & translatebit) | (b[i] & ourbit & translatebit)) << 1;
					ourbit <<= 1;
				}
				if (translatebit == 256)
				{
					translatebit = 1;
				}
				else
				{
					translatebit = 0;
				}
				res[i] = s;
			}
		}
		if (translatebit != 0)
		{
			if (*pBoolean)
			{
				auto *newRes = new std::uint8_t[std::max(size_a, size_b) + 1];
				memcpy(newRes, res, std::max(size_a, size_b) * 2);
				delete [] res;
				res = newRes;
				res[std::max(size_a, size_b)] = 1;
			}
			*pBoolean = true;
		}
		else
		{
			*pBoolean = false;
		}
		return res;
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "bad_alloc error");
	}
}
std::uint8_t *LN::inversecode(const std::uint8_t* a, long long size_t, long long size_a, bool* bul)
{
	try
	{
		std::uint8_t *b;
		b = new std::uint8_t[size_t];
		for (long long i = 0; i < size_a; i++)
		{
			b[i] = 255 - a[i];
		}
		for (long long i = size_a; i < size_t; i++)
		{
			b[i] = 255;
		}
		std::uint8_t res[] = { 1 };
		auto res1 = sum(b, res, size_t, 1, bul);
		delete[] b;
		return res1;
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "");
	}
}
std::uint8_t *LN::sub(const std::uint8_t* a, const std::uint8_t* b, long long size_a, long long size_b, bool* bul, long long* size, bool* sign)
{
	try
	{
		std::uint8_t *res = inversecode(b, size_a, size_b, bul);
		*bul = !*bul;
		auto res1 = sum(a, res, size_a, size_a, bul);
		if (size_b == 1 && b[0] == 0)
		{
			*size = size_a;
			return res1;
		}
		delete[] res;
		*size = size_a;
		if (!*bul)
		{
			*bul = !*bul;
			auto final_res = inversecode(res1, size_a, size_a, bul);
			delete[] res1;
			*sign = true;
			final_res = LN::delete_extra_zeros(final_res, size_a, size);
			return final_res;
		}
		else
		{
			*sign = false;
			res1 = LN::delete_extra_zeros(res1, size_a, size);
			return res1;
		}
	}
	catch (std::bad_alloc e)
	{
		throw Exceptions(ERROR_OUT_OF_MEMORY, "");
	}
	catch (Exceptions e)
	{
		throw;
	}
}
std::uint8_t *LN::delete_extra_zeros(std::uint8_t* res, long long size, long long* size_res)
{
	try
	{
		int k = 0;
		for (long long i = size - 1; i > 0; i--)
		{
			if (res[i] == 0b0000)
			{
				k++;
			}
			else
			{
				break;
			}
		}
		if (k > 0)
		{
			auto newRes = new std::uint8_t[size - k];
			memcpy(newRes, res, (size - k) * 2);
			delete [] res;
			res = newRes;
		}
		*size_res = size - k;
		return res;
	}
	catch (std::bad_alloc e)
	{
		throw new Exceptions(ERROR_OUT_OF_MEMORY, "");
	}
}
int LN::convert_to_int(const unsigned char c)
{
	if (c >= 'A' && c <= 'F')
	{
		return c - '0' - 7;
	}
	else if(c >= 'a' && c <= 'f')
	{
		return c - '0' - 39;
	}
	else
	{
		return c - '0';
	}
}
int LN::len(const char *str)
{
	int k = 0;
	while (str[k] != '\0')
	{
		k++;
	}
	return k;
}
