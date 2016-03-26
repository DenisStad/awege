//
//  MeshLoader.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "MeshLoader.hpp"
#include "Data.hpp"
#include "Log.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>


Mesh* MeshLoader::loadMeshFromAssets(String assetName)
{
  DevLogTag("MeshLoader", "Load", assetName, "from assets");
  
  
  constexpr int count = 3 * 4 * 3 * 2;
  auto rawData = new float[count] {
    -1.0, -1.0, 0.0, 1.0,
    -1.0,  1.0, 0.0, 1.0,
    1.0, -1.0, 0.0, 1.0,
    
    1.0, -1.0, 0.0, 1.0,
    -1.0,  1.0, 0.0, 1.0,
    1.0,  1.0, 0.0, 1.0,
    
    -0.0, 0.25, 0.0, 1.0,
    -0.25, -0.25, 0.0, 1.0,
    0.25, -0.25, 0.0, 1.0
    
    
    
    -1.0, -1.0, 0.0, 1.0,
    -1.0,  1.0, 0.0, 1.0,
    1.0, -1.0, 0.0, 1.0,
    
    1.0, -1.0, 0.0, 1.0,
    -1.0,  1.0, 0.0, 1.0,
    1.0,  1.0, 0.0, 1.0,
    
    -0.0, 0.25, 0.0, 1.0,
    -0.25, -0.25, 0.0, 1.0,
    0.25, -0.25, 0.0, 1.0
  };
  
  Data data;
  data.setData((Data::Byte*) rawData, count * sizeof(float));
  
  std::vector<VertexAttribute> attributes;
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributePositionName, VertexAttribute::DataType_Float3, 0));
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributeNormalName, VertexAttribute::DataType_Float3, 12));
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributeTexCoordsName, VertexAttribute::DataType_Half2, 24));
  VertexAttributeFormat attributeFormat(attributes, 28);
  
  auto mesh = new Mesh();
  mesh->setVertexData(data, attributeFormat);
  return mesh;
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}


Mesh* MeshLoader::loadMeshFromFile(String filename)
{
  DevLogTag("MeshLoader", "Load", filename, "from file");
  
  std::ifstream file;
  file.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    
    auto mesh = new Mesh();
    
    std::streampos size = file.tellg();
    
    file.seekg (0, std::ios::beg);
    
    while (file.tellg() < size) {
      unsigned int sectionLength = 0;
      file.read((char*) &sectionLength, sizeof(int));
      
      DevLogTag("MeshLoader", "Section length", sectionLength);
      
      
      char sectionHeader[sectionLength + 1];
      file.read(sectionHeader, sectionLength);
      sectionHeader[sectionLength] = '\0';
      
      DevLogTag("MeshLoader", "Section Data Type", sectionHeader);
      
      std::vector<std::string> types;
      split(sectionHeader, '|', types);
      
      bool isFaceData = false;
      
      unsigned int dataPointSize = 0;
      for (auto type : types) {
        if (type == "Position") {
          dataPointSize += 3;
        } else if (type == "Tangent") {
          dataPointSize += 3;
        } else if (type == "Normal") {
          dataPointSize += 3;
        } else if (type == "UV") {
          dataPointSize += 1;
        } else if (type == "Face") {
          isFaceData = true;
          dataPointSize += 3;
        }
      }
      
      
      unsigned int dataLength = 0;
      file.read((char*) &dataLength, sizeof(unsigned int));
      
      
      DevLogTag("MeshLoader", "Num data points", dataLength);
      DevLogTag("MeshLoader", "Data point size in bytes", dataPointSize);
      
      if (isFaceData) {
        auto rawData = new unsigned int[dataLength * dataPointSize];
        file.read((char*) rawData, dataLength * dataPointSize * sizeof(unsigned int));
        
        Data data;
        data.setData((Data::Byte*) rawData, dataLength * dataPointSize * sizeof(unsigned int));
        mesh->setFaceData(data);
      } else {
        auto rawData = new float[dataLength * dataPointSize];
        file.read((char*) rawData, dataLength * dataPointSize * sizeof(float));
        
//        for (int i = 0; i < 28; i++) {
//          DevLog(rawData[i]);
//        }
//        
//        for (int i = 0; i < 14; i++) {
////          DevLog((int)rawData[i * 7 + 6]);
////          short a = (rawData[i * 7 + 6]);
//          DevLog(rawData[i * 7 + 0], rawData[i * 7 + 1], rawData[i * 7 + 2]);
//          const char* beg = reinterpret_cast<const char*>(&rawData[i * 7 + 6]);
//          std::bitset<16> b(*(beg + 0));
//          DevLog(b);
//        }
        
        Data data;
        data.setData((Data::Byte*) rawData, dataLength * dataPointSize * sizeof(float));
        
        std::vector<VertexAttribute> attributes;
        attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributePositionName, VertexAttribute::DataType_Float3, 0));
        attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributeNormalName, VertexAttribute::DataType_Float3, 12));
            attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributeTexCoordsName, VertexAttribute::DataType_Half2, 24));
            VertexAttributeFormat attributeFormat(attributes, 28);
//        VertexAttributeFormat attributeFormat(attributes, 24);
        
        mesh->setVertexData(data, attributeFormat);
      }
    }
    
    file.close();

    return mesh;
  }
  
  
  return new Mesh();
}

Mesh* MeshLoader::loadMeshFromNetwork(String url)
{
  DevLogTag("Render", "Load", url, "from url");
  return new Mesh();
}