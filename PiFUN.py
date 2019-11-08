#!/usr/bin/python
#
#THINKEDINTHESEA
#PiFUN
#
#rev081119
#
import RPIO
import time
import os
#
RPIO.setwarnings(False)
RPIO.cleanup()
#led
#segnale di vitalità inviato
RPIO.setup(23, RPIO.OUT)
#segnale di vitalità ricevuto
RPIO.setup(10, RPIO.IN)
#start mettiamo su la vitalità
RPIO.output(23, True)
#
#ciclo principale
while True:
  #se perdiamo la vitalità ricevuta spegniamo
  if (RPIO.input(10) == False):
      os.system("sudo poweroff")
      break
  time.sleep(0.01)
