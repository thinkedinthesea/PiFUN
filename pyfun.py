#!/usr/bin/python3
#
#rev171219
#
#read file
import configparser
config = configparser.ConfigParser()
config.read('pyfun.cfg')
#assign GPIO
LEFT = config['DEFAULT']['LEFT']
RIGHT = config['DEFAULT']['RIGHT']
UP = config['DEFAULT']['UP']
DOWN = config['DEFAULT']['DOWN']
BTN_A = config['DEFAULT']['BTN_A']
BTN_B = config['DEFAULT']['BTN_B']
BTN_X = config['DEFAULT']['BTN_X']
BTN_Y = config['DEFAULT']['BTN_Y']
BTN_L = config['DEFAULT']['BTN_L']
BTN_R = config['DEFAULT']['BTN_R']
SELECT = config['DEFAULT']['SELECT']
START = config['DEFAULT']['START']
#
