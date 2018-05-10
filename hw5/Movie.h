/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.h: header file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#ifndef MOVIE_H
#define MOVIE_H

#include "ImageList.h"

typedef struct {
	ILIST *Frames;
} MOVIE;

MOVIE *CreateMovie(void);

void DeleteMovie(MOVIE *movie);

void YUV2RGBMovie(MOVIE *movie);

void RGB2YUVMovie(MOVIE *movie);

unsigned char clip(int x);

#endif
