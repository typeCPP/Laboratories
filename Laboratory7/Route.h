#pragma once
#ifndef ROUTE_H
#define ROUTE_H
#include <iostream>
#include "MyString.h"

class Route
{
private:
	MyString routeStart;
	MyString routeEnd;
	int routeNumber;
public:
	void setRouteStart(const char* str);
	void setRouteEnd(const char* str);
	void setRouteNumber(int num);
	MyString& getRouteEnd();
	MyString& getRouteStart();
	int getRouteNumber();
	Route();
	Route(const char* start, const char* end, int num);
	Route(const MyString start, const MyString end, int num);
	Route(const Route& ob);
	~Route();
	
	Route& operator=(const Route& ob);
	Route operator+(Route& ob);
	friend Route operator-(Route& ob, Route& ob2);
	bool operator>(Route& ob);
	friend bool operator<(Route& ob, Route& ob2);
	Route& operator++();
	friend Route operator++(Route& ob, int unused);
	friend std::ostream& operator<< (std::ostream& out, const Route& ob);
	friend std::istream& operator>> (std::istream& in, Route& ob);
};

#endif

