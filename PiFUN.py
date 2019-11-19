#! /usr/bin/python3
#
#THINKEDINTHESEA
#PiFUN
#
#rev191119
#
import RPIO
import time
import os
#
RPIO.setwarnings(False)
RPIO.cleanup()
#led
#watchdog signal to the PiFUN board
RPIO.setup(23, RPIO.OUT)
#watchdog signal received from PiFUN board
RPIO.setup(10, RPIO.IN)
#start, make watchdog high
RPIO.output(23, True)
#
#
while True:
  #check for watchdog signal received
  if (RPIO.input(10) == False):
      os.system("sudo poweroff")
      break
  time.sleep(0.01)
