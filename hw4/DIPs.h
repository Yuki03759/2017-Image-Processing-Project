/********************************************************************	*/
/* PhotoLab.c: assignment 4 for EECS 22 in Fall 2017             	    */
/*                                                            	     	*/
/* Author Yuki Hayashi         			                   			  	*/
/* 11/21/2017				                            			 	*/
/********************************************************************	*/

#ifndef DIPS_H
#define DIPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "Image.h"
#include "FileIO.h"
#include "Constants.h"

IMAGE *BlackNWhite(IMAGE *image);
IMAGE *Negative(IMAGE *image);
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);
IMAGE *Edge(IMAGE *image);
IMAGE *Shuffle(IMAGE *image);
IMAGE *VFlip(IMAGE *image);
IMAGE *VMirror(IMAGE *image);
IMAGE *AddBorder(IMAGE *image, char color[SLEN], int border_width);

#endif /*DIPS_H*/

/*EOF DIPs.h */


