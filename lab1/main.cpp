
#include <iostream>
#include "DoubleLinkedList.h"


std::ostream& operator<< (std::ostream& out, DoubleLinkedList& src)
{
    src.outAll();
    return out;
}

int main() {
    //testing
    DoubleLinkedList list;
    list.insertHead(1);
    list.insertHead(2);
    list.insertHead(3);
    std::cout << "First list:" << std::endl;
    list.outAll();

    std::cout << ((list.searchItem(1)) ? "1 find" : "1 not find") << std::endl;
    std::cout << ((list.searchItem(8)) ? "8 find" : "8 not find") << std::endl;

    DoubleLinkedList  list1(list);
    list1.insertHead(4);
    list1.insertHead(5);
    list1.deleteHead();
    std::cout << "Second list, copied from first:" << std::endl;
    list1.outAll();
    list1.insertTail(6);
    list1.deleteTail();
    list1.deleteItem(3);
    std::cout << "Second list, after deleting:" << std::endl;
    list1.outAll();
    std::cout << "Checking overloaded operator <<:" << std::endl;
    std::cout << list;
    std::cout << "Checking overloaded operator &" << std::endl;
    DoubleLinkedList list2;
    list2 = list & list1;
    list2.outAll();
    std::cout << "Checking list comparing:" << std::endl;
    bool temp = list == list1;
    std::cout << temp << std::endl;
    list1.insertHead(5);
    list = list1;
    std::cout << "Checking copy-and-swap idiom:" << std::endl;
    list.outAll();
    list1.outAll();

    list.merge(list1);
    std::cout << "Merged lists:" << std::endl;
    list.outAll();



    return 0;
}

DoubleLinkedList operator| (DoubleLinkedList& src1, DoubleLinkedList& src2)
{
    DoubleLinkedList list3;
    int count1 = src1.count_;   
    DoubleLinkedList::Node* head1 = src1.head_;
    for (int i = 0; i < count1; i++)
    {
        list3.insertTail(head1->item_);
        head1 = head1->next_;
    }
    int count2 = src2.count_;
    DoubleLinkedList::Node* head2 = src2.head_;
    for (int i = 0; i < count2; i++)
    {
        if (!list3.searchItem(head2->item_))
        {
            list3.insertTail(head2->item_);
        }
        head2 = head2->next_;
    }
    return list3;
}

DoubleLinkedList operator& (DoubleLinkedList& src1, DoubleLinkedList& src2)
{
    DoubleLinkedList list3;
    int count1 = src1.count();
    DoubleLinkedList::Node* head1 = src1.head_;
    for (int i = 0; i < count1; i++)
    {
        if (src2.searchItem(head1->item_))
        {
            list3.insertTail(head1->item_);
        }
        head1 = head1->next_;
    }
    return list3;
}


