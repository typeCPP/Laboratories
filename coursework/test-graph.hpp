#ifndef COURSEWORK_TEST_GRAPH_HPP
#define COURSEWORK_TEST_GRAPH_HPP

#include <iostream>
#include "directedGraph.hpp"
#include "undirectedGraph.hpp"
#include "exceptions.hpp"

void printDashes()
{
  for (int i = 0; i < 30; i++)
    std::cout << "-";
  std::cout << "\n";
}

void printTheme(std::string theme)
{
  std::cout << "\n";
  printDashes();
  std::cout << theme << "\n";
  printDashes();
}

void testEmptyGraphError()
{
  printTheme("TESTING EMPTY GRAPH ERROR");
  DirectedGraph<int> dirGraph;
  UndirectedGraph<int> unGraph;
  std::cout << "Result of isEmpty function for directed graph: " << dirGraph.isEmpty() << "\n";
  std::cout << "Result of isEmpty function for undirected graph: " << unGraph.isEmpty() << "\n";
  std::cout << "Attempt to delete node from empty directed graph.\n";
  try
  {
    dirGraph.deleteNode(5);
  }
  catch (GraphEmpty &error)
  {
    std::cout << error.what() << "\n";
  }
  std::cout << "Attempt to delete node from empty undirected graph.\n";
  try
  {
    unGraph.deleteNode(5);
  }
  catch (GraphEmpty &error)
  {
    std::cout << error.what() << "\n";
  }
}

void testUndirectedGraphCreation()
{
  printTheme("TESTING UNDIRECTED GRAPH CREATION");
  UndirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  std::cout << "Making connections.\n";
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 0);
  graph.addWay(2, 5);
  graph.addWay(2, 4);
  graph.print();
}

void testDirectedGraphCreation()
{
  printTheme("TESTING DIRECTED GRAPH CREATION");
  DirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  std::cout << "Making connections.\n";
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 0);
  graph.addWay(2, 5);
  graph.addWay(2, 4);
  graph.print();
}

void testUndirectedGraphDeleteMethods()
{
  printTheme("TESTING UNDIRECTED GRAPH DELETE METHODS");
  UndirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  std::cout << "Making connections.\n";
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 0);
  graph.addWay(2, 5);
  graph.addWay(2, 4);
  graph.print();
  std::cout << "\nDeleting node 5 and then checking graph again.\n";
  graph.deleteNode(5);
  graph.print();
  std::cout << "\nDeleting a way between 0 and 1 and then checking graph.\n";
  graph.deleteWay(0, 1);
  graph.print();
}

void testDirectedGraphDeleteMethods()
{
  printTheme("TESTING DIRECTED GRAPH DELETE METHODS");
  DirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  std::cout << "Making connections.\n";
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 0);
  graph.addWay(2, 5);
  graph.addWay(2, 4);
  graph.print();
  std::cout << "\nDeleting node 5 and then checking graph again.\n";
  graph.deleteNode(5);
  graph.print();
  std::cout << "\nDeleting a way between 3 and 4 and then checking graph.\n";
  graph.deleteWay(3, 4);
  graph.print();
}

void testDFSUndirected()
{
  printTheme("TESTING UNDIRECTED GRAPH DFS");
  UndirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  std::cout << "Making connections.\n";
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 0);
  graph.addWay(2, 5);
  graph.addWay(2, 4);
  graph.print();
  graph.DFS();
}

void testDFSDirected()
{
  printTheme("TESTING DIRECTED GRAPH DFS");
  DirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  std::cout << "Making connections.\n";
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 0);
  graph.addWay(2, 5);
  graph.addWay(2, 4);
  graph.print();
  graph.DFS();
}

void testTransposeDirected()
{
  printTheme("TESTING DIRECTED GRAPH TRANSPOSING");
  DirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  std::cout << "Making connections.\n";
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 0);
  graph.addWay(2, 5);
  graph.addWay(2, 4);
  graph.print();
  std::cout << "\nTransposing current graph.\n\n";
  graph.transpose();
  graph.print();
}

void testSCC()
{
  printTheme("TESTING DIRECTED GRAPH SCCs");
  DirectedGraph<int> graph;
  std::cout << "Adding nodes: 0, 1, 2, 3, 4, 5, 6, 7.\n";
  graph.addNode(0);
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  graph.addNode(6);
  graph.addNode(7);
  graph.addWay(0, 1);
  graph.addWay(1, 2);
  graph.addWay(2, 3);
  graph.addWay(3, 0);
  graph.addWay(2, 4);
  graph.addWay(4, 5);
  graph.addWay(5, 6);
  graph.addWay(6, 4);
  graph.addWay(6, 7);
  graph.print();
  std::cout << "\nStrongly connected components are: \n";
  graph.SCC();
}

void testGraph()
{
  testEmptyGraphError();
  testUndirectedGraphCreation();
  testDirectedGraphCreation();
  testUndirectedGraphDeleteMethods();
  testDirectedGraphDeleteMethods();
  testDFSUndirected();
  testDFSDirected();
  testTransposeDirected();
  testSCC();
}

#endif
