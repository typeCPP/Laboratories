#ifndef LINKEDLIST_DOUBLELINKEDLIST_H
#define LINKEDLIST_DOUBLELINKEDLIST_H

#include <iostream>
#include <stdexcept>

template<class T>
class DoubleLinkedList
{
private:

  struct Node
  {
    T item_;
    Node *next_;
    Node *prev_;

    explicit Node(T item, Node *next = nullptr, Node *prev = nullptr) : item_(item), next_(next), prev_(prev)
    {}
  };

  int count_;
  Node *head_;
  Node *tail_;

  Node *head() const
  { return head_; }

  Node *tail() const
  { return tail_; }

  void insertTail(Node *x);

  void insertHead(Node *x); // (int item);

  void deleteNode(Node *x);

  Node *searchNode(T item);

  Node *replaceNode(Node *x, T item);

public:

  bool operator==(DoubleLinkedList &src);

  DoubleLinkedList &operator=(const DoubleLinkedList &src);

  DoubleLinkedList &operator=(DoubleLinkedList &&src) noexcept;

  DoubleLinkedList &operator=(DoubleLinkedList *src);

  DoubleLinkedList():
    count_(0), head_(nullptr), tail_(nullptr)
  {}

  DoubleLinkedList(const DoubleLinkedList &src);

  DoubleLinkedList(DoubleLinkedList &&src) noexcept;

  int count() const;

  T headItem() const;

  T &headItem();

  T tailItem() const;

  T &tailItem();

  void insertHead(T item);

  void insertTail(T item);

  bool isEmpty();

  bool deleteHead();

  bool deleteTail();

  bool deleteItem(T item);

  bool searchItem(T item);

  bool replaceItem(T itemOld, T itemNew);

  void print();

  int size();

  void merge(DoubleLinkedList &src);

  void swap(DoubleLinkedList &src);

  virtual ~DoubleLinkedList();
};

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList &src)
{
  head_ = nullptr;
  tail_ = nullptr;
  count_ = 0;
  Node *temp = src.head_;
  while (temp != nullptr)
  {
    insertTail(temp->item_);
    temp = temp->next_;
  }
}

template<class T>
void DoubleLinkedList<T>::insertTail(Node *x)
{
  x->prev_ = tail_;
  if (head_ == nullptr)
  {
    insertHead(x);
    count_ = count_ - 1;
  }
  tail_->next_ = x;
  x->next_ = nullptr;
  tail_ = x;
  count_++;
}

template<class T>
void DoubleLinkedList<T>::insertHead(Node *x)
{
  x->next_ = head_;
  if (head_ != nullptr)
  {
    head_->prev_ = x;
  }
  else
  {

    tail_ = x;
  }
  head_ = x;
  count_++;
}

template<class T>
void DoubleLinkedList<T>::deleteNode(Node *x)
{
  if (x == nullptr)
  {
    throw std::invalid_argument("Wrong node address");
  }
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
  count_--;
}

template<class T>
typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::searchNode(T item)
{
  if(count_ == 0)
  {
    return nullptr;
  }
  Node *x = head_;
  while (x != nullptr && x->item_ != item)
  {
    x = x->next_;
  }
  return x;
}

template<class T>
typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::replaceNode(DoubleLinkedList::Node *x, T item)
{
  x->item_ = item;
  return x;
}

template<class T>
int DoubleLinkedList<T>::count() const
{ return count_; }

template<class T>
T DoubleLinkedList<T>::headItem() const
{
  if (head_ != nullptr)
  {
    return head_->item_;
  }
  throw std::logic_error("List is empty!");
}

template<class T>
T &DoubleLinkedList<T>::headItem()
{
  if (head_ != nullptr)
  {
    return head_->item_;
  }
  throw ("headItem - список пуст!");
}

template<class T>
T DoubleLinkedList<T>::tailItem() const
{
  if (tail_ != nullptr)
  {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}

template<class T>
T &DoubleLinkedList<T>::tailItem()
{
  if (tail_ != nullptr)
  {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}

template<class T>
void DoubleLinkedList<T>::insertHead(T item)
{
  insertHead(new Node(item));
}

template<class T>
void DoubleLinkedList<T>::insertTail(T item)
{
  insertTail(new Node(item));
}

template<class T>
bool DoubleLinkedList<T>::deleteHead()
{
  if (head_ == nullptr)
  {
    return 0;
  }
  deleteNode(head_);
  return 1;
}

template<class T>
bool DoubleLinkedList<T>::deleteTail()
{
  deleteNode(tail_);
  return 1;
}

template<class T>
bool DoubleLinkedList<T>::deleteItem(T item)
{
  Node *x = head_;
  while (x->next_ != nullptr && x->item_ != item)
  {
    x = x->next_;
  }
  if (x->item_ == item)
  {
    deleteNode(x);
  }
  else
  {
    return 0;
  }
  return 1;
}

template<class T>
bool DoubleLinkedList<T>::searchItem(T item)
{
  return (searchNode(item) != nullptr);
}

template<class T>
bool DoubleLinkedList<T>::replaceItem(T itemOld, T itemNew)
{
  Node *x = head_;
  while (x != nullptr && x->item_ != itemOld)
  {
    x = x->next_;
  }
  if (x->item_ != itemOld)
  {
    return 0;
  }
  if (x->item_ == itemOld)
  {
    replaceNode(x, itemNew);
  }
  return 1;
}

template<class T>
void DoubleLinkedList<T>::print()
{
  Node *current = head_;
  while (current != nullptr)
  {
    if(current != tail_)
    {
      std::cout << current->item_ << ", ";
    }
    else
    {
      std::cout << current->item_;
    }
    current = current->next_;
  }
}

template<class T>
DoubleLinkedList<T>::~DoubleLinkedList()
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
bool DoubleLinkedList<T>::operator==(DoubleLinkedList &src)
{
  if (count_ != src.count_)
  {
    return 0;
  }
  else
  {
    Node *rightSideNode = src.head_;
    Node *leftSideNode = head_;
    for (int i = 0; i < count_; i++)
    {
      if (leftSideNode->item_ != rightSideNode->item_)
      {
        return 0;
      }
    }
    return 1;
  }

}

template<class T>
void DoubleLinkedList<T>::merge(DoubleLinkedList &src)
{
  Node *h = src.head_;
  while (h != nullptr)
  {
    insertTail(h->item_);
    h = h->next_;
  }
  return;
}

template<class T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(const DoubleLinkedList &src)
{
  DoubleLinkedList temp(src);
  this->swap(temp);
  return *this;
}

template<class T>
void DoubleLinkedList<T>::swap(DoubleLinkedList &src)
{
  DoubleLinkedList temp(src);
  src.head_ = this->head_;
  src.tail_ = this->tail_;
  src.count_ = this->count_;
  this->head_ = temp.head_;
  this->tail_ = temp.tail_;
  this->count_ = temp.count_;
  temp.head_ = nullptr;
  temp.tail_ = nullptr;
  temp.count_ = 0;
}

template<class T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(DoubleLinkedList &&src) noexcept
{
  if (this != &src)
  {
    count_ = -1;
    DoubleLinkedList temp(src);
    head_ = temp.head_;
    tail_ = temp.tail_;
    count_ = temp.count_;
    src.~DoubleLinkedList();
    temp.head_ = nullptr;
    temp.tail_ = nullptr;
    temp.count_ = 0;
  }
  return *this;
}

template<class T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(DoubleLinkedList *src)
{
  this->count_ = src->count_;
  this->head_ = src->head_;
  this->tail_ = src->tail_;
  return *this;
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList &&src) noexcept
{
  if (this != &src)
  {
    DoubleLinkedList temp(src);
    head_ = temp.head_;
    tail_ = temp.tail_;
    count_ = temp.count_;
    src.~DoubleLinkedList();
    temp.head_ = nullptr;
    temp.tail_ = nullptr;
    temp.count_ = 0;
  }
}

template<class T>
bool DoubleLinkedList<T>::isEmpty()
{
  return count_ == 0;
}

template<class T>
int DoubleLinkedList<T>::size()
{
  return count_;
}

#endif
