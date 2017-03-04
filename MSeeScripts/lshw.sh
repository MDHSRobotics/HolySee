#!/bin/bash

# alternatives to try
# udevadm info --query all -name /dev/ttyUSB0 --attribute-walk
# ls -l /sys/bus/usb-serial/devices
# cd /sys/class/tty/
# readlink ttyUSBn
# ls -l /dev/ttyUSB0
# ls -l /sys/dev/char/116:7
# dmesg | grep tty

for sysdevpath in $(find /sys/bus/usb/devices/usb*/ -name dev); do
    (
        syspath="${sysdevpath%/dev}"
        devname="$(udevadm info -q name -p $syspath)"
        [[ "$devname" == "bus/"* ]] && continue
        eval "$(udevadm info -q property --export -p $syspath)"
        [[ -z "$ID_SERIAL" ]] && continue
        echo "/dev/$devname - $ID_SERIAL"
    )
done

