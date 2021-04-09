#ifndef COURSEWORK_DIRECTEDGRAPH_HPP
#define COURSEWORK_DIRECTEDGRAPH_HPP

#include <vector>
#include "graph.hpp"
#include "exceptions.hpp"
#include "DoubleLinkedList.hpp"
#include "stacklist.hpp"

template<class T>
class DirectedGraph : public Graph<T>
{
public:

  DirectedGraph() :
    head(nullptr), size(0)
  {}

  void addNode(T obj) override;

  void addWay(int numberOfNode1, int numberOfNode2) override;

  void deleteNode(T value) override;

  void deleteWay(int numberOfNode1, int numberOfNode2) override;

  void print() override;

  void DFS() override;

  void transpose();

  void SCC();

  int searchNodeByValue(T value) override;

  bool hasNode(T value) override;

  bool hasWay(int numberOfNode1, int numberOfNode2) override;

  bool isEmpty() override;

private:

  struct Node
  {
    T value;
    Node *next;
    int number;
    DoubleLinkedList<int> connections;

    Node() :
      next(nullptr), number(0)
    {}

    Node(T value_, Node *next_, int number_) :
      value(value_), next(next_), number(number_)
    {}
  };

  Node *head;
  size_t size;
  std::vector<DoubleLinkedList<int>> ways;

  void doDFS(Node *node, char *colors);

  void fillOrder(Node *node, char *colors, StackList<int> &stack);

  Node *getNodeByIndex(int number);
};

template<class T>
void DirectedGraph<T>::addNode(T obj)
{
  if (size == 0)
  {
    head = new Node(obj, nullptr, size);
    ways.push_back(head->connections);
  }
  else
  {
    Node *current = head;
    Node *temp = new Node(obj, nullptr, size);
    while (current->next != nullptr)
    {
      if (current->value == obj)
      {
        throw std::invalid_argument("Current number already exists in the graph");
      }
      current = current->next;
    }
    current->next = temp;
    ways.push_back(current->connections);
  }
  size++;
}

template<class T>
void DirectedGraph<T>::addWay(int numberOfNode1, int numberOfNode2)
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  if (numberOfNode1 == numberOfNode2)
  {
    throw std::logic_error("Attempt to connect point to itself");
  }
  Node *temp = head;
  Node *num1 = nullptr;
  Node *num2 = nullptr;
  while (temp != nullptr)
  {
    if (temp->number == numberOfNode1)
    {
      num1 = temp;
    }
    if (temp->number == numberOfNode2)
    {
      num2 = temp;
    }
    temp = temp->next;
  }
  if (num1 == nullptr || num2 == nullptr)
  {
    return;
  }
  else
  {
    num1->connections.insertTail(num2->number);
    ways[numberOfNode1] = num1->connections;
  }
}

template<class T>
void DirectedGraph<T>::deleteNode(T value)
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  Node *current = head;
  Node *prev = current;
  while (current != nullptr)
  {
    if (current->value == value)
    {
      break;
    }
    prev = current;
    current = current->next;
  }
  if (current == nullptr)
  {
    return;
  }
  else
  {
    prev->next = current->next;
    ways.erase(ways.begin() + current->number);
    Node *counterForLoop = head;
    while (counterForLoop != nullptr)
    {
      if (counterForLoop->connections.searchItem(current->number))
      {
        counterForLoop->connections.deleteItem(current->number);
      }
      if (counterForLoop->number > current->number)
      {
        counterForLoop->number--;
      }
      ways[counterForLoop->number] = counterForLoop->connections;
      counterForLoop = counterForLoop->next;
    }
    size--;
    delete current;
  }
}

template<class T>
void DirectedGraph<T>::deleteWay(int numberOfNode1, int numberOfNode2)
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  if (numberOfNode1 == numberOfNode2)
  {
    throw std::logic_error("Attempt to delete connection between same point");
  }
  Node *temp = head;
  Node *num1 = nullptr;
  Node *num2 = nullptr;
  while (temp != nullptr)
  {
    if (temp->number == numberOfNode1)
    {
      num1 = temp;
    }
    if (temp->number == numberOfNode2)
    {
      num2 = temp;
    }
    temp = temp->next;
  }
  if (num1 == nullptr || num2 == nullptr)
  {
    return;
  }
  else
  {
    if (num1->connections.searchItem(numberOfNode2))
    {
      num1->connections.deleteItem(numberOfNode2);
      ways[num1->number] = num1->connections;
    }
    else
    {
      return;
    }
  }
}

template<class T>
void DirectedGraph<T>::print()
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  std::cout << "All nodes, starting from index 0: ";
  Node *current = head;
  while (current != nullptr)
  {
    std::cout << current->value << " ";
    current = current->next;
  }
  std::cout << "\n";
  std::cout << "All ways between nodes:";
  for (int i = 0; i < ways.size(); i++)
  {
    if (!ways[i].isEmpty())
    {
      std::cout << "\nNode with index " << i << " connected with nodes: ";
      ways[i].print();
    }
    else
    {
      std::cout << "\nNode with index " << i << " connected with no nodes.";
    }
  }
  std::cout << "\n";
}

template<class T>
int DirectedGraph<T>::searchNodeByValue(T value)
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  Node *temp = head;
  while (temp->next != nullptr || temp->value != value)
  {
    temp = temp->next;
  }
  if (temp->value == value)
  {
    return temp->number;
  }
  else
  {
    return 0;
  }
}

template<class T>
bool DirectedGraph<T>::hasNode(T value)
{
  Node *current = head;
  while (current->next != nullptr)
  {
    if (current->value == value)
    {
      return true;
    }
  }
  return false;
}

template<class T>
bool DirectedGraph<T>::hasWay(int numberOfNode1, int numberOfNode2)
{
  return ways[numberOfNode1].searchItem(numberOfNode2);
}

template<class T>
bool DirectedGraph<T>::isEmpty()
{
  return size == 0;
}

template<class T>
void DirectedGraph<T>::doDFS(DirectedGraph::Node *node, char *colors)
{
  Node *current = node;
  if (colors[current->number] == 'u')
  {
    std::cout << current->value << " ";
  }
  colors[current->number] = 'w';
  DoubleLinkedList<int> nodeWays(current->connections);
  for (int i = 0; i < size; i++)
  {
    if (nodeWays.searchItem(i))
    {
      if (colors[i] == 'w')
      {
        continue;
      }
      else
      {
        doDFS(getNodeByIndex(i), colors);
      }
    }
  }
  colors[current->number] = 'd';
}

template<class T>
void DirectedGraph<T>::DFS()
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  char *colors = new char[size + 1];
  for (int i = 0; i < size; i++)
  {
    colors[i] = 'u';
  }
  colors[size] = '\0';

  for (Node *current = head; current != nullptr; current = current->next)
  {
    if (colors[current->number] == 'u')
    {
      doDFS(current, colors);
    }
  }
  for (int i = 0; i < size; i++)
  {
    if (colors[i] != 'd')
    {
      std::cout << "DFS error!\n";
      return;
    }
  }
  std::cout << "DFS successful!\n";
}

template<class T>
typename DirectedGraph<T>::Node *DirectedGraph<T>::getNodeByIndex(int number)
{
  Node *current = head;
  while (current != nullptr)
  {
    if (current->number == number)
    {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

template<class T>
void DirectedGraph<T>::transpose()
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  std::vector<DoubleLinkedList<int>> usedNodes;
  Node *current = head;
  for (int i = 0; i < size; i++)
  {
    DoubleLinkedList<int> temp;
    usedNodes.push_back(temp);
  }
  while (current != nullptr)
  {
    DoubleLinkedList<int> temp;
    for (int i = 0; i < size; i++)
    {
      if (current->connections.searchItem(i) && !usedNodes[i].searchItem(current->number))
      {
        deleteWay(current->number, i);
        addWay(i, current->number);
        temp.insertTail(i);
        usedNodes[current->number] = temp;
      }
    }
    current = current->next;
  }
}

template<class T>
void DirectedGraph<T>::SCC()
{
  if (size == 0)
  {
    throw GraphEmpty();
  }
  StackList<int> stack;
  char *colors = new char[size + 1];
  for (int i = 0; i < size; i++)
  {
    colors[i] = 'u';
  }
  colors[size] = '\0';
  for (Node *i = head; i != nullptr; i = i->next)
  {
    if (colors[i->number] != 'd')
      fillOrder(i, colors, stack);
  }
  transpose();
  for (int i = 0; i < size; i++)
  {
    colors[i] = 'u';
  }
  colors[size] = '\0';

  while (!stack.isEmpty())
  {
    int v = stack.getTop();
    stack.pop();

    if (colors[v] != 'd')
    {
      doDFS(getNodeByIndex(v), colors);
      std::cout << "\n";
    }
  }
  transpose();
}

template<class T>
void DirectedGraph<T>::fillOrder(DirectedGraph::Node *node, char *colors, StackList<int> &stack)
{
  Node *current = node;
  colors[current->number] = 'w';

  DoubleLinkedList<int> nodeWays(current->connections);
  for (int i = 0; i < size; i++)
  {
    if (nodeWays.searchItem(i))
    {
      if (colors[i] == 'w')
      {
        continue;
      }
      else
      {
        fillOrder(getNodeByIndex(i), colors, stack);
      }
    }
  }
  colors[current->number] = 'd';
  stack.push(current->number);
}

#endif
