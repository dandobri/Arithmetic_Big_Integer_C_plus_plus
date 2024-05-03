#ifndef ITMO_CPP_LN_DANDOBRI_MAIN_LN_H
#define ITMO_CPP_LN_DANDOBRI_MAIN_LN_H
#include "return_codes.h"
#include "exceptionsLN.h"
class LN
{
  public:
	LN();
	LN(const LN &b);
	LN(LN&& b);
	LN(long long num);
	LN(const char *a);
	LN(std::string str);
	std::uint8_t *get_m_number() const
	{
		return m_number;
	}
	bool get_m_sign() const
	{
		return m_sign;
	}
	bool get_isNan() const
	{
		return is_Nan;
	}
	long long get_m_size() const
	{
		return m_size;
	}
	LN& operator = (LN&& b);
	LN& operator = (const LN& b);
	~LN();
	bool operator ==(const LN &b) const;
	bool operator !=(const LN &b) const;
	bool operator >(const LN &b) const;
	bool operator <(const LN &b) const;
	bool operator >=(const LN &b) const;
	bool operator <=(const LN &b) const;
	LN operator +(const LN &b) const;
	LN& operator +=(const LN& b);
	LN operator -(const LN &b) const;
	LN& operator -=(const LN& b);
	LN operator *(const LN& b) const;
	LN& operator *=(const LN& b);
	LN operator /(LN& b);
	LN& operator /=(LN& b);
	LN operator -();
    LN operator +();
	LN operator ~();
	LN operator %(LN& b);
	LN& operator %=(LN& b);
    LN& operator ++();
    LN& operator --();
    LN operator ++(int);
    LN operator --(int);
    operator long long() const;
	operator bool() const;
  private:
    std::uint8_t* m_number{};
    bool m_sign{};
    bool is_Nan{};
    long long m_size{};
    static std::uint8_t* sum(const std::uint8_t* a, const std::uint8_t* b, long long size_a, long long size_b, bool* pBoolean);
    static std::uint8_t* divide_to_two(const std::uint8_t* a, long long size_a, long long *size);
    static std::uint8_t* sub(const std::uint8_t* a, const std::uint8_t* b, long long size_a, long long size_b, bool* bul, long long* size, bool* sign);
    static int bigger(const std::uint8_t* a, const std::uint8_t*b, unsigned int size_a, unsigned int size_b, const bool* sign);
    static std::uint8_t* delete_extra_zeros(std::uint8_t* res, long long size, long long* size_res);
    static std::uint8_t* mult(const std::uint8_t* a, const std::uint8_t* b, long long size_a, long long size_b, long long* size);
	static std::uint8_t* inversecode(const std::uint8_t* a, long long size_t, long long size_a, bool* bul);
	static int convert_to_int(unsigned char c);
	static int len(const char *str);
};
LN operator"" _ln(const char *a);
#endif
