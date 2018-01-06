//*******************************************************
// Author:                       Matt Matuk
// Created:                      11/15/2017
// Source File:                  TNode.cpp
// Description:
//
// Editor:                          Emacs
//*******************************************************

#include "TNode.h"
#include <iomanip>
#include <iostream>

using namespace std;

/**
 * @brief Constructs an empty tree with null as root
 *
 */
template <class T>
RBT<T>::RBT() { root = TNIL; }

/**
 * @brief Deconstructor for the Binary Tree
 *
 */
template <class T>
RBT<T>::~RBT() { destroySubTree(root); }

/**
 * @brief Called by the deconstructor and used to delete the nodes of the tree.
 *
 * @param node Node to be deleted
 */
template <class T>
void RBT<T>::destroySubTree(TNode<T> *node)
{
  if (node)
  {
    if (node->left)
    {
      destroySubTree(node->left);
    }
    if (node->right)
    {
      destroySubTree(node->right);
    }
    delete node;
  }
}

/**
 * @brief Prints the inOrder
 *
 * @param x Root node
 */
template <class T>
void RBT<T>::inOrder(TNode<T> const *x)
{
  if (x != TNIL)
  {
    inOrder(x->left);
    if (x->color == RBT_RED)
    {
      cout << DISPLAY_RED << " " << x->data << DISPLAY_CLEAR;
    }
    else
    {
      cout << " " << x->data;
    }
    inOrder(x->right);
  }
}

/**
 * @brief Prints postOrder values for the tree
 *
 * @param x Root
 */
template <class T>
void RBT<T>::postOrder(TNode<T> const *x)
{
  if (x != TNIL)
  {
    postOrder(x->left);
    postOrder(x->right);
    if (x->color == RBT_RED)
    {
      cout << DISPLAY_RED << " " << x->data << DISPLAY_CLEAR;
    }
    else
    {
      cout << " " << x->data;
    }
  }
}

/**
 * @brief Prints preOrder values for the tree
 *
 * @param x Description of x
 */
template <class T>
void RBT<T>::preOrder(TNode<T> const *x)
{
  if (x != TNIL)
  {
    if (x->color == RBT_RED)
    {
      cout << DISPLAY_RED << " " << x->data << DISPLAY_CLEAR;
    }
    else
    {
      cout << " " << x->data;
    }
    preOrder(x->left);
    preOrder(x->right);
  }
}

/**
 * @brief Insert a value into the Binary tree. Will return -1 if value
 *        is already in the tree and 0 is insert sucessful.
 *
 * @param value Value to insert
 * @return -1 if value found in tree, 0 if insert successful
 */
template <class T>
int RBT<T>::RBTInsert(T const value)
{
  if (RBTSearch(value) != NULL) // value was not in tree
  {
    return -1; // value in tree already
  }
  TNode<T> *y = TNIL;
  TNode<T> *x = root;
  TNode<T> *z = createNode(value);

  // While x is not null
  while (x != TNIL)
  {
    y = x;
    if (z->data < x->data) // less then current node
    {
      x = x->left;
    }
    else // greater then current node
    {
      x = x->right;
    }
  }

  z->parent = y;
  if (y == TNIL) // emtpy tree
  {
    root = z;
  }
  else if (z->data < y->data) // set as root left
  {
    y->left = z;
  }
  else // set as root right
  {
    y->right = z;
  }

  z->left = TNIL;
  z->right = TNIL;
  z->color = RBT_RED;
  rbInsertFixUp(z);

  return 0; // value not in tree and was added
}

/**
 * @brief Remove a value from the tree by first finding if the value exists,
 *        then deleting the node under three conditions:
 *             1) Node has no childs
 *                   Just delete.
 *             2) Node has only one child
 *                   Delete and replace child parent ads deleted nodes parent
 * and deleted nodes parents child with the delted nodes child. 3) Node has two
 * childs Find successor and then replace the deleted node with it.
 *
 * @param value Value to be deleted.
 * @return -1 If value is not in tree, 0 if deleted successful.
 */
template <class T>
int RBT<T>::RBTDelete(T const value)
{
  TNode<T> *z = RBTSearch(value); // searches for passed value in tree
  TNode<T> *y = TNIL;             // node to delete
  TNode<T> *x;

  if (z == NULL) // value to delete was not found //
    return -1;
  else // Value found and will be deleted //
  {
    if (z->left == TNIL || z->right == TNIL) // value has a most 1 child
    {
      y = z;
    }
    else // value has two children
    {
      y = successor(z);
    }

    if (y->left != TNIL) // value left child is not null
    {
      x = y->left;
    }
    else // value right child is not null
    {
      x = y->right;
    }
    if (x != TNIL)
    {
      x->parent = y->parent; // set values child->parent to current->parent
    }

    if (y->parent == TNIL) // value is the root
    {
      root = x;
    }
    else if (y == y->parent->left) // value is parents left child. Set
                                   // parents->left to values-> child x
    {
      y->parent->left = x;
    }
    else // value is parents right child. Set parents->right to values->child
         // x
    {
      y->parent->right = x;
    }

    if (y != z) // did need successor
    {
      z->data = y->data;
    }

    if (y->color == RBT_BLACK)
    {
      rbDeleteFixUp(y, x); // y == 38, x == 41
    }

    delete y;
    return 0; // value to delete was deleted
  }
}

/**
 * @brief Find the successor of the passed value.
 *
 * @param x Node with value that needs a successor.
 * @return Successor *node to the passed node.
 */
template <class T>
TNode<T> *RBT<T>::successor(TNode<T> const *x)
{
  if (x->right != TNIL) // reight subtree is not null, find min and thats successor
  {
    return minimum(x->right);
  }
  else
  {
    TNode<T> *y = x->parent;
    // if x is y's left child then y is successor pf x
    while (y != TNIL && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
  }
}

/**
 * @brief Find the min value of the passed nodes subtrees.
 *
 * @param x Node to start at.
 * @return *Node with the min found, X if min was the passed value.
 */
template <class T>
TNode<T> *RBT<T>::minimum(TNode<T> *x)
{
  TNode<T> *y = x;
  while (y->left != TNIL) // get left most child of the subtree
  {
    y = y->left;
  }
  return y;
}

/**
 * @brief Search the tree to find if the passed value is in the tree.
 *
 * @param value Value to search for.
 * @return *Node of the value found, NULL if value not in tree.
 */
template <class T>
TNode<T> *RBT<T>::RBTSearch(T value)
{
  TNode<T> *temp = root;                      // temp node
  while (temp != TNIL && value != temp->data) // find data in tree
  {
    if (value < temp->data)
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }
  if (temp == TNIL)
  {
    return NULL;
  }
  else
  {
    return temp; // return node with data or NUll if not found
  }
}

/**
 * @brief Root of the tree
 *
 * @return The Root *Node
 */
template <class T>
TNode<T> *RBT<T>::getRoot() { return root; }

/**
 * @brief Left rotate the tree
 *
 */
template <class T>
void RBT<T>::leftRotate(TNode<T> *x)
{
  TNode<T> *y = x->right;
  x->right = y->left;
  y->left->parent = x;
  y->parent = x->parent; // Link x's parent to y

  if (x->parent == TNIL)
  {
    root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

/**
 * @brief Right rotate tree
 *
 */
template <class T>
void RBT<T>::rightRotate(TNode<T> *x)
{
  TNode<T> *y = x->left; // set y
  x->left = y->right;    // Turn y's right subtree into x's left subtree
  y->right->parent = x;
  y->parent = x->parent; // x's parent to y
  if (x->parent == TNIL)
  {
    root = y;
  }
  else if (x == x->parent->right)
  {
    x->parent->right = y;
  }
  else
  {
    x->parent->left = y;
  }

  y->right = x; // put x on y's right
  x->parent = y;
}

/**
 * INsert fix up
 */
template <class T>
void RBT<T>::rbInsertFixUp(TNode<T> *z)
{
  TNode<T> *y;
  while (z->parent->color == RBT_RED)
  {
    if (z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right; // y is pointing z’s uncle 4
      if (y->color == RBT_RED)      // z’s uncle’s color is RED
      {
        z->parent->color = RBT_BLACK;       // Case 1
        y->color = RBT_BLACK;               // Case 1
        z->parent->parent->color = RBT_RED; // Case
        z = z->parent->parent;              // Case 1
      }
      else // z’s uncle (y) color = BLACK
      {
        if (z == z->parent->right)
        {
          z = z->parent; // Case 2
          leftRotate(z); // Case 2
        }
        z->parent->color = RBT_BLACK;       // Case 3
        z->parent->parent->color = RBT_RED; // Case 3
        rightRotate(z->parent->parent);     // Case 3
      }
    }
    else
    {
      y = z->parent->parent->left;
      if (y->color == RBT_RED)
      {
        z->parent->color = RBT_BLACK;       // Case 1
        y->color = RBT_BLACK;               // Case 1
        z->parent->parent->color = RBT_RED; // Case 1
        z = z->parent->parent;              // Case 1
      }
      else // z’s uncle (y) color = BLACK
      {
        if (z == z->parent->left)
        {
          z = z->parent;  // Case 2
          rightRotate(z); // Case 2
        }
        z->parent->color = RBT_BLACK;       // Case 3
        z->parent->parent->color = RBT_RED; // Case 3
        leftRotate(z->parent->parent);      // Case 3
      }
    }
  }
  root->color = RBT_BLACK;
}

/**
 * Creaste a new dynamic TNode with the value passed.
 *
 * @param x Data value to add to node.
 *
 * @return Pointer to new TNode.
 */
template <class T>
TNode<T> *RBT<T>::createNode(T const x)
{
  TNode<T> *temp = new TNode<T>(x, TNIL, TNIL, TNIL, RBT_RED);
  return temp;
}

/**
 * Fixup for the delete function if needed
 */
template <class T>
void RBT<T>::rbDeleteFixUp(TNode<T> *x, TNode<T> *replacedNode)
{
  TNode<T> *w;
  if (replacedNode == root) // Root was deleted and had only one child
  {
    replacedNode->color = RBT_BLACK;
  }
  else //
  {
    while (x != root && x->color == RBT_BLACK)
    {
      if (replacedNode == x->parent->left)
      {
        w = x->parent->right; // w is x’s sibling
        if (w->color == RBT_RED)
        {
          w->color = RBT_BLACK;       //  Case 1
          x->parent->color = RBT_RED; //  Case 1
          leftRotate(x->parent);      //  Case 1
          w = x->parent->right;       //  Case 1
        }
        if (w->left->color == RBT_BLACK && w->right->color == RBT_BLACK)
        {
          w->color = RBT_RED; //  Case 2
          x = x->parent;      //  Case 2
        }
        else
        {
          if (w->right->color == RBT_BLACK)
          {
            w->left->color = RBT_BLACK; //  Case 3
            w->color = RBT_RED;         //  Case 3
            rightRotate(w);             //  Case 3
            w = x->parent->right;       //  Case 3
          }
          w->color = x->parent->color;  //  Case 4
          x->parent->color = RBT_BLACK; //  Case 4
          w->right->color = RBT_BLACK;  //  Case 4
          leftRotate(x->parent);        //  Case 4
          x = root;                     //  Case 4
        }
      }
      else // x== x->parent->right
      {
        w = x->parent->left; // w is x’s sibling
        if (w->color == RBT_RED)
        {
          w->color = RBT_BLACK;       //  Case 1
          x->parent->color = RBT_RED; //  Case 1
          rightRotate(x->parent);     //  Case 1
          w = x->parent->left;        //  Case 1
        }
        if (w->right->color == RBT_BLACK && w->left->color == RBT_BLACK)
        {
          w->color = RBT_RED; //  Case 2
          x = x->parent;      //  Case 2
        }
        else
        {
          if (w->left->color == RBT_BLACK)
          {
            w->right->color = RBT_BLACK; //  Case 3
            w->color = RBT_RED;          //  Case 3
            leftRotate(w);               //  Case 3
            w = x->parent->left;         //  Case 3
          }
          w->color = x->parent->color;  //  Case 4
          x->parent->color = RBT_BLACK; //  Case 4
          w->left->color = RBT_BLACK;   //  Case 4
          rightRotate(x->parent);       //  Case 4
          x = root;                     //  Case 4
        }
      }
    } // end while
    x->color = RBT_BLACK;
  }
}
