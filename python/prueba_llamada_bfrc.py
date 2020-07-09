#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sat Jul  4 19:49:36 2020

@author: jc
"""

import os


comando = "./bfrc -f image_2.png"
salida = os.popen(comando).read()

vec_entrada = salida.split(":")

print (salida)

if (vec_entrada[0] == 'Ok'):
    print( vec_entrada[1] )

