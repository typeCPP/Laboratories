#include <iostream>
#include <fstream>

void sort(int* mas, int length); // объявляем наши функции
void arrayOut(int* mas, int length);
int enterSize();

int main()
{
	setlocale(LC_ALL, "Russian");
	const int SIZE = 10;
	int N = 0;
	int firstArray[SIZE] = { 4,5,-7,57,68,-23,5,7,-81,57 }; //простой статический массив

	N = enterSize();
	
	int* dynArray = new int[N];
	for (int i = 0; i < N; i++)
	{
		dynArray[i] = -16000 + rand() % 32000; // заполнение динамического массива рандомными числами от -16000 до 32000
	}
	std::cout << std::endl;
	std::cout << "Стандартный массив в неотсортированном виде: " << std::endl;
	arrayOut(firstArray,SIZE);
	std::cout << std::endl;
	std::cout << "Массив в динамической памяти в неотсортированном виде: " << std::endl;
	arrayOut(dynArray, N);

	int s = 0;
	int len = 0;
	int counter = 0;
	std::ifstream file;
	file.open("array.txt"); // работаем с файлом
	file >> s;
	len = s;
	int* fileArray = new int[s];

	for (file >> s; !file.eof(); file >> s)
	{
		fileArray[counter] = static_cast<int>(s);
		counter++;
	}

	std::cout << std::endl;
	std::cout << "Массив из файла в неотсортированном виде: " << std::endl;
	arrayOut(fileArray, len);

	sort(firstArray, SIZE);
	std::cout << std::endl;
	std::cout << "Стандартный массив в отсортированном виде: " << std::endl;
	arrayOut(firstArray, SIZE);

	sort(dynArray, N);
	std::cout << std::endl;
	std::cout << "Динамический массив в отсортированном виде: " << std::endl;
	arrayOut(dynArray, N);

	sort(fileArray, len);
	std::cout << std::endl;
	std::cout << "Массив из файла в отсортированном виде: " << std::endl;
	arrayOut(fileArray, len);

	//подчищаем за собой мусор
	file.close();
	delete[] dynArray;
	delete[] fileArray;

	return 0;
}

int enterSize()
{
	int N = -1;
	while (N <= 0)
	{
		std::cout << "Введите размер массива в динамической памяти: ";
		std::cin >> N;
		if (N <= 0)
		{
			std::cout << "Неверный ввод." << std::endl;
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
	}
	return N;
}

void sort(int* mas, int length) //собсна сортировка массива
{
	int temp = 0;
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if ((mas[i] > mas[j]) && (mas[i] > 0) && (mas[j] > 0))
			{
				temp = mas[i];
				mas[i] = mas[j];
				mas[j] = temp;
			}
		}
	}
	return; 
}

void arrayOut(int* mas, int length)//вывод массива
{
	for (int i = 0; i < length; i++)
	{
		std::cout << "Элемент массива = " << mas[i] << std::endl;
	}
	return;
}