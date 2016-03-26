//
//  VertexAttribute.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef VertexAttribute_hpp
#define VertexAttribute_hpp

#include <string>
#include <vector>

class VertexAttribute {
  
public:
  
  enum DataType {
    DataTypeInvalid = 0,
    
    DataType_UChar2 = 1,
    DataType_UChar3 = 2,
    DataType_UChar4 = 3,
    
    DataType_Char2 = 4,
    DataType_Char3 = 5,
    DataType_Char4 = 6,
    
    DataType_UChar2Normalized = 7,
    DataType_UChar3Normalized = 8,
    DataType_UChar4Normalized = 9,
    
    DataType_Char2Normalized = 10,
    DataType_Char3Normalized = 11,
    DataType_Char4Normalized = 12,
    
    DataType_UShort2 = 13,
    DataType_UShort3 = 14,
    DataType_UShort4 = 15,
    
    DataType_Short2 = 16,
    DataType_Short3 = 17,
    DataType_Short4 = 18,
    
    DataType_UShort2Normalized = 19,
    DataType_UShort3Normalized = 20,
    DataType_UShort4Normalized = 21,
    
    DataType_Short2Normalized = 22,
    DataType_Short3Normalized = 23,
    DataType_Short4Normalized = 24,
    
    DataType_Half2 = 25,
    DataType_Half3 = 26,
    DataType_Half4 = 27,
    
    DataType_Float = 28,
    DataType_Float2 = 29,
    DataType_Float3 = 30,
    DataType_Float4 = 31,
    
    DataType_Int = 32,
    DataType_Int2 = 33,
    DataType_Int3 = 34,
    DataType_Int4 = 35,
    
    DataType_UInt = 36,
    DataType_UInt2 = 37,
    DataType_UInt3 = 38,
    DataType_UInt4 = 39,
    
    DataType_Int1010102Normalized = 40,
    DataType_UInt1010102Normalized = 41,
  };
  
private:
  
  std::string name;
  DataType dataType;
  unsigned int byteOffset;
  
public:
  
  VertexAttribute(std::string name, DataType dataType, unsigned int byteOffset);
  
  std::string getName();
  DataType getDataType();
  unsigned int getByteOffset();
  
  static const std::string VertexAttributePositionName;
  static const std::string VertexAttributeNormalName;
  static const std::string VertexAttributeTangentName;
  static const std::string VertexAttributeTexCoordsName;
};

class VertexAttributeFormat {
  
  std::vector<VertexAttribute> attributes;
  size_t byteStride;
  
public:
  
  VertexAttributeFormat(std::vector<VertexAttribute> attributes, unsigned int byteStride);
  size_t getNumberOfAttributes();
  size_t getByteStride();
  std::vector<VertexAttribute> getAttributes();
  
};

#endif /* VertexAttribute_hpp */
