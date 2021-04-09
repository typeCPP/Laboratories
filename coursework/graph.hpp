#ifndef COURSEWORK_GRAPH_HPP
#define COURSEWORK_GRAPH_HPP

template<class T>
class Graph
{
public:
  virtual ~Graph() = default;

  virtual void addNode(T obj) = 0;

  virtual void addWay(int numberOfNode1, int numberOfNode2) = 0;

  virtual void deleteNode(T value) = 0;

  virtual void deleteWay(int numberOfNode1, int numberOfNode2) = 0;

  virtual void print() = 0;

  virtual void DFS() = 0;

  virtual int searchNodeByValue(T value) = 0;

  virtual bool hasNode(T value) = 0;

  virtual bool hasWay(int numberOfNode1, int numberOfNode2) = 0;

  virtual bool isEmpty() = 0;
};

#endif
