#!/bin/sh

# Acceleration rate
ACCEL_TIME=1000

# Copy crontab
mount -o rw,remount /
mkdir -p /var/spool/cron/crontabs
cp /home/accel/crond/root /var/spool/cron/crontabs
mount -o ro,remount /

sync; sync; sync

# Create crond process with max priority
crond
PID_CROND=`ps | grep crond | awk '{print $1}'`
chrt -p 99 $PID_CROND

# Change priority for getty and shell
PID_SHELL=`ps | grep -- "-sh" | awk '{print $1}'`
PID_GETTY=`ps | grep "getty" | awk '{print $1}'`
chrt -p 99 $PID_SHELL
chrt -p 99 $PID_GETTY

# Change priority for hrtimer and events
PID_HRTIMER=`ps | grep "hrtimer" | awk '{print $1}'`
PID_EVENTS=`ps | grep "events" | awk '{print $1}'`
chrt -p 99 $PID_HRTIMER
chrt -p 99 $PID_EVENTS

# Start test script in back ground
/home/accel/testClock > /dev/null &
/home/accel/testTime > /dev/null &
PID_TCLOCK=`ps | grep "testClock" | awk '{print $1}'`
PID_TTIME=`ps | grep "testTime" | awk '{print $1}'`

# Start acceleration
echo $ACCEL_TIME > /proc/sys/kernel/accel
