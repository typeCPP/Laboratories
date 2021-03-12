#include <iostream>
#include <fstream>
#include <iomanip>
#include "MyString.h"
#include "Route.h"
#include "Array.h"

int countStrings(std::ifstream file);
int findMax(Array<Route>& arr);

template <typename T>
void sort(Array<Route>& arr, T unsued);

template <typename T>
void routesInFile(const char* fileName, Array<T>& arr);

void listOfPoints(Array<Route>& routes, Array<MyString>& start, Array<MyString>& end);
void listInFile(const char* fileName, Array<MyString>& start, Array<MyString>& end);

int main()
{
	setlocale(LC_ALL, "Russian");
	MyString fileName;
	std::cout << "Введите название файла: ";
	std::cin >> fileName;
	std::ifstream file;
	file.open(fileName.getValue(), std::ifstream::in);
	if (!file.is_open())
	{
		while (!file.is_open())
		{
			std::cout << "Файл не был открыт. Введите корректное название.\n";
			std::cin.clear();
			std::cin.ignore(32625, '\n');
			std::cin >> fileName;
			file.open(fileName.getValue(), std::ifstream::in);
		}
	}
	std::cout << "Файл успешно открыт." << std::endl;
	int counter = 0;
	Route temp;
	while (!file.eof())
	{
		file >> temp;
		counter++;
	}
	Array<Route> routes(counter);
	Array<MyString> starts(counter);
	Array<MyString> ends(counter);
	file.close();
	file.open(fileName.getValue(), std::ifstream::in);
	for (int i = 0; i < counter; i++)
	{
		file >> routes[i];
	}
	file.close();

	std::cout << "Наибольший номер маршрута: " << findMax(routes) << std::endl;
	sort(routes, 0);
	routesInFile("output.txt", routes);
	listOfPoints(routes, starts, ends);
	listInFile("output.txt", starts, ends);
    return 0;
}

void listInFile(const char* fileName, Array<MyString>& start, Array<MyString>& end)
{

	std::ofstream file(fileName, std::ofstream::app);
	file << "\n\n\n";
	file << "---------------------------------\n";
	file << "|" << std::setw(15) << "Отправление" << "|" << std::setw(15) << "Назначение" << "|\n";
	file << "---------------------------------\n";
	for (int i = 0; i < start.getSize(); i++)
	{
		file << "|" <<std::setw(15) << start[i] << "|" <<std::setw(15) << end[i] << "|\n";
	}
	file << "---------------------------------\n";
	file.close();
}

void listOfPoints(Array<Route>& routes, Array<MyString>& start, Array<MyString>& end)
{
	for (int i = 0; i < routes.getSize(); i++)
	{
		start[i] = routes[i].getRouteStart();
		end[i] = routes[i].getRouteEnd();
	}
}

template <typename T>
void routesInFile(const char* fileName, Array<T>& arr)
{
	std::ofstream file(fileName, std::ofstream::out);
	file << "-------------------------------------------------\n";
	file << "|" << std::setw(15) << "Отправление" << "|" << std::setw(15) << "Назначение" << "|" << std::setw(15) << "Номер маршрута" << "|\n";
	file << "-------------------------------------------------\n";
	for (int i = 0; i < arr.getSize(); i++)
	{
		file << arr[i] << std::endl;
	}
	file << "-------------------------------------------------\n";
	file.close();
}

template <typename T>
void sort(Array<Route>& arr, T unsued)
{
	int min;
	Route temp;
	for (int i = 0;i < arr.getSize() - 1;i++)
	{
		min = i;
		for (int j = i + 1;j < arr.getSize();j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

int findMax(Array<Route>& arr)
{
	Route max;
	for (int i = 0; i < arr.getSize(); i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max.getRouteNumber();
}

int countStrings(std::ifstream file)
{
	int counter = 0;
	Route temp;
	while (!file.eof())
	{
		file >> temp;
		counter++;
	}
	return counter;
}

Route operator-(Route& ob, Route& ob2)
{
	int num = ob.getRouteNumber() - ob2.getRouteNumber();
	MyString start;
	MyString end;
	start = ob.getRouteStart();
	end = ob2.getRouteEnd();
	Route temp;
	temp.setRouteStart(start.getValue());
	temp.setRouteEnd(end.getValue());
	temp.setRouteNumber(num);
	return temp;
}

bool operator<(Route& ob, Route& ob2)
{
	if (ob.getRouteNumber() < ob2.getRouteNumber())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Route operator++(Route& ob, int unused)
{
	Route temp(ob.getRouteStart(), ob.getRouteEnd(), ob.getRouteNumber());
	temp.routeNumber++;
	ob = temp;
	return temp;
}

std::ostream& operator<<(std::ostream& out, const Route& ob)
{
	Route temp(ob);
	out << "|"<< std::setw(15) << temp.getRouteStart() << "|" << std::setw(15) << temp.getRouteEnd() << "|" << std::setw(15) << temp.getRouteNumber() << "|";
	return(out);
}

std::ostream& operator<<(std::ostream& out, const MyString& ob)
{
	out << ob.str;
	return out;
}

std::istream& operator>>(std::istream& in, Route& ob)
{
	MyString start, end;
	int num;
	in >> start >> end >> num;
	ob.setRouteStart(start.getValue());
	ob.setRouteEnd(end.getValue());
	ob.setRouteNumber(num);
	return in;
}
std::istream& operator>>(std::istream& in, MyString& ob)
{
	setlocale(LC_ALL, "RUS");
	char BUFF[2048];

	in >> BUFF;
	ob = BUFF;

	return in;
}