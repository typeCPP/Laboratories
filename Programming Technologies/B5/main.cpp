#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include "shape.hpp"

void task1(std::istream &input, std::ostream &output);
void task2(std::istream &input, std::ostream &output);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  std::istringstream num(argv[1]);
  int taskNumber = 0;
  num >> taskNumber;
  if ((taskNumber > 2) || (taskNumber < 1) || (!num.eof()))
  {
    std::cerr << "Wrong task number\n";
    return 1;
  }
  if (taskNumber == 1)
  {
    try
    {
      task1(std::cin, std::cout);
    }
    catch (const std::runtime_error &error)
    {
      std::cerr << error.what();
      return 2;
    }
    catch (const std::exception &exception)
    {
      std::cerr << exception.what();
      return 3;
    }

  }
  else if (taskNumber == 2)
  {
    try
    {
      task2(std::cin, std::cout);
    }
    catch (const std::runtime_error &error)
    {
      std::cerr << error.what();
      return 2;
    }
    catch (const std::exception &exception)
    {
      std::cerr << exception.what();
      return 3;
    }

  }
  return 0;
}

void task1(std::istream &input, std::ostream &output)
{
  std::unordered_set<std::string> uniqueWords((std::istream_iterator<std::string>(input)),
      std::istream_iterator<std::string>());
  if (!input.eof())
  {
    throw std::runtime_error("An error occurred while reading words");
  }
  std::copy(uniqueWords.begin(), uniqueWords.end(), std::ostream_iterator<std::string>(output, "\n"));
}

void task2(std::istream &input, std::ostream &output)
{
  std::vector<Shape> shapes((std::istream_iterator<Shape>(input)), std::istream_iterator<Shape>());
  if (!input.eof())
  {
    throw std::runtime_error("An error occurred while reading shapes");
  }
  size_t numberOfVertexes = 0;

  std::for_each(shapes.begin(), shapes.end(),
      [&numberOfVertexes](const Shape &shape)
      {
        numberOfVertexes += shape.size();
      });

  const size_t numberOfTriangles = std::count_if(shapes.begin(), shapes.end(), &isTriangle);
  const size_t numberOfSquares = std::count_if(shapes.begin(), shapes.end(), &isSquare);
  const size_t numberOfRectangles = std::count_if(shapes.begin(), shapes.end(), &isRectangle);

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), &isPentagon), shapes.end());

  std::vector<Point> points;
  points.reserve(shapes.size());
  std::for_each(shapes.begin(), shapes.end(),
      [&points](const Shape& shape)
      {
        points.push_back(shape[0]);
      });

  std::sort(shapes.begin(), shapes.end(), ShapesComparator());

  output << "Vertices: " << numberOfVertexes << "\nTriangles: " << numberOfTriangles << "\nSquares: " << numberOfSquares
         << "\nRectangles: " << numberOfRectangles << "\nPoints: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(output, " "));
  output << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(output, "\n"));
}
