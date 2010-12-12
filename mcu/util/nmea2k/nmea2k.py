import struct
import re
import json

nmea_dict = json.load(open("out.json"))

class NMEA2K:

    def __init__(self, message_fun):
        self.fast_packet_messages = {}
        self.message_callback = message_fun

    def process_received_str(self,s):
#        self.message_callback('received str: {}'.format(s.strip()))
        m = re.match(r"(?P<len>[\dA-F]{2} )(?P<header>([\dA-F]{2} ){4})(?P<data>([\dA-F]{2} ){8})",s)
        if (m):
            h = header(bytes.fromhex(m.group('header')))
            d = bytes.fromhex(m.group('data'))
            message = process_message(h,d)
            self.message_callback(message)
        else:
            self.message_callback(None)


def unpack(format, value):
    std_f = "bBhHiIqQs"
    std_format = re.sub(r"[er\(,\)0-9]","",format)
    try:
        vals = struct.unpack_from(std_format, value)
    except:
        return(None)

    format_list = re.findall(r'e\([bBhHiIqQslL,0-9]*?\)|[bBhHiIqQslL]',format)
    #print(format_list)
    new_vals = []
    for f,v in zip(format_list,vals):
        if (f[0] == 'e'):
            bit_list = [int(x) for x in re.findall(r'[0-9]+(?=[ ,\)])',f) ]
            
            vv = []
            for x in reversed(bit_list):
                vv.append( v & 2**x-1 )
                v = v >> x
            #vv.reverse()
            new_vals.extend(reversed(vv))
        else:
            new_vals.append(v)
        
    return(new_vals)


def header(s):
    b = unpack(">e(I,3,1,1,6,2,2,8,8,1)",s)
    header_names = ['priority','edp','dp','pf_upper','ide','pf_lower','ps','sa','rtr']
    c = dict(zip(header_names,b))
    c['raw'] = s
    c['pf'] = (c['pf_upper']<<2) + c['pf_lower']
    if (c['pf'] >= 240):
        c['pgn'] = (c['dp']<<16) + (c['pf']<<8) + c['ps']
    else:
        c['pgn'] = (c['dp']<<16) + (c['pf']<<8)
    return(c)

def process_message(c,d):
    # if (c['pgn'] == 127250):
    #     format = {'frm':'<BHhhe(B,2,6)','fields':[('sid',1,''),
    #                                               ('heading',.0001,'rad'),
    #                                               ('deviation',.0001,'rad'),
    #                                               ('variation',.0001,'rad'),
    #                                               ('reference',1,'')]}
    #     v = unpack(format['frm'],d)
    #     c2 = format_fields(v,format['fields'])
    #     print(c2)
    format = nmea_dict.get(str(c['pgn']),None)
    if (format):
        desc = format['description']
#        print(format['description'])
#        print(format['field_str'])
        v = unpack(format['field_str'],d)
        if(v):
            fields = format_fields(v,format['fields'])
        else:
            fields = None
    else:
        fields = 'not in dictionary'
        desc = fields

    return({'pgn':c['pgn'], 'raw':d, 'fields':fields, 'description':desc, 'header':c})



def format_fields(vals,form):
    d = {}
 #   print(form)
#    print(vals)
    for k,v in zip(form,vals):
#        print(k)
        res = k['resolution'] if k['resolution'] else 1
        if(isinstance(k['units'], dict)):
            d[k['name']] = k['units'].get(str(v),None),
        elif(k['signed'] and v==2**(k['bitlength']-1)-1 or \
               not k['signed'] and v==2**k['bitlength']-1):
            d[k['name']] = None, k['units'] # could omit this altogether
        else:
            d[k['name']] = v*res, k['units']
    return(d)



#print(header(bytes.fromhex('4F 9A 24 12')))



# example header (this comes is big endian format)

# priority	e(L,3)
# edp		e(L,1)
# dp		e(L,1)
# pf_upper	e(L,6)
# ide		e(L,2)
# pf_lower	e(L,2)
# ps		e(L,8)
# sa		e(L,8)
# rtr		e(L,1)
# pf = pf_upper<<2 + pf_lower
# if (pf >= 240)
#    pgn = dp<<16 + pf<<8 + ps
#    da = 255
# else
#    pgn = dp<<16 + pf<<8
#    da = ps
# end
# class DataField:
#     def __init__(self,value=0,format=0):
#         self._d = value
#         self._f = format

#     def __getitem__(self, index):
#         return (self._d >> index) & 1 

#     def __setitem__(self,index,value):
#         value    = (value&1)<<index
#         mask     = (1)<<index
#         self._d  = (self._d & ~mask) | value

#     def __getslice__(self, start, end):
#         mask = 2**(end - start) -1
#         return (self._d >> start) & mask

#     def __setslice__(self, start, end, value):
#         mask = 2**(end - start) -1
#         value = (value & mask) << start
#         mask = mask << start
#         self._d = (self._d & ~mask) | value
#         return (self._d >> start) & mask

#     def __int__(self):
#         return self._d

#     def unpack(self):
#         return struct.unpack(self._f,self._d)

# class HeaderField:
#     def __init__(self,value=0):
#         self.d = bf(struct.unpack('>L',value)[0])
#         print(int(self.d))

#     def priority(self):
#         return(self.d[2:3])

#     def unpack(self):
#         return struct.unpack('BBBB',self.d)


# p = bytes.fromhex('C7 FF 18 00')
# b = bf(p)
# c = bf(struct.unpack('>l',p)[0])
# print(int(c))
# #print(int(c)>>4)

# h = HeaderField(p)
# print(h.priority())

# a = bytes.fromhex('41 9F 04 32 4E 08 F1 FF')
# print(a)
# d = DataField(a,'<hhl')
# print(d.unpack())
# e = DataField(a,'<BBBBBBBB')
# print(e.unpack())
