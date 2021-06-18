#ifndef B4_DATA_STRUCT_HPP
#define B4_DATA_STRUCT_HPP

#include <iostream>
#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

struct ComparingDataStructs
{
  bool operator()(const DataStruct &first, const DataStruct &second) const;
};

std::istream &operator>>(std::istream &input, DataStruct &dataStruct);
std::ostream &operator<<(std::ostream &output, const DataStruct &dataStruct);

#endif
