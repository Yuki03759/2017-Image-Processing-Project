/********************************************************************	*/
/* PhotoLab.c: assignment 3 for EECS 22 in Fall 2017             	    */
/*                                                            	     	*/
/* Author Yuki Hayashi         			                   			  	*/
/* 11/07/2017				                            			 	*/
/********************************************************************	*/

#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"

int LoadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
int SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

#endif /*FILEIO_H */

/*EDF FileIo.h */
