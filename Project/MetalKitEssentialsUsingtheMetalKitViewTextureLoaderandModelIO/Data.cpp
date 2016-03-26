//
//  Data.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 06/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Data.hpp"

Data::Data()
:
data(nullptr),
byteCount(0)
{
}

Data::~Data()
{
}

void Data::setData(Byte* data, unsigned int byteCount)
{
  releaseData();
  
  this->data = data;
  this->byteCount = byteCount;
}

Data::Byte* const Data::getData()
{
  return data;
}

const unsigned int Data::getByteCount() const
{
  return byteCount;
}

void Data::releaseData()
{
  if (data != nullptr) {
    delete[] data;
    data = nullptr;
  }
  byteCount = 0;
}