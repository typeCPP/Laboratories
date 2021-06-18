#include <iostream>
#include "queuearray.hpp"
#include "queuelist.hpp"
#include "BinarySearchTree.hpp"

int main()
{
  std::cout << "Creating queue array with size = 10.\n";
  QueueArray<int> firstArrayQueue(10);
  std::cout << "Inserting numbers from 1 to 10.\n";
  firstArrayQueue.enQueue(1);
  firstArrayQueue.enQueue(2);
  firstArrayQueue.enQueue(3);
  firstArrayQueue.enQueue(4);
  firstArrayQueue.enQueue(5);
  firstArrayQueue.enQueue(6);
  firstArrayQueue.enQueue(7);
  firstArrayQueue.enQueue(8);
  firstArrayQueue.enQueue(9);
  firstArrayQueue.enQueue(10);
  try
  {
    std::cout << "Trying to insert one more number: \n";
   firstArrayQueue.enQueue(4);
  }
  catch (const QueueOverflow& error)
  {
    std::cout << error.what() << "\n";
  }
  std::cout << "Copying current queue to the new one.\n";
  QueueArray<int> secondArrayQueue(firstArrayQueue);
  std::cout << "Popping items from queue: \n";
  for(int i = 0;i<10;i++)
  {
    std::cout << secondArrayQueue.deQueue() << " ";
  }
  try
  {
    std::cout << "\nTrying to pop one more item: \n";
    secondArrayQueue.deQueue();
  }
  catch (const QueueUnderflow& error)
  {
    std::cout << error.what() << "\n";
  }

  std::cout << "\nCreating list queue and filling it with numbers from 1 to 3.\n";
  QueueList<int> firstQueueList;
  firstQueueList.enQueue(1);
  firstQueueList.enQueue(2);
  firstQueueList.enQueue(3);
  std::cout << "Copying current queue list to the new one.\n";
  QueueList<int> secondQueueList(firstQueueList);
  std::cout << "Popping items from queue: \n";
  for(int i = 0;i<3;i++)
  {
    std::cout << secondQueueList.deQueue() << " ";
  }
  std::cout << "\n\nTesting tree algorithms.\n";
  BinarySearchTree<int> tree;
  tree.addIterative(10);
  tree.addIterative(5);
  tree.addIterative(12);
  tree.addIterative(3);
  tree.addIterative(7);
  tree.addIterative(2);
  tree.addIterative(6);
  tree.addIterative(8);
  std::cout << "Created tree with nodes: 10 5 12 3 7 2 6 8\n";
  std::cout << "Iterative walk in width of the tree: ";
  tree.iterativeBreadth();
  std::cout << "\n";
  std::cout << "Iterative walk inorder(prefix form): ";
  tree.iterativeInorder();
  std::cout << "\nCopying the tree to a new one.\n";
  BinarySearchTree<int> tree2(tree);
  std::cout << "Are these trees same? ";
  if(tree.sameTrees(tree2)) std::cout << "Yes";
  else std::cout << "No";

  std::cout << "\nCreating a new tree with nodes: 10 5 12 3 7 2 6\n";
  BinarySearchTree<int> tree3;
  tree3.addIterative(10);
  tree3.addIterative(5);
  tree3.addIterative(12);
  tree3.addIterative(3);
  tree3.addIterative(7);
  tree3.addIterative(2);
  tree3.addIterative(6);
  std::cout << "Are first tree and third same? ";
  if(tree.sameTrees(tree3)) std::cout << "Yes";
  else std::cout << "No";
  return 0;
}

