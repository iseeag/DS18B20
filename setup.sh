#!/bin/bash

# setup your pi by adding 1-wire module to your pi 
sudo modprobe w1-gpio
sleep 0.1
sudo modprobe w1-therm 
sleep 0.1 

# if there's nothing under the directory /sys/bus/w1/devices try the following command
# sudo echo "dtoverlay=w1-gpio" >>  /boot/config.txt 



