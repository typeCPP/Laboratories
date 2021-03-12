#include "Route.h"
#include <iostream>
#include "MyString.h"

void Route::setRouteStart(const char* str)
{
	MyString temp(str);
	if ((int)(str[0]) >= 97 && (int)(str[0]) <= 122 || (int)(str[0]) >= -32 && (int)(str[0]) <= -1)
	{
		temp[0] = (int)(str[0]) - 32;
	}
	routeStart = temp;
}

 MyString& Route::getRouteStart()
{
	return this->routeStart;
}

int Route::getRouteNumber()
{
	return this->routeNumber;
}

Route::Route()
{
	this->setRouteStart("");
	this->setRouteEnd("");
	this->setRouteNumber(0);
	
}

Route::Route(const char* start, const char* end, int num)
{
	this->setRouteStart(start);
	this->setRouteEnd(end);
	this->setRouteNumber(num);
}

Route::Route(const MyString start, const MyString end, int num)
{
	this->routeStart = start;
	this->routeEnd = end;
	this->setRouteNumber(num);
}

Route::Route(const Route& ob)
{
	MyString temp;
	temp = ob.routeStart;
	this->setRouteStart(temp.getValue());
	MyString temp2;
	temp2 = ob.routeEnd;
	this->setRouteEnd(temp2.getValue());
	this->setRouteNumber(ob.routeNumber);
}

Route::~Route()
{
	routeEnd.~MyString();
	routeStart.~MyString();
}

Route& Route::operator=(const Route& ob)
{
	routeStart = ob.routeStart;
	routeEnd = ob.routeEnd;
	routeNumber = ob.routeNumber;
	return *this;
}

Route Route::operator+(Route& ob)
{
	int num = ob.getRouteNumber() + this->getRouteNumber();
	MyString start;
	MyString end;
	start = this->getRouteStart();
	end = ob.getRouteEnd();
	Route temp;
	temp.setRouteStart(start.getValue());
	temp.setRouteEnd(end.getValue());
	temp.setRouteNumber(num);
	return temp;
}

bool Route::operator>(Route& ob)
{
	if (this->getRouteNumber() > ob.getRouteNumber())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Route& Route::operator++()
{
	this->routeNumber++;
	return *this;
}

void Route::setRouteEnd(const char* str)
{
	MyString temp(str);
	if ((int)(str[0]) >= 97 && (int)(str[0]) <= 122 || (int)(str[0]) >= -32 && (int)(str[0]) <= -1)
	{
		temp[0] = (int)(str[0]) - 32;
	}
	routeEnd = temp;
}

void Route::setRouteNumber(int num)
{
	if (num < 0) num = 0;
	this->routeNumber = num;
}

 MyString& Route::getRouteEnd()
{
	return this->routeEnd;
}