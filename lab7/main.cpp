#include <iostream>
#include "sort.hpp"

bool arrayIsOrdered(int array[], int size);

int main()
{
  const int SIZE = 6;
  std::cout << "The worst case of counting sort is a big range of numbers: ";
  int arrayForWorstCountingSort[SIZE] = {1000, 65, 1, 2, 5, 3};
  display(arrayForWorstCountingSort, SIZE);
  countingSort(arrayForWorstCountingSort, SIZE);
  display(arrayForWorstCountingSort, SIZE);
  std::cout << "\nIs array ordered? ";
  arrayIsOrdered(arrayForWorstCountingSort, SIZE)? std::cout << "Yes.\n" : std::cout << "No.\n";

  std::cout << "\nThe best case of counting sort is a small range of numbers: ";
  int arrayForBestCountingSort[SIZE] = {1, 6, 3, 2, 5, 4};
  display(arrayForBestCountingSort, SIZE);
  countingSort(arrayForBestCountingSort, SIZE);
  display(arrayForBestCountingSort, SIZE);
  std::cout << "\nIs array ordered? ";
  arrayIsOrdered(arrayForBestCountingSort, SIZE)? std::cout << "Yes.\n" : std::cout << "No.\n";

  std::cout << "\nThe worst case of radix sort is a numbers with a big number of digits: ";
  int arrayForWorstRadixSort[SIZE] = {1000000, 6500, 100000, 223255, 5244, 10021321};
  display(arrayForWorstRadixSort, SIZE);
  radixSort(arrayForWorstRadixSort, SIZE);
  display(arrayForWorstRadixSort, SIZE);
  std::cout << "\nIs array ordered? ";
  arrayIsOrdered(arrayForWorstRadixSort, SIZE)? std::cout << "Yes.\n" : std::cout << "No.\n";

  std::cout << "\nThe best case of radix sort is a numbers with a small number of digits: ";
  int arrayForBestRadixSort[SIZE] = {1, 5, 4, 2, 5, 3};
  display(arrayForBestRadixSort, SIZE);
  radixSort(arrayForBestRadixSort, SIZE);
  display(arrayForBestRadixSort, SIZE);
  std::cout << "\nIs array ordered? ";
  arrayIsOrdered(arrayForBestRadixSort, SIZE)? std::cout << "Yes.\n" : std::cout << "No.\n";

  std::cout << "\nThe worst case of bucket sort is a numbers with a small difference between them: ";
  int arrayForWorstBucketSort[SIZE] = {1, 2, 1, 2, 1, 1};
  display(arrayForWorstBucketSort, SIZE);
  bucketSort(arrayForWorstBucketSort, SIZE);
  display(arrayForWorstBucketSort, SIZE);
  std::cout << "\nIs array ordered? ";
  arrayIsOrdered(arrayForWorstBucketSort, SIZE)? std::cout << "Yes.\n" : std::cout << "No.\n";

  std::cout << "\nThe worst case of bucket sort is a numbers with a big difference between them: ";
  int arrayForBestBucketSort[SIZE] = {10, 500, 400, 20, 9000, 8000};
  display(arrayForBestBucketSort, SIZE);
  bucketSort(arrayForBestBucketSort, SIZE);
  display(arrayForBestBucketSort, SIZE);
  std::cout << "\nIs array ordered? ";
  arrayIsOrdered(arrayForBestBucketSort, SIZE)? std::cout << "Yes.\n" : std::cout << "No.\n";

  return 0;
}

bool arrayIsOrdered(int array[], int size)
{
  for (int i = 1; i < size; i++)
  {
    if (array[i] < array[i - 1]) return false;
  }
  return true;
}
