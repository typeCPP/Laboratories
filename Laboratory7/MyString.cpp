#include <iostream>
#include "MyString.h"
#include <cmath>

int MyString::strLength(const char* str)
{
	int i = 0;
	while (str[i] != '\0') i++;
	return i;
}

int MyString::getLength()
{
	return length;
}

MyString& MyString::operator=(const MyString& ob)
{
	this->length = ob.length;
	this->str = new char[this->length];
	for (int i = 0; i < this->length; i++)
	{
		this->str[i] = ob.str[i];
	}
	this->str[length] = '\0';
	return *this;
}

MyString& MyString::operator=(const char* str)
{
	this->length = strLength(str);
	this->str = new char[this->length];
	for (int i = 0; i < this->length; i++)
	{
		this->str[i] = str[i];
	}
	this->str[length] = '\0';
	return *this;
}

const char* MyString::getValue()
{
	return str;
}

void MyString::Add(char a)
{
	char* newStr = new char[this->length+2];
	for (int i = 0; i < this->length; i++)
	{
		newStr[i] = this->str[i];
	}
	newStr[length] = a;
	newStr[length+1] = '\0';
	*this = newStr;
	delete[] newStr;
	return;
}

char& MyString::operator[](int i)
{
	if (i < 0)
	{
		i = 0;
	}
	if (i >= length)
	{
		i = length - 1;
	}
	return str[i];
}

MyString::MyString()
{
	length = 0;
	str = new char[1];
	str[0] = '\0';
}

MyString::MyString(const char* newString)
{
	this->length = strLength(newString);
	int temp = this->length;
	if (newString[length-1] != '\0')
	{
		temp += 1;
	}
	this->str = new char[temp];
	for (int i = 0; i < this->length; i++)
	{
		this->str[i] = newString[i];
	}
	if (newString[length-1] != '\0')
	{
		this->str[this->length + 1] = '\0';
	}
}

MyString::MyString(MyString& ob)
{
	this->length = ob.length;
	this->str = new char[this->length+1];
	for (int i = 0; i < this->length; i++)
	{
		this->str[i] = ob.str[i];
	}
	this->str[this->length + 1] = '\0';
	this->length = ob.length;
}

MyString::~MyString()
{
	this->str = nullptr;
	delete[] this->str;
}