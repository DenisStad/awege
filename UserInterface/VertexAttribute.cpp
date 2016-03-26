//
//  VertexAttribute.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "VertexAttribute.hpp"

VertexAttribute::VertexAttribute(std::string name, DataType dataType, unsigned int byteOffset)
:
name(name),
dataType(dataType),
byteOffset(byteOffset)
{
}

const std::string VertexAttribute::VertexAttributePositionName = "Position";
const std::string VertexAttribute::VertexAttributeNormalName = "Normal";
const std::string VertexAttribute::VertexAttributeTangentName = "Tangent";
const std::string VertexAttribute::VertexAttributeTexCoordsName = "TexCoords";

std::string VertexAttribute::getName()
{
  return name;
}

VertexAttribute::DataType VertexAttribute::getDataType()
{
  return dataType;
}

unsigned int VertexAttribute::getByteOffset()
{
  return byteOffset;
}

VertexAttributeFormat::VertexAttributeFormat(std::vector<VertexAttribute> attributes, unsigned int byteStride)
:
attributes(attributes),
byteStride(byteStride)
{
  
}

size_t VertexAttributeFormat::getNumberOfAttributes()
{
  return attributes.size();
}

std::vector<VertexAttribute> VertexAttributeFormat::getAttributes()
{
  return attributes;
}
size_t VertexAttributeFormat::getByteStride()
{
  return byteStride;
}