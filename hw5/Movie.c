/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Movie.h"

unsigned int width = 480;
unsigned int height = 270;

MOVIE *CreateMovie(void)
{
	MOVIE *movie;
	movie = malloc(sizeof(movie));
	assert(movie);
	movie->Frames = CreateImageList();
	return movie;
}

void DeleteMovie(MOVIE *movie)
{
	if (movie == NULL)
	{
		return;
	}
	DeleteImageList(movie->Frames);
	movie->Frames = NULL;
	free(movie);
	movie = NULL;
}

void YUV2RGBMovie(MOVIE *movie)
{
	int x, y;
	int C, D, E;
	int width, height;
	
	ILIST* list = movie -> Frames;
	IENTRY* current_frames = list->First;
	
	while (current_frames != NULL)
	{
		YUVIMAGE* YUVI = current_frames -> YUVImage;
		if (YUVI != NULL)
		{
			width = YUVI -> W;
			height = YUVI -> H;
			IMAGE* newRGBImage = CreateImage(width, height);
			
			for (y=0; y < height; y++)
			{
				for (x=0; x< width; x++)
				{
					C = GetPixelY(YUVI, x, y) -16;
					D = GetPixelU(YUVI, x, y) -128;
					E = GetPixelV(YUVI, x, y) -128;
		
					SetPixelR(newRGBImage, x, y, clip(( 298*C		   + 409*E + 128) >> 8));
					SetPixelG(newRGBImage, x, y, clip(( 298*C - 100*D - 208*E + 128) >> 8));
					SetPixelB(newRGBImage, x, y, clip(( 298*C + 516*D         + 128) >> 8));
				}
			}
			current_frames -> RGBImage =newRGBImage;
			DeleteYUVImage(YUVI);
			current_frames -> YUVImage = NULL;
		}
		current_frames = current_frames -> Next;
	}
}

void RGB2YUVMovie(MOVIE *movie)
{
	int x, y;
	int R, G, B;
	int width, height;
	
	ILIST* list = movie -> Frames;
	IENTRY* current_frames = list->First;
	
	while (current_frames != NULL)
	{
		IMAGE* RGBI = current_frames -> RGBImage;
		if (RGBI != NULL)
		{
			width = RGBI -> W;
			height = RGBI -> H;
			YUVIMAGE* newYUVImage = CreateYUVImage(width, height);
			
			for (y=0; y < height; y++)
			{
				for (x=0; x< width; x++)
				{
					R = GetPixelR(RGBI, x, y);
					G = GetPixelG(RGBI, x, y);
					B = GetPixelB(RGBI, x, y);
		
					SetPixelY(newYUVImage, x, y, clip((( 66*R + 129*G + 25*B + 128) >> 8) + 16));
					SetPixelU(newYUVImage, x, y, clip((( -38*R - 74*G + 112*B + 128) >> 8) + 128));
					SetPixelV(newYUVImage, x, y, clip((( 112*R - 94*G -  18*B + 128) >> 8) + 128));
				}
			}
			current_frames -> YUVImage =newYUVImage;
			DeleteImage(RGBI);
			current_frames -> RGBImage = NULL;
		}
		current_frames = current_frames -> Next;
	}
}

unsigned char clip(int x)
{
	return ( (x>255) ? 255 : (x<0) ? 0 : x );
}

/* EOF */
