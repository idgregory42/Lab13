#if !defined (NULL)
   #define NULL 0
#endif
#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

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
  if(left->isEmpty()) return right;
  if(right->isEmpty()) return left;
  
  T* left_root  = left->getRootItem();
  T* right_root = right->getRootItem();
  
  int comp = (*compare_items)(left_root, right_root);
  
  if(comp < 0)
  {
	  left  = right;
	  right = left;
  }

}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
   if(item == NULL) return;
   
   BinaryTree<T>* left  = bt;
   BinaryTree<T>* right = new BinaryTree<T>(item);
   
   bt = merge(left, right);
   left->destroy();
   right->destroy();
   sze++
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   BinaryTree<T>* left  = bt->detachLeftSubtree();
   BinaryTree<T>* right = bt->detachRightSubtree();
   T* root_item = bt->getRootItem();
   
   bt->destroy();
   
   bt = merge(left, right);
   left->destroy();
   right->destroy();
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
