/********************************************************************/
/* PhotoLab.c : PhotoLab.c for assignment 4 EECS 22, Fall 2017		*/
/* Author: Yuki Hayashi												*/
/* Date: 11/21														*/
/********************************************************************/

#include "DIPs.h"

IMAGE *BlackNWhite(IMAGE *image)
{	
	assert(image);
	
	int x, y, tmp;
	
    for (y = 0; y < ImageHeight(image); y++)
	{
        for (x = 0; x < ImageWidth(image); x++)
		{
           tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
           SetPixelR(image, x, y, tmp);
		   SetPixelG(image, x, y, tmp);
		   SetPixelB(image, x, y, tmp);
        }
    }
	assert(image);
	return image;
}


IMAGE *Negative(IMAGE *image)
{
	assert(image);
	
	int x, y;
	
    for (y = 0; y < ImageHeight(image); y++) 
	{
        for (x = 0; x < ImageWidth(image); x++) 
		{
            SetPixelR(image, x, y, 255 - GetPixelR(image, x, y));
            SetPixelG(image, x, y, 255 - GetPixelG(image, x, y));
            SetPixelB(image, x, y, 255 - GetPixelB(image, x, y));
        }
    }
	assert(image);
	return image;
}

IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) 
{
	assert(image);
	
	int x, y;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_g = (replace_g > MAX_PIXEL)? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
    replace_b = (replace_b > MAX_PIXEL)? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

    for (y = 0; y < ImageHeight(image); y++)
	{
        for (x = 0; x < ImageWidth(image); x++)
		{
            if (abs(GetPixelR(image, x, y) - target_r) <= threshold
                    && abs(GetPixelG(image, x, y) - target_g) <= threshold
                    && abs(GetPixelB(image, x, y) - target_b) <= threshold) 
					{
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
        }
    }
	assert(image);
	return image;
}


IMAGE *Edge(IMAGE *image)
{
	assert(image);
	
	int r, g, b;
	IMAGE *temp_image = NULL;
	temp_image = CreateImage(ImageWidth(image), ImageHeight(image));
	
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
			r = 8*GetPixelR(temp_image, x, y)-GetPixelR(temp_image, x-1, y-1)-GetPixelR(temp_image, x, y-1)-GetPixelR(temp_image, x+1, y)-GetPixelR(temp_image, x-1, y)-GetPixelR(temp_image, x+1, y)-GetPixelR(temp_image, x-1, y+1)-GetPixelR(temp_image, x, y+1)-GetPixelR(temp_image, x+1, y+1);
			g = 8*GetPixelG(temp_image, x, y)-GetPixelG(temp_image, x-1, y-1)-GetPixelG(temp_image, x, y-1)-GetPixelG(temp_image, x+1, y)-GetPixelG(temp_image, x-1, y)-GetPixelG(temp_image, x+1, y)-GetPixelG(temp_image, x-1, y+1)-GetPixelG(temp_image, x, y+1)-GetPixelG(temp_image, x+1, y+1);
			b = 8*GetPixelB(temp_image, x, y)-GetPixelB(temp_image, x-1, y-1)-GetPixelB(temp_image, x, y-1)-GetPixelB(temp_image, x+1, y)-GetPixelB(temp_image, x-1, y)-GetPixelB(temp_image, x+1, y)-GetPixelB(temp_image, x-1, y+1)-GetPixelB(temp_image, x, y+1)-GetPixelB(temp_image, x+1, y+1);
		
			SetPixelR(image, x, y, (r>255) ? 255: (r<0) ? 0 : r);
			SetPixelG(image, x, y, (g>255) ? 255: (g<0) ? 0 : g);
			SetPixelB(image, x, y, (b>255) ? 255: (b<0) ? 0 : b);
		}	
	}	
	
	for (y = 0; y < ImageHeight(image); y++)
	{
		SetPixelR(image, 0, y, 0);
		SetPixelG(image, 0, y, 0);
		SetPixelB(image, 0, y, 0);
		SetPixelR(image, ImageWidth(image)-1, y, 0);
		SetPixelG(image, ImageWidth(image)-1, y, 0);
		SetPixelB(image, ImageWidth(image)-1, y, 0);


		}
	
	for (x = 0; x < ImageWidth(image); x++)
	{
		SetPixelR(image, x, 0, 0);
		SetPixelG(image, x, 0, 0);
		SetPixelB(image, x, 0, 0);
		SetPixelR(image, x, ImageHeight(image)-1, 0);
		SetPixelG(image, x, ImageHeight(image)-1, 0);
		SetPixelB(image, x, ImageHeight(image)-1, 0);
    }
	
	assert(image);
	DeleteImage(temp_image);
	return image;
	printf("Edge operation is done!\n");
}
	

IMAGE *VFlip(IMAGE *image)
{
	assert(image);
	
    int             x, y;
    unsigned char   r, g, b;

    for (y = 0; y < ImageHeight(image)/2; y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
			r = GetPixelR(image, x, ((image->H)-1-y));
			g = GetPixelG(image, x, ((image->H)-1-y));
			b = GetPixelB(image, x, ((image->H)-1-y));

			SetPixelR(image, x, ((image->H)-1-y), GetPixelR(image, x, y));
			SetPixelG(image, x, ((image->H)-1-y), GetPixelG(image, x, y));
			SetPixelB(image, x, ((image->H)-1-y), GetPixelB(image, x, y));
			
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
        }
    }
	
	assert(image);
	return image;
}


IMAGE *VMirror(IMAGE *image)
{
	assert(image);
	
    int x, y;
    for (y = 0; y < ImageHeight(image)/ 2; y++) 
	{
        for (x = 0; x < ImageWidth(image); x++) 
		{
			SetPixelR(image, x, ((image->H)-1-y), GetPixelR(image, x, y));
			SetPixelG(image, x, ((image->H)-1-y), GetPixelG(image, x, y));
			SetPixelB(image, x, ((image->H)-1-y), GetPixelB(image, x, y));
        }
    }
	assert(image);
	return image;
}


IMAGE *Shuffle(IMAGE *image)
{
	assert(image);
	
    int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
    int block_width = (image->W)/SHUFF_WIDTH_DIV;
    int block_height = (image->H)/SHUFF_HEIGHT_DIV;
    int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV]; 
    int i, j;


    srand(time(NULL));
    for (i = 0; i < SHUFF_WIDTH_DIV; i++) 
	{
        for (j = 0; j< SHUFF_HEIGHT_DIV; j++) 
		{
            block[i][j] = -1;
        }
    }

	while (block_cnt > 0) 
	{
	 
        int dest_height = rand() % SHUFF_HEIGHT_DIV;
        int dest_width = rand() % SHUFF_WIDTH_DIV;
        int src_height = rand() % SHUFF_HEIGHT_DIV;
        int src_width = rand() % SHUFF_WIDTH_DIV;

        if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) 
		{
            for (i = 0; i < block_height; i++) 
			{
                int h_dest = ((dest_height * block_height) + i) % (image->H);
                int h_src  = ((src_height * block_height) + i) % (image->H);
                for (j = 0; j < block_width; j++) 
				{
                    int temp;
                    int w_src  = ((src_width * block_width) + j) % (image->W);
                    int w_dest = ((dest_width * block_width) + j) % (image->W);

                    temp = GetPixelR(image, w_dest, h_dest);
                    SetPixelR(image, w_dest, h_dest, GetPixelR(image,  w_src, h_src));
					SetPixelR(image, w_src, h_src, temp);
					
					temp = GetPixelG(image, w_dest, h_dest);
                    SetPixelG(image, w_dest, h_dest, GetPixelG(image,  w_src, h_src));
					SetPixelG(image, w_src, h_src, temp);
					
					temp = GetPixelB(image, w_dest, h_dest);
                    SetPixelB(image, w_dest, h_dest, GetPixelB(image,  w_src, h_src));
					SetPixelB(image, w_src, h_src, temp);
				}
            }
            block[dest_width][dest_height] = 1;
            block[src_width][src_height] = 1;
            block_cnt -= 2; 
        }

    }
	assert(image);
	return image;

}


IMAGE *AddBorder(IMAGE *image, char color[SLEN], int border_width) 
{
	assert(image);
	
    int x, y;
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Unsurported color.\n");
    }
    const int X_BORDER_WIDTH = border_width * 9 / 16;
    for (y = 0; y < ImageHeight(image); y++) 
	{
        for (x = 0; x < ImageWidth(image); x++) 
		{
            if ((y < border_width) || (y > (image->H) - 1 - border_width) ||
                    (x < X_BORDER_WIDTH) || (x > (image->W) - 1 - X_BORDER_WIDTH)) 
			{
                SetPixelR(image, x, y, border_r);
                SetPixelG(image, x, y, border_g);
                SetPixelB(image, x, y, border_b);
            }
        }
    }
	
	assert(image);
	return image;
}
