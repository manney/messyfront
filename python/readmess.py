#!/usr/bin/env python

#############################################################################
#                                                                           #
#   MessyFront - readmess.py                                                #
#   (C) 2005 - 2007 Aaron Sebold                                            #
#   Version 19                                                              #
#                                                                           #
#############################################################################
#                                                                           #
#   This program is free software; you can redistribute it and/or modify    #
#   it under the terms of the GNU General Public License as published by    #
#   the Free Software Foundation; either version 2 of the License, or       #
#   (at your option) any later version.                                     #
#                                                                           #
#   This program is distributed in the hope that it will be useful,         #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of          #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            #
#   GNU General Public License for more details.                            #
#                                                                           #
#   You should have received a copy of the GNU General Public License       #
#   along with this program; if not, write to the Free Software             #
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA #
#                                                                           #
#############################################################################

import os, sys, string
import pygtk
pygtk.require ('2.0')
import gtk 

class Readconf:
	def __init__ (self, filename):
		self.filename = filename
		self.commands = ["BIOS_IMAGE",
										 "CARTRIDGE_IMAGE",
										 "FLOPPY_IMAGES",
										 "HDD_IMAGE",
										 "MESS_EXECUTABLE",
										 "IMAGES_DIRECTORY",
										 "BIOS_DIRECTORY",
										 "DISPLAY_COMMAND",
										 "RAM_SIZE",
										 "VIDEO_MODE",
										 "CASSETTE_IMAGE",
										 "PRINTER_IMAGE",
										 "NO_DISCLAIMER",
										 "SKIP_INTRO"]
		self.conffile = []
		self.symbols = {}
		self.mess_version = 0.0
		self.command_line = ""
		self.getconf ()
		self.parsefile ()
		self.get_mess_version ()
		self.create_command ()
		self.run_mess ()

	def getconf (self):
		# Open and put in to memory MESSyFront's conf file
		fp = open (self.filename, 'r')
		self.conffile = fp.readlines ()
		fp.close ()

	def parsefile (self):
		# Step through each element in the self.conffile list.
		for x in self.conffile:
			# Strip off leading and trailing whitespace.
			line = x.strip ()
			# If the line is a comment (starting with '#') then skip.
			if (line != "" and line[0] == '#'):
				continue
			# If we have a blank line, then skip.
			elif (line == ""):
				continue
			# Find the first space in the line, which should denote between a 'symbol' (or command) and it's 'argument'.
			wts = line.find (' ')
			# If the 'symbol' has an argument put it in the self.symbols' dictionary.
			if (wts != -1):
				self.symbols[line[0:wts]] = line[wts + 1:]
				# Step through the argument looking for spaces to change in to escape sequences.
				tochange = self.symbols[line[0:wts]]
				shouldbe = ''
				for x in range (0, len (tochange)):
					if (tochange[x] == ' '):
						# Found a space.
						if (tochange[x - 1] != ','):
							# The space wasn't part of a separator.
							shouldbe = shouldbe + '\\ '
						else:
							# The space was a part of a separator.
							shouldbe = shouldbe + ' '
					else:
						# No space was detected
						shouldbe = shouldbe + tochange[x]
				# Put the new version in to the list.
				self.symbols[line[0:wts]] = shouldbe[:]

	def get_mess_version (self):
		# Try to get MESS' version number
		try:
			version = os.popen (self.symbols['MESS_EXECUTABLE'] + " -V")
			verfile = version.read ()
			lp = verfile.find ('version')
			# Found the version number
			if (lp != -1):
				# Find the space before the version number and after
				lp2 = verfile.find (' ', lp) + 1
				lp3 = verfile.find (' ', lp2)
				# Put the version number in the variable
				self.mess_version = string.atof (verfile[lp2:lp3])
				print "MESSYFRONT: Found xMESS version %0.3f" % self.mess_version
			else:
				# Couldn't find the version number!
				print "MESSYFRONT: Couldn't find xMESS' version number; using 0.117 instead."
				self.mess_version = 0.117
		except:
			# Had a big problem finding anything! Try defaults!
				print "MESSYFRONT: Couldn't find xMESS' version number; using 0.117 instead."
				self.mess_version = 0.117

	def create_command (self):
		# Creates the command to execute MESS according to user's input.
		# Take a different course of action depending on MESS' version number.
		# Let's start with MESS' executable.
		if (self.symbols.has_key ("MESS_EXECUTABLE")):
			self.command_line = self.symbols["MESS_EXECUTABLE"] + " "
		else:
			self.command_line = "usr/bin/sdlmess "
		# Let's move on to the BIOS were going to use.
		if (self.symbols.has_key ("BIOS_IMAGE")):
			if (self.symbols["BIOS_IMAGE"].rfind("zip") != -1):
				self.command_line += self.symbols["BIOS_IMAGE"][self.symbols["BIOS_IMAGE"].rfind("/") + 1:self.symbols["BIOS_IMAGE"].rfind(".zip")] + " "
			else:
				self.command_line += self.symbols["BIOS_IMAGE"] + " "
		else:
			self.command_line += "coco3 "
		# Okay, now the bios' path.
		if (self.symbols.has_key ("BIOS_DIRECTORY")):
			self.command_line += "-bp " + self.symbols["BIOS_DIRECTORY"] + " "
		else:
			self.command_line += "-bp " + os.path.expanduser ("~/.mess") + " "
		# We need the cartridge image.
		if (self.symbols.has_key ("CARTRIDGE_IMAGE")):
			self.command_line += "-cart " + self.symbols["CARTRIDGE_IMAGE"] + " "
		# On to the floppy disks.
		if (self.symbols.has_key ("FLOPPY_IMAGES")):
			# Separate the images if there are more than one.
			floppies = []
			if (self.symbols["FLOPPY_IMAGES"].find (', ') != -1):
				floppies = self.symbols["FLOPPY_IMAGES"].split (", ")
			else:
				floppies = [self.symbols["FLOPPY_IMAGES"]]
			# Which version of MESS are we using?
			if (self.mess_version >= 0.105):
				# A 'current' version of MESS.
				for x in range (0, len (floppies)):
					self.command_line += "-flop" + str (x) + " " + floppies[x] + " "
			else:
				# An older version of MESS.
				for x in floppies:
					self.command_line += "-flop " + x + " "
		# We're ready for the VHD.
		if (self.symbols.has_key ("HDD_IMAGE")):
			self.command_line += "-hard " + self.symbols["HDD_IMAGE"] + " "

	def run_mess (self):
		# Check to see if the user wanted MESSyFront to display the command line.
		if (self.symbols.has_key ("DISPLAY_COMMAND")):
			if (self.symbols["DISPLAY_COMMAND"] == "TRUE"):
				self.show_commandline ()
		# Use the command line to start MESS
		# Use os.popen () for usage later.
		try:
			mess_output = os.popen (self.command_line + '&')
			self.mess_output = mess_output.read ()
		except:
			print "MESSYFRONT: Unable to execute:"
			print "  \"" + self.command_line + "\"!"

	def show_commandline (self):
		# Display the commnad line via the console.
		print self.command_line
		# Display the command line via a GTK dialog box.
		dialog = gtk.MessageDialog (None, 0, type = gtk.MESSAGE_INFO, buttons = gtk.BUTTONS_OK, message_format = self.command_line)
		dialog.run ()
		dialog.destroy ()

if (__name__ == "__main__"):
	if (len (sys.argv) == 2):
		Readconf (sys.argv[1])
	else:
		print "MESSYFRONT: USAGE: readmess FILE"
		print "    Too many (or few) arguments; using default: \"" + os.path.expanduser ('~/.messyfront') + "\""
		Readconf (os.path.expanduser ('~/.messyfront'))
