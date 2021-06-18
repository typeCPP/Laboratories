#include <iostream>
#include "BinarySearchTree.hpp"

int main()
{
  BinarySearchTree<int> myBinaryTree;
  myBinaryTree.addIterative(10);
  myBinaryTree.addIterative(5);
  myBinaryTree.addIterative(12);
  myBinaryTree.addIterative(3);
  myBinaryTree.addIterative(7);
  myBinaryTree.addIterative(2);
  myBinaryTree.addIterative(6);
  myBinaryTree.addIterative(8);
  std::cout << "Created tree with elements 10,5,12,3,8,7,6,2.\n";
  myBinaryTree.printInfo(1);
  myBinaryTree.printInfo(3);
  if (myBinaryTree.findElement(7))
  {
    std::cout << "Element with value 7 was found\n";
  }
  std::cout << "Number of nodes is " << myBinaryTree.numberOfNodes() << "\n";
  std::cout << "Height of tree is " << myBinaryTree.height() << "\n";
  myBinaryTree.removeElement(5);
  std::cout << "Next node after node with key 3 is " << myBinaryTree.findNext(3) << "\n";
  myBinaryTree.deleteTreeRecursive();

  std::cout << "\nCreating a tree with chars 'g','a','k'.\n";
  BinarySearchTree<char> charTree;
  charTree.addRecursive('g');
  charTree.addRecursive('a');
  charTree.addRecursive('k');
  std::cout << "Number of nodes is " << charTree.numberOfNodes() << "\n";
  if(charTree.findElement('g')) std::cout << "Node 'g' found.\n";
  if(charTree.findElement('a')) std::cout << "Node 'a' found.\n";
  if(charTree.findElement('k')) std::cout << "Node 'k' found.\n";

  return 0;
}

