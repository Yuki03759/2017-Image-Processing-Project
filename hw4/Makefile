##############################################################################
# Makefile: Makefile for Assignment 4 EECS22 2017								#
# 11/21 Yuki Hayashi:															#
##############################################################################

CC 		= gcc
DEBUG	= -DDEBUG -g
CFLAGS 	= -ansi -Wall -c
LFLAGS 	= -ansi -Wall
AR		= ar rc
RANLIB	= ranlib

LIBS 	= libfilter.a libfieIO.a

IMAGES	= 	bw.ppm \
			edge.ppm \
			negative.ppm \
			colorfilter.ppm \
			shuffle.ppm \
			vflip.ppm \
			vmirror.ppm\
			noise.ppm \
			posterize.ppm \
			border.ppm \
			sharpen.ppm \
			blur.ppm \
			smallresize.ppm \
			bigresize.ppm \
			crop.ppm \
			brightnessandcontrast.ppm \
			watermark.ppm 
			

all: PhotoLab PhotoLabTest

clean:
		rm -rf *.o
		rm -rf PhotoLab PhotoLabTest libfilter.a
		rm -rf $(IMAGES)
	
libfilter.a : DIPs.o Advanced.o
	$(AR) libfilter.a DIPs.o Advanced.o
	$(RANLIB) libfilter.a	
 
PhotoLab: FileIO.o libfilter.a PhotoLab.o Test.o Image.o
	$(CC) $(LFLAGS) -std=c99 FileIO.o PhotoLab.o Image.o Test.o -lfilter -L. -o PhotoLab

PhotoLab.o: PhotoLab.c Constants.h DIPs.h FileIO.h Advanced.h Test.h Image.h
	$(CC) $(CFLAGS) -std=c99 PhotoLab.c -o PhotoLab.o
		
FileIO.o: FileIO.c FileIO.h Constants.h Image.h
	$(CC) $(CFLAGS) -std=c99 FileIO.c -o FileIO.o
	
DIPs.o: DIPs.c DIPs.h Constants.h Image.h
	$(CC) $(CFLAGS) -std=c99 DIPs.c -o DIPs.o
	
Advanced.o: Advanced.c Advanced.h Constants.h Image.h
	$(CC) $(CFLAGS) -std=c99 Advanced.c -o Advanced.o
	
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) -std=c99 Image.c -o Image.o

Test.o: Test.c Test.h Advanced.h DIPs.h Image.h Constants.h 
	$(CC) $(CFLAGS) Test.c -o Test.o

Test_debug.o: Test.c Test.h Advanced.h DIPs.h Image.h Constants.h 
	$(CC) $(CFLAGS) Test.c -o Test_debug.o $(DEBUG)

PhotoLabTest: PhotoLab_debug.o FileIO.o libfilter.a Test_debug.o Image.o
	$(CC) $(LFLAG) -std=c99 FileIO.o PhotoLab_debug.o Image.o Test_debug.o -lfilter -L. -o PhotoLabTest 

PhotoLab_debug.o: PhotoLab.c Constants.h DIPs.h FileIO.h Advanced.h Test.h Image.h
	$(CC) $(CFLAGS) -std=c99 PhotoLab.c -o PhotoLab_debug.o $(DEBUG)


	
#EOF