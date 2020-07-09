#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jul  4 19:49:36 2020

@author: jc
"""

import os
import urllib
from selenium import webdriver
import time 

driver = webdriver.Firefox(executable_path = '/home/jc/Source/Script/python/selenium01/geckodriver')

driver.get('http://localhost/spc2/demo.php')


url_img = driver.find_element_by_id("image").get_attribute("src")
vec = url_img.split('/')
file_name = vec[ len(vec) - 1 ]

urllib.request.urlretrieve(url_img, file_name)


comando = "./bfrc -f " + file_name
salida = os.popen(comando).read()
vec_entrada = salida.split(":")

if (vec_entrada[0] == 'Ok'):
    valor = vec_entrada[1]
    time.sleep(5)
    input_text = driver.find_element_by_name("input")
    input_text.send_keys(valor)
    time.sleep(5)
    button_send = driver.find_element_by_name("submit")
    button_send.click()
    time.sleep(5)
    driver.close()
else:
    time.sleep(5)
    print (salida)
    
#    driver.close()


