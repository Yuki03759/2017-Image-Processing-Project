/********************************************************************	*/
/* PhotoLab.c: assignment 3 for EECS 22 in Fall 2017             	    */
/*                                                            	     	*/
/* Author Yuki Hayashi         			                   			  	*/
/* 11/07/2017				                            			 	*/
/********************************************************************	*/

#include "DIPs.h"
#include "FileIO.h"
#include "Advanced.h"
#include "Constants.h"


void PrintMenu();
void AutoTest();

int main() 
{
    unsigned char   R[WIDTH][HEIGHT];   /* use three 2-D arrays to store R, G, B components */
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    int option;                 /* user input option */
    char fname[SLEN];           /* input file name */
    char colorOption[SLEN];

	
	#ifdef DEBUG
	AutoTest();
	return 0;
	#endif
	
    PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);

    int rc = -1;                        /* return code of ReadImage() */
    /* ColorFilter() parameters */
    int target_r, target_g, target_b, threshold;
    double factor_r, factor_g, factor_b;
    /* AddBorder() parameter */
    int border_width;
	int n = 0;
	int bluramount = 0;
	int rbits = 0, gbits = 0, bbits = 0;

    while (option != EXIT) 
	{
        if (option == 1) 
		{
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }
        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option <= 14) 
		{
            if (rc != SUCCESS)   
			{
                printf("No image is read.\n");
            }
            /* now image is loaded */
			else 
			{
                switch(option) 
				{
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, R, G, B);
                        break;
                    case 3:
                        BlackNWhite(R, G, B);
                        printf("\"Black & White\" operation is done!\n");
                        break;
                    case 4:
                        Negative(R,G,B);
                        printf("\"Negative\" operation is done!\n");
                        break;
                    case 5:
                        printf("Enter Red   component for the target color: ");
                        scanf("%d", &target_r);
                        printf("Enter Green component for the target color: ");
                        scanf("%d", &target_g);
                        printf("Enter Blue  component for the target color: ");
                        scanf("%d", &target_b);
                        printf("Enter threshold for the color difference: ");
                        scanf("%d", &threshold);
                        printf("Enter value for Red component in the target color: ");
                        scanf("%lf", &factor_r);
                        printf("Enter value for Green component in the target color: ");
                        scanf("%lf", &factor_g);
                        printf("Enter value for Blue  component in the target color: ");
                        scanf("%lf", &factor_b);

                        ColorFilter(R, G, B, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                        printf("\"Color Filter\" operation is done!\n");
                        break;
                    case 6:
                        Edge(R, G, B);                                       
						printf("\"Edge\" operation is done!\n");
                        break;
                    case 7:
                        Shuffle(R, G, B);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
                    case 8:
                        VFlip(R, G, B);
                        printf("\"VFlip\" operation is done!\n");
                        break;
                    case 9:
                        VMirror(R, G, B);
                        printf("\"Vertically Mirror\" operation is done!\n");
                        break;
                    case 10:
                        printf("Enter border width:");
                        scanf("%d", &border_width);
                        printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                        printf("Select border color from the options: ");
                        scanf("%s",colorOption);
                        AddBorder(R, G, B, colorOption, border_width);
                        printf("\"Border\" operation is done!\n");
                        break;
					case 11:
						printf("Please input noise percentage: ");
						scanf("%d", &n);
						Noise(n, R, G, B);
						printf("\"Noise\" operation is done!\n");
						break;
					case 12:
						Sharpen(R, G, B);
						printf("\"Sharpen\" operation is done!\n");
						break;
					case 13:
						printf("Enter the number of posterization bits for R channel (1 to 8): ");
						scanf("%d", &rbits);
						printf("Enter the number of posterization bits for G channel (1 to 8): ");
						scanf("%d", &gbits);
						printf("Enter the number of posterization bits for B channel (1 to 8): ");
						scanf("%d", &bbits);
						Posterize(R, G, B, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
						break;
					case 14:
						printf("Please input blue amount: ");
						scanf("%d", &bluramount);
						MotionBlur(bluramount, R, G, B);
						printf("\"MotionBlur\" operation is done!\n");
						break;

                    default:
                        break;
                }
            }
        }
        else if (option == 15) 
		{
            AutoTest();
            rc = SUCCESS;       /* set returned code SUCCESS, since image is loaded */
        }
        else 
		{
            printf("Invalid selection!\n");
        }
                           
   
        /* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
    return 0;
}

void PrintMenu()
{
        printf("\n----------------------------\n");
        printf(" 1: Load a PPM image\n");
        printf(" 2: Save an image in PPM and JPEG format\n");
        printf(" 3: Change a color image to Black & White\n");
        printf(" 4: Make a negative of an image\n");
        printf(" 5: Color filter an image\n");
        printf(" 6: Sketch the edge of an image\n");
        printf(" 7: Shuffle an image\n");
        printf(" 8: Flip an image vertically\n");
        printf(" 9: Mirror an image vertically\n");
        printf("10: Add border to an image\n");
        printf("11: Add noise to an image\n");
        printf("12: Sharpen an image\n");
        printf("13: Posterize an image\n");
        printf("14: Motion Blur\n");
        printf("15: Test all functions\n");
        printf("16: Exit\n");
}

void AutoTest() 
{
	unsigned char R[WIDTH][HEIGHT] , G[WIDTH][HEIGHT], B[WIDTH][HEIGHT];
	char fname[SLEN] = "HSSOE";

    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
	#ifndef DEBUG
    printf("Black & White tested!\n\n");
	#endif

    LoadImage(fname, R, G, B);
    Negative(R, G, B);
    SaveImage("negative", R, G, B);
	#ifndef DEBUG
    printf("Negative tested!\n\n");
	#endif

    LoadImage(fname, R, G, B);
    ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
    SaveImage("colorfilter", R, G, B);
	#ifndef DEBUG
    printf("Color Filter tested!\n\n");
	#endif

    LoadImage(fname, R, G, B);
    Edge(R, G, B);
    SaveImage("edge", R, G, B);
	#ifndef DEBUG
    printf("Edge Detection tested!\n\n");
	#endif

    LoadImage(fname, R, G, B);
    VMirror(R, G, B);
    SaveImage("vmirror", R, G, B);
	#ifndef DEBUG
    printf("VMirror tested!\n\n");
	#endif

    LoadImage(fname, R, G, B);
    VFlip(R, G, B);
    SaveImage("vflip", R, G, B);
	#ifndef DEBUG
    printf("VFlip tested!\n\n");
	#endif

    LoadImage(fname, R, G, B);
    Shuffle(R, G, B);
    SaveImage("shuffle", R, G, B);
	#ifndef DEBUG
    printf("Shuffle tested!\n\n");
	#endif

    LoadImage(fname, R, G, B);
    AddBorder(R, G, B, "yellow", 32);
    SaveImage("border", R, G, B);
	#ifndef DEBUG
    printf("Border tested!\n\n");
	#endif
	
    LoadImage(fname, R, G, B);
    Noise(30, R, G, B);
    SaveImage("noise", R, G, B);
	#ifndef DEBUG
    printf("Noise tested!\n\n");
	#endif
	
    LoadImage(fname, R, G, B);
    Sharpen (R, G, B);
    SaveImage("sharpen", R, G, B);
	#ifndef DEBUG
    printf("Sharpen	tested!\n\n");
	#endif

	LoadImage(fname, R, G, B);
    Posterize (R, G, B, 7, 7, 7);
    SaveImage("posterize", R, G, B);
	#ifndef DEBUG
    printf("posterize tested!\n\n");
	#endif

	LoadImage(fname, R, G, B);
    MotionBlur (50, R, G, B);
    SaveImage("blur", R, G, B);
	#ifndef DEBUG
    printf("Blur tested!\n\n");
	#endif

}
 
