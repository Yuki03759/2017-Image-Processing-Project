#include "Advanced.h"

void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int p = 0, i = 0, x = 0, y = 0;
	p = WIDTH*HEIGHT*n/100;
	srand(0);
	for (i=0; i<p; i++)
	{
		x = rand()%WIDTH;
		y = rand()%HEIGHT;
		R[x][y] = 255;
		G[x][y] = 255;
		B[x][y] = 255;
	
	}
	
}

void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_temp[WIDTH][HEIGHT];
	unsigned char G_temp[WIDTH][HEIGHT];
	unsigned char B_temp[WIDTH][HEIGHT]; 
	int a, b, c;
	
	int k,j;
	for (k=0; k < HEIGHT; k++)
		for (j = 0; j < WIDTH; j++)
		{	
			R_temp[j][k] = R[j][k];
			G_temp[j][k] = G[j][k];
			B_temp[j][k] = B[j][k]; 
		}
	int y, x;
	for (y = 1; y < HEIGHT-1; y++)
		for (x=1; x < WIDTH-1; x++)
			{
		
			a = 9*R_temp[x][y]-R_temp[x-1][y-1]-R_temp[x][y-1]-R_temp[x+1][y-1]-R_temp[x-1][y]-R_temp[x+1][y]-R_temp[x-1][y+1]-R_temp[x][y+1]-R_temp[x+1][y+1];
			b = 9*G_temp[x][y]-G_temp[x-1][y-1]-G_temp[x][y-1]-G_temp[x+1][y-1]-G_temp[x-1][y]-G_temp[x+1][y]-G_temp[x-1][y+1]-G_temp[x][y+1]-G_temp[x+1][y+1];
			c = 9*B_temp[x][y]-B_temp[x-1][y-1]-B_temp[x][y-1]-B_temp[x+1][y-1]-B_temp[x-1][y]-B_temp[x+1][y]-B_temp[x-1][y+1]-B_temp[x][y+1]-B_temp[x+1][y+1];	
	
			if (a > 255)
			{
				a = 255;
			}
			else if (a < 0 )
			{
				a = 0;
			}
			if (b > 255)
			{
				b = 255;
			}
			else if (b < 0)
			{
				b = 0;
			}
			if (c > 255)
			{
				c = 255;
			}
			else if (c < 0)
			{
				c = 0;
			}
		
			R[x][y] = a;
			G[x][y] = b;
			B[x][y] = c;
		}				
}

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int x, y, i;
	for (y = 0; y < HEIGHT-1; y++)
		for (x = 0; x < WIDTH-1; x++)
		{
			R[x][y] = R[x][y] >> rbits << rbits;
			for (i = 0; i < rbits -1; i++)
				R[x][y] |=  (1<<i);
			G[x][y] = G[x][y] >> gbits << gbits;
			for (i = 0; i < gbits - 1; i++)
				G[x][y] |=  (1<<i);
			B[x][y] = B[x][y] >> bbits << bbits;
			for (i = 0; i <bbits - 1; i++)
				B[x][y] |=  (1<<i);
		}
}

void MotionBlur(int bluramount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int r_ave = 0, g_ave = 0, b_ave = 0;
	int i;
	
	int x, y; 
	for (y = 0; y < HEIGHT; y++)
		for(x = 0; x < WIDTH; x++)
		{
			r_ave = 0;
			g_ave = 0;
			b_ave = 0;
			
			for (i=1; i <= bluramount; i++)
				{
					if(x+i< WIDTH-1){
					r_ave += R[x+i][y];
					g_ave += G[x+i][y];
					b_ave += B[x+i][y];
					}	
				}
			
			r_ave /= bluramount;
			g_ave /= bluramount;
			b_ave /= bluramount;
			
			R[x][y] = ( R[x][y] + r_ave )/2;
			G[x][y] = ( G[x][y] + g_ave )/2;
			B[x][y] = ( B[x][y] + b_ave )/2;
			
			
			
		}
}

