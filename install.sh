#! /bin/bash
#
#THINKEDINTHESEA
#PiFUN
#
#rev19112019
#
if [ $(id -u) -ne 0 ]; then
	echo "Installer must be run as root."
	echo "Try 'sudo bash $0'"
	exit 1
fi
clear
#
echo "This script downloads and install"
echo "PiFUN, a GPIO-to-keypress board"
echo "with one WS2812b led"
echo
echo "1. Adafruit retrogame script"
echo "2. PiFUN python code for watchdog"
echo "3. PiFUN python code for WS2812B"
echo
echo
#
#############################################################
echo -n "Downloading, installing PiFUN..."
#Download to tmpfile because might already be running
curl -f -s -o /tmp/PiFUN.py https://raw.githubusercontent.com/thinkedinthesea/PiFUN/master/PiFUN.py
if [ $? -eq 0 ]; then
	mv /tmp/PiFUN.py /usr/local/bin
	chmod 755 /usr/local/bin/PiFUN.py
	echo "OK"
else
	echo "ERROR"
fi

echo -n "Downloading, installing retrogame..."
# Download to tmpfile because might already be running
curl -f -s -o /tmp/retrogame https://raw.githubusercontent.com/adafruit/Adafruit-Retrogame/master/retrogame
if [ $? -eq 0 ]; then
	mv /tmp/retrogame /usr/local/bin
	chmod 755 /usr/local/bin/retrogame
	echo "OK"
else
	echo "ERROR"
fi

echo -n "Downloading, installing retrogame.cfg..."
curl -f -s -o /boot/retrogame.cfg https://raw.githubusercontent.com/thinkedinthesea/PiFUN/master/retrogame.cfg
if [ $? -eq 0 ]; then
	echo "OK"
else
	echo "ERROR"
fi

echo -n "Performing other system configuration..."

# Add udev rule (will overwrite if present)
echo "SUBSYSTEM==\"input\", ATTRS{name}==\"retrogame\", ENV{ID_INPUT_KEYBOARD}=\"1\"" > /etc/udev/rules.d/10-retrogame.rules

# install libs
sudo pip3 install rpi_ws281x adafruit-circuitpython-neopixel
echo

# Start retrogame on boot
grep retrogame /etc/rc.local >/dev/null
if [ $? -eq 0 ]; then
	# retrogame already in rc.local, but make sure correct:
	sed -i "s/^.*retrogame.*$/\/usr\/local\/bin\/retrogame \&/g" /etc/rc.local >/dev/null
else
	# Insert retrogame into rc.local before final 'exit 0'
	sed -i "s/^exit 0/\/usr\/local\/bin\/retrogame \&\\nexit 0/g" /etc/rc.local >/dev/null
fi
echo "Adafruit retrogame OK"
echo

# Start PiFUN on boot
grep PiFUN /etc/rc.local >/dev/null
if [ $? -eq 0 ]; then
	echo
	# PiFUN already in rc.local, do nothing
	#sed -i "s/^.*PiFUN.*$/\python3 /usr\/local\/bin\/PiFUN.py \&/g" /etc/rc.local >/dev/null
else
	# Insert PiFUN into rc.local before final 'exit 0'
	sed -i "s/^exit 0/\python3 \/usr\/local\/bin\/PiFUN.py \&\\nexit 0/g" /etc/rc.local >/dev/null
fi
echo "PiFUN watchdog OK"
echo
##
echo
echo -n "REBOOT NOW? [y/N]"
read
if [[ "$REPLY" =~ ^(yes|y|Y)$ ]]; then
	echo "Reboot started..."
	reboot
#else
	echo
	echo "Done"
fi
