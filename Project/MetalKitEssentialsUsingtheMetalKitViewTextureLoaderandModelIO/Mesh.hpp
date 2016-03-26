//
//  Mesh.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include "Data.hpp"
#include <vector>
#include "VertexAttributes.hpp"

class Mesh {
  
private:
  
  Data vertexData;
  Data faceData;
  VertexAttributeFormat vertexAttributeFormat;
  
public:
  
  Mesh();
  
  void setVertexData(Data data, VertexAttributeFormat vertexAttributeFormat);
  Data& getVertexData();
  
  void setFaceData(Data data);
  Data& getFaceData();
  
};

#endif /* Mesh_hpp */
