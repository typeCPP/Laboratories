#pragma once
#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
class Array
{
private:
	T* data;
	int size;
public:
	Array(int n);
	~Array();
	int getSize();
	T& operator[](int i);
};

#endif

template<typename T>
Array<T>::Array(int n)
{
	data = new T[n];
	size = n;
}

template<typename T>
Array<T>::~Array()
{
	delete[] data;
}

template<typename T>
inline int Array<T>::getSize()
{
	return size;
}

template<typename T>
T& Array<T>::operator[](int i)
{
	if (i < 0)
	{
		i = 0;
	}
	if (i >= size)
	{
		i = size - 1;
	}
	return data[i];
}