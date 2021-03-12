#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H

class MyString
{
private:
	char* str;
	int length;
public:
	MyString();
	MyString(const char* newString);
	MyString(MyString& ob);
	~MyString();
	int strLength(const char* str);
	int getLength();
	MyString& operator=(const MyString& ob);
	MyString& operator=(const char* str);
	const char* getValue();
	friend std::istream& operator>>(std::istream& in, MyString& ob);
	friend std::ostream& operator<< (std::ostream& out, const MyString& ob);
	void Add(char a);
	char& operator[](int i);
};

#endif
