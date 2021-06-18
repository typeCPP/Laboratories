#ifndef LINKEDLIST_DOUBLELINKEDLIST_H
#define LINKEDLIST_DOUBLELINKEDLIST_H

#include <iostream>

class DoubleLinkedList
{
private:

    struct Node
    {
        int item_;
        Node* next_;
        Node* prev_;

        Node(int item, Node* next = nullptr, Node* prev = nullptr) : item_(item), next_(next), prev_(prev) { }
    };

    int count_;
    Node* head_;
    Node* tail_;

    Node* head() const { return head_; }

    Node* tail() const { return tail_; }

    void insertTail(Node* x);

    void insertHead(Node* x); // (int item);

    void deleteNode(Node* x);

    Node* searchNode(int item);

    Node* replaceNode(Node* x, int item);

public:

    friend std::ostream& operator<< (std::ostream& out, DoubleLinkedList& src);
    friend DoubleLinkedList operator| (DoubleLinkedList& src1, DoubleLinkedList& src2);
    friend DoubleLinkedList operator& (DoubleLinkedList& src1, DoubleLinkedList& src2);

    bool operator==(DoubleLinkedList& src);

    DoubleLinkedList& operator=(const DoubleLinkedList& src);
    DoubleLinkedList& operator=(DoubleLinkedList&& src) noexcept;
    DoubleLinkedList& operator=(DoubleLinkedList* src);

    DoubleLinkedList() : count_(0), head_(nullptr), tail_(nullptr) {  }

    DoubleLinkedList(const DoubleLinkedList& src);

    DoubleLinkedList(DoubleLinkedList&& src) noexcept;

    int count()const;

    int headItem() const;
    int& headItem();

    int tailItem() const;
    int& tailItem();

    void insertHead(int item);

    void insertTail(int item);

    bool deleteHead();

    bool deleteTail();

    bool deleteItem(const int item);

    bool searchItem(int item);

    bool replaceItem(int itemOld, int itemNew);

    void outAll();

    void merge(DoubleLinkedList& src);

    void swap(DoubleLinkedList& src);

    virtual ~DoubleLinkedList();
};

#endif //LINKEDLIST_DOUBLELINKEDLIST_H
