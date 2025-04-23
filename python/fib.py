#!/usr/bin/python3
# from: https://www.mikrocontroller.net/topic/577155
# -*- coding: UTF-8 -*-
# vim: fileencoding=utf-8: ts=4: sw=4: expandtab:

value1, value2 = 0, 1

for i in range(383):
    value1, value2 = value2, value1 + value2
    print(f'┃{value2:080}┃')

