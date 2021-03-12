#include <iostream>
#include <string>
#include <fstream>
#pragma warning(disable : 4996) //выключаю предупреждение

std::string mergeStrings(const std::string *str1, const std::string* str2);
char* mergeChars(char* dest, const char* str1, const char* str2, int length1, int length2);

int main()
{
    setlocale(LC_ALL, "Russian");
	std::ifstream file;
	std::string firstString;
	std::string secondString;
	char firstChar[255];//ограничиваю длину строки введенной чтобы можно было вообще создать массив.
	char secondChar[255];
	char charRes[510]; //255+255 = 510
	std::string stringRes = "";


	file.open("strings.txt"); 
	file >> firstString;
	file >> secondString;
	file.close();
	file.open("strings.txt");//дважды открываю файл чтобы он правильно читался, без проблем
	file.getline(firstChar, 255);
	file.getline(secondChar, 255);
	file.close();//сразу же закрываю его

	int length1, length2;
	length1 = firstString.length();
	length2 = secondString.length();
	stringRes = mergeStrings(&firstString, &secondString);
	mergeChars(charRes, firstChar, secondChar, length1, length2);//здесь вызываю методы
	std::cout << charRes << std::endl;

}

std::string mergeStrings(const std::string* str1, const std::string* str2)
{
	int max = -1;
	std::string result = "";
	if (str1->length() >= str2->length()) max = str1->length();
	if (str1->length() <= str2->length()) max = str2->length();//выясняем какая из строчек длиннее, чтобы цикл до нее запустить

	for (int i = 0;i < max;i++)
	{
		if (i < str1->length())
		{
			result += str1->substr(i,1);
		}
		if (i < str2->length())
		{
			result += str2->substr(i, 1);
		}
	}
	return result;
}

char* mergeChars(char* dest, const char* str1, const char* str2, int length1, int length2)
{
	int max = -1;
	std::string res = "";
	if (length1 >= length2) max = length1;
	if (length1 <= length2) max = length2;//здесь логика та же что и в методе выше.
	for (int i = 0;i < max;i++)
	{
		if (i < length1)
		{
			res += str1[i];
		}
		if (i < length2)
		{
			res += str2[i];
		}
	}
	std::strcpy(dest, res.c_str());
	return dest;
}