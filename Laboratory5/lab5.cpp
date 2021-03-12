#include <iostream>

bool isSorted(int arr[], int N);
int checking(int(*arr)[3], int rows, int tables);
void printMas(int(*arr)[3], int rows, int tables);
int max(int* arr, int M);
int diagonales(int** arr, int N);
int enterN();

int main()
{
    setlocale(LC_ALL, "Russian");
    int mas[4][3] = { {1,2,3}, {4,5,6}, {7,7,6}, {1,2,1} };
    printMas(mas, 4, 3);
    int N = 0;
    std::cout << "Количество строк, элементы которых упорядочены по возрастанию элементов: " << checking(mas,4,3) << std::endl << std::endl;

    N = enterN();

    int **dynMas = new int*[N];
    for (int i = 0; i < N; i++)
    {
        dynMas[i] = new int[N];
    }
    for (int i = 0;i < N;i++)
    {
        for (int j = 0;j < N;j++)
        {
            dynMas[i][j] = rand() % 10;
            std::cout << dynMas[i][j] << " ";
            if (j == N - 1) std::cout << std::endl;
        }
    }
    std::cout << "Максимум среди сумм элементов диагоналей, параллельных побочной диагонали матрицы: " << diagonales(dynMas, N) << std::endl;

    return 0;
}

int enterN()
{
    int N = -1;
    while (N <= 0)
    {
        std::cout << "Введите размерность матрицы в динамической памяти: " << std::endl;
        std::cin >> N;
        if (N <= 0)
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неверный ввод." << std::endl;
        }
    }
    return N;

}


bool isSorted(int arr[], int N)
{
    for (int i = 1;i < N;i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}

int checking(int(*arr)[3], int rows, int tables)
{
    int counter = 0;
    for (int i = 0;i < rows;i++)
    {
        if (isSorted(arr[i], tables))
        {
            counter++;
        }
    }
    return counter;
}

void printMas(int(*arr)[3], int rows, int tables)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << arr[i][j] << " ";
            if (j == 2) std::cout << std::endl;
        }
    }
}

int max(int* arr, int M)
{
    int max = -2147483647;
    for (int i = 0;i < M;i++)
    {
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}

int diagonales(int** arr, int N)
{
    int M = 2 * (N - 1);
    int* mas = new int[M];
    for (int i = 0;i < M;i++)
    {
        mas[i] = 0;
    }

    int counter = 0;
    int a = 0, b = 0;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            for (int g = 0;g <= i;g++)
            {
                if (j + g == i)
                {
                    mas[counter] += arr[j][g];
                }
            }
        }
        counter++;
    }
    for (int i = N; i <= 2 * (N - 1); i++)
    {
        for (int j = N - 1; j >= 0; j--)
        {
            for (int g = N - 1;g >= 0;g--)
            {
                if (j + g == i)
                {
                    mas[counter] += arr[j][g];
                }
            }
        }
        counter++;
    }

    return max(mas, M);
}
