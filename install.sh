#!/bin/bash
#
#THINKEDINTHESEA
#PiFUN
#
#rev08112019
#
if [ $(id -u) -ne 0 ]; then
	echo "Installer must be run as root."
	echo "Try 'sudo bash $0'"
	exit 1
fi
clear
#
echo "This script downloads and installs"
echo "PiFUN, a GPIO-to-keypress board"
echo "with one WS2812b led"
echo
#
