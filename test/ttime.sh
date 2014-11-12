#!/bin/sh

LOGDIR=/home/accel/log
DATE=$(date +%Y%m%d-%H%M%S)

mkdir -p $LOGDIR
#cp /var/log/syslog ${LOGDIR}/syslog-${DATE}.txt
#tail -n 1000 /var/log/syslog > ${LOGDIR}/syslog-${DATE}.txt
#vmstat > ${LOGDIR}/vmstat-${DATE}.txt
free > ${LOGDIR}/free-${DATE}.txt
cat /proc/meminfo > ${LOGDIR}/meminfo-${DATE}.txt
