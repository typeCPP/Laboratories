#include "DoubleLinkedList.h"
#include <iostream>

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& src)
{
    head_ = nullptr;
    tail_ = nullptr;
    count_ = 0;
    Node* temp = src.head_;
    while (temp != nullptr)
    {
        insertTail(temp->item_);
        temp = temp->next_;
    }
}

void DoubleLinkedList::insertTail(Node* x)
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

void DoubleLinkedList::insertHead(Node* x)
{
    x->next_ = head_;
    if (head_ != nullptr) {
        head_->prev_ = x;
    }
    else {

        tail_ = x;
    }
    head_ = x;
    count_++;
}


void DoubleLinkedList::deleteNode(Node* x)
{
    if (x == nullptr) {
        throw ("DoubleLinkedList::deleteNode  - неверно задан адрес удаляемого узла");
    }
    if (x->prev_ != nullptr) {
        (x->prev_)->next_ = x->next_;
    }
    else {
        head_ = x->next_;
    }
    if (x->next_ != nullptr) {
        (x->next_)->prev_ = x->prev_;
    }
    else {
        tail_ = x->prev_;
    }
    delete x;
    count_--;
}


DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
    Node* x = head_;
    while (x != nullptr && x->item_ != item) {
        x = x->next_;
    }
    return x;
}


DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
    x->item_ = item;
    return x;
}


int DoubleLinkedList::count()const { return count_; }


int DoubleLinkedList::headItem() const
{
    if (head_ != nullptr) {
        return head_->item_;
    }
    throw ("headItem - список пуст!");
}

int& DoubleLinkedList::headItem()
{
    if (head_ != nullptr) {
        return head_->item_;
    }
    throw ("headItem - список пуст!");
}


int DoubleLinkedList::tailItem() const
{
    if (tail_ != nullptr) {
        return tail_->item_;
    }
    throw ("tailItem - список пуст!");
}
int& DoubleLinkedList::tailItem()
{
    if (tail_ != nullptr) {
        return tail_->item_;
    }
    throw ("tailItem - список пуст!");
}


void DoubleLinkedList::insertHead(int item)
{
    insertHead(new Node(item));
}



void DoubleLinkedList::insertTail(int item)
{
    insertTail(new Node(item));
}

bool DoubleLinkedList::deleteHead()
{
    if (head_ == nullptr) {
        return 0;
    }
    deleteNode(head_);
    return 1;
}


bool DoubleLinkedList::deleteTail()
{
    deleteNode(tail_);
    return 1;
}


bool DoubleLinkedList::deleteItem(const int item)
{
    Node* x = head_;
    while (x != nullptr && x->item_ != item) {
        x = x->next_;
    }
    if (x->item_ == item)
    {
        deleteNode(x);
    }
    return 1;
}


bool DoubleLinkedList::searchItem(int item)
{
    return (searchNode(item) != nullptr);
}


bool DoubleLinkedList::replaceItem(int itemOld, int itemNew)
{
    Node* x = head_;
    while (x != nullptr && x->item_ != itemOld) {
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


void DoubleLinkedList::outAll()
{
    Node* current = head_;
    while (current != nullptr)
    {
        std::cout << current->item_ << ' ';
        current = current->next_;
    }
    std::cout << std::endl;
}


DoubleLinkedList::~DoubleLinkedList()
{
  Node *next = head_;
  while (next != nullptr)
  {
    next = head_->next_;
    delete head_;
    head_ = next;
  }
}

bool DoubleLinkedList::operator==(DoubleLinkedList& src)
{
    if (count_ != src.count_)
    {
        return 0;
    }
    else
    {
        Node* rightSideNode = src.head_;
        Node* leftSideNode = head_;
        for (int i = 0;i < count_;i++)
        {
            if (leftSideNode->item_ != rightSideNode->item_)
            {
                return 0;
            }
        }
        return 1;
    }

}

void DoubleLinkedList::merge(DoubleLinkedList& src)
{
    Node* h = src.head_;
    while (h != nullptr)
    {
        insertTail(h->item_);
        h = h->next_;
    }
    return;
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& src)
{
    DoubleLinkedList temp(src);
    this->swap(temp);
    return *this;
}


void DoubleLinkedList::swap(DoubleLinkedList& src)
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
    temp.count_ = NULL;
    return;
}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& src) noexcept
{
    if (this != &src)
    {
        delete[] head_;
        delete[] tail_;
        count_ = -1;
        DoubleLinkedList temp(src);
        head_ = temp.head_;
        tail_ = temp.tail_;
        count_ = temp.count_;
        src.~DoubleLinkedList();
        temp.head_ = nullptr;
        temp.tail_ = nullptr;
        temp.count_ = NULL;

    }
    return *this;
}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList* src)
{
    this->count_ = src->count_;
    this->head_ = src->head_;
    this->tail_ = src->tail_;
    return *this;
}

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src) noexcept
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
        temp.count_ = NULL;

    }
}
