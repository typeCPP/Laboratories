#ifndef COURSEWORK_UNDIRECTEDGRAPH_HPP
#define COURSEWORK_UNDIRECTEDGRAPH_HPP

#include <vector>
#include "graph.hpp"
#include "exceptions.hpp"
#include "DoubleLinkedList.hpp"

template<class T>
class UndirectedGraph : public Graph<T>
{
public:
  UndirectedGraph() :
    head(nullptr), size(0)
  {}

  UndirectedGraph(const UndirectedGraph<T> &src) = delete;

  UndirectedGraph(UndirectedGraph<T> &&src) = delete;

  UndirectedGraph<T> operator=(const UndirectedGraph<T> &src) = delete;

  UndirectedGraph<T> operator=(UndirectedGraph<T> &&src) = delete;

  void addNode(T obj) override;

  void addWay(int numberOfNode1, int numberOfNode2) override;

  void deleteNode(T value) override;

  void deleteWay(int numberOfNode1, int numberOfNode2) override;

  void print() override;

  void DFS() override;

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

  Node *getNodeByIndex(int number);
};

template<class T>
void UndirectedGraph<T>::addNode(T obj)
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
void UndirectedGraph<T>::addWay(int numberOfNode1, int numberOfNode2)
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
    num2->connections.insertTail(num1->number);
    ways[numberOfNode1] = num1->connections;
    ways[numberOfNode2] = num2->connections;
  }
}

template<class T>
int UndirectedGraph<T>::searchNodeByValue(T value)
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
void UndirectedGraph<T>::deleteNode(T value)
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
void UndirectedGraph<T>::deleteWay(int numberOfNode1, int numberOfNode2)
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
    if (num1->connections.searchItem(numberOfNode2) && num2->connections.searchItem(numberOfNode1))
    {
      num1->connections.deleteItem(numberOfNode2);
      num2->connections.deleteItem(numberOfNode1);
      ways[num1->number] = num1->connections;
      ways[num2->number] = num2->connections;
    }
    else
    {
      return;
    }
  }
}

template<class T>
bool UndirectedGraph<T>::hasNode(T value)
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
bool UndirectedGraph<T>::hasWay(int numberOfNode1, int numberOfNode2)
{
  return ways[numberOfNode1].searchItem(numberOfNode2) || ways[numberOfNode2].searchItem(numberOfNode1);
}

template<class T>
bool UndirectedGraph<T>::isEmpty()
{
  return size == 0;
}

template<class T>
void UndirectedGraph<T>::print()
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
void UndirectedGraph<T>::DFS()
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
  doDFS(head, colors);
  for (int i = 0; i < size; i++)
  {
    if (colors[i] != 'd')
    {
      std::cout << "DFC error!\n";
      return;
    }
  }
  std::cout << "DFC successful!\n";
}

template<class T>
void UndirectedGraph<T>::doDFS(UndirectedGraph::Node *node, char *colors)
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
typename UndirectedGraph<T>::Node *UndirectedGraph<T>::getNodeByIndex(int number)
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

#endif
