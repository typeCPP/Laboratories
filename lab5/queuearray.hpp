#ifndef LAB5_QUEUEARRAY_HPP
#define LAB5_QUEUEARRAY_HPP

#include "queue.hpp"
#include "qexceptions.hpp"

template<class T>
class QueueArray : public Queue<T>
{
public:
  explicit QueueArray(int size = 10);

  QueueArray(QueueArray<T> &src);

  virtual ~QueueArray()
  { delete[] array_; }

  void enQueue(const T &e);

  const T deQueue();

  bool isEmpty()
  { return head_ == tail_; }

private:
  T *array_;
  int head_{};
  int tail_{};
  int size_{};
};

template<class T>
QueueArray<T>::QueueArray(int size)
{
  if (size <= 0)
  {
    throw WrongQueueSize();
  }
  size_ = size;
  array_ = new T[size_];
  head_ = 0;
  tail_ = 0;
}

template<class T>
void QueueArray<T>::enQueue(const T &e)
{
  if (tail_ == size_)
  {
    throw QueueOverflow();
  }
  array_[tail_] = e;
  tail_++;
}

template<class T>
const T QueueArray<T>::deQueue()
{
  if (head_ == tail_)
  {
    throw QueueUnderflow();
  }

  const T temp = array_[head_];
  for (int i = 0; i < tail_; i++)
  {
    if (i == size_ - 1) break;
    array_[i] = array_[i + 1];
  }
  tail_--;
  return temp;
}

template<class T>
QueueArray<T>::QueueArray(QueueArray<T> &src):
head_(src.head_), tail_(src.tail_), size_(src.size_)
{
  array_ = new T[size_];
  for (int i = 0; i < size_; i++)
  {
    array_[i] = src.array_[i];
  }
}

#endif
