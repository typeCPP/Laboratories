#include <iostream>
#include <iomanip>


double function(double x, double absError, int N);


int main()
{
    setlocale(LC_ALL, "Russian");
    double e = 0.0;
    double start, end;
    double absError;
    int maxN;
    std::cout << "Введите начальное значение и конечное: " << std::endl;
    std::cin >> start >> end;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Неверный ввод!" << std::endl;
        main();
        return 0;
    }
    if (start > end)
    {
        std::cout << "Вы ввели начало числового промежутка большее, чем конечное. Ошибка." << std::endl;
        main();
        return 0;
    }
    if (start < -1 || end > 1)
    {
        std::cout << "Границы промежутка не принадлежат интервалу [-1;1]. Ошибка." << std::endl;
        main();
        return 0;
    }
    std::cout << "Введите абсолютную погрешность функции и максимальное число элементов: " << std::endl;
    std::cin >> absError >> maxN;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Неверный ввод!" << std::endl;
        main();
        return 0;
    }

    double fResult = 0.0;
    std::cout << "\tx\t" << "  y(x)\t"<< std::setw(15) << "exp(x)" << std::endl;
    for (double i = start; i <= end; i += 0.001)
    {
        e = exp(i);
        fResult = function(i, absError, maxN);
        if (fResult != -1)
        {
            std::cout << std::setw(10) << i << std::setw(15) << fResult << std::setw(15) << e << std::endl;
        }
    }
    return 0;
}

double function(double x, double absError, int N)
{
    if (x < -1 || x>1)
    {
        return -1;
    }
    double y = 1.0 + x;
    double argument = 1.0;
    int splitter = 2;
    int s = 2;
    double x2 = x * x;
    for (int i = 0; i <= N; i++)
    {
        argument = argument * x2 / static_cast<double>(splitter);
        x2 *= x;
        if (argument >= absError)
        {
            return -1;
        }
        s++;
        splitter *= s;
        y += argument;
    }

    return y;
}
