import struct
import re

def unpack(format, value):
    std_f = "bBhHiIqQs"
    std_format = re.sub(r"[er\(,\)0-9]","",format)
    vals = struct.unpack(std_format, value)
    format_list = re.findall(r'e\([bBhHiIqQs,0-9]*?\)|[bBhHiIqQs]',format)
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
    c['pf'] = (c['pf_upper']<<2) + c['pf_lower']
    if (c['pf'] >= 240):
        c['pgn'] = (c['dp']<<16) + (c['pf']<<8) + c['ps']
    else:
        c['pgn'] = (c['dp']<<16) + (c['pf']<<8)
    return(c)

def process_message(c,d):
    if (c['pgn'] == 127250):
        format = {'frm':'<BHhhe(B,2,6)','fields':[('sid',1,''),
                                                  ('heading',.0001,'rad'),
                                                  ('deviation',.0001,'rad'),
                                                  ('variation',.0001,'rad'),
                                                  ('reference',1,'')]}
        v = unpack(format['frm'],d)
        c2 = format_fields(v,format['fields'])
        print(c2)


def format_fields(v,form):
    d = {}
    for k,v in zip(form,v):
        d[k[0]] = v*k[1], k[2]
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
