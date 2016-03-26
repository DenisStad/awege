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

def writeFile(data, filename):
    contents = json.dumps(data, indent=2, sort_keys=True)
    file = open(filename, "w")
    file.write(contents)
    file.close()
