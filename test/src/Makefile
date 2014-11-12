##
# Makefile for Network Program
# author:  OKAMOTO Kouta
# created: 2010-08-24
# updated: 2010-08-24
##

PATH := $(PATH):/opt/arm-toolchain/bin

CC		= arm-linux-gnueabi-gcc
LINK		= ${CC} -Wall $^ -o $@

PROGRAM1	= testClock
PROGRAM1SRCS	= testClock.c

PROGRAM2	= testReadWrite
PROGRAM2SRCS	= testReadWrite.c

PROGRAM3	= testTime
PROGRAM3SRCS	= testTime.c

SRCS		= ${PROGRAM1SRC} ${PROGRAM2SRCS} ${PROGRAM3SRCS}
TARGET		= ${PROGRAM1} ${PROGRAM2} ${PROGRAM3}

all: ${TARGET}

${PROGRAM1}: ${PROGRAM1SRCS}
	${LINK}

${PROGRAM2}: ${PROGRAM2SRCS}
	${LINK}

${PROGRAM3}: ${PROGRAM3SRCS}
	${LINK}

clean:
	rm -f ${TARGET}

