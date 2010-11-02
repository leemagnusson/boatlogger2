import re
import operator
#import protocol

class protocol:
    pass # FIXME

class ProtocolException(Exception):
    pass

class protocol_nmea0183(protocol):

    def __init__(self):
#        protocol.__init__()
        self.checksum_re = re.compile(r'\*([A-Fa-f0-9]{2})$')

    def checksum(self, sentence):
        return '%02X' % reduce(operator.xor, map(ord, sentence))

    def extract(self, sentence, labels=None):
        '''Extract fields from a raw NMEA 0183 setence and do checksum
        verification.  If a list of labels is given, returns a dict
        with the labels as keys for the values with the same index as
        the keys.  Otherwise a list is returned.  Throws an exception
        on parsing or checksum verification error.'''

        # certain newer sentences may use '!' as start delim
        if sentence[0] not in '$!':
            raise ProtocolException('NMEA0183 sentences must begin with a "$"')

        # drop the $ and trailing whitespace
        sentence = sentence[1:].rstrip()

        # is there a checksum?  if so, extract it then check it
        m = self.checksum_re.search(sentence)
        if m:
            cs_a = m.group(1)
            sentence = sentence[:m.start(1)-1] # drop the checksum
            print 'checksum against '+sentence
            cs_b = self.checksum(sentence)
            if cs_a != cs_b:
                raise ProtocolException('NMEA0183 checksum failure ('+cs_a+'!='+cs_b+')')

        fields = sentence.split(',')
        if labels:
            if len(labels) != len(fields):
                raise ProtocolException('Sentence has more fields than labels')
            return dict(zip(labels, fields))
        else:
            return fields


    def sentence(self, fields, tag=None, labels=None, crc=True):
        '''Generates a string containing an NMEA0183 sentence given a set of
        fields.  The fields param may be a list, in which case all
        fields will be inserted into the sentence in order.  It may
        also be a dict; in that case, the list given in the labels
        param will be used to determine the output ordering of the
        fields (each item in labels must be a key in fields).  If tag
        is given, its value is used as the first field; otherwise the
        first item in fields (if a list) or labels (if fields is a
        dict) is used as the sentence tag.  Finally, if crc is True, a
        checksum is added to the sentence.  The returned string
        includes carriage return and newline characters.'''

        S = [tag] if tag else []

        if isinstance(fields, dict):
            S += [str(fields[l]) for l in labels]
        else:
            S += [str(f) for f in fields]

        sentence = ','.join(S)

        if crc:
            sentence += '*'+self.checksum(sentence)

        return '$'+sentence+'\r\n'
