/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2016                     */
/*                                                                   */
/* Author : Yuki Hayashi											*/
/* Date: 12/05/2017			                                         */
/*                                                                   */
/* ImageList.h: header file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#ifndef IMAGELIST_H
#define IMAGELIST_H

#include "Image.h"

typedef struct ImageEntry IENTRY;
typedef struct ImageList ILIST;

struct ImageEntry 
{
	ILIST *List;
	IENTRY *Next;
	IENTRY *Prev;
	IMAGE *RGBImage;
	YUVIMAGE *YUVImage;
};

struct ImageList
{
	unsigned int Length;
	IENTRY *First;
	IENTRY *Last;
};

ILIST *CreateImageList(void);

void DeleteImageList(ILIST *list);

void DeleteImageEntry(IENTRY *entry);

void AppendRGBImage(ILIST *list, IMAGE *RGBimage);

void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage);

void CropImageList(ILIST *list, unsigned int start, unsigned int end);

void FastImageList(ILIST *list, unsigned int factor);

void ReverseImageList(ILIST *list);

#endif
