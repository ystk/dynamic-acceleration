#!/bin/sh

# Stop acceleration
echo 1 > /proc/sys/kernel/accel

# Kill test processes
pkill testClock
pkill testTime
pkill crond
