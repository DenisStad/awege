#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 denis <denis@Deniss-MBP.fritz.box>
#
# Distributed under terms of the MIT license.

"""
Awege project
"""

import os
import shutil
import projectFile
from engine import Engine
from fileManager import FileManager

class Project:
    """A project"""

    @staticmethod
    def CreateNew(name, path):
        newProject = Project()
        newProject.setPath(path)
        newProject.setName(name)
        # newProject.addModule('render')
        newProject.saveToFile()
        return newProject

    @staticmethod
    def LoadFromProjectFilePath(projectFilePath):
        project = projectFile.CreateProjectFromFile(projectFilePath)
        project.setPath(os.path.dirname(projectFilePath))
        return project

    def __init__(self):
        self.__files = FileManager()

    def setPath(self, path):
        self.__path = path

    def getPath(self):
        return self.__path

    def setName(self, name):
        self.__name = name

    def getName(self):
        return self.__name

    def saveToFile(self):
        projectFile.SaveProjectFile(self)

    def files(self):
        return self.__files



    def addModule(self, name):
        self.copyDefaultModule(name)
        self.__projectFile.addModule(name)

    def copyDefaultModule(self, name):
        dirname = os.path.join(Engine.DefaultModulePath(), name)
        if (os.path.isdir(dirname)):
            targetDirname = os.path.join(self.path, 'modules', name)
            shutil.copytree(dirname, targetDirname)
