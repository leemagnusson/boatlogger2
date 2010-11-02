import serial

class serial_sentence_io:
    '''This is a utility class for line-based serial I/O.  Drivers for
    devices with line-based serial I/O can derive from this class, and
    will mostly just need to implement validation/manipulation of the
    individual data sentences.'''

    name = None
    publisher = None
    opt = None
    ser = None
    read_buf = ''
    read_sz = 1024

    def __init__(self, name, options, publisher):
        self.name = name
        self.publisher = publisher
        self.opt = options

        if self.opt.has_key('read_size'):
	    self.read_buf_sz = self.opt['read_size']

        # open the tty and set callbacks
        seropts = {'port': self.opt['tty'],
                   'baudrate': self.opt['baudrate'],
                   'parity': (serial.PARITY_EVEN
                              if self.opt['parity'] == 'Even'
                              else serial.PARITY_NONE),
                   'timeout': 0, # nonblocking
                   'xonxoff': self.opt['software_flow_control'],
                   'rtscts': self.opt['rtscts_flow_control']
                   }
        self.ser = serial.Serial(**seropts)

        # FIXME
        # seems broken in pyserial, but maybe don't need with
        # timeout=0 self.ser.nonblocking()


    def send(self, data):
        '''Called by MCU to send a sentence when a subscriber wants to
        deliver something.  Child classes should do some basic
        protocol validation to ensure the sentence is correct.'''

        if not self.opt['allow_writes']:
            raise DriverException('writes to '+self.name+' not allowed')
        else:
            self.ser.write(data)


    def read(self, fd):
        '''Callback when data is available to be read from the fd.
        Reads and buffers a complete line, then returns it.  Derived
        driver classes are responsible for munging it into something
        useful and then sending it to the MCU for publishing.'''

        sentences = []

        while True:
            data = self.ser.read(self.read_sz)
            if not data:
                break

            self.read_buf += data

            while True:
                endl = self.read_buf.find('\n')
                if endl >= 0:
                    # extract the sentence and drop trailing
                    # whitespace (spaces/tabs, \r, \n)
                    S, self.read_buf = self.read_buf[:endl+1], self.read_buf[endl+1:]
                    sentences.append(S.rstrip())
                else:
                    break

        return sentences if sentences else None


    def write(self, fd):
        '''Callback when the write buffer has space.  Not normally a
        concern.'''
        pass

    def get_fd(self):
        return self.ser.fileno()
