/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22 in Fall 2017                 */
/*                                                                   */
/* Author Yuki Hayashi         			                     */
/* 10/23/2017				                             */
/*********************************************************************/

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/

const int WIDTH  = 600;	/* image width */
const int HEIGHT = 400;	/* image height */
const int SLEN   =  80;	/* max. string length */

/*** function declarations ***/

void PrintMenu();

/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);


/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]);


/* sharpen the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], int r, int g, int b, int border_width);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);


/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/*** main program ***/
/*	int R_temp[WIDTH][HEIGHT] =  R[WIDTH][HEIGHT]; */

int main(void)
{
	unsigned char R[WIDTH][HEIGHT];
	unsigned char G[WIDTH][HEIGHT];
	unsigned char B[WIDTH][HEIGHT];
	int target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b;
	int r,g ,b, border_width;	
 
	int exit = 1, choice;
	char name[SLEN];
	char color[SLEN];	
	while (exit == 1)	/*while loop until the user click 12*/
	{
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &choice);
		
		switch (choice)	/*menu option*/
		{
		case 1:		/*load*/
			printf("Please input the file name to load: ");
			scanf("%75s", name);
			LoadImage(name, R, G, B);
/*			if (LoadImage("HSSOE", R, G, B) != 0)
   			 { return 10;}*/
			break;
    		case 2:		/*save*/
			printf("Please input the file name to save: ");
			scanf("%75s", name);
			SaveImage(name, R, G, B);
			break;
		case 3:		/*black and white*/
			BlackNWhite(R, G, B);
			break;
		case 4:		/*negative*/
			Negative(R, G, B);
			break;
		case 5:		/*colorfilter*/
			printf("Enter Red component for the target color: ");
			scanf("%d", &target_r);
			printf("Enter Green component for the target color: ");
			scanf("%d", &target_g);
			printf("Enter Blue component for the target color: ");
			scanf("%d", &target_b);
			printf("Enter threshold for the color difference: ");
			scanf("%d", &threshold);
			printf("Enter value Red for component in the target color: ");
			scanf("%d", &replace_r);
			printf("Enter value Green for component in the target color: ");
			scanf("%d", &replace_g);
			printf("Enter value Blue for component in the target color: ");
			scanf("%d", &replace_b);
			ColorFilter(R, G, B, target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b); 
			break;
		case 6: /*edge*/
			Edge(R, G, B);
			break;
		case 7: /*shuffle*/
			Shuffle(R, G, B);
			break;
		case 8: /*vertical flip*/
			VFlip(R, G, B);
			break;
		case 9:	/*vertical mirro*/
			VMirror(R, G, B);
			break;
		case 10:/*add border*/	
			printf("Enter border witdth: ");
			scanf("%d", &border_width);
			printf("Avaiable border colors: black, white, red, green, blue, yellow, cyan, pink, organge: ");
			scanf("%s", color);
			if(strcmp(color, "black") == 0)
			{
				r = 0;
				g = 0;
				b = 0;	
			}
			else if (strcmp(color, "white") == 0)
			{
				r = 255;
				g = 255;
				b = 255;
			}	
			else if (strcmp(color, "red") == 0)
			{
				r = 255;
				g = 0;
				b = 0;
			}
			else if (strcmp(color, "green") == 0)
			{
				r = 0;
				g = 255;
				b = 0;
			}	
			else if (strcmp(color, "blue") == 0)
			{
				r = 0;
				g = 0;
				b = 255;
			}	
			else if (strcmp(color, "yellow") == 0)
			{
				r = 255;
				g = 255;
				b = 0;
			}	
			else if (strcmp(color, "cyan") == 0)
			{
				r = 0;
				g = 255;
				b = 255;
			}		
			else if (strcmp(color, "pink") == 0)
			{
				r = 255;
				g = 192;
				b = 203;
			}	
			else if (strcmp(color, "orange") == 0)
			{
				r = 255;
				g = 165;
				b = 0;
			}
			AddBorder(R, G, B, r, g, b, border_width);
			break;
		case 11: /*autotest*/
			AutoTest(R, G, B);
			break;
		case 12: /*exit*/
			exit = 0;	
			break;
		}

    }

    return 0;
} /* end of main */


/*** function definitions ***/

/* read a photo from the specified file into the specified */
/* RGB data structure; returns 0 for success, >0 for error */


int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE           *File;
        char            Type[SLEN];
        int             Width, Height, MaxValue;
        int             x, y;
        char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];      
        strcpy(fname_tmp, fname);
        strcat(fname_tmp, ftype);

        File = fopen(fname_tmp, "r");
        if (!File) {
                printf("Cannot open file \"%s\" for reading!\n", fname);
                return 1;
                    }
        fscanf(File, "%79s", Type);
        if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
                printf("\nUnsupported file format!\n");
                return 2;
                                                                }
        fscanf(File, "%d", &Width);
        if (Width != WIDTH) {
                printf("\nUnsupported image width %d!\n", Width);
                return 3;
                             }
        fscanf(File, "%d", &Height);
        if (Height != HEIGHT) {
                 printf("\nUnsupported image height %d!\n", Height);
                 return 4;
                              }
        fscanf(File, "%d", &MaxValue);
        if (MaxValue != 255) {
                 printf("\nUnsupported image maximum value %d!\n", MaxValue);
                 return 5;
                            }
        if ('\n' != fgetc(File)) {
                 printf("\nCarriage return expected!\n");
                 return 6;
                                }
        for (y = 0; y < HEIGHT; y++)
             for (x = 0; x < WIDTH; x++) {
                         R[x][y] = fgetc(File);
                         G[x][y] = fgetc(File);
                         B[x][y] = fgetc(File);
                                         }
        if (ferror(File)) {
             printf("\nFile error while reading from file!\n");
             return 7;
                           }
        printf("%s was loaded successfully!\n", fname_tmp);
        fclose(File);
        return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE    *File;
        int x, y;
        char    SysCmd[SLEN * 5];
        char    ftype[] = ".ppm";
        char    fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char    fname_tmp2[SLEN];

        strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
        strcat(fname_tmp2, ftype);

        File = fopen(fname_tmp2, "w");
        if (!File) {
                printf("Cannot open file \"%s\" for writing!\n", fname);
                return 1;
                   }
        fprintf(File, "P6\n");
        fprintf(File, "%d %d\n", WIDTH, HEIGHT);
        fprintf(File, "255\n");
        for (y = 0; y < HEIGHT; y++)
                 for (x = 0; x < WIDTH; x++) {
                               fputc(R[x][y], File);
                               fputc(G[x][y], File);
                               fputc(B[x][y], File);
                                              }
         if (ferror(File)) {
                  printf("\nFile error while writing to file!\n");
                  return 2;
                            }
         fclose(File);
         printf("%s was saved successfully.\n", fname_tmp2);
   /*
     *      * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     *           * and make it world readable
                                   *                */
        sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
        if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
                                  }
        printf("%s.jpg was stored for viewing.\n", fname_tmp);
        return 0;
}

void PrintMenu()
{
	printf("--------------------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG formet\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image \n");	
	printf(" 6: Sketch the edge of an image \n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image vertically\n");
	printf("10: Adder Border to an iamge\n");
	printf("11: Test all functions\n");
	printf("12: Exit\n");
}
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT])
{
	int ave;
	for (int y = 0; y <HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			{
				ave = (R[x][y] + G[x][y] + B[x][y])/3;
				R[x][y] = ave;
				G[x][y] = ave;
				B[x][y] = ave; 
			}
	printf("Black & White operation is done!\n");
}

void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT])
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			R[x][y] = 255 - R[x][y];
     			G[x][y] = 255 - G[x][y];
			B[x][y] = 255 - B[x][y];
		} 
	printf("Negative operation is done!\n");
}

void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			if(R[x][y] < target_r + threshold && R[x][y] > target_r - threshold && G[x][y] < target_g + threshold && G[x][y] > target_g - threshold && B[x][y] < target_b + threshold && B[x][y] > target_b - threshold)
			{	
				R[x][y] = replace_r;
				G[x][y] = replace_g;
				B[x][y] = replace_b;
			}
		}
	printf("Color filter operation is done!\n");
		
	
}
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_temp[WIDTH][HEIGHT];
	unsigned char G_temp[WIDTH][HEIGHT];
	unsigned char B_temp[WIDTH][HEIGHT]; 
	int a, b, c;
	
	for (int y=0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{	
			R_temp[x][y] = R[x][y];
			G_temp[x][y] = G[x][y];
			B_temp[x][y] = B[x][y]; 
		}

	for (int y = 1; y < HEIGHT-1; y++)
		for (int x=1; x < WIDTH-1; x++)
			{
		
			a = 8*R_temp[x][y]-R_temp[x-1][y-1]-R_temp[x][y-1]-R_temp[x+1][y-1]-R_temp[x-1][y]-R_temp[x+1][y]-R_temp[x-1][y+1]-R_temp[x][y+1]-R_temp[x+1][y+1];

		
			b = 8*G_temp[x][y]-G_temp[x-1][y-1]-G_temp[x][y-1]-G_temp[x+1][y-1]-G_temp[x-1][y]-G_temp[x+1][y]-G_temp[x-1][y+1]-G_temp[x][y+1]-G_temp[x+1][y+1];
			c = 8*B_temp[x][y]-B_temp[x-1][y-1]-B_temp[x][y-1]-B_temp[x+1][y-1]-B_temp[x-1][y]-B_temp[x+1][y]-B_temp[x-1][y+1]-B_temp[x][y+1]-B_temp[x+1][y+1];	
	
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
	printf("Edge operation is done!\n");
}

void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT])
{	
	unsigned char R_temp[WIDTH][HEIGHT], G_temp[WIDTH][HEIGHT], B_temp[WIDTH][HEIGHT];

	int from_row, from_column, to_row, to_column;
	int s[16];


	for (int i = 0; i < 16; i++)
	{
		int okay =0;
		
		while (!okay)
		{
			s[i] = rand()%16;
			okay = 1;
	
			for (int k = 0; k < i; k++)
			{
				if(s[i] == s[k])
					okay = 0;
			}
		}
	
			from_row = i/4;
			from_column = i%4;
			to_row = s[i]/4;
			to_column = s[i] % 4;

			for (int r = 0; r < 100; r++)
				for (int c =0; c < 150; c++)
		
			{

					R_temp[to_column*150+c][to_row*100+r] = R[from_column*150+c][from_row*100+r];
					G_temp[to_column*150+c][to_row*100+r] = G[from_column*150+c][from_row*100+r];
					B_temp[to_column*150+c][to_row*100+r] = B[from_column*150+c][from_row*100+r];
			}
	}
	
	for(int y=0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
			{
				R[x][y] = R_temp[x][y];
				G[x][y] = G_temp[x][y];
				B[x][y] = B_temp[x][y];
			}

	printf("Shuffle operation is done!\n");	
}

void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT])
{	
	unsigned char R_temp[WIDTH][HEIGHT], G_temp[WIDTH][HEIGHT], B_temp[WIDTH][HEIGHT];

	for (int y= 0; y< HEIGHT; y++)
		for (int x =0; x< WIDTH; x++)
		{
			R_temp[x][HEIGHT-1-y] = R[x][y];
			G_temp[x][HEIGHT-1-y] = G[x][y];
			B_temp[x][HEIGHT-1-y] = B[x][y];
		}
	
	for ( int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			R[x][y] = R_temp[x][y];
			G[x][y] = G_temp[x][y];
			B[x][y] = B_temp[x][y];
	 	}
	
	printf("VFlip operation is done!\n");
}

void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_temp[WIDTH][HEIGHT], G_temp[WIDTH][HEIGHT], B_temp[WIDTH][HEIGHT];


	for (int y=0; y< HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			R_temp[x][HEIGHT-1-y] = R[x][y];
			G_temp[x][HEIGHT-1-y] = G[x][y];
			B_temp[x][HEIGHT-1-y] = B[x][y];
		}
		
	for (int y = 200; y < HEIGHT-1; y++)
		for (int x = 0; x < WIDTH-1; x++)
		{
			R[x][y] = R_temp[x][y];
			G[x][y] = G_temp[x][y];
			B[x][y] = B_temp[x][y];
		}
	
	SaveImage("vmirror", R, G, B);
	printf("VMirror opeartion is done!\n");
}

void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], int r, int g, int b, int border_width)
{
	int border_height;
	border_height = (9*border_width)/16;

	for (int y = 0; y<border_width/2; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;			
		}
	for (int y = HEIGHT-border_width/2; y<HEIGHT; y++)
		for (int x=0; x<WIDTH; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	for (int y = 0; y<HEIGHT; y++)
		for (int x = 0; x<border_height/2; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	for (int y = 0; y<HEIGHT; y++)
		for (int x = WIDTH-border_height/2; x<WIDTH; x++)
		{
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	printf("Border operation is done!\n");	
	
}	

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT])
{
	char fname[5] = "HSSOE";
	char sname[SLEN];

	LoadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	printf("Black and white tested!\n\n");

	LoadImage(fname, R, G, B);
	Negative(R, G, B);
	strcpy(sname, "negative");
	SaveImage(sname, R, G, B);
	printf("Negative tested!\n\n");	
	
	LoadImage(fname, R, G, B);
	ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	printf("Color Filter tested!\n\n");

	LoadImage(fname, R, G, B);
	Edge(R, G, B);
	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
	printf("Edge tested!\n\n");
	
	LoadImage(fname, R, G, B);
	Shuffle(R, G, B);
	strcpy(sname, "shuffle");
	SaveImage(sname, R, G, B);
	printf("Shuffle tested!\n\n");

	LoadImage(fname, R, G, B);
	VFlip(R, G, B);
	strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
	printf("VFlip tested!\n\n");

	LoadImage(fname, R, G, B);
	VMirror(R, G, B);
	strcpy(sname, "vmirror");
	SaveImage(sname, R, G, B);
	printf("VMirror tested!\n\n");

	LoadImage(fname, R, G, B);
	AddBorder(R, G, B, 255, 255, 255, 64);
	strcpy(sname, "border");
	SaveImage(sname, R, G, B);
	printf("AddBorder tested!\n\n"); 
	

}




/*

 
        .
        .
        .
        .
        .
 
 
 
*/




/* EOF */
