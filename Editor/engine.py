#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 denis <denis@Deniss-MBP.fritz.box>
#
# Distributed under terms of the MIT license.

"""
Engine
"""
import os

class Engine:

    @staticmethod
    def EnginePath():
        return os.path.realpath(os.path.join(__file__, '..'))

    @staticmethod
    def DefaultModulePath():
        return os.path.join(Engine.EnginePath(), 'modules')
