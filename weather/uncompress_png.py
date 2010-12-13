#!/usr/bin/python

# given base and diff images, decompress and output as png

import sys
from PIL import Image, ImageChops

base = Image.open(sys.argv[1]).convert('RGB')
src = Image.open(sys.argv[2]).convert('RGB')

out = ImageChops.add(src, base)
out.save('uncompressed.png')

