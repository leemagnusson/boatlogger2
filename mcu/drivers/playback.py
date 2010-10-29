import os

class driver:
    '''This is a driver for reading in previously logged data over a named
    pipe (FIFO).  Use devices with this driver in conjunction with the
    "playback" utility to play back previously captured log files.'''

    name = None
    publisher = None
    opt = None
    read_buf = ''
    read_sz = 1024
    fifo_name = '/tmp/.boatlogger_playback.fifo'

    def __init__(self, name, options, publisher):
        self.name = name
        self.publisher = publisher
        self.opt = options

        if self.opt.has_key('read_size'):
	    self.read_buf_sz = self.opt['read_size']
        if self.opt.has_key('fifo_name'):
	    self.fifo_name = self.opt['fifo_name']

        # open the FIFO for reading
        if not os.path.exists(self.fifo_name):
            os.mkfifo(self.fifo_name)

        self.fifo = open(self.fifo_name, 'r')


    def send(self, data):
        '''Illegal for this driver!'''
        raise DriverException('writes to '+self.name+' not allowed')


    def read(self, fd):
        '''Callback when data is available to be read from the fd.  Reads and
        buffers a complete line, then extracts the original data from
        the log and publishes it.'''

        while True:
            data = self.fifo.read(self.read_sz)
            if not data:
                break

            self.read_buf += data
            endl = self.read_buf.find('\n')
            if endl >= 0:
                # extract the sentence and drop trailing whitespace
                # (spaces/tabs, \r, \n), then split out logging
                # metadata
                S, self.read_buf = self.read_buf[:endl+1], self.read_buf[endl+1:]
                timestamp, source, data = S.rstrip().split(',', 2)
                self.publisher.publish_sentence(source, data)


    def write(self, fd):
        '''Callback when the write buffer has space.  Not normally a
        concern.'''
        pass

    def get_fd(self):
        return self.fifo.fileno()
