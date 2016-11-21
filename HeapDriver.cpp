#include "HeapArray.h"
#include "HeapSkew.h"
#include "PQHeap.h"
#include "CD.h"
using CSC2110::CD;
#include "Text.h"
using CSC2110::String;
using CSC2110::String;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include <memory>
#include <iostream>
using namespace std;

void deleteCDs(auto_ptr< ListArray<CD> > list)
{
   unique_ptr< ListArrayIterator<CD> > iter(list->iterator());

   while(iter->hasNext())
   {
      CD* cd(iter->next());
      delete cd;
   }
   //delete iter;
}

int main()
{
   auto_ptr<ListArray<CD> > cds(CD::readCDs("cds.txt"));
   int num_items = cds->size();
   cout << num_items << endl;

while(true)
{
   unique_ptr< HeapSkew<CD> > sh(new HeapSkew<CD>(&CD::compare_items));

   unique_ptr< ListArrayIterator<CD> > iter(cds->iterator());
   
   while(iter->hasNext())
   {
      CD* cd = (iter->next());
      sh->heapInsert(cd);
   }
   //delete iter;

   while(!(sh->heapIsEmpty()))
   {
      CD* cd(sh->heapRemove());
      //cd->displayCD();
   }

   //delete sh;
}
   deleteCDs(cds);
   //delete cds;

   return 0;
}
