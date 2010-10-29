#!/usr/bin/python

import sys
import signal
import configobj
from PyQt4.QtCore import QCoreApplication, QSocketNotifier, SIGNAL
import dbus
import dbus.service
import dbus.mainloop.qt


class DriverException(Exception): pass

class mcu:
	'''Main MCU (or "ingester") class.  Upon initialization, the
	MCU loads a config file describing all the devices to connect
	to, along with the drivers for the devices and settings for
	the drivers.  The MCU publishes all data read in by the
	drivers on the bus for other programs to use, and accepts
	calls over the bus to publish data back to the drivers for
	delivery over the wire.'''

	app = None
	config = None
	devices = None

	class dbus_signaller(dbus.service.Object):
		def __init(self, object_path):
			dbus.service.Object.__init__(self, dbus.SystemBus(), object_path)

		# note that although the object_path encodes the real
		# device generating the data, it can occasionally be
		# useful to let the driver specify the "real"
		# originating device.  for example, the playback
		# driver sends along the original generator of a
		# sentence when it plays back log data.  that is why
		# we have a device argument to this method.
		@dbus.service.signal(dbus_interface='org.boatlogger.MCU', signature='ss')
		def publish_sentence(self, device, data):
			print 'publishing: '+repr(data)+' from '+device
#			pass


	class device:
		name = None
		config = None
		module = None
		driver = None
		publisher = None
		io_handlers = None

		def __init__(self, mcu, name, config):
			self.name = name
			self.config = config
			self.module = __import__(config['driver'])
			self.publisher = mcu.dbus_signaller('/'+name)
			self.driver = self.module.driver(name, config, self.publisher)
			self.make_io_handlers(mcu)

		def make_io_handlers(self, mcu):
			fd = self.driver.get_fd()
			self.io_handlers = [(QSocketNotifier(fd, QSocketNotifier.Read),
					     (lambda fd: self.driver.read(fd))),
					    (QSocketNotifier(fd, QSocketNotifier.Write),
					     (lambda fd: self.driver.write(fd)))]
#					    (QSocketNotifier(fd, QSocketNotifier.Write),
#					     self.make_error_handler(self.name))]
			for notifier, callback in self.io_handlers:
				mcu.app.connect(notifier, SIGNAL('activated(int)'), callback)

		def make_error_handler(self, name):
			def error_handler(fd):
				raise DriverException('I/O error in '+name)
			return error_handler



	def __init__(self, config='mcu.ini'):

		self.app = QCoreApplication(sys.argv)
		dbus.mainloop.qt.DBusQtMainLoop(set_as_default=True)

		# load config file
		print('loading '+config)
		self.config = configobj.ConfigObj(config, file_error=True, unrepr=True)

		print repr(self.config)

		# initialize i/o drivers and callbacks
		for p in ['utility_path','path']:
			sys.path.append(self.config['drivers'][p])
		self.devices = [self.device(self, name, self.config[name])
				for name in self.config['devices']]

	def run(self):
		signal.signal(signal.SIGINT, signal.SIG_DFL)  # allow ctrl-c
		sys.exit(self.app.exec_())


if __name__ == '__main__':
	mcu().run()
