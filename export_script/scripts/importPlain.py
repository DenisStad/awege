#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 denis <denis@Deniss-MBP.fritz.box>
#
# Distributed under terms of the MIT license.

"""

"""

import json

def readFile(filename):
    file = open(filename, "r")
    contents = file.read()
    file.close()

    return json.loads(contents)
