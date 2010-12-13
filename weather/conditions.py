#!/usr/bin/python

# fetch current conditions from weather.gov.sg and reduce them to a
# simple text format

import urllib
import re
import string

url = 'http://www.weather.gov.sg/wip/pp/mmtops/web/ship.html'

f = urllib.urlopen(url)
str = f.read()

datapoints = [
    ('Issued',
     'DATE\/TIME OF ISSUE:\s*(.*?)\s*<br>'),
    ('Forecast validity',
     '<!-- VAILDITY DATE AND TIME -->\s*(.*?)\s*</'),
    ('Storm warnings',
     '<!-- STORM WARNINGS -->\s*(.*?)\s*</'),
    ('General situation',
     '<!-- GENERAL SITUATION -->\s*(.*?)\s*</'),
    ('Conditions in Phuket',
     '<!-- CONDITIONS IN PHUKET -->\s*(.*?)\s*</'),
    ('Conditions in Malacca',
     '<!-- CONDITIONS IN MALACCA -->\s*(.*?)\s*</'),
    ('Conditions in Tioman',
     '<!-- CONDITIONS IN TIOMAN -->\s*(.*?)\s*</'),
    ('Conditions in Bunguran',
     '<!-- CONDITIONS IN BUNGURAN -->\s*(.*?)\s*</'),
    ('Conditions in Condore',
     '<!-- CONDITIONS IN CONDORE -->\s*(.*?)\s*</'),
    ('Conditions in Reef',
     '<!-- CONDITIONS IN REEF -->\s*(.*?)\s*</')
    ]

for dp in datapoints:
    m = re.search(dp[1], str)
    val = m.groups(1)[0].replace('\r','\n'+' '*25) if m else 'UNKNOWN'
    #print '%s\t%s\n' % (dp[0], val)
    print '{0:<25}'.format(dp[0]) + val + '\n'
