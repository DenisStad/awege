#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 denis <denis@Deniss-MBP.fritz.box>
#
# Distributed under terms of the MIT license.

"""

"""

import importPlain
import struct
import binascii
from array import array

def convertToHalfFloat(float32):
    F16_EXPONENT_BITS = 0x1F
    F16_EXPONENT_SHIFT = 10
    F16_EXPONENT_BIAS = 15
    F16_MANTISSA_BITS = 0x3ff
    F16_MANTISSA_SHIFT =  (23 - F16_EXPONENT_SHIFT)
    F16_MAX_EXPONENT =  (F16_EXPONENT_BITS << F16_EXPONENT_SHIFT)

    a = struct.pack('>f',float32)
    b = binascii.hexlify(a)

    f32 = int(b, 16)
    f16 = 0
    sign = (f32 >> 16) & 0x8000
    exponent = ((f32 >> 23) & 0xff) - 127
    mantissa = f32 & 0x007fffff

    if exponent == 128:
        f16 = sign | F16_MAX_EXPONENT
        if mantissa:
            f16 |= (mantissa & F16_MANTISSA_BITS)
    elif exponent > 15:
        f16 = sign | F16_MAX_EXPONENT
    elif exponent > -15:
        exponent += F16_EXPONENT_BIAS
        mantissa >>= F16_MANTISSA_SHIFT
        f16 = sign | exponent << F16_EXPONENT_SHIFT | mantissa
    else:
        f16 = sign
    return f16

def convertToByteList(num, expectedSize):
    byteList = []
    while num > 0:
        byteList.append(num & 0xFF)
        num >>= 8
    #byteList = byteList[::-1]
    if len(byteList) > expectedSize:
        print("ERROR")
    while expectedSize > len(byteList):
        byteList = [0] + byteList

    return bytes(byteList)

def packTwoFloatsIntoHalfFloats(float1, float2):
    float1 = convertToByteList(convertToHalfFloat(float1), 2)
    float2 = convertToByteList(convertToHalfFloat(float2), 2)
    return float1 + float2



def writeVertexData(data, outFile):
    writeSectionHeader(outFile, b'Position|Normal|Tangent|UV')

    positions = data['positions']['data']
    normals = data['normals']['data']
    texCoords = data['texCoords']['data']
    tangents = data['tangents']['data']

    numVerts = struct.pack('I', len(positions))
    outFile.write(numVerts)
    for i in range(0, len(positions)):
        position = positions[i]
        normal = normals[i]
        uv = texCoords[i]
        tangent = tangents[i]

        float_array = []
        float_array.append(position['x'])
        float_array.append(position['y'])
        float_array.append(position['z'])
        float_array.append(normal['x'])
        float_array.append(normal['y'])
        float_array.append(normal['z'])
        float_array.append(tangent['x'])
        float_array.append(tangent['y'])
        float_array.append(tangent['z'])
        float_array = array('f', float_array)
        float_array.tofile(outFile)

        uvs = packTwoFloatsIntoHalfFloats(uv['u'], uv['v'])
        outFile.write(uvs)


def writeFaceData(data, outFile):
    writeSectionHeader(outFile, b'Face')

    faces = data['faces']['data']
    numFaces = struct.pack('I', int(len(faces) / 3))
    outFile.write(numFaces)
    int_array = []
    for face in faces:
        int_array.append(face)
    int_array = array('I', int_array)
    int_array.tofile(outFile)

def writeSectionHeader(outFile, sectionInfo):
    sectionLength = struct.pack('I', len(sectionInfo))
    outFile.write(sectionLength)
    outFile.write(sectionInfo)


data = importPlain.readFile('Output2.json')
outFile = open('./out.test', 'wb')
writeVertexData(data, outFile)
writeFaceData(data, outFile)
outFile.close()
