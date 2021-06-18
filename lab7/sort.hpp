#ifndef LAB7_SORT_HPP
#define LAB7_SORT_HPP

int findMaxNumInArray(int arr[], int size)
{
  int max = INT_MIN;
  for (int i = 0; i < size; i++)
  {
    if (arr[i] > max) max = arr[i];
  }
  return max;
}

void countingSort(int arr[], int n)
{
  int max = findMaxNumInArray(arr, n);
  int C[max + 1];
  for (int i = 0; i < max + 1; i++)
  {
    C[i] = 0;
  }
  for (int i = 0; i < n; i++)
  {
    C[arr[i]]++;
  }
  int j = 0;
  for (int i = 0; i < max + 1; i++)
  {
    for (int counter = 0; counter < C[i]; counter++)
    {
      arr[j] = i;
      j++;
    }
  }
}

void radixSort(int a[], int n)
{
  int i;
  int semiSorted[n];
  int significantDigit = 1;
  int largestNum = findMaxNumInArray(a, n);
  while (largestNum / significantDigit > 0)
  {
    int bucket[10] = {0};
    for (i = 0; i < n; i++)
      bucket[(a[i] / significantDigit) % 10]++;
    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];
    for (i = n - 1; i >= 0; i--)
      semiSorted[--bucket[(a[i] / significantDigit) % 10]] = a[i];
    for (i = 0; i < n; i++)
      a[i] = semiSorted[i];
    significantDigit *= 10;
  }
}

void bucketSort(int array[], int array_size)
{
  const int max = array_size;
  int bucket[10][max + 1];
  for (int x = 0; x < 10; x++)
    bucket[x][max] = 0;
  // main loop for each digit position
  for (int digit = 1; digit <= 1000000000; digit *= 10)
  {
    for (int i = 0; i < max; i++)
    {
      int dig = (array[i] / digit) % 10;
      bucket[dig][bucket[dig][max]++] = array[i];
    }
    int idx = 0;
    for (int x = 0; x < 10; x++)
    {
      for (int y = 0; y < bucket[x][max]; y++)
      {
        array[idx++] = bucket[x][y];
      }
      bucket[x][max] = 0;
    }
  }
}

void display(int arr[], int n)
{
  std::cout << "\n";
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << " ";
}

#endif
