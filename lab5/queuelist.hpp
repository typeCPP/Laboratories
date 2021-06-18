#ifndef LAB5_QUEUELIST_HPP
#define LAB5_QUEUELIST_HPP

#include <iostream>
#include "queue.hpp"
#include "qexceptions.hpp"

template<class T>
class QueueList : public Queue<T>
{

public:
  QueueList() : size_(0), head_(nullptr), tail_(nullptr)
  {}

  QueueList(const QueueList &src);

  virtual ~QueueList();

  void enQueue(const T &e);

  const T deQueue();

  bool isEmpty();

private:

  struct Node
  {
    T item_;
    Node *next_;
    Node *prev_;

    Node(T item, Node *next = nullptr, Node *prev = nullptr) : item_(item), next_(next), prev_(prev)
    {}
  };

  int size_;
  Node *head_;
  Node *tail_;

  void deleteHead();

  void insertTail(Node *x);

  void deleteNode(Node *x);

  void insertHead(Node* x);

};

template<class T>
QueueList<T>::~QueueList()
{
  Node *next = head_;
  while (next != nullptr)
  {
    next = head_->next_;
    delete head_;
    head_ = next;
  }
}

template<class T>
void QueueList<T>::deleteNode(QueueList::Node *x)
{
  if (x->prev_ != nullptr)
  {
    (x->prev_)->next_ = x->next_;
  }
  else
  {
    head_ = x->next_;
  }
  if (x->next_ != nullptr)
  {
    (x->next_)->prev_ = x->prev_;
  }
  else
  {
    tail_ = x->prev_;
  }
  delete x;
  size_--;
}

template<class T>
void QueueList<T>::deleteHead()
{
  if (head_ == nullptr)
  {
    return;
  }
  deleteNode(head_);
}

template<class T>
void QueueList<T>::insertTail(QueueList::Node *x)
{
  x->prev_ = tail_;
  if (head_ == nullptr)
  {
    insertHead(x);
    size_ = size_ - 1;
  }
  tail_->next_ = x;
  x->next_ = nullptr;
  tail_ = x;
  size_++;
}

template<class T>
void QueueList<T>::enQueue(const T &e)
{
  insertTail(new Node(e));
}

template<class T>
const T QueueList<T>::deQueue()
{
  if(size_ == 0)
  {
    throw QueueUnderflow();
  }
  T temp = head_->item_;
  deleteHead();
  return temp;
}

template<class T>
bool QueueList<T>::isEmpty()
{
  if (head_ == nullptr && tail_ == nullptr) return 1;
  else return 0;
}

template<class T>
void QueueList<T>::insertHead(QueueList::Node* x)
{
  x->next_ = head_;
  if (head_ != nullptr) {
    head_->prev_ = x;
  }
  else {

    tail_ = x;
  }
  head_ = x;
  size_++;
}

template<class T>
QueueList<T>::QueueList(const QueueList &src)
{
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
  Node* temp = src.head_;
  while (temp != nullptr)
  {
    enQueue(temp->item_);
    temp = temp->next_;
  }
}

#endif
