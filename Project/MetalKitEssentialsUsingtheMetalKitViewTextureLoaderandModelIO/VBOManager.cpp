//
//  MeshManager.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "VBOManager.hpp"
#include "MeshLoader.hpp"
#include "Log.hpp"

MeshIdentifier::MeshIdentifier(MeshDataSourceType type, String identifierName)
:
type(type),
identifierName(identifierName)
{
}

bool MeshIdentifier::operator==(const MeshIdentifier other) const
{
  DevLog("Equal called");
  return type == other.type && identifierName == other.identifierName;
}

bool MeshIdentifier::operator<(MeshIdentifier other) const
{
  if (type == other.type) {
    return identifierName < other.identifierName;
  }
  return type < other.type;
}

VBOManager& VBOManager::SharedManager()
{
  static VBOManager sharedInstance;
  return sharedInstance;
}

VBOManager::VBOManager()
{
}

VBOManager::~VBOManager()
{
}

bool VBOManager::isVBOLoaded(const MeshIdentifier identifer) const
{
  auto position = loadedBuffers.find(identifer);
  return position != loadedBuffers.end();
}

VBOManager::SharedVBOPointer VBOManager::getVBO(MeshIdentifier identifier)
{
  if (isVBOLoaded(identifier)) {
    return loadedBuffers[identifier];
  }
  
  MeshVBO vbo = loadVBO(identifier);
  SharedVBOPointer pointer(vbo);
  loadedBuffers[identifier] = pointer;
  return pointer;
}

MeshVBO VBOManager::loadVBO(MeshIdentifier identifier)
{
  MeshLoader loader;
  Mesh *mesh;
  switch (identifier.type) {
    case MeshDataSourceType_CompiledAssets:
      mesh = loader.loadMeshFromAssets(identifier.identifierName);
      break;
    case MeshDataSourceType_File:
      mesh = loader.loadMeshFromFile(identifier.identifierName);
      break;
    case MeshDataSourceType_Network:
      mesh = loader.loadMeshFromNetwork(identifier.identifierName);
      break;
  }
  auto vertexBuffer = VertexBufferObject::CreateWithData(mesh->getVertexData());
  auto faceBuffer = VertexBufferObject::CreateWithData(mesh->getFaceData());
  mesh->getVertexData().releaseData();
  mesh->getFaceData().releaseData();
  
  MeshVBO vbo;
  vbo.vertexBuffer = vertexBuffer;
  vbo.indexBuffer = faceBuffer;
  return vbo;
}

void VBOManager::destroyVBO(MeshVBO buffer)
{
  buffer.vertexBuffer.deallocateBuffer();
  buffer.indexBuffer.deallocateBuffer();
}

VBOManager::SharedVBOPointer VBOManager::getVBOFromAssets(String assetName)
{
  return getVBO(MeshIdentifier(MeshDataSourceType_CompiledAssets, assetName));
}

VBOManager::SharedVBOPointer VBOManager::getVBOFromFile(String filename)
{
  return getVBO(MeshIdentifier(MeshDataSourceType_File, filename));
}

VBOManager::SharedVBOPointer VBOManager::getVBOFromNetwork(String url)
{
  return getVBO(MeshIdentifier(MeshDataSourceType_Network, url));
}