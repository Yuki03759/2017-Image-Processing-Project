/********************************************************************/
/* PhotoLab.c : PhotoLab.c for assignment 4 EECS 22, Fall 2017		*/
/* Author: Yuki Hayashi												*/
/* Date: 11/21														*/
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DIPs.h"
#include "FileIO.h"
#include "Advanced.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

void PrintMenu();

int main()
{

	#ifdef DEBUG
	AutoTest();
	return 0;
	#endif
	
	
	int option;
    char fname[SLEN];
		
    char colorOption[SLEN];
	int rc = -1; 
    int target_r, target_g, target_b, threshold;
    double factor_r, factor_g, factor_b;
    int border_width;
	int n = 0;
	int bluramount = 0; 
	int rbits = 0, gbits = 0, bbits = 0; 
	int x, y, W, H;
	int percentage;
	int brightness, contrast;
	int centerX;
	int centerY;
	unsigned int radius;
	IMAGE *image;
	IMAGE *temp = NULL;
	temp = LoadImage("watermark_template");


	PrintMenu();
	printf("Please make your choice: ");
    scanf("%d", &option);
	
	while (option != EXIT) 
	{
        if (option == 1) 
		{
			printf("Please input the file name to load: ");
            scanf("%s", fname); 
            image = LoadImage("HSSOE");
			rc = SUCCESS;
        }
        else if (option >= 2 && option <= 18) 
		{
            if (rc != SUCCESS)   
			{
                printf("No image to process!\n");
            }
			else 
			{
                switch(option) 
				{
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
						SaveImage(fname, image);
                        break;
                    case 3:
                        image = BlackNWhite(image);
                        printf("\"Black & White\" operation is done!\n");
                        break;
                    case 4:
                        image = Negative(image);
                        printf("\"Negative\" operation is done!\n");
                        break;
                    case 5:
                        printf("Enter Red component for the target color: ");
                        scanf("%d", &target_r);
                        printf("Enter Green component for the target color: ");
                        scanf("%d", &target_g);
                        printf("Enter Blue component for the target color: ");
                        scanf("%d", &target_b);
                        printf("Enter threshold for the color difference: ");
                        scanf("%d", &threshold);
                        printf("Enter value for Red component in the target color: ");
                        scanf("%lf", &factor_r);
                        printf("Enter value for Green component in the target color: ");
                        scanf("%lf", &factor_g);
                        printf("Enter value for Blue  component in the target color: ");
                        scanf("%lf", &factor_b);

                        image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                        printf("\"Color Filter\" operation is done!\n");
                        break;
					case 6:
                        image = Edge(image);                                       
						printf("\"Edge\" operation is done!\n");
                        break; 
                    case 7:
                        image = Shuffle(image);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
                    case 8:
                        image = VFlip(image);
                        printf("\"VFlip\" operation is done!\n");
                        break;
                    case 9:
                        image = VMirror(image);
                        printf("\"Vertically Mirror\" operation is done!\n");
                        break;
                    case 10:
                        printf("Enter border width:");
                        scanf("%d", &border_width);
                        printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                        printf("Select border color from the options: ");
                        scanf("%s",colorOption);
                        image = AddBorder(image, colorOption, border_width);
                        printf("\"Border\" operation is done!\n");
                        break;
					case 11:
						printf("Please input noise percentage: ");
						scanf("%d", &n);
						image = AddNoise(image, n);
						printf("\"Noise\" operation is done!\n");
						break;
					case 12:
						image = Sharpen(image);
						printf("\"Sharpen\" operation is done!\n");
						break;
					case 13:
						printf("Enter the number of posterization bits for R channel (1 to 8): ");
						scanf("%d", &rbits);
						printf("Enter the number of posterization bits for G channel (1 to 8): ");
						scanf("%d", &gbits);
						printf("Enter the number of posterization bits for B channel (1 to 8): ");
						scanf("%d", &bbits);
						image = Posterize(image, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
						break;
					
					case 14:
						printf("Please input blue amount: ");
						scanf("%d", &bluramount);
						image = MotionBlur(image, bluramount);
						printf("\"MotionBlur\" operation is done!\n");
						break;
					case 15:
						printf("Please enter the X offset value: ");
						scanf("%d", &x);
						printf("Please enter the Y offset value: ");
						scanf("%d", &y);
						printf("Please input the crop width: ");
						scanf("%d", &W);
						printf("Please input the crop height: ");
						scanf("%d", &H);
						image = Crop(image, x, y, W, H);
						printf("\"Crop\" operation is done!\n");
						break;
					case 16:
						printf("Please input the resizing percentage (integer between 1 - 500):");
						scanf("%d", &percentage);
						image = Resize(image, percentage);
						printf("\"Resize the image\" operation is done!\n");
						break;
					case 17:
						printf("Please input the brightness level (integer between -255 - 255): ");
						scanf("%d", &brightness);
						if ((brightness < -255) | (brightness >255))
						{
							printf("brightness is out of range.\n");
							break;
						}
						printf("Please input the contrast level (integer between -255 - s255): ");
						scanf("%d", &contrast);
						if ((contrast < -255) | (contrast > 255))
						{
							printf("contrast is out of range.\n");
							break;
						}
						image = BrightnessAndContrast(image, brightness, contrast);
						printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
						break;
					case 18:
						image = Watermark(image, temp);
						printf("\"Watermark\" operation is done!\n");
						break; 
                    default:
                        break;
                }
            }
        }
        else if (option == 19) 
		{
            rc = SUCCESS;
			AutoTest();
        }
        else 
		{
            printf("Invalid selection!\n");
        }
		
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
	DeleteImage(temp);
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
    printf("15: Crop an image\n");
    printf("16: Resize an image\n");
    printf("17: Adjust the Brightness and Constast of an image\n");
    printf("18: Add Watermark to an image\n");
    printf("19: Test all functions\n");
    printf("20: Exit\n");
}
