# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort t help text ReadInt PrintInt ReadChar PrintChar ReadString PrintString createfile echo cat

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

t.o: t.c
	$(CC) $(CFLAGS) -c t.c
t: t.o start.o
	$(LD) $(LDFLAGS) start.o t.o -o t.coff
	../bin/coff2noff t.coff test

help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help

text.o: text.c
	$(CC) $(CFLAGS) -c text.c
text: text.o start.o
	$(LD) $(LDFLAGS) start.o text.o -o text.coff
	../bin/coff2noff text.coff text

ReadInt.o: ReadInt.c
ReadInt: ReadInt.o start.o
	$(LD) $(LDFLAGS) start.o ReadInt.o -o ReadInt.coff
	../bin/coff2noff ReadInt.coff ReadInt

PrintInt.o: PrintInt.c
PrintInt: PrintInt.o start.o
	$(LD) $(LDFLAGS) start.o PrintInt.o -o PrintInt.coff
	../bin/coff2noff PrintInt.coff PrintInt

ReadChar.o: ReadChar.c
ReadChar: ReadChar.o start.o
	$(LD) $(LDFLAGS) start.o ReadChar.o -o ReadChar.coff
	../bin/coff2noff ReadChar.coff ReadChar

PrintChar.o: PrintChar.c
PrintChar: PrintChar.o start.o
	$(LD) $(LDFLAGS) start.o PrintChar.o -o PrintChar.coff
	../bin/coff2noff PrintChar.coff PrintChar

ReadString.o: ReadString.c
ReadString: ReadString.o start.o
	$(LD) $(LDFLAGS) start.o ReadString.o -o ReadString.coff
	../bin/coff2noff ReadString.coff ReadString

PrintString.o: PrintString.c
PrintString: PrintString.o start.o
	$(LD) $(LDFLAGS) start.o PrintString.o -o PrintString.coff
	../bin/coff2noff PrintString.coff PrintString

createfile.o: createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

echo.o: echo.c
echo: echo.o start.o
	$(LD) $(LDFLAGS) start.o echo.o -o echo.coff
	../bin/coff2noff echo.coff echo

cat.o: cat.c
cat: cat.o start.o
	$(LD) $(LDFLAGS) start.o cat.o -o cat.coff
	../bin/coff2noff cat.coff cat
