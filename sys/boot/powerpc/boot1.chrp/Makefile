# $FreeBSD$

SSP_CFLAGS=

PROG=           boot1.elf
NEWVERSWHAT=    "Open Firmware boot block" ${MACHINE_ARCH}
BINDIR?=        /boot
INSTALLFLAGS=   -b

FILES=		boot1.hfs
SRCS=		boot1.c ashldi3.c syncicache.c

MAN=

CFLAGS= -ffreestanding -msoft-float \
	-I${.CURDIR}/../../common -I${.CURDIR}/../../../ \
	-D_STANDALONE
LDFLAGS=-nostdlib -static -Wl,-N

.include "../Makefile.inc"

.PATH:  ${.CURDIR}/../../../libkern ${SRCTOP}/lib/libc/powerpc/gen ${.CURDIR}

# The following inserts out objects into a template HFS 
# created by generate-hfs.sh

.include "${.CURDIR}/Makefile.hfs"

boot1.hfs: boot1.elf bootinfo.txt
	echo ${.OBJDIR}
	uudecode ${.CURDIR}/hfs.tmpl.bz2.uu
	mv hfs.tmpl.bz2 ${.TARGET}.bz2
	bzip2 -f -d ${.TARGET}.bz2
	${DD} if=boot1.elf of=${.TARGET} seek=${BOOT1_OFFSET} conv=notrunc
	${DD} if=${.CURDIR}/bootinfo.txt of=${.TARGET} seek=${BOOTINFO_OFFSET} \
	    conv=notrunc

CLEANFILES= boot1.hfs

boot1.o: ${SASRC}/ufsread.c

.include <bsd.prog.mk>

