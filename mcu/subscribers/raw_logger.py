#!/usr/bin/python

import sys
import signal
import dbus
import dbus.mainloop.qt
from PyQt4.QtCore import QCoreApplication

class subscriber:

    def __init__(self, signal_name=None, object_path=None):
        '''Specify signal_name or object_path to filter and receive
        only matching signals.'''

        self.app = QCoreApplication(sys.argv)
        dbus.mainloop.qt.DBusQtMainLoop(set_as_default=True)
        self.dbus = dbus.SystemBus()

        self.dbus.add_signal_receiver(self.receiver,
                                      dbus_interface='org.boatlogger.MCU',
                                      signal_name=signal_name,
                                      path=object_path)

    def run(self):
        signal.signal(signal.SIGINT, signal.SIG_DFL)
        sys.exit(self.app.exec_())

    def receiver(self, device, data):
        print device+' published: '+data


if __name__ == '__main__':
    subscriber().run()
