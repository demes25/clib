/* Demetre Seturidze
 * Library
 * Images
 */

#include"./image.h"

// This will handle image processing, reading and saving images, etc.


// BINARY IMAGES:

Bitmap* bts__emptyBitmap(){
    return (Bitmap*)malloc(sizeof(Bitmap));
}

void bts__wipeBitmap(Bitmap* b) {
    for (nat j = 0; j < b -> height; j++)
        free(b -> grid[j]);
    free(b -> grid);
}

void bts__deleteBitmap(Bitmap* b) {
    bts__wipeBitmap(b);
    free(b);
}

void bts__initBitmap(Bitmap* b, nat h, nat w) {
    b -> height = h;
    b -> width = w;
    b -> refs = 0;

    b -> grid = (boolean**)malloc(sizeof(boolean*) * h);
    for (nat j = 0; j < h; j++)
        b -> grid[j] = (boolean*)malloc(sizeof(boolean) * w);
}



void deleteBitmap(Bitmap* b) {
    if (b && !(b -> refs && --(b -> refs))) bts__deleteBitmap(b);
}

Bitmap* newBitmap(nat h, nat w) {
    Bitmap* b = bts__emptyBitmap();
    bts__initBitmap(b, h, w);
    return b;
}

boolean getBit(Bitmap* b, nat i, nat j) {
    return b -> grid[i][j];
}

void setBit(Bitmap* b, nat i, nat j, boolean k){
    b -> grid[i][j] = k;
}


void print_Bitmap(Bitmap* b) {
    nat lastRow = b -> height - 1;
    nat lastCol = b -> width - 1;

    for (nat i = 0; i < lastRow; i++) {
        for (nat j = 0; j < lastCol; j++)
            print_cstr(b -> grid[i][j] ? "1 " : "0 ");
        print_cstr(b -> grid[i][lastCol] ? "1\n" : "0\n");
    }
    for (nat j = 0; j < lastCol; j++)
        print_cstr(b -> grid[lastRow][j] ? "1 " : "0 ");
    print_cstr(b -> grid[lastRow][lastCol] ? "1" : "0");
}

void println_Bitmap(Bitmap* b) {
    print_Bitmap(b); println();
}

// reader/writer

boolean bts__read_Bitmap(Bitmap* empty, cstr filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) return False;

    // formatting (NO COMMENTS):
    // 
    // P1\n
    // w h\n
    // (img)

    char l[3];
    nat w, h;

    fgets(l, 3, file);

    if (!(l[0] == 'P' && l[1] == '1') ||
        fscanf(file, "%d %d\n", &w, &h) < 0 ||
        (w < 0 || h < 0)) return False;

    bts__initBitmap(empty, h, w);
    int temp;

    for (nat i = 0; i < h; i++)
        for (nat j = 0; j < w; j++){
            if (fscanf(file, "%d ", &temp) < 0 ||
                !(temp == 0 || temp == 1)) return False;
            else empty -> grid[i][j] = (boolean)temp;
        }
    
    fclose(file);

    return True;
}

Bitmap* importBitmap(cstr filename) {
    Bitmap* b = bts__emptyBitmap();
    if (bts__read_Bitmap(b, filename)) return b;
    else {deleteBitmap(b); return null;}
}

boolean exportBitmap(Bitmap* b, cstr filename) {
    // b MUST NOT BE EMPTY

    FILE* file = fopen(filename, "w");

    if (file == NULL) return False;

    // formatting:
    // 
    // P1\n
    // w h\n
    // (img)

    if (!fprintf(file, "P1\n%d %d\n", b -> width, b -> height)) return False;

    for (nat i = 0; i < b -> height; i++)
        for (nat j = 0; j < b -> width; j++)
            if (!fprintf(file, "%d ", (b -> grid[i][j]) ? 1 : 0)) 
                return False;

    fclose(file);

    return True;
}


// Matrix conversions:

Matrix* newMatrix_Bitmap(Bitmap* b) {
    Matrix* result = newMatrix(b -> height, b -> width);

    for (nat i = 0; i < b -> height; i++)
    for (nat j = 0; j < b -> width; j++)
        setEntry(result, i, j, (double)((nat)(b -> grid[i][j])));
    
    return result;
}






// GREYSCALE IMAGES:

Greyscale* bts__emptyGreyscale() {
    return (Greyscale*)malloc(sizeof(Greyscale));
}

void bts__wipeGreyscale(Greyscale* i) {
    for (nat j = 0; j < i -> height; j++)
        free(i -> grid[j]);
    free(i -> grid);
}

void bts__deleteGreyscale(Greyscale* i) {
    bts__wipeGreyscale(i);
    free(i);
}

void bts__initGreyscale(Greyscale* i, nat h, nat w) {
    i -> height = h;
    i -> width = w;
    i -> refs = 0;

    i -> grid = (byte**)malloc(sizeof(byte*) * h);
    for (nat j = 0; j < h; j++)
        i -> grid[j] = (byte*)malloc(sizeof(byte) * w);
}



void deleteGreyscale(Greyscale* i) {
    if (i && !(i -> refs && --(i -> refs))) bts__deleteGreyscale(i);
}

Greyscale* newGreyscale(nat h, nat w) {
    Greyscale* i = bts__emptyGreyscale();
    bts__initGreyscale(i, h, w);
    return i;
}

Greyscale* newGreyscale_Bitmap(Bitmap* b) {
    Greyscale* i = bts__emptyGreyscale();
    bts__initGreyscale(i, b -> height, b -> width);

    for (nat k = 0; k < i -> width; k++) 
        for (nat j = 0; j < i -> height; j++)
            i -> grid[j][k] = b -> grid[j][k] ? byte_max : 0;

    return i;
}

Greyscale* newGreyscale_Matrix(Matrix* M) {
    // M must be normalized to 255, otherwise will truncate.
    // Additional condition is that the height of M must be divisible by 3.
    // Treats M as a grid-vector, where the top block entry is the red grid,
    // middle block entry is the green grid, and lower block entry is the blue grid.

    Greyscale* i = bts__emptyGreyscale();
    bts__initGreyscale(i, M -> height, M -> width);

    for (nat k = 0; k < M -> width; k++) 
        for (nat j = 0; j < i -> height; j++) 
            i -> grid[j][k] = (byte)((MIN(byte_max, ABS(getEntry(M, j, k)))));

    return i;
}




byte getByte(Greyscale* i, nat j, nat k) {
    return i -> grid[j][k];
}

void setByte(Greyscale* i, nat j, nat k, byte gs){
    i -> grid[j][k] = gs;
}




boolean bts__read_Greyscale(Greyscale* empty, cstr filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) return False;

    // formatting (NO COMMENTS):
    // 
    // P2\n
    // w h max\n
    // (img)

    char l[32];
    nat w, h, max;

    fgets(l, 32, file);

    if (!(l[0] == 'P' && l[1] == '2' && l[2] == '\n') ||
        fscanf(file, "%d %d %d\n", &w, &h, &max) < 0 ||
        (w < 0 || h < 0 || max != byte_max)) return False;

    bts__initGreyscale(empty, h, w);
    int gs;

    for (nat i = 0; i < h; i++)
        for (nat j = 0; j < w; j++){
            if (fscanf(file, "%d ", &gs) < 0 ||
                (gs > byte_max)) return False;
            else 
                empty -> grid[i][j] = gs;
        }
    
    fclose(file);

    return True;

}


Greyscale* importGreyscale(cstr filename) {
    Greyscale* i = bts__emptyGreyscale();
    if (bts__read_Greyscale(i, filename)) return i;
    else {deleteGreyscale(i); return null;}
}

boolean exportGreyscale(Greyscale* i, cstr filename) {
    // i MUST NOT BE EMPTY

    FILE* file = fopen(filename, "w");

    if (file == NULL) return False;

    // formatting:
    // 
    // P2\n
    // w h max\n
    // (img)

    if (!fprintf(file, "P2\n%d %d %d\n", i -> width, i -> height, byte_max)) return False;

    for (nat k = 0; k < i -> height; k++)
        for (nat j = 0; j < i -> width; j++){
            int gs = (int)(i -> grid[k][j]);

            if (!fprintf(file, "%d ", gs)) 
                return False;
        }
    
    fclose(file);

    return True;
}


// conversions

Matrix* newMatrix_Greyscale(Greyscale* i) {
    // no conditions on i

    Matrix* M = bts__emptyMatrix();
    bts__initMatrix(M, i -> height, i -> width);

    for (nat j = 0; j < i -> height; j++)
    for (nat k = 0; k < i -> width; k++)
        setEntry(M, j, k, (double)(i -> grid[j][k]));

    return M;
}





// PIXEL IMAGES:

Image* bts__emptyImage() {
    return (Image*)malloc(sizeof(Image));
}

void bts__wipeImage(Image* i) {
    for (nat j = 0; j < i -> height; j++)
        free(i -> grid[j]);
    free(i -> grid);
}

void bts__deleteImage(Image* i) {
    bts__wipeImage(i);
    free(i);
}

void bts__initImage(Image* i, nat h, nat w) {
    i -> height = h;
    i -> width = w;
    i -> refs = 0;

    i -> grid = (Pixel**)malloc(sizeof(Pixel*) * h);
    for (nat j = 0; j < h; j++)
        i -> grid[j] = (Pixel*)malloc(sizeof(Pixel) * w);
}



void deleteImage(Image* i) {
    if (i && !(i -> refs && --(i -> refs))) bts__deleteImage(i);
}


Image* newImage(nat h, nat w) {
    Image* i = bts__emptyImage();
    bts__initImage(i, h, w);
    return i;
}

Image* newImage_Bitmap(Bitmap* b) {
    Image* i = bts__emptyImage();
    bts__initImage(i, b -> height, b -> width);

    for (nat k = 0; k < i -> width; k++) {
        for (nat j = 0; j < i -> height; j++) {
            byte c = b -> grid[j][k] ? byte_max : 0;
            i -> grid[j][k].r = c;
            i -> grid[j][k].g = c;
            i -> grid[j][k].b = c;
        }
    }

    return i;
}

Image* newImage_Greyscale(Greyscale* gs) {
    Image* i = bts__emptyImage();
    bts__initImage(i, gs -> height, gs -> width);

    for (nat k = 0; k < i -> width; k++) {
        for (nat j = 0; j < i -> height; j++) {
            byte c = gs -> grid[j][k];
            i -> grid[j][k].r = c;
            i -> grid[j][k].g = c;
            i -> grid[j][k].b = c;
        }
    }

    return i;
}

Image* newImage_Matrix(Matrix* M) {
    // M must be normalized to 255, otherwise will truncate.
    // Additional condition is that the height of M must be divisible by 3.
    // Treats M as a grid-vector, where the top block entry is the red grid,
    // middle block entry is the green grid, and lower block entry is the blue grid.

    Image* i = bts__emptyImage();
    bts__initImage(i, M -> height/3, M -> width);

    nat l = 2 * i -> height;

    for (nat k = 0; k < M -> width; k++) {
        for (nat j = 0; j < i -> height; j++) {
            i -> grid[j][k].r = (byte)MIN(byte_max, ABS(getEntry(M, j, k)));
            i -> grid[j][k].g = (byte)MIN(byte_max, ABS(getEntry(M, i -> height + j, k)));
            i -> grid[j][k].b = (byte)MIN(byte_max, ABS(getEntry(M, l + j, k))); 
        }
    }

    return i;
}



Pixel getPixel(Image* i, nat j, nat k) {
    return i -> grid[j][k];
}

void setPixel(Image* i, nat j, nat k, Pixel rgb){
    i -> grid[j][k] = rgb;
}




boolean bts__read_Image(Image* empty, cstr filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) return False;

    // formatting (NO COMMENTS):
    // 
    // P3\n
    // w h max\n
    // (img)

    char l[32];
    nat w, h, max;

    fgets(l, 32, file);

    if (!(l[0] == 'P' && l[1] == '3' && l[2] == '\n') ||
        fscanf(file, "%d %d %d\n", &w, &h, &max) < 0 ||
        (w < 0 || h < 0 || max != byte_max)) return False;

    bts__initImage(empty, h, w);
    int r, g, b;

    for (nat i = 0; i < h; i++)
        for (nat j = 0; j < w; j++){
            if (fscanf(file, "%d %d %d ", &r, &g, &b) < 0 ||
                (r > byte_max || g > byte_max || b > byte_max)) return False;
            else {
                empty -> grid[i][j].r = r;
                empty -> grid[i][j].g = g;
                empty -> grid[i][j].b = b;
            }
        }
    
    fclose(file);

    return True;

}


Image* importImage(cstr filename) {
    Image* i = bts__emptyImage();
    if (bts__read_Image(i, filename)) return i;
    else {deleteImage(i); return null;}
}

boolean exportImage(Image* i, cstr filename) {
    // i MUST NOT BE EMPTY

    FILE* file = fopen(filename, "w");

    if (file == NULL) return False;

    // formatting:
    // 
    // P3\n
    // w h max\n
    // (img)

    if (!fprintf(file, "P3\n%d %d %d\n", i -> width, i -> height, byte_max)) return False;

    for (nat k = 0; k < i -> height; k++)
        for (nat j = 0; j < i -> width; j++){
            int r = (int)(i -> grid[k][j].r);
            int g = (int)(i -> grid[k][j].g);
            int b = (int)(i -> grid[k][j].b);

            if (!fprintf(file, "%d %d %d ", r, g, b)) 
                return False;
        }
    
    fclose(file);

    return True;
}



// conversions

Greyscale* newGreyscale_Image(Image* i) {
    Greyscale* gs = bts__emptyGreyscale();
    bts__initGreyscale(gs, i -> height, i -> width);

    for (nat j = 0; j < i -> height; j++)
    for (nat k = 0; k < i -> width; k++)
        gs -> grid[j][k] = (byte)(((double)i -> grid[j][k].r + i -> grid[j][k].g + i -> grid[j][k].b)/3.0);

    return gs;
}

Matrix* newMatrix_Image(Image* i) {
    // no conditions on i

    Matrix* M = bts__emptyMatrix();
    bts__initMatrix(M, 3 * i -> height, i -> width);

    nat J2 = 2 * i -> height;

    for (nat j = 0; j < i -> height; j++)
    for (nat k = 0; k < i -> width; k++) {
        setEntry(M, j, k, (double)(i -> grid[j][k].r));
        setEntry(M, j + i -> height, k, (double)(i -> grid[j][k].g));
        setEntry(M, j + J2, k, (double)(i -> grid[j][k].b));
    }

    return M;
}
