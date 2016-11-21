#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

#include <memory>
using namespace std;

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS
  if(left->isEmpty())
  {
	  delete left;  //for memory usage
	  return right;
  }

  if(right->isEmpty())
  {
	  delete right; //for memory usage
	  return left;
  }  
  
  //gets left and right root for compare
  T* left_root  = left->getRootItem();
  T* right_root = right->getRootItem();
  
  int comp = (*compare_items)(left_root, right_root);
  
  if(comp < 0) return merge(right, left);  //swap with reverse merge
  
  //get left's left and right
  BinaryTree<T>* lefts_left = left->detachLeftSubtree();   
  BinaryTree<T>* lefts_right = left->detachRightSubtree();
  
  left->attachRightSubtree(lefts_left);  //attach left's left to left's right
  delete lefts_left;  //for memory usage

  if(lefts_right->isEmpty())
  {
	  left->attachLeftSubtree(right);  //attach right to left's left
  }
  else
  {
	  left->attachLeftSubtree(merge(lefts_right, right));  //attach binary tree to left's left
  }
    
  
  delete lefts_right; //for memory usage
  return left;
}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
   BinaryTree<T>* right = new BinaryTree<T>(item);
   BinaryTree<T>* left  = bt;
   bt = merge(left, right);
   sze++;
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   T* root_item = bt->getRootItem();
   BinaryTree<T>* left  = bt->detachLeftSubtree();
   BinaryTree<T>* right = bt->detachRightSubtree();
   
   delete bt; //for memory usage
   bt = merge(left, right);
   sze--;
   return root_item;
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
