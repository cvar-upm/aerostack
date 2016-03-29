/*!*****************************************************************************
 *  \file    TreeNode.h
 *  \brief   Definition of the class TreeNode in the file
 *       TreeNode.cpp .
 *   
 *  \author  Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *       Released under license BSD-3.
 ********************************************************************************/
#ifndef TREE_NODE_H
#define TREE_NODE_H
 
#include <iostream>
#include <cstdlib>
#include <vector>

/*!***************************************************************************
 *  \class TreeNode
 *  \brief This class represents an abstraction of a non-binary tree.
 *****************************************************************************/
 template <class T> 
 class TreeNode
 {
 private:
  T root;
  std::vector<TreeNode<T> > children;
 public:
  TreeNode();
  ~TreeNode();
 public:
  T * getNode();
  std::vector<TreeNode<T> > * getChildren();
  int setNode(T treeNode);
  int setChildren(std::vector<TreeNode<T> > children);
  bool empty();
 };
 #endif
 
//IMPORTANT:
//The implementation of tthe following functions must be in this header file, if not, 
//the compiler will no be able to link the instantiation of treeNode<Task>
//with their proper source code.

//Constructor & destructor
template <class T>
TreeNode<T>::TreeNode(){
  
}

template <class T>
TreeNode<T>::~TreeNode(){
  //TO DO
}
/*!************************************************************************
*  \brief  This method gets the tree's root. 
*  \return A pointer to the tree's root.
*************************************************************************/
template <class T>
T * TreeNode<T>::getNode(){
  T * rootPointer = &root;
  return rootPointer;
}
/*!************************************************************************
*  \brief  This method sets the tree's root. 
*  \return 0 if finished without errors, !=0 in other case.
*************************************************************************/
template <class T>
int TreeNode<T>::setNode(T tree_node){
  root = tree_node;
  return 0;
}
/*!************************************************************************
*  \brief  This method gets the tree's children. 
*  \return A pointer to a vector of the tree's children.
*************************************************************************/
template <class T>
std::vector<TreeNode<T> > * TreeNode<T>::getChildren(){   
  std::vector <TreeNode<T>> *child = &children;
  return child;
}
/*!************************************************************************
*  \brief  This method sets the tree's children. 
*  \return 0 if finished without errors, !=0 in other case.
*************************************************************************/
template <class T>
int TreeNode<T>::setChildren(std::vector<TreeNode<T> > tree_children){
  children = tree_children;
  return 0;
}
/*!************************************************************************
*  \brief  This method check whether the tree is empty or it is not. 
*  \return True if the tree is empty, false in other case.
*************************************************************************/
template <class T>
bool TreeNode<T>::empty(){
  return root == NULL;
}