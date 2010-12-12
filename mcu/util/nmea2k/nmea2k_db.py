

# maintain a dictionary of all of the item boxes
# import sys
# import xml.etree.ElementTree as etree

# tree = etree.parse(sys.argv[1])
# root = tree.find('PGNs')

# def xml_to_dict(el):
#     return { c.tag: c if list(c) else c.text for c in list(el)}

# d = {}
# for pgninfo in root:
#     x = xml_to_dict(pgninfo)
#     d[x['PGN']] = x
#     if 'Fields' in x:
#         f = xml_to_dict(x['Fields'])
#         d[x['PGN']]['Fields'] = f


    
# print(d)

import nmea2k
import re
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-n",type="int",dest="num_lines",default=100000)
parser.add_option("-d",dest="print_dict",action="store_true",default=False)
(opts,args) = parser.parse_args()

filename = args[0]

def bytetohex(s):
    return(' '.join(["{:02X}".format(c) for c in s]))

def print_message(m):
    if (opts.print_dict):
        print(m)
    elif(m):
        print("""pgn: {pgn}
description: {description}
raw: {}
fields: {fields}
header: {header}
""".format(bytetohex(m['raw']),**m))


n2k = nmea2k.NMEA2K(print_message)

i = 0
with open(filename,encoding='ascii',errors='ignore') as f:
    for l in f:
        i += 1
        if (i>opts.num_lines):
            break

        n2k.process_received_str(l)


        
