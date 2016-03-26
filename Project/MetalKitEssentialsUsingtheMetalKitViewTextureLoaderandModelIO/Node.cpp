//
//  Node.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Node.hpp"

/*
void Engine::Node::setParent(std::shared_ptr<Node> parent)
{
  this->parent = parent;
}

void Engine::Node::addChild(std::shared_ptr<Node> node)
{
  node->removeFromParent();
  children.insert(node);
  node->setParent(shared_from_this());
}

void Engine::Node::removeChild(std::shared_ptr<Node> node)
{
  node->setParent(std::shared_ptr<Node>());
  children.erase(node);
}

void Engine::Node::removeChildren()
{
  std::set<std::shared_ptr<Node>>::iterator it = children.begin();
  for (; it != children.end(); ++it) {
    (*it)->setParent(std::shared_ptr<Node>());
  }
  children.clear();
}

void Engine::Node::removeFromParent()
{
  if (auto p = parent.lock()) {
    p->removeChild(shared_from_this());
  }
}

void Engine::Node::appendToParent(std::shared_ptr<Node> node)
{
  node->addChild(shared_from_this());
}
*/