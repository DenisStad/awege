#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 denis <denis@Deniss-MBP.fritz.box>
#
# Distributed under terms of the MIT license.

"""
Create a new project
"""

from project import Project

projectPath = '../test/'
Project.CreateNew('test', projectPath)

from project import Project

projectPath = '../test/test.awege'
project = Project.LoadFromProjectFilePath(projectPath)
print(project)
