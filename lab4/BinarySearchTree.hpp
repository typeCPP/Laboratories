#ifndef LAB4_BINARYSEARCHTREE_HPP
#define LAB4_BINARYSEARCHTREE_HPP

#include <iostream>
#include "stacklist.hpp"

template<class T>
class BinarySearchTree
{
public:
  BinarySearchTree();

  void deleteTreeRecursive();

  void addRecursive(T obj);

  void addIterative(T obj);

  bool findElement(const T &obj);

  T findNext(const T &obj);

  int numberOfNodes();

  int height();

  void removeElement(const T &obj);

  void printInfo(int obj);

private:
  struct Node
  {
    T key_;
    int number_;
    Node *left_;
    Node *right_;
    Node *p_;

    explicit Node(T value, int num = 0, Node *left = nullptr, Node *right = nullptr, Node *p = nullptr) :
      key_(value), left_(left), right_(right), p_(p), number_(num)
    {}
  };

  Node *root_;

  int currentNumber;

  void insertRecursive(Node *&node, T key);

  int findHeight(Node *&node);

  int sizeOfTree(Node *&node);

  void printNode(Node *&node, int key);

  void deleteTree(Node *&node);
};

template<class T>
BinarySearchTree<T>::BinarySearchTree():
  root_(nullptr), currentNumber(0)
{}

template<class T>
void BinarySearchTree<T>::addIterative(T obj)
{
  currentNumber++;
  Node *tempNode = new Node(obj, currentNumber);
  Node *head = root_;
  if (head == nullptr)
  {
    root_ = tempNode;
    return;
  }

  while (head != nullptr)
  {
    if (tempNode->key_ < head->key_)
    {
      if (head->left_ == nullptr)
      {
        tempNode->p_ = head;
        head->left_ = tempNode;
        return;
      }
      head = head->left_;
    }
    else if (tempNode->key_ > head->key_)
    {
      tempNode->p_ = head;
      if (head->right_ == nullptr)
      {
        head->right_ = tempNode;
        return;
      }
      head = head->right_;
    }
  }
  tempNode->p_ = head;
  if (tempNode->key_ < head->key_)
  {
    head->left_ = tempNode;
  }
  else
  {
    head->right_ = tempNode;
  }
}

template<class T>
void BinarySearchTree<T>::insertRecursive(BinarySearchTree::Node *&node, T key)
{
  if (node == nullptr)
  {
    currentNumber++;
    node = new Node(key, currentNumber);
  }
  else
  {
    if (key < node->key_)
    {
      insertRecursive(node->left_, key);
    }
    else if (key > node->key_)
    {
      insertRecursive(node->right_, key);
    }
  }
}

template<class T>
void BinarySearchTree<T>::addRecursive(T obj)
{
  insertRecursive(root_, obj);
}

template<class T>
bool BinarySearchTree<T>::findElement(const T &obj)
{
  Node *head = root_;
  while (head != nullptr)
  {
    if (obj < head->key_)
    {
      head = head->left_;
    }
    else if (obj > head->key_)
    {
      head = head->right_;
    }
    else if (obj == head->key_)
    {
      return true;
    }
  }
  return false;
}

template<class T>
void BinarySearchTree<T>::removeElement(const T &obj)
{
  StackList<Node *> stack;
  Node *current = root_;
  while (current != nullptr)
  {
    stack.push(current);
    if (obj < current->key_)
    {
      current = current->left_;
    }
    else if (obj > current->key_)
    {
      current = current->right_;
    }
    else if (obj == current->key_)
    {
      stack.pop();
      Node *parent = stack.getTop();
      Node *lowestLeft;
      if (current->right_ != nullptr)
      {
        parent->left_ = current->right_;
      }
      else
      {
        parent->left_ = current->left_;
      }
      lowestLeft = parent->left_;
      while (lowestLeft != nullptr)
      {
        lowestLeft = lowestLeft->left_;
        stack.push(lowestLeft);
      }
      stack.pop();
      Node *parentOfLowestLeft = stack.getTop();
      parentOfLowestLeft->left_ = current->left_;
      while (!stack.isEmpty())
      {
        stack.pop();
      }
      delete current;
    }
  }
}

template<class T>
T BinarySearchTree<T>::findNext(const T &obj) //returns same value if not found
{
  Node *head = root_;
  while (head != nullptr)
  {
    if (obj < head->key_)
    {
      head = head->left_;
    }
    else if (obj > head->key_)
    {
      head = head->right_;
    }
    else if (obj == head->key_)
    {

      if (head->right_ != nullptr)
      {
        return head->right_->key_;
      }
      else if (head->left_ != nullptr)
      {
        return head->left_->key_;
      }
      else
      {
        return obj;
      }

    }
  }
  return obj;
}

template<class T>
int BinarySearchTree<T>::numberOfNodes()
{
  return sizeOfTree(root_);
}

template<class T>
int BinarySearchTree<T>::height()
{
  return findHeight(root_);
}

template<class T>
int BinarySearchTree<T>::findHeight(BinarySearchTree::Node *&node)
{
  int heightLeft = 0;
  int heightRight = 0;
  if (node->left_ != nullptr)
  {
    heightLeft = findHeight(node->left_);
  }
  if (node->right_ != nullptr)
  {
    heightRight = findHeight(node->right_);
  }

  if (heightLeft > heightRight)
  {
    return heightLeft + 1;
  }
  else
  {
    return heightRight + 1;
  }
}

template<class T>
int BinarySearchTree<T>::sizeOfTree(BinarySearchTree::Node *&node)
{
  static int size = 0;
  if (node != nullptr)
  {
    size++;
    sizeOfTree(node->left_);
    sizeOfTree(node->right_);
  }
  return size;
}

template<class T>
void BinarySearchTree<T>::printInfo(int obj)
{
  printNode(root_, obj);
}

template<class T>
void BinarySearchTree<T>::printNode(Node *&node, int key)
{
  static int size = 0;
  if (node != nullptr)
  {
    size++;
    if (key == node->number_)
    {
      std::cout << "Value of node with number " << key << " is " << node->key_ << "\n";
      size = 0;
      return;
    }
    printNode(node->right_, key);
    printNode(node->left_, key);
  }
}

template<class T>
void BinarySearchTree<T>::deleteTree(BinarySearchTree::Node *&node)
{
  if (node != nullptr)
  {
    deleteTree(node->left_);
    deleteTree(node->right_);
    if (node != root_)
    {
      Node *parentNode = node->p_;
      if (parentNode->left_ == node)
      {
        parentNode->left_ = nullptr;
        delete node;
      }
      else
      {
        parentNode->right_ = nullptr;
        delete node;
      }

    }
    else
      delete node;
  }
}

template<class T>
void BinarySearchTree<T>::deleteTreeRecursive()
{
  deleteTree(root_);
}

#endif
