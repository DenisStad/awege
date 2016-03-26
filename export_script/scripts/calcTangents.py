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
import savePlain
import math


def subtractVectors(v1, v2):
    return { 'x': v1['x'] - v2['x'], 'y': v1['y'] - v2['y'], 'z': v1['z'] - v2['z'] }

def normalizeVector(v):
    length = v['x'] * v['x'] + v['y'] * v['y'] + v['z'] * v['z']
    length = math.sqrt(length)
    return { 'x': v['x']/length, 'y': v['y']/length, 'z': v['z']/length }

data = importPlain.readFile('Output.json')

faces = data['faces']['data']
vertices = data['positions']['data']
texCoords = data['texCoords']['data']

data['tangents'] = { 'data': [], 'numberOfDataPoints': len(vertices) }
for v in vertices:
    data['tangents']['data'].append({ 'x': 0, 'y': 0, 'z': 0 })
tangents = data['tangents']['data']

for i in range(0, len(faces), 3):
    i0 = faces[i+0]
    i1 = faces[i+1]
    i2 = faces[i+2]

    v0 = vertices[i0]
    v1 = vertices[i1]
    v2 = vertices[i2]

    t0 = texCoords[i0]
    t1 = texCoords[i1]
    t2 = texCoords[i2]

    dU1 = t1['u'] - t0['u']
    dV1 = t1['v'] - t0['v']
    dU2 = t2['u'] - t0['u']
    dV2 = t2['v'] - t0['v']

    f = 1.0 / (dU1 * dV2 - dU2 * dV1)

    e1 = subtractVectors(v1, v0)
    e2 = subtractVectors(v2, v0)

    tx = f * (dV2 * e1['x'] - dV1 * e2['x'])
    ty = f * (dV2 * e1['y'] - dV1 * e2['y'])
    tz = f * (dV2 * e1['z'] - dV1 * e2['z'])

    #btx = f * (-dU2 * e1['x'] - dU1 * e2['x'])
    #bty = f * (-dU2 * e1['y'] - dU1 * e2['y'])
    #btz = f * (-dU2 * e1['z'] - dU1 * e2['z'])

    tangents[i0]['x'] += tx
    tangents[i0]['y'] += ty
    tangents[i0]['z'] += tz

    tangents[i1]['x'] += tx
    tangents[i1]['y'] += ty
    tangents[i1]['z'] += tz

    tangents[i2]['x'] += tx
    tangents[i2]['y'] += ty
    tangents[i2]['z'] += tz

for i in range(0, len(data['tangents']['data'])):
    data['tangents']['data'][i] = normalizeVector(data['tangents']['data'][i])

savePlain.writeFile(data, "Output2.json")
