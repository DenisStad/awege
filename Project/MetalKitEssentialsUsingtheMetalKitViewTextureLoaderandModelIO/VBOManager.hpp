//
//  MeshManager.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef MeshManager_hpp
#define MeshManager_hpp

#include "VertexBufferObject.hpp"
#include <map>
#include <iostream>
typedef std::string String;
#include "Mesh.hpp"

enum MeshDataSourceType {
  MeshDataSourceType_CompiledAssets,
  MeshDataSourceType_File,
  MeshDataSourceType_Network
};

struct MeshIdentifier {
  MeshDataSourceType type;
  String identifierName;
  
  MeshIdentifier(MeshDataSourceType type, String identifierName);
  bool operator==(MeshIdentifier other) const;
  bool operator<(MeshIdentifier other) const;
  
};

struct MeshVBO {
  VertexBufferObject vertexBuffer;
  VertexBufferObject indexBuffer;
};

class VBOManager {
  
public:

  class SharedVBOPointer {
    MeshVBO vbo;
    unsigned int* useCount;
    
    void increaseCount() {
      (*useCount)++;
    }
    
    void decreaseCount() {
      (*useCount)--;
      if (*useCount == 1) {
        VBOManager::SharedManager().destroyVBO(vbo);
      }
    }
    
  public:
    
    SharedVBOPointer()
    {
    }
    
    SharedVBOPointer(MeshVBO vbo)
    :
    useCount(new unsigned int),
    vbo(vbo)
    {
      increaseCount();
    }
    
    SharedVBOPointer(const SharedVBOPointer& pointer)
    :
    useCount(pointer.useCount),
    vbo(pointer.vbo)
    {
      increaseCount();
    }
    
    SharedVBOPointer& operator=(const SharedVBOPointer& pointer)
    {
      useCount = pointer.useCount;
      vbo = pointer.vbo;
      increaseCount();
      return *this;
    }
    
    ~SharedVBOPointer()
    {
      decreaseCount();
    }
    
    MeshVBO get()
    {
      return vbo;
    }
  };
  
private:
  
  std::map<MeshIdentifier, SharedVBOPointer> loadedBuffers;

  Mesh* loadMesh(MeshIdentifier identifier);

private:
  VBOManager();
  VBOManager(const VBOManager&);
  VBOManager& operator=(const VBOManager&);
  ~VBOManager();
  
  MeshVBO loadVBO(const MeshIdentifier identifer);
  void destroyVBO(MeshVBO buffer);
  
public:
  
  static VBOManager& SharedManager();
  
  bool isVBOLoaded(const MeshIdentifier identifer) const;
  
  SharedVBOPointer getVBO(const MeshIdentifier identifier);
  SharedVBOPointer getVBOFromAssets(const String assetName);
  SharedVBOPointer getVBOFromFile(const String filename);
  SharedVBOPointer getVBOFromNetwork(const String url);

};

#endif /* MeshManager_hpp */
