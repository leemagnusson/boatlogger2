# convert the keversoft xml file into a json format

import xml.etree.ElementTree as ET
import sys
import json
import re
from optparse import OptionParser

parser = OptionParser(usage="usage: %prog [options] filename")
parser.add_option("-f", "--file", dest="filename")
parser.add_option("-d", "--dictionary", dest="dic", action="store_true", default=False)
parser.add_option("-m",type="string",dest="modifier_file")
(options,args) = parser.parse_args()

def get_field_text(el,s):
    tmp = el.find(s)
    if(tmp is not None):
        return tmp.text
    else:
        return None

def get_field_str(length,signed):
    if(signed):
        f = {8:'b', 16:'h', 32:'l', 64:'q'}.get(length,length)
    else:
        f = {8:'B', 16:'H', 32:'L', 64:'Q'}.get(length,length)
    return(f)

def list_nums_to_tuples(l):
    new_list = []
    first_int = True
    for item in l:
        if(isinstance(item,int)):
            if(first_int):
                new_list.append([item])
                first_int = False
            else:
                new_list[-1].append(item)
        else:
            first_int = True
            new_list.append(item)
    return(new_list)

def assem_field_str(str_list):
    l = list_nums_to_tuples(str_list)
    format_str = "<"
    for c in l:
        if(isinstance(c,list)):
            format_str += "e(" + str(get_field_str(sum(c),False)) + ","\
            + ",".join(map(str,c)) + ")"
        else:
            format_str += c
    return(format_str)

if(options.filename):
    fname = filename
elif(len(args) == 1):
    fname = args[0]
else:
    parser.print_help()
    sys.exit(1)

t = ET.parse(fname)

d = {} if options.dic else []
pgns = t.find('PGNs')
for pgninfo in pgns:
    pgn = int(pgninfo.find('PGN').text)
#    print(pgn)
    desc = pgninfo.find('Description').text
#    fields = {} if options.dic else []
    fields = []
    try:
        # I construct a format string to represent the fields
        # because I think that it is neccesary due to the
        # little-endian byte ordering

        field_str_list = []
        for field in pgninfo.find('Fields'):
            name = get_field_text(field,'Name')
            fdesc = get_field_text(field,'Description')
            typ = get_field_text(field,'Type')
            length = int(get_field_text(field,'BitLength'))
            res = get_field_text(field,'Resolution')
            units = get_field_text(field,'Units')
            signed = True if get_field_text(field,'Signed') == 'true' else False
            field_str = get_field_str(length,signed)
            field_str_list.append(field_str)

            try:
                if(res is not None):
                    res = float(res)
            except(ValueError):
                m = re.match(r'([\.\d]+)\s+(\w+)',res)
                res = float(m.group(1))
                units = m.group(2)

            if(typ == 'Lookup table'):
                units = {int(enum.get('Value')):enum.get('Name') \
                             for enum in field.find('EnumValues')}
            elif(typ == 'Latitude'):
                res = 1e-7
                units = 'N'
            elif(typ == "Longitude"):
                res = 1e-7
                units = 'E'
                
            if(options.dic):
                fields.append({'name':name, 'field_description':fdesc,
                               'bitlength':length, 'resolution':res, 
                               'units':units, "signed":signed})
            else:
                fields.append([name, fdesc, length, res, units, signed])
    except(TypeError):
       # sys.stderr.write("couldn't get fields for " + pgn)
        fields = None

    field_str = assem_field_str(field_str_list)
    if(options.dic):
        d[str(pgn)] = {"description": desc, "fields":fields, "field_str":field_str}
    else:
        d.append((pgn, desc, fields, field_str))


def recur_update(d,mod_d):
    for k,v in mod_d.items():
        if (isinstance(v,dict)):
            recur_update(d.setdefault(k),v)
        elif (isinstance(v,list)):
            for i,j in zip(d[k],v):
                recur_update(i,j)
        else:
            d[k] = v

if(options.dic and options.modifier_file):
    mod_d = json.load(open(options.modifier_file))
    recur_update(d,mod_d)
        

print(json.dumps(d,indent=4))
    

