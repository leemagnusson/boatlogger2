
import nmea2k
import sys

pgn_occurances = {}
with open(sys.argv[1],'r') as f:
    for line in f:
        try:
            h = bytes.fromhex(line[2:14])
#            print(h)
            if(len(h) != 4):
                raise(ValueError)
            c = nmea2k.header(h)
            if c['pgn'] in pgn_occurances:
                pgn_occurances[c['pgn']] += 1;
            else:
                pgn_occurances[c['pgn']] = 1;

            if (c['pgn'] == 127250):
                d = bytes.fromhex(line[14:].strip())
                if(len(d) != 8):
                    raise(ValueError)
               # print('heading',d)
                # vessel heading
                nmea2k.process_message(c,d)

#            print(c['pgn'], pgn_occurances[c['pgn']])
        except(ValueError):
            pass


for k,v in sorted(pgn_occurances.items()):
    print(k,v,sep=',')
