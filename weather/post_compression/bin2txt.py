#!/usr/bin/python3

import sys

data = open(sys.argv[1], 'rb').read()
binary = ''.join([format(b, 'b') for b in data])
print(binary)
