#include <iostream>

int main()
{
    int enteredNumber = -1;
    int countAfter = 0;
    int numCount = 0;
    int max = -2147483648;
    while (enteredNumber != 0)
    {
        std::cout << "Введите число:" << std::endl;
        std::cin >> enteredNumber;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неверный ввод!" << std::endl;
            continue;
        }

        if (enteredNumber == 0) break;

        numCount++;

        if (enteredNumber > max)
        {
            max = enteredNumber;
            countAfter = 0;
        }
        else
        {
            countAfter++;
        }

    }
    if (numCount == 0)
    {
        std::cout << "Последовательность чисел пуста." << std::endl;
        return 0;
    }
    std::cout << "Количество элементов, расположенных после максимального элемента: " << countAfter << std::endl;
    return 0;
}

