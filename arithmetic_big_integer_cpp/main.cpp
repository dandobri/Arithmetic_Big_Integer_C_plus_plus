#include "vector.h"
#include "return_codes.h"

#include <fstream>
#include <map>

std::map<std::string, int> map1 { {"+", 2}, {"-", 2}, { "_", 1},
                                  {"*", 2}, {"/", 2}, {"~", 1},
                                  {"==", 2}, {"!=", 2}, {">=", 2}, {">", 2},
                                  {"<=", 2}, {"<", 2} };
int main(int argc, char* argv[])
{
	Vector stack = Vector();
	if (argc != 4)
	{
      fprintf(stderr, "error in parameters of command line");
  		return ERROR_PARAMETER_INVALID;
	}
	std::ifstream file(argv[1]);
	if (!file.good())
	{
  		file.close();
        fprintf(stderr, "error in opening file");
  		return ERROR_CANNOT_OPEN_FILE;
	}
	std::string s;
	int inv = 0;
	std::string third = argv[3];
	if (third == "inverse")
	{
		inv = 1;
	}
	else if (third != "direct")
	{
      fprintf(stderr, "error in third argument");
		return ERROR_PARAMETER_INVALID;
	}
	try
	{
		while (getline(file, s))
		{
			if (map1[s] == 2)
			{
				LN a = stack.pop();
				LN b = stack.pop();
				if (inv == 1)
				{
					LN betw = a;
					a = b;
					b = betw;
				}
				if (s == "+")
				{
					LN res = a + b;
					stack.push(res);
				}
				else if (s == "-")
				{
					LN res = a - b;
					stack.push(res);
				}
				else if (s == "*")
				{
					LN res = a * b;
					stack.push(res);
				}
				else if (s == "==")
				{
					bool r = a == b;
					LN res = LN(r);
					stack.push(res);
				}
				else if (s == ">=")
				{
					bool r = a >= b;
					LN res = LN(r);
					stack.push(res);
				}
				else if (s == ">")
				{
					bool r = a > b;
					LN res = LN(r);
					stack.push(res);
				}
				else if (s == "!=")
				{
					bool r = a != b;
					LN res = LN(r);
					stack.push(res);
				}
				else if (s == "<=")
				{
					bool r = a <= b;
					LN res = LN(r);
					stack.push(res);
				}
				else if (s == "<")
				{
					bool r = a < b;
					LN res = LN(r);
					stack.push(res);
				}
				else if (s == "/")
				{
					LN res = a / b;
					stack.push(res);
				}
				else if (s == "%")
				{
					LN res = a % b;
					stack.push(res);
				}
			}
			else if (map1[s] == 1)
			{
				LN a = stack.pop();
				if (s == "_")
				{
					LN res = -a;
					stack.push(res);
				}
				else if (s == "~")
				{
					LN res = ~a;
					stack.push(res);
				}
			}
			else
			{
				LN add = LN(s);
				stack.push(add);
			}
		}
	}
	catch (const Exceptions& e)
	{
		fprintf(stderr, "%s", e.error_msg.c_str());
		file.close();
		return e.error_code;
	}
	file.close();
	FILE *f = fopen(argv[2],"w");
	if (f == nullptr)
	{
      fprintf(stderr, "error in opening file");
    	return ERROR_CANNOT_OPEN_FILE;
	}
	for (long long i = stack.size_() - 1; i > -1; i--)
	{
		LN el = stack.pop();
		if (el.get_isNan())
		{
			fprintf(f, "isNan");
		}
		if (el.get_m_sign() == 1)
		{
			fprintf(f, "%c", '-');
		}
		for (long long j = el.get_m_size() - 1; j > -1; j--)
		{
			if (el.get_m_number()[j] / 16 == 0 && j == 0)
			{
				fprintf(f, "%X", el.get_m_number()[j] % 16);
			}
			else
			{
				fprintf(f, "%X%X", el.get_m_number()[j] / 16, el.get_m_number()[j] % 16);
			}
		}
		fprintf(f, "\n");
	}
	fclose(f);
	return SUCCESS;
}
