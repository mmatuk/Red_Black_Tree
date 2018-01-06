//*******************************************************
//Author:                       Matt Matuk
//Created:                      11/15/2017
//Source File:                  TNode.cpp
//Description:
//
//Editor:                          Emacs
//*******************************************************

#include <iostream>
#include <iomanip>
#include <iomanip>

using namespace std;

/**
 * @brief Constructor
 *
 * @param value Value to add
 */
template <class T>
TNode<T>::TNode(T const value)
{
  parent = NULL;
  left = NULL;
  right = NULL;
  data = value;
  color = RBT_RED;
}

template <class T>
TNode<T>::TNode(TNode<T> *p, TNode<T> *r, TNode<T> *l, int const c)
{
  parent = p;
  left = l;
  right = r;
  color = c;
}

/**
 * Constructor for a new TNode
 * 
 * @param value Data value of the node.
 * @param p Pointer to the Parent TNode.
 * @param r Pointer to the right child of the TNode.
 * @param l Pointer to the left child of the TNode.
 * @param c Color of the TNode. (RBT_RED or RBT_BLACK)
 */
template <class T>
TNode<T>::TNode(T const value, TNode<T> *p, TNode<T> *r, TNode<T> *l, int const c)
{
  parent = p;
  left = l;
  right = r;
  data = value;
  color = c;
}

/**
 * @brief Gets the data value of the node
 *
 * @return Value of the data
 */
template <class T>
T TNode<T>::getData()
{
  return data;
}

/**
 * @brief Print out the info about the node
 *
 */
template <class T>
void TNode<T>::printNode()
{
  cout << "Parent: " << parent << "\n";
  cout << "Left: " << left << "\n";
  cout << "Right: " << right << "\n";
  cout << "Data: " << data;
}
