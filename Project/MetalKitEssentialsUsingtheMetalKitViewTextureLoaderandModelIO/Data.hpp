//
//  Data.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 06/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Data_hpp
#define Data_hpp

class Data {
  
public:
  
  typedef char Byte;
  
private:
  
  Byte* data;
  unsigned int byteCount;
  
public:
  
  Data();
  ~Data();
  
  void releaseData();
  void setData(Byte* data, unsigned int byteCount);
  
  Byte* const getData();
  const unsigned int getByteCount() const;
};

#endif /* Data_hpp */
