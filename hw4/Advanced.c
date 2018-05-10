/********************************************************************/
/* PhotoLab.c : PhotoLab.c for assignment 4 EECS 22, Fall 2017		*/
/* Author: Yuki Hayashi												*/
/* Date: 11/21														*/
/********************************************************************/

#include "Advanced.h"

IMAGE *AddNoise(IMAGE *image, int n)
{
	assert(image);

	int p, i, x, y;
	p = ImageWidth(image)*ImageHeight(image)*n/100;
	srand(time(NULL));

	for (i=0; i<p; i++)
	{

		x = rand()%(ImageWidth(image));
		y = rand()%(ImageHeight(image)); 

		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);

	}
	assert(image);
	return image;
}

IMAGE *Sharpen(IMAGE *image)
{
	assert(image);
	
	int r, g, b;
	IMAGE *temp_image = NULL;
	temp_image = CreateImage((ImageWidth(image)), ImageHeight(image));
	
	assert(temp_image);
	int i, j;
	for (j=0; j < ImageHeight(image); j++)
	{
		for (i = 0; i < ImageWidth(image); i++)
		{	
			SetPixelR(temp_image, i, j, GetPixelR(image, i, j));
			SetPixelG(temp_image, i, j, GetPixelG(image, i, j));
			SetPixelB(temp_image, i, j, GetPixelB(image, i, j));
		}
	}

	int x, y;
	for (y = 1; y < ImageHeight(image)-1; y++)
	{
		for (x=1; x < ImageWidth(image)-1; x++)
			{
			r = 9*GetPixelR(temp_image, x, y)-GetPixelR(temp_image, x-1, y-1)-GetPixelR(temp_image, x, y-1)-GetPixelR(temp_image, x+1, y)-GetPixelR(temp_image, x-1, y)-GetPixelR(temp_image, x+1, y)-GetPixelR(temp_image, x-1, y+1)-GetPixelR(temp_image, x, y+1)-GetPixelR(temp_image, x+1, y+1);
			g = 9*GetPixelG(temp_image, x, y)-GetPixelG(temp_image, x-1, y-1)-GetPixelG(temp_image, x, y-1)-GetPixelG(temp_image, x+1, y)-GetPixelG(temp_image, x-1, y)-GetPixelG(temp_image, x+1, y)-GetPixelG(temp_image, x-1, y+1)-GetPixelG(temp_image, x, y+1)-GetPixelG(temp_image, x+1, y+1);
			b = 9*GetPixelB(temp_image, x, y)-GetPixelB(temp_image, x-1, y-1)-GetPixelB(temp_image, x, y-1)-GetPixelB(temp_image, x+1, y)-GetPixelB(temp_image, x-1, y)-GetPixelB(temp_image, x+1, y)-GetPixelB(temp_image, x-1, y+1)-GetPixelB(temp_image, x, y+1)-GetPixelB(temp_image, x+1, y+1);
		
			SetPixelR(image, x, y, (r>255) ? 255: (r<0) ? 0 : r);
			SetPixelG(image, x, y, (g>255) ? 255: (g<0) ? 0 : g);
			SetPixelB(image, x, y, (b>255) ? 255: (b<0) ? 0 : b);
		}	
	}
	DeleteImage(temp_image);
	assert(image);
	return image;
}


IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits)
{

	assert(image);
	
	int x, y;
	int r, g, b;
	
	r = 1 << (rbits-1);
	g = 1 << (gbits-1);
	b = 1 << (bbits-1);
	
	for (y = 0; y < ImageHeight(image)-1; y++)
	{
		for (x = 0; x < ImageWidth(image)-1; x++)
		{
			SetPixelR(image, x, y, (~r & GetPixelR(image, x, y)) | (r-1));
			SetPixelG(image, x, y, (~g & GetPixelG(image, x, y)) | (g-1));
			SetPixelB(image, x, y, (~b & GetPixelB(image, x, y)) | (b-1));
		}
	}
	
	assert(image);
	return image;
}

IMAGE *MotionBlur(IMAGE *image, int bluramount)
{
	assert(image);
	
	int r_ave = 0, g_ave = 0, b_ave = 0;
	int i;
	
	int x, y; 
	for (y = 0; y < ImageHeight(image); y++)
	{
		for(x = 0; x < ImageWidth(image); x++)
		{
			r_ave = 0;
			g_ave = 0;
			b_ave = 0;
			
			for (i=1; i <= bluramount; i++)
				{
					if(x+i< ImageWidth(image)-1)
					{
					r_ave += GetPixelR(image, x+i, y);
					g_ave += GetPixelG(image, x+i, y);
					b_ave += GetPixelB(image, x+i, y);
					}	
				}
			
			r_ave /= bluramount;
			g_ave /= bluramount;
			b_ave /= bluramount;
			
			SetPixelR(image, x, y, (r_ave + GetPixelR(image, x, y))/2);
			SetPixelG(image, x, y, (g_ave + GetPixelG(image, x, y))/2);
			SetPixelB(image, x, y, (b_ave + GetPixelB(image, x, y))/2);
		}
	}
	
	assert(image);
	return image;
}		

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H)
{
	assert(image);
	int new_W = (W+x < ImageWidth(image)) ? W : ImageWidth(image)-x;
	int new_H = (H+x < ImageHeight(image)) ? H : ImageHeight(image) - y;
	int i, j;
	if ((x>ImageWidth(image))|(y>ImageHeight(image)))
	{
		printf("\nx or y is out of range\n");
		return image;
	}
	IMAGE *temp_image = CreateImage(new_W, new_H);
	assert(temp_image);

	for (j = 0; j < new_H; j++)
		{	
			for(i = 0; i < new_W; i++)
			{
				if ( j < ImageHeight(image) && i < ImageWidth(image))
				{
					SetPixelR(temp_image, i, j, GetPixelR(image, i+x, j+y));
					SetPixelG(temp_image, i, j, GetPixelG(image, i+x, j+y));
					SetPixelB(temp_image, i, j, GetPixelB(image, i+x, j+y));
				}
			}
		}
		assert(temp_image);
		DeleteImage(image);
		return temp_image;
		
}

IMAGE *Resize(IMAGE *image, int percentage)
{
	assert(image);

	int x, y, i, j,	x1, y1, x2, y2, sumR=0, sumG=0, sumB=0, devide=0, aveR=0, aveG=0, aveB=0;
	
	IMAGE *temp_image = NULL;
	
	if (percentage == 100)
	{
		return image;
	}
	
	temp_image = CreateImage(ImageWidth(image)*(percentage/100.00), ImageHeight(image)*(percentage/100.00));
	assert(temp_image);
	
	if (percentage > 100)
	{
		for (y = 0; y < ImageHeight(temp_image); y++)
		{	
			for(x = 0; x < ImageWidth(temp_image); x++)
			{
				x1 = x*(100.00/percentage);
				y1 = y*(100.00/percentage);
				
				SetPixelR(temp_image, x, y, GetPixelR(image, x1, y1));
				SetPixelG(temp_image, x, y, GetPixelG(image, x1, y1));
				SetPixelB(temp_image, x, y, GetPixelB(image, x1, y1));
			  
			}
		}
	}
	else if (percentage < 100)
	{
		for (y = 0; y < ImageHeight(temp_image); y++)
		{ 
			for (x = 0; x < ImageWidth(temp_image); x++)
			{
				x1 = x/(percentage / 100.00);
				y1 = y/(percentage / 100.00);
				x2 = (x+1)/(percentage / 100.00);
				y2 = (y+1)/(percentage / 100.00);

				for(j = y1; j <=y2; j++)
				{
					if(x2>= ImageWidth(image))
					{
						break;
					}

						for (i = x1; i <= x2; i++)
						{
							if (y2 >= (ImageHeight(image)))
							{
								break;
							}
	
								sumR = sumR + GetPixelR(image, i, j);
								sumG = sumG + GetPixelG(image, i, j);
								sumB = sumB + GetPixelB(image, i, j);
								devide += 1;
						}
				}

					if(devide != 0)
					{
						aveR = sumR/devide;
						aveG = sumG/devide;
						aveB = sumB/devide;
					}
						SetPixelR(temp_image, x, y, aveR);
						SetPixelG(temp_image, x, y, aveG);
						SetPixelB(temp_image, x, y, aveB);
						
						devide = 0;
						sumR = 0;
						sumG = 0;
						sumB = 0;
						aveR = 0;
						aveG = 0;
						aveB = 0;
						devide = 0;
						
			}
			
		}
	}

	DeleteImage(image);
	assert(temp_image);
	return temp_image;
	
}
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast)
{
	assert(image);
	
	int x, y;
	double factor, new_pixel_value_R, new_pixel_value_G, new_pixel_value_B;
	
	factor = (double)(259*(contrast + 255))/(double)(255*(259 - contrast));
	
	for (y = 0; y < ImageHeight(image); y++)
		{ 
			for (x = 0; x < ImageWidth(image); x++)
			{
				new_pixel_value_R = (int)(factor*(GetPixelR(image, x, y)-128) + 128);
				new_pixel_value_G = (int)(factor*(GetPixelG(image, x, y)-128) + 128);
				new_pixel_value_B = (int)(factor*(GetPixelB(image, x, y)-128) + 128);
	
				SetPixelR(image, x, y, (new_pixel_value_R + brightness)>255 ? 255 :(new_pixel_value_R + brightness) < 0 ? 0 :(new_pixel_value_R + brightness));
				SetPixelG(image, x, y, (new_pixel_value_G + brightness)>255 ? 255 :(new_pixel_value_G + brightness) < 0 ? 0 :(new_pixel_value_G + brightness));
				SetPixelB(image, x, y, (new_pixel_value_B + brightness)>255 ? 255 :(new_pixel_value_B + brightness) < 0 ? 0 :(new_pixel_value_B + brightness));
			}
		}
	assert(image);
	return image;
}

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image)
{
	assert(image);
	int x, y;
	int r, g, b;

	for (y=0; y < ImageHeight(image); y++)
	{
		for (x=0; x < ImageWidth(image); x++)
		{
			
			if( GetPixelR(watermark_image, x%ImageWidth(watermark_image), y%ImageHeight(watermark_image)) == 0 && 
			GetPixelG(watermark_image, x%ImageWidth(watermark_image), y%ImageHeight(watermark_image)) == 0 && 
			GetPixelB(watermark_image, x%ImageWidth(watermark_image), y%ImageHeight(watermark_image)) == 0)
			{
				r = GetPixelR(image, x, y)*1.45;
				if (r>255)
					r = 255;
				g = GetPixelG(image, x, y)*1.45;
				if (g>255)
					g = 255;
				b = GetPixelB(image, x, y)*1.45;
				if (b>255)
					b = 255;
				
				SetPixelR(image, x, y, r);
				SetPixelG(image, x, y, g);
				SetPixelB(image, x, y, b);
			}
		}
	}
	assert(image);
	return image;

}

