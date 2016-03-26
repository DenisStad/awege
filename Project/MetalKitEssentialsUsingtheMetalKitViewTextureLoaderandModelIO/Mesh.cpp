//
//  Mesh.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh()
:
vertexAttributeFormat(VertexAttributeFormat(std::vector<VertexAttribute>(), 0))
{
  
}

void Mesh::setVertexData(Data data, VertexAttributeFormat vertexAttributeFormat)
{
  this->vertexData = data;
  this->vertexAttributeFormat = vertexAttributeFormat;
}

void Mesh::setFaceData(Data data)
{
  this->faceData = data;
}

Data& Mesh::getVertexData()
{
  return vertexData;
}

Data& Mesh::getFaceData()
{
  return faceData;
}