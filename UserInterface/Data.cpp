//
//  Data.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
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