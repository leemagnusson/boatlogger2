#!/usr/bin/python3

import sys

txt = open(sys.argv[1], 'r').read()
data = ''.join([chr(int(txt[i:i+8], 2)) for i in range(0, len(txt), 8)])
sys.stdout.write(data)
