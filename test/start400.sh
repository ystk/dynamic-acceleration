#!/bin/sh

# Acceleration rate
ACCEL_TIME=400

# Copy crontab
mount -o rw,remount /
mkdir -p /var/spool/cron/crontabs
cp /home/accel/crond/root /var/spool/cron/crontabs
mount -o ro,remount /

sync; sync; sync

# Start crond
crond

# Start test script in back ground
/home/accel/testClock > /dev/null &
/home/accel/testTime > /dev/null &
PID_TCLOCK=`ps | grep "testClock" | awk '{print $1}'`
PID_TTIME=`ps | grep "testTime" | awk '{print $1}'`

# Start acceleration
echo $ACCEL_TIME > /proc/sys/kernel/accel
