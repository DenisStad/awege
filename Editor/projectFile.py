#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 denis <denis@Deniss-MBP.fritz.box>
#
# Distributed under terms of the MIT license.

"""
Manipulate project file
"""

import json
import os
import project
from trackedFile import TrackedFile


def makeProjectFilename(project):
    return os.path.join(project.getPath(), project.getName() + '.awege')

def makeProjectData(project):
    data = {}
    data['name'] = project.getName()
    data['files'] = []
    for trackedFile in project.files().getFilesList():
        data['files'].append(trackedFile.toDictionary())
    return data

def createProjectFromData(data):
    loadedProject = project.Project()
    loadedProject.setName(data['name'])
    files = []
    for fileData in data['files']:
        trackedFile = TrackedFile.FromDictionary(fileData)
        files.append(trackedFile)
    loadedProject.files().setFilesList(files)
    return loadedProject

def SaveProjectFile(project):
    data = makeProjectData(project)

    try:
        os.makedirs(project.getPath())
    except OSError:
        pass

    fileContents = json.dumps(data, sort_keys=True, indent=2)

    projectFile = open(makeProjectFilename(project), 'w')
    projectFile.write(fileContents)
    projectFile.close()

def CreateProjectFromFile(filename):
    projectFile = open(filename, 'r')
    fileContents = projectFile.read()
    projectFile.close()

    data = json.loads(fileContents)
    return createProjectFromData(data)
