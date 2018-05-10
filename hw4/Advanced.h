#ifndef ADVANCED_H
#define ADVANCED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "Constants.h"
#include "FileIO.h"

IMAGE *AddNoise(IMAGE *image, int n);
IMAGE *Sharpen(IMAGE *image);
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits);
IMAGE *MotionBlur(IMAGE *image, int bluramount);

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H);
IMAGE *Resize(IMAGE *image, int percentage);
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image);



#endif /*ADVANCE_H*/

/*EOF Advanced.h*/

