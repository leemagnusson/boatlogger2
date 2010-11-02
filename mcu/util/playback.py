#!/usr/bin/python

import os
import sys
import time
from optparse import OptionParser

usage = 'Usage: %prog [options] logfile'
optparser = OptionParser(usage=usage)
optparser.add_option('-o', '--fifo', dest='fifo_name',
                     help='Path to playback FIFO file',
                     metavar='FILE',
                     default='/tmp/.boatlogger_playback.fifo')
optparser.add_option('-r', '--realtime', dest='realtime',
                     help='Play back the log in "real time", relative to start',
                     action='store_true',
                     default=False)
optparser.add_option('-s', '--source-filter', dest='sources',
                     help='Only playback entries from the specified source (multiple allowed)',
                     action='append',
                     default=None)
(opts, args) = optparser.parse_args()

if len(args) != 1:
    optparser.error('You must specify a logfile')

# open the log file
log = open(args[0], 'r')

# open the MCU playback driver's FIFO
try:
    fifo = os.open(opts.fifo_name, os.O_WRONLY)
except:
    print 'Failed opening FIFO ('+opts.fifo_name+ \
        '); is the playback driver loaded in MCU?'
    sys.exit(1)


last_time = None
lineno = 0

# send the log data to the FIFO
while True:
    data = log.readline()
    if not data:
        break

    ++lineno

    timestamp, source, sentence = data.split(',', 2)

    if not timestamp or not source or not sentence:
        print args[0]+' is not a boatlogger log (line '+lineno+')'
        sys.exit(1)

    # filter out sources we aren't interested in
    if opts.sources != None and len(opts.sources) > 0:
        if source not in opts.sources:
            continue

    # note that this assumes log entries are in order
    if opts.realtime:
        if last_time is None:
            last_time = float(timestamp)
        else:
            time.sleep(float(timestamp) - last_time)
            last_time = float(timestamp)

    print 'sending '+repr(data)+' to fifo'
    os.write(fifo, data)
