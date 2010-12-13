#!/usr/bin/python

# compute a simple diff image from base and source images, and output as png

import sys
from PIL import Image, ImageChops

base = Image.open(sys.argv[1]).convert('RGB')
src = Image.open(sys.argv[2]).convert('RGB')

out = ImageChops.subtract(src, base)
out.save('compressed.png')

