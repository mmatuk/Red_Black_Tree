//*******************************************************
//Author:                       Matt Matuk
//Created:                      10/12/2017
//Source File:                  TNode.h
//Description:
//
//Editor:                          Emacs
//*******************************************************

#ifndef TNODE_H
#define TNODE_H
#define RBT_BLACK 1
#define RBT_RED 0

template <class T>
class TNode
{
  template <class U>
  friend class RBT;

private:
  TNode<T> *parent;
  TNode<T> *left;
  TNode<T> *right;
  T data;
  int color;

public:
  TNode(TNode<T> *, TNode<T> *, TNode<T> *, int const);
  TNode(T const, TNode<T> *, TNode<T> *, TNode<T> *, int const);
  TNode(T const);
  //~TNode();
  T getData();
  void printNode();
};

#include "TNode.cpp"

#endif /* TNODE_H */
