# Makefile:
#
#/********************************************************************	*/
#/* PhotoLab.c: assignment 2 for EECS 22 in Fall 2017             	    */
#/*                                                            	     	*/
#/* Author Yuki Hayashi         			                   			*/
#/* 11/07/2017				                            			 	*/
#/********************************************************************	*/

all: PhotoLab

clean:
		rm -rf *.o
		rm -rf PhotoLab PhotoLabTest libfilter.a
		rm -rf bw.ppm edge.ppm negative.ppm colorfilter.ppm shuffle.ppm vflip.ppm vmirror.ppm noise.ppm posterize.ppm border.ppm sharpen.ppm blur.ppm

PhotoLab: FileIO.o libfilter.a PhotoLab.o
	gcc FileIO.o PhotoLab.o -lfilter -L. -o PhotoLab

libfilter.a : Advanced.o DIPs.o
	ar rc libfilter.a DIPs.o Advanced.o
	ranlib libfilter.a
	
PhotoLab.o: PhotoLab.c Constants.h DIPs.h FileIO.h Advanced.h
	gcc -Wall -ansi -c PhotoLab.c -o PhotoLab.o
		
FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -c FileIO.c -o FileIO.o
	
DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -c DIPs.c -o DIPs.o
	
Advance.o: Advanced.c Advanced.h Constants.h
	gcc -Wall -ansi -c Advanced.c -o Advanced.o

PhotoLabTest: PhotoLabTest.o FileIO.o libfilter.a
	gcc FileIO.o PhotoLabTest.o -lfilter -L. -o PhotoLabTest
	
PhotoLabTest.o: PhotoLab.c Constants.h DIPs.h FileIO.h Advanced.h
	gcc -Wall -ansi -g  -c PhotoLab.c  -o PhotoLabTest.o -DDEBUG


	
#EOF