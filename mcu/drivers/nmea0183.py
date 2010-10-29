from serial_sentence_io import serial_sentence_io

class driver(serial_sentence_io):

	def send(self, data):
		'''Do validation of NMEA 0183 before passing out to
		our base serial I/O class'''

		# FIXME: validate data

		serial_sentence_io.send(data)

	def read(self, fd):
		sentence = serial_sentence_io.read(self, fd)
		if sentence:
			# FIXME: make any necessary adjustments to the
			# sentence before publishing it
			self.publisher.publish_sentence(self.name, sentence)
