/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ImageList.h"

ILIST *CreateImageList(void)
{
	ILIST *l;
	l = malloc(sizeof(ILIST));
	l -> Length = 0;
	l -> First = NULL;
	l -> Last = NULL;
	
	return l;
}

void DeleteImageList(ILIST *list)
{
		IENTRY *curr = list -> First;
		IENTRY *next;
		
		while ( curr != NULL)
		{
			next = curr -> Next;
			DeleteImageEntry(curr);
			curr = next;
		} 
		
		free(list);
	
		list = NULL;
	
}


void DeleteImageEntry(IENTRY *entry)
{
	entry -> List = NULL;
	entry -> Next = NULL;
	entry -> Prev = NULL;
	                                                     
	if (entry -> RGBImage != NULL)
	{
		DeleteImage(entry -> RGBImage);	
	}
	if (entry -> YUVImage != NULL)
	{
		DeleteYUVImage(entry -> YUVImage);
	}
	
	free(entry);
	entry = NULL;
}

void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	IENTRY *e = NULL;
	
	assert(RGBimage);
	assert(list);
	
	e = malloc(sizeof(IENTRY));
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->RGBImage = RGBimage;
	
	if (list->Last)
	{
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
	}
	else
	{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
	}
	list->Length++;
}

void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	IENTRY *e = NULL;
	
	assert(YUVimage);
	assert(list);
	
	e = malloc(sizeof(IENTRY));
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->YUVImage = YUVimage;
	e->RGBImage = NULL;

	if (list->Last != NULL)
	{
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
	}
	else
	{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
	}
	list->Length++;
}

void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	assert(list);

	int frames_num = list -> Length;
	IENTRY *curr = list->First;
	IENTRY *next;
	IENTRY *prev;
	int i;

	for (i=0; i<start; i++)
	{
		next = curr -> Next;
		DeleteImageEntry(curr);
		curr = next;
	}

	list -> First = curr;
	assert(list->Last);
	curr = list -> Last;

	for (i = 0; i < frames_num-end-1; i++)
	{
		prev = curr -> Prev;
		DeleteImageEntry(curr);
		curr = prev;
	}

		list -> Last = curr;
		list -> First -> Prev = NULL;
		list -> Last -> Next = NULL;
}

void FastImageList(ILIST *list, unsigned int factor)
{
	assert(list);
	
	IENTRY *curr = list -> First, *next;
	int i = 0;
	
	while (curr != NULL)
	{
		next = curr -> Next;
		if (i % factor)
		{
			if (curr == list -> Last){
				list -> Last = curr -> Prev;
			}
			else {
				next -> Prev = curr -> Prev;
			}
			curr -> Prev -> Next = next;
			DeleteImageEntry(curr);
			list -> Length = list -> Length-1;
		}
		i++;
		curr = next;
	}
}	

void ReverseImageList(ILIST *list)
{
	assert(list);
	
	IENTRY *curr = list -> First, *prev = NULL, *next = list->First->Next;
	
	while (next != NULL)
	{
		curr->Next = prev;
		curr->Prev = next;
		
		prev = curr;
		
		curr = next;
		
		next = next->Next;
		
		curr -> Next = prev;
		curr -> Prev = next;
	}
	
	list -> Last = list -> First;
	
	list -> First = curr;

}

/* EOF */
