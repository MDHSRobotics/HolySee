#!/bin/sh

rm /usr/local/msee/CSee.so
cp ../CSee/Release/CSee.so /usr/local/msee/.

rm /usr/local/msee/avahi.sh
cp ./avahi.sh /usr/local/msee/.

rm /usr/local/msee/lshw.sh
cp ./lshw.sh /usr/local/msee/.

rm /usr/local/msee/v4l2.sh
cp ./v4l2.sh /usr/local/msee/.

rm /usr/local/msee/msee.sh
cp ./msee.sh /usr/local/msee/.

rm /usr/local/msee/msee.conf
cp ../MSee/msee.conf /usr/local/msee/.

rm /usr/local/msee/MSee
cp ../MSee/Release/MSee /usr/local/msee/.
