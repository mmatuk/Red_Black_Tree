//*******************************************************
//Author:                       Matt Matuk
//Created:                      11/15/2017
//Source File:                  RBT.h
//Description:
//  Template for the Red Black Tree main cpp file.
//
//Editor:                          Emacs
//*******************************************************

#ifndef RBT_H
#define RBT_H
#define DISPLAY_RED "\e[31m"
#define DISPLAY_CLEAR "\e[0m"

#include "TNode.h"

template <class T>
class RBT
{
private:
  TNode<T> *const TNIL = new TNode<T>(NULL, NULL, NULL, RBT_BLACK);
  TNode<T> *root;
  TNode<T> *successor(TNode<T> const *);
  TNode<T> *minimum(TNode<T> *);
  void destroySubTree(TNode<T> *);
  void leftRotate(TNode<T> *);
  void rightRotate(TNode<T> *);
  void rbInsertFixUp(TNode<T> *);
  void rbDeleteFixUp(TNode<T> *, TNode<T> *);
  TNode<T> *createNode(T const);

public:
  RBT();
  ~RBT();
  void inOrder(TNode<T> const *);
  void preOrder(TNode<T> const *);
  void postOrder(TNode<T> const *);
  int RBTInsert(T const);
  int RBTDelete(T const);
  TNode<T> *RBTSearch(T);
  TNode<T> *getRoot();
};

#include "RBT.cpp"

#endif /* RBT_H */
