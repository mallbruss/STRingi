
#include <istream>
using namespace std;
class MyString
{
private:
	size_t length;
	char* str;

public:
	MyString();
	MyString(const char* c);
	MyString(const MyString& t);
	~MyString();

	MyString& operator= (const MyString& t);
	MyString& operator= (const char* c);
	MyString operator+ (const MyString& t) const;
	MyString& operator+= (const MyString& t);
	char& operator[] (size_t i);
	const char& operator[] (size_t i) const;

	char& at(size_t i);
	const char& at(size_t i) const;
	void get_input(istream& in);
	size_t get_length() const;
	void from_c_str(const char* other);

	friend ostream& operator<< (ostream& out, const MyString& t);
	friend istream& operator>> (istream& in, MyString& t);
	friend bool operator== (const MyString& t, char* c);
	friend bool operator== (const MyString& t, const MyString& t1);
	friend bool operator!= (const MyString& t, char* c);
	friend bool operator!= (const MyString& t, const MyString& t1);
};

MyString::MyString()
{
	length = 1;
	str = '\0';
}

MyString::MyString(const char* c)
{
	from_c_str(c);
}

MyString::MyString(const MyString& t)
{
	from_c_str(t.str);
}

MyString::~MyString()
{
	delete[] str;
}

MyString& MyString::operator= (const MyString& t)
{
	from_c_str(t.str);

	return *this;
}

MyString& MyString::operator= (const char* c)
{
	from_c_str(c);

	return *this;
}

MyString MyString::operator+ (const MyString& t) const
{
	return (MyString(str) += t.str);
}

bool operator== (const MyString& t, char* c)
{
	return (strcmp(t.str, c) == 0);
}

bool operator== (const MyString& t, const MyString& t1)
{
	return (strcmp(t.str, t1.str) == 0);
}

bool operator!= (const MyString& t, char* c)
{
	return !(operator== (t, c));
}

bool operator!= (const MyString& t, const MyString& t1)
{
	return !(operator== (t, t1.str));
}

MyString& MyString::operator+= (const MyString& t)
{
	length = strlen(str) + strlen(t.str) + 1;
	char* newStr = new char[length];
	strcpy(newStr, str);
	strcat(newStr, t.str);
	strcpy(str, newStr);
	str[length - 1] = '\0';
	delete[] newStr;

	return *this;
}

char& MyString::operator[] (size_t i)
{
	return str[i];
}

const char& MyString::operator[] (size_t i) const
{
	return str[i];
}

char& MyString::at(size_t i)
{
	if (str != NULL && i >= 0 && i < length)
	{
		return str[i];
	}
	else
	{
		throw exception("wrong index");
	}
}

const char& MyString::at(size_t i) const
{
	if (str != NULL && i >= 0 && i < length)
	{
		return str[i];
	}
	else
	{
		throw exception("wrong index");
	}
}

void MyString::get_input(istream& in)
{
	while (true)
	{
		char c = in.get();

		if (c == '\n')
		{
			break;
		}

		if (length == 0)
		{
			length = 2;
		}
		else
		{
			++length;
		}

		char* newStr = new char[length];
		if (str != NULL)
		{
			strcpy(newStr, str);
		}
		newStr[length - 2] = c;
		newStr[length - 1] = '\0';

		delete[] str;

		str = newStr;
	}
}

size_t MyString::get_length() const
{
	return (length - 1);
}

void MyString::from_c_str(const char* c)
{
	length = strlen(c) + 1;
	str = new char[length];
	strcpy(str, c);
}

ostream& operator<< (ostream& out, const MyString& t)
{
	out << t.str;
	return out;
}

istream& operator>> (istream& in, MyString& t)
{
	t.get_input(in);
	return in;
}