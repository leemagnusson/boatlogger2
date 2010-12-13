#!/usr/bin/python

# generate an image using the most common pixel values from among all
# input images; all input images must be of the same type and
# dimensions

import sys
import Image
import itertools
import operator


def most_common(L):
    # get an iterable of (item, iterable) pairs
    SL = sorted((x, i) for i, x in enumerate(L))
    # print 'SL:', SL
    groups = itertools.groupby(SL, key=operator.itemgetter(0))
    # auxiliary function to get "quality" for an item
    def _auxfun(g):
        item, iterable = g
        count = 0
        min_index = len(L)
        for _, where in iterable:
            count += 1
            min_index = min(min_index, where)
            # print 'item %r, count %r, minind %r' % (item, count, min_index)
        return count, -min_index
    # pick the highest-count/earliest item
    return max(groups, key=_auxfun)[0]


ident = Image.open(sys.argv[1])
mode = ident.mode
(w,h) = ident.size

ident = ident.convert('RGB')
inputs = [ident] + [Image.open(f).convert('RGB') for f in sys.argv[2:]]

output = Image.new('RGB', (w,h))

for x in range(0, w):
    for y in range(0, h):
        pixels = [im.getpixel((x,y)) for im in inputs]
#        print repr(pixels)
        winner = most_common(pixels)
#        print repr(winner)
        output.putpixel((x,y), winner)


output.convert(mode)
output.save('out.png')
