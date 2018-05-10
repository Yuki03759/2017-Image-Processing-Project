/************************************************************/
/* Image.c : Image.c for assignment 4 EECS 22, Fall 2017	*/
/* Author: Yuki Hayashi										*/
/* Date: 11/21												*/
/************************************************************/

#include "Image.h"

unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{	
	assert(image);
	assert(y >= 0);
	assert(y < ImageHeight(image));
	assert(x >= 0);
	assert(x < ImageWidth(image));

	return *(image->R + x + y*ImageWidth(image));
}
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{	
	assert(image);
	assert(y >= 0);
	assert(y < ImageHeight(image));
	assert(x >= 0);
	assert(x < ImageWidth(image));

	return *(image->G + x + y*ImageWidth(image));
}
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(y >= 0);
	assert(y < ImageHeight(image));
	assert(x >= 0);
	assert(x < ImageWidth(image));
	return *(image->B + x + y*ImageWidth(image));
}
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	assert(image);
	assert(y >= 0);
	assert(y < ImageHeight(image));
	assert(x >= 0);
	assert(x < ImageWidth(image));
	*((image->R) + x + y*ImageWidth(image)) = r;
}
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	assert(image);
	assert(y >= 0);
	assert(y < ImageHeight(image));
	assert(x >= 0);
	assert(x < ImageWidth(image));
	*((image->G) + x + y*ImageWidth(image)) = g;
}
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
	assert(image);
	assert(y >= 0);
	assert(y < ImageHeight(image));
	assert(x >= 0);
	assert(x < ImageWidth(image));
	*((image->B) + x + y*ImageWidth(image)) = b;
}
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *image = NULL;
	image = malloc(sizeof(IMAGE));
	image -> W = Width;
	image -> H = Height; 
	image->R = (unsigned char *)malloc(Width*Height);
	image->G = (unsigned char *)malloc(Width*Height);
	image->B = (unsigned char *)malloc(Width*Height);
	return image;
}
void DeleteImage(IMAGE *image)
{
	assert(image);
	assert(image->R);
	free(image->R);
	assert(image->G);
	free(image->G);
	assert(image->B);
	free(image->B);
	free(image);
	
}

unsigned int ImageWidth(const IMAGE *image)
{
	return (image-> W);
}
unsigned int ImageHeight(const IMAGE *image)
{
	return (image->H);
} 

