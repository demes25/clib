/* Demetre Seturidze
 * Library
 * Images
 * [Header]
 */

#ifndef IMAGE
#define IMAGE

#include"./basics.h"
#include"./matrix.h"


// BINARY IMAGES:

typedef struct Bitmap {
    nat height;
    nat width;
    boolean** grid;

    nat refs;
} Bitmap;


// back-end ("behind the scenes") functions

Bitmap* bts__emptyBitmap();
void bts__wipeBitmap(Bitmap* b);
void bts__deleteBitmap(Bitmap* b);
void bts__initBitmap(Bitmap* b, nat h, nat w);

boolean bts__read_Bitmap(Bitmap* empty, cstr filename);


// front-end functions

void deleteBitmap(Bitmap* b);
Bitmap* newBitmap(nat h, nat w);

boolean getBit(Bitmap* b, nat i, nat j);
void setBit(Bitmap* b, nat i, nat j, boolean k);

void print_Bitmap(Bitmap* b);
void println_Bitmap(Bitmap* b);

Bitmap* importBitmap(cstr filename);
boolean exportBitmap(Bitmap* b, cstr filename);

Matrix* newMatrix_Bitmap(Bitmap* b);



// GREYSCALE IMAGES:

typedef struct Greyscale {
    nat height;
    nat width;
    byte** grid;

    nat refs;
} Greyscale;

// back-end ("behind the scenes") functions

Greyscale* bts__emptyGreyscale();
void bts__wipeGreyscale(Greyscale* i);
void bts__deleteGreyscale(Greyscale* i);
void bts__initGreyscale(Greyscale* i, nat h, nat w);

boolean bts__read_Greyscale(Greyscale* empty, cstr filename);



// front-end functions

void deleteGreyscale(Greyscale* i);
Greyscale* newGreyscale(nat h, nat w);
Greyscale* newGreyscale_Bitmap(Bitmap* b);
Greyscale* newGreyscale_Matrix(Matrix* M);

byte getByte(Greyscale* i, nat j, nat k);
void setByte(Greyscale* i, nat j, nat k, byte gs);

Greyscale* importGreyscale(cstr filename);
boolean exportGreyscale(Greyscale* i, cstr filename);

Matrix* newMatrix_Greyscale(Greyscale* i);




// PIXEL IMAGES:

// range between 255 and 0.
typedef struct {
    byte r, g, b;
} Pixel;

typedef struct Image {
    nat height;
    nat width;
    Pixel** grid;

    nat refs;
} Image;


// back-end ("behind the scenes") functions

Image* bts__emptyImage();
void bts__wipeImage(Image* i);
void bts__deleteImage(Image* i);
void bts__initImage(Image* i, nat h, nat w);

boolean bts__read_Image(Image* empty, cstr filename);


// front-end functions

void deleteImage(Image* i);
Image* newImage(nat h, nat w);
Image* newImage_Bitmap(Bitmap* b);
Image* newImage_Greyscale(Greyscale* gs);
Image* newImage_Matrix(Matrix* M);

Pixel getPixel(Image* i, nat j, nat k);
void setPixel(Image* i, nat j, nat k, Pixel rgb);

Image* importImage(cstr filename);
boolean exportImage(Image* i, cstr filename);

Greyscale* newGreyscale_Image(Image* i);
Matrix* newMatrix_Image(Image* i);

#endif