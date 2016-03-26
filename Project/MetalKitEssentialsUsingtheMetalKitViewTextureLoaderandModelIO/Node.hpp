//
//  Node.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <set>
#include "LinkedList.hpp"

namespace Engine {

template <class T>
class Node : public std::enable_shared_from_this<T> {

  typedef std::set<std::shared_ptr<T>> ChildContainerType;
//  typedef LinkedList<std::shared_ptr<T>> ChildContainerType;

  std::weak_ptr<T> parent;
  ChildContainerType children;

  void setParent(std::shared_ptr<T> parent)
  {
    this->parent = parent;
  }

public:

  void addChild(std::shared_ptr<T> node)
  {
    node->removeFromParent();
    children.insert(node);
    node->setParent(T::shared_from_this());
  }

  void removeChild(std::shared_ptr<T> node)
  {
    node->setParent(std::shared_ptr<T>());
    children.erase(node);
  }

  void removeChildren()
  {
    typename std::set<std::shared_ptr<T>>::iterator it = children.begin();
    for (; it != children.end(); ++it) {
      (*it)->setParent(std::shared_ptr<Node>());
    }
    children.clear();
  }

  void removeFromParent()
  {
    if (auto p = parent.lock()) {
      p->removeChild(T::shared_from_this());
    }
  }

  void appendToParent(std::shared_ptr<T> node)
  {
    node->addChild(T::shared_from_this());
  }


  typedef typename ChildContainerType::iterator iterator;
  typedef typename ChildContainerType::const_iterator const_iterator;
  iterator begin() { return children.container.begin(); }
  const_iterator begin() const { return children.container.begin(); }
  iterator end() { return children.container.end(); }
  const_iterator end() const { return children.const_container.end(); }
};

}

#endif /* Node_hpp */
