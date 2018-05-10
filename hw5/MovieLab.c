/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Yuki Hayashi                                               */
/* Date: 12/05/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

int SaveMovie(const char *fname, MOVIE *movie);

void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	int factor = 0;
	int frameNum = 0;
	int start = 0, end = 0;
	int aging = 0, hflip = 0, edge = 0, crop = 0, fast = 0, reverse = 0, watermark= 0, spotlight = 0, zoom = 0;
	char *fin = NULL;
	char *fout = NULL;
	char *watermarkname = NULL;
	int centerX = 0;
	int centerY = 0;
	int watermark_count = 0;
	int percentage = 0;
	int y = 2;
	double radius = 0;
	unsigned int topLeftX = 0;
	unsigned int topLeftY = 0;

	unsigned int width = 480;
	unsigned int height = 270;
	
	MOVIE *movie = NULL;

	
	while (x < argc) {
		
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
			} 
			else {
				printf("Missing argument for the input file name!\n");
				return 5;
			} 
			x += 2;
			continue;
		} 

		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
			} 
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			} 
			x += 2;
			continue;
		} 

		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		} 

		if (strcmp(argv[x], "-s") == 0) {
			if (x < argc -1){
				if(sscanf(argv[x+1], "%ux%u", &width, &height) == 2)
				{
					/*correct*/
				}
				else
				{
					printf("width = %d, height = %d\n", width, height);
					printf("input formet error\n");
				}
			}
			x+= 2;
			continue;
		}
		
		
		if (strcmp(argv[x], "-f") == 0) {
			if (x < argc -1){
				if(sscanf(argv[x+1], "%d", &frameNum) == 1)
				{
					/*correct*/
				}
				else 
				{
					printf("incorrent input format (-f)\n");
				}
			}
			x+=2;
			continue;
		}
		
		if (strcmp(argv[x], "-aging") == 0) {
			aging = 1;
			
		}
		
		if (strcmp(argv[x], "-hflip") == 0) {
			hflip = 1;
		}
		
		if (strcmp(argv[x], "-edge") == 0) {
			edge = 1;
		}
		
		if (strcmp(argv[x], "-crop") == 0) {
			if (x < argc -1){
				if(sscanf(argv[x+1], "%i-%i", &start, &end) == 2)
				{	
					crop = 1;
				}
			}
		}
		
		if (strcmp(argv[x], "-fast") == 0) {
			if (x < argc -1){
				if(sscanf(argv[x+1], "%i", &factor) == 1)
					fast = 1;
			}
		}
		
		if (strcmp(argv[x], "-reverse") == 0) {
			reverse = 1;
		}
		
		if (strcmp(argv[x], "-watermark") == 0) {
			if (x < argc - 1) {
				watermarkname = argv[x + 1];
				watermark = 1;
			}
			else
			{
				printf("watermark.ppm is not loaded");
			}
		}
		
		if (strcmp(argv[x], "-spotlight") == 0) {
			spotlight = 1;
		}

		if (strcmp(argv[x], "-zoom") == 0) {
			zoom = 1;
		}
		x++;
	} 

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}

	movie = LoadMovie(fin, frameNum, width, height);
	YUV2RGBMovie(movie);

	if (aging == 1){
	
		ILIST *list = movie -> Frames;
		IENTRY *curr = list->First;
		
		while (curr != NULL)
		{
			curr -> RGBImage = Aging (curr-> RGBImage);
			curr= curr->Next;
		}
		printf("Operation Aging is done!\n");
	}

	if (hflip == 1){
		
		ILIST *list = movie -> Frames;
		IENTRY *curr = list->First;
		
		while (curr != NULL)
		{
			curr -> RGBImage = HFlip(curr-> RGBImage);
			curr= curr->Next;
		}
		printf("Operation HFlip is done!\n");
	}

	if (edge == 1){
		ILIST *list = movie -> Frames;
		IENTRY *curr = list->First;
		
		while (curr != NULL)
		{
			curr -> RGBImage = Edge(curr-> RGBImage);
			curr= curr->Next;
		}
		printf("Operation Edge is done!\n");
	}

	if (crop == 1){
	
		CropImageList(movie->Frames, start, end);
		printf("Operation Crop is done!\n");
	}
	
	if (fast == 1){
		FastImageList(movie->Frames, factor);
		printf("Operation Fast is done!\n");
	}
	
	if (reverse == 1){
		ReverseImageList(movie->Frames);
		printf("Operation Reverse is done!\n");
	}

	if (watermark == 1){
			IMAGE *watermarkimage = NULL;
			watermarkimage = LoadImage(watermarkname);
			if (watermarkimage == NULL)
			{
				printf("watermark is not loaded");
				return 0;
			}
			ILIST *list = movie -> Frames;
			IENTRY *curr = list->First;
	
			while (curr != NULL)
			{				
				if (watermark_count % 15 ==0)
					{
						topLeftX = rand()%width;
						topLeftY = rand()%height;
					}
				curr -> RGBImage = Watermark(curr-> RGBImage, watermarkimage, topLeftX, topLeftY);
				curr= curr->Next;
				watermark_count++;

			}
		
			DeleteImage(watermarkimage);
			printf("Operation Watermark is done!\n");
	
	}
	
	if (spotlight == 1){
		
		if (frameNum < 60)
		{
			printf("you have less frames\n");
			return 0;
		}
		ILIST *list = movie -> Frames;
		IENTRY *curr = list->First;
		centerX = width/2;
		centerY = height/2;
		double radius_constant = sqrt(centerX*centerX + centerY*centerY)/39;
		int index = 0;
		while (index < 40)
		{	
			curr -> RGBImage = Spotlight(curr-> RGBImage, centerX, centerY, radius);
			curr= curr->Next;
			radius = radius + radius_constant;
			index++;
		}
		
		index = list->Length-1;
		curr = list->Last;
		radius = 0;
		radius_constant = sqrt(centerX*centerX + centerY*centerY)/19;
		while (index >= list-> Length -1 - 20)
		{
			curr -> RGBImage = Spotlight(curr-> RGBImage, centerX, centerY, radius);
			curr= curr->Prev;
			radius = radius + radius_constant;
			index--;
		}	
			printf("Operation Spotlight is done!\n");
	}
	
	if (zoom == 1){
		ILIST *list = movie -> Frames;
		IENTRY *curr = list->First;
		
		while (curr != NULL)
		{
			curr -> RGBImage = Zoom(curr-> RGBImage, percentage);
			curr= curr->Next;
			percentage = percentage + y;	
			if (percentage >= 100)
			{
				y = -ZOOM_SPEED;
			}
			else if (percentage <= 0)
			{
				y = ZOOM_SPEED;
			}
			
		}
			printf("Operation Zoom is done!\n");
	}
	RGB2YUVMovie(movie);
	SaveMovie(fout, movie);
	DeleteMovie(movie);
	fin = NULL;
	fout = NULL;

	return 0;

}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} 
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	assert(ferror(file) == 0);

	fclose(file);
	file = NULL;
	return YUVimage;
}

MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
	MOVIE *movie;
	movie = CreateMovie();
	
	int i;
	for (i=0; i < frameNum; i++)
	{
		AppendYUVImage(movie->Frames, LoadOneFrame(fname, i, width, height));
	}
	printf("The movie %s has been loaded successfully!\n", fname);
	
	return movie;

}

int SaveMovie(const char *fname, MOVIE *movie)
{

	int count;
	FILE *file;
	IENTRY *curr;

	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}

	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {

		SaveOneFrame(curr->YUVImage, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;
	
	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}




/* EOF */
