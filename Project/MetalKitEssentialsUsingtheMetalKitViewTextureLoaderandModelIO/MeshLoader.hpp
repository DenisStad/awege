//
//  MeshLoader.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef MeshLoader_hpp
#define MeshLoader_hpp

#include "Mesh.hpp"
#include <iostream>
typedef std::string String;

class MeshLoader {
  
public:
  Mesh* loadMeshFromAssets(String assetName);
  Mesh* loadMeshFromFile(String filename);
  Mesh* loadMeshFromNetwork(String url);
};

#endif /* MeshLoader_hpp */
