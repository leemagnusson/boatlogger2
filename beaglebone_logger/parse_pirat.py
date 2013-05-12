#!/usr/bin/python

from lessgps.parser import Parser
import pyparsing
import sys
from pprint import pprint

fnames = sys.argv[1:]
print fnames

fileout = "data.csv"
parser = Parser('lessgps/data/nmea.yaml')

sentence_filter = ['VHW','MWV']
out_format = [[['WindAngle','Value'],['WindAngle','Ref'],['WindSpeed','Value'],['WindSpeed','Ref']],
 [['DegreesTrue','Value'],['DegreesTrue','Ref'],['SOW','Value'],['SOW','Ref']]]

def format_out(d,form):
    l = []
    for f in form:
        l += str(reduce(dict.get, f, d))
    print l
    return l.join(',')

#with open(fileout,'w') as fout:
with [open(fileout + '.csv','w') for fileout in sentence_filter] as fout:
    for fname in fnames:
        print fname
        with open(fname,'r') as f:
            for sentence in f:
                sentence = sentence.strip()
                #print sentence[1:6]
                if sentence:
                    if sentence[3:6] in sentence_filter:
                        ind = sentence_filter.index(sentence[3:6])
                        try:
                            p = parser.parse(sentence)
                            #fout.write("{0}\n".format(p['Temp']['Value']))
                            fout[ind].write(format_out(p,out_format[ind]))
                        except pyparsing.ParseException as e:
                            print e
