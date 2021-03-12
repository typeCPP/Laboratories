#include <iostream>

bool sign(char sym);
bool isNumber(char num);
bool noSign(std::string number);
bool mantissa(std::string mant);
bool isOrder(std::string ord);

int main()
{
    setlocale(LC_ALL, "Russian");
    
    std::cout << "Введите строку: " << std::endl;
    std::string str;
    std::string mant = "";
    std::string ord = "";
    std::cin >> str;
    bool beforeOrd = true;
    for (int i = 1;i < str.length();i++)
    {
        if (str[i] == 'E' || str[i] == 'Е')
        {
            beforeOrd = false;
        }

        if (beforeOrd)
        {
            mant += str[i];
        }
        else
        {
            ord += str[i];
        }
    }
    
    if (sign(str[0]) && mantissa(mant) && isOrder(ord))
    {
        std::cout << "ДА" << std::endl;
    }
    else
    {
        std::cout << "НЕТ" << std::endl;
    }
    return 0;
}

bool sign(char sym)
{
    if (sym == '+' || sym == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isNumber(char num)
{
    if (num == '0' || num == '1' || num == '2' || num == '3' || num == '4' || num == '5' || num == '6' || num == '7' || num == '8' || num == '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool noSign(std::string number)
{
    if (isNumber(number[0]))
    {
        if (number.length() != 1)
        {
            if (!noSign(number.erase(0, 1)))
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool mantissa(std::string mant)
{
    std::string beforePoint = "";
    std::string afterPoint = "";
    bool bP = true;
    for (int i = 0;i < mant.length();i++)
    {
        if (mant[i] == '.')
        {
            bP = false;
        }

        if (bP)
        {
            beforePoint += mant[i];
        }
        else
        {
            if (mant[i] != '.')
            {
                afterPoint += mant[i];
            }
        }
    }
    if (noSign(beforePoint) && noSign(afterPoint))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isOrder(std::string ord)
{
    if (sign(ord[1]) && noSign(ord.erase(0, 2)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

