#######################################################################
# Homework Assignment 5, for EECS 22, Fall 2017
#
# Author: Tim Schmidt
# Date: 11/09/2017
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
CC = gcc
DEBUG 	= -DDEBUG -g
CFLAGS 	= -ansi -Wall -c
LFLAGS 	= -ansi -Wall
AR 		= ar rc
RANLIB 	= ranlib

# Default target
all : MovieLab

# Link
libfilter.a : DIPs.o Image.o ImageList.o Movie.o FileIO.o
	$(AR) libfilter.a DIPs.o Image.o ImageList.o Movie.o FileIO.o
	$(RANLIB) libfilter.a
 
######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o : MovieLab.c 
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o -lm

# Target for FileIO.o
FileIO.o : FileIO.c FileIO.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
	
# Target for DIPs.o
DIPs.o : DIPs.c DIPs.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
	
# Target for Image.o
Image.o : Image.c Image.h	
	$(CC) $(CFLAGS) Image.c -o Image.o
	
# Target for ImageList.o
ImageList.o : ImageList.c ImageList.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
	
# Target for Movie.o
Movie.o : Movie.c Movie.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o
	

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o libfilter.a 
	$(CC) $(LFLAGS) MovieLab.o -lfilter -L. -o MovieLab -lm 

###############################  others  ##############################
# Target for clean-up
clean:
		rm -rf *.o
		rm -rf out.yuv
		rm -rf MovieLab
		
backup:
		rm -rf ../hw5Backup
		cp -r  ../hw5 ../hw5Backup		
