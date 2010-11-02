#!/usr/bin/python

# this script converts a raw GPS NMEA0183 log containing various
# sentences into a boatlogger-format log for testing.  GPS sentences
# that include timestamp details are used to set the boatlogger
# timestamp; sentences without time details use the most recent
# timestamp.

# this is a really naive conversion and it just uses a fixed date and
# assumes the timestamps don't cross midnight.  that's fine for
# testing purposes.

# just pass the name of the raw GPS log file as the first argument,
# e.g.:
#   $ ./gps2boatlogger.py gps.log > output.log

import re
import datetime
import time

lines = [l for l in open('gps.log', 'r')]

ts = 0
for l in lines:
	# the following sentences include UTC timestamps
	m = re.search(r'(GPGGA|GPRMC|GPBWC|GPZDA),(\d+\.\d+)', l)

	if m:
		t = m.group(2)
		d = datetime.datetime(2010, 11, 2,
				      int(t[0:2]), # HH
				      int(t[2:4]), # mm
				      int(t[4:6]), # ss
				      10000*int(t[7:9])) # us
		ts = time.mktime(d.timetuple())

	print str(ts)+',gps,'+l.rstrip()
