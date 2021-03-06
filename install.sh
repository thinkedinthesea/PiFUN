#! /bin/bash
#
#THINKEDINTHESEA
#PiFUN
#
#rev03122019
#
if [ $(id -u) -ne 0 ]; then
	echo "Installer must be run as root."
	echo "Try 'sudo bash $0'"
	exit 1
fi
clear
#
echo "------------------------------------------------------------------"
echo "This script downloads and install"
echo "PiFUN, a GPIO-to-keypress board"
echo "with one WS2812b led"
echo
echo "- Update package index files (apt-get update)."
echo "- Install Python libraries."
echo "- Install Adafruit retrogame script."
echo "- Install led.py scripts in /usr/local/bin."
echo
echo "WARNING:"
echo "After install complete, shutdown and connect PiFUN board."
echo "------------------------------------------------------------------"
echo
echo -n "CONTINUE? [y/N] "
read
if [[ ! "$REPLY" =~ ^(yes|y|Y)$ ]]; then
	echo "Cancelled."
	exit 0
fi
#
#############################################################
echo -n "Downloading, installing LED.py..."
#Download to tmpfile because might already be running
curl -f -s -o /tmp/led.py https://raw.githubusercontent.com/thinkedinthesea/PiFUN/master/led.py
if [ $? -eq 0 ]; then
	mv /tmp/led.py /usr/local/bin
	chmod 755 /usr/local/bin/led.py
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
echo
echo
echo "Add udev rule (will overwrite if present)"
echo
# Add udev rule (will overwrite if present)
echo "SUBSYSTEM==\"input\", ATTRS{name}==\"retrogame\", ENV{ID_INPUT_KEYBOARD}=\"1\"" > /etc/udev/rules.d/10-retrogame.rules
echo "install libs"
echo
# install libs
apt-get update
sudo apt install python3-pip
sudo pip3 install rpi_ws281x adafruit-circuitpython-neopixel
echo
echo
echo "Start retrogame on boot"
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
echo "Start LED on boot"
# Start PiFUN on boot
grep LED /etc/rc.local >/dev/null
if [ $? -eq 0 ]; then
	echo
	# LED already in rc.local, do nothing
	#sed -i "s/^.*PiFUN.*$/\python3 /usr\/local\/bin\/PiFUN.py \&/g" /etc/rc.local >/dev/null
else
	# Insert LED into rc.local before final 'exit 0'
	sed -i "s/^exit 0/\python3 \/usr\/local\/bin\/led.py \&\\nexit 0/g" /etc/rc.local >/dev/null
fi
echo "PiFUN LED OK"
echo
##
echo
echo -n "SHUTDOWN NOW? [y/N]"
read
if [[ "$REPLY" =~ ^(yes|y|Y)$ ]]; then
	echo "Shutdown started..."
	shutdown
#else
	echo
	echo "Done"
fi
