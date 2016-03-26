#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 denis <denis@Deniss-MBP.fritz.box>
#
# Distributed under terms of the MIT license.

"""
Exports vertex data from blender
"""

import sys
import os
import bpy
from array import array
import copy
import savePlain

class DataWriter:

    def writeCleanMesh(self, cleanMesh):
        self.data = {}
        self.writeVertexData(cleanMesh)
        self.writeFaceData(cleanMesh)

        savePlain.writeFile("Output.json", self.data)

    def writeVertexData(self, cleanMesh):
        self.data['positions'] = { 'numberOfDataPoints': cleanMesh.numberOfVertices(), 'data': [] }
        self.data['normals'] = { 'numberOfDataPoints': cleanMesh.numberOfVertices(), 'data': [] }
        self.data['texCoords'] = { 'numberOfDataPoints': cleanMesh.numberOfVertices(), 'data': [] }
        verticesData = cleanMesh.verticesData()
        for vertex in verticesData:
            self.data['positions']['data'].append({ 'x': vertex.position['x'], 'y': vertex.position['y'], 'z': vertex.position['z'] })
            self.data['normals']['data'].append({ 'x': vertex.normal['x'], 'y': vertex.normal['y'], 'z': vertex.normal['z'] })
            self.data['texCoords']['data'].append({ 'u': vertex.uv.u, 'v': vertex.uv.v })

    def writeFaceData(self, cleanMesh):
        self.data['faces'] = { 'numberOfDataPoints': cleanMesh.numberOfFaces(), 'data': [] }
        for face in cleanMesh.facesData():
            for index in face.indices:
                self.data['faces']['data'].append(index)

class Obj:
    pass

class CleanMesh:

    def readMesh(self, mesh):
        self.mesh = mesh
        self.copyVertices()
        self.copyFacesAndUVs()
        self.cleanUV()
        self.triangulate()
        #self.printData()

    def copyVertices(self):
        vertices = self.mesh.vertices
        self.originalVertices = []
        index = 0
        for vertex in vertices:
            newVertex = Obj()
            newVertex.index = index
            newVertex.position = { 'x': vertex.co.x, 'y': vertex.co.y, 'z': vertex.co.z }
            newVertex.normal = { 'x': vertex.normal.x, 'y': vertex.normal.y, 'z': vertex.normal.z }
            newVertex.furtherIndicesOfVerticesWithSamePosition = []
            self.originalVertices.append(newVertex)
            index += 1

    def copyFacesAndUVs(self):
        faces = list(self.mesh.tessfaces)
        uvs = mesh.uv_layers[0].data

        self.originalFaces = []

        polygons = self.mesh.polygons
        for face in polygons:
            newFace = Obj()
            newFace.vertexIndices = []
            for vertexIndex, uvIndex in zip(face.vertices, face.loop_indices):
                newIndex = Obj()
                newIndex.vertexIndex = vertexIndex
                newUV = Obj()
                newUV.u = uvs[uvIndex].uv[0]
                newUV.v = uvs[uvIndex].uv[1]
                newIndex.uv = newUV
                newFace.vertexIndices.append(newIndex)
            self.originalFaces.append(newFace)

    def cleanUV(self):
        self.vertices = list(self.originalVertices)
        self.faces = []

        for face in self.originalFaces:
            newFace = Obj()
            newFace.indices = []
            for vertexIndex in face.vertexIndices:
                uv = vertexIndex.uv
                newIndex = self.getIndexWithSamePositionAndSameUV(vertexIndex, uv)
                newFace.indices.append(newIndex)
            self.faces.append(newFace)

    def getIndexWithSamePositionAndSameUV(self, vertexIndex, uv):
        index = vertexIndex.vertexIndex
        vertex = self.vertices[index]
        if self.setUVIfDoesntExist(vertex, uv):
            return index

        samePositionVertices = self.getVertexAndFurtherVertices(vertex)
        for vertexWithSamePosition in samePositionVertices:
            if self.isUVSame(vertexWithSamePosition.uv, uv):
                return vertexWithSamePosition.index

        return self.appendVertexWithNewUVToVertices(vertex, uv)

    def setUVIfDoesntExist(self, vertex, uv):
        if not hasattr(vertex, 'uv'):
            vertex.uv = uv
            return True
        return False
                
    def getVertexAndFurtherVertices(self, vertex):
        vertices = []
        vertices.append(vertex)
        for index in vertex.furtherIndicesOfVerticesWithSamePosition:
            vertices.append(self.vertices[index])
        return vertices

    def isUVSame(self, uv1, uv2):
        return abs(uv1.u - uv2.u) + abs(uv1.v - uv2.v) < 0.0001

    def appendVertexWithNewUVToVertices(self, vertex, uv):
        index = len(self.vertices)
        newVertex = Obj()
        newVertex.index = index
        newVertex.position = { 'x': vertex.position['x'], 'y': vertex.position['y'], 'z': vertex.position['z'] }
        newVertex.normal = { 'x': vertex.normal['x'], 'y': vertex.normal['y'], 'z': vertex.normal['z'] }
        newVertex.uv = uv
        newVertex.furtherIndicesOfVerticesWithSamePosition = []
        self.vertices.append(newVertex)
        vertex.furtherIndicesOfVerticesWithSamePosition.append(index)
        return index

    def triangulate(self):
        newFaces = []
        for face in self.faces:
            if len(face.indices) is 3:
                newFace = Obj()
                newFace.indices = []
                newFace.indices.append(face.indices[0])
                newFace.indices.append(face.indices[1])
                newFace.indices.append(face.indices[2])
                newFaces.append(newFace)
            else:
                newFace = Obj()
                newFace.indices = []
                newFace.indices.append(face.indices[0])
                newFace.indices.append(face.indices[1])
                newFace.indices.append(face.indices[2])
                newFaces.append(newFace)

                newFace = Obj()
                newFace.indices = []
                newFace.indices.append(face.indices[2])
                newFace.indices.append(face.indices[3])
                newFace.indices.append(face.indices[0])
                newFaces.append(newFace)

        self.faces = newFaces

    def printOriginalData(self):
        for vertex in self.originalVertices:
            print(vertex.index)
            print(vertex.position)
            print(vertex.normal)
        for face in self.originalFaces:
            indices = []
            for index in face.vertexIndices:
                indices.append(index.vertexIndex)
            for index in face.vertexIndices:
                indices.append((index.uv.u, index.uv.v))
            print(indices)

    def printData(self):
        for vertex in self.vertices:
            print(vertex.index)
            print(vertex.position)
            print(vertex.normal)
            if hasattr(vertex, 'uv'):
                print((vertex.uv.u, vertex.uv.v))
        for face in self.faces:
            print(face.indices)

    def numberOfVertices(self):
        return int(len(self.vertices))

    def numberOfFaces(self):
        return int(len(self.faces))

    def verticesData(self):
        return self.vertices

    def facesData(self):
        return self.faces


#print(dir(bpy.data.meshes[0]))
#for i in bpy.context.scene.objects: i.select = False
#
#me_ob.select = True
#bpy.ops.objcet.mode_set(mode='EDIT')
#bpy.ops.mesh.select_all(action='SELECT')
#bpy.ops.mesh.quads_convert_to_tris
#indices = bpy.data.meshes[0].indices
#mesh.update(True, True)


mesh = bpy.data.meshes[0]
mesh.calc_tessface()

#print(dir(mesh.uv_textures[0].data[0].image.filepath))
#print(mesh.uv_textures[0].data[0].image.filepath_from_user())
#print(mesh.materials[0].name)

cleanMesh = CleanMesh()
cleanMesh.readMesh(mesh)


dataWriter = DataWriter()
dataWriter.writeCleanMesh(cleanMesh)
