//
//  LinkedList.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 05/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

template <typename T>
class LinkedListItem {
  
  T* previousItem;
  T* nextItem;
  
public:
  LinkedListItem();
};


template <typename T>
class LinkedList {
  
  LinkedListItem<T>* firstItem;
  LinkedListItem<T>* lastItem;
  
public:
  
  LinkedList();
  void push_back(T const & item);
  
};




template <typename T>
LinkedListItem<T>::LinkedListItem()
:
previousItem(nullptr),
nextItem(nullptr)
{
}

template <typename T>
LinkedList<T>::LinkedList()
:
firstItem(nullptr),
lastItem(nullptr)
{
}

template <typename T>
void LinkedList<T>::push_back(T const & item)
{
  if (lastItem == nullptr) {
    firstItem = item;
    lastItem = item;
  } else {
    auto oldLast = lastItem;
    lastItem = item;
    oldLast->nextItem = item;
    item->previousItem = oldLast;
    item->nextItem = nullptr;
  }
}

#endif /* LinkedList_hpp */
