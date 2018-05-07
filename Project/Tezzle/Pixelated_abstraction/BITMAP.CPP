#include "stdafx.h"
#include "main.h"
#include "BITMAP.H"
#include <iostream>
using namespace std;

GLubyte *                          /* O - Bitmap data */
LoadDIBitmap(const char *filename, /* I - File to load */
BITMAPINFO **info)    /* O - Bitmap information */
{

	FILE             *fp;          /* Open file pointer */
	GLubyte          *bits;        /* Bitmap pixel bits */
	int              bitsize;      /* Size of bitmap */
	int              infosize;     /* Size of header information */
	BITMAPFILEHEADER header;       /* File header */

	/* Try opening the file; use "rb" mode to read this *binary* file. */
	if ((fp = fopen(filename, "rb")) == NULL){

		return (NULL);
	}
	/* Read the file header and any following bitmap information... */

	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		/* Couldn't read the file header - return NULL... */
		fclose(fp);
		return (NULL);
	}
	printf("bfType: %d\n", header.bfType);
	printf("bfSize: %d\n", header.bfSize);
	printf("bfReserved1: %d\n", header.bfReserved1);
	printf("bfReserved2: %d\n", header.bfReserved2);
	printf("bfOffBits: %d\n", header.bfOffBits);

	if (header.bfType != 'MB')	/* Check for BM reversed... */
	{
		/* Not a bitmap file - return NULL... */
		fclose(fp);
		return (NULL);
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		/* Couldn't allocate memory for bitmap info - return NULL... */
		fclose(fp);
		return (NULL);
	}

	if (fread(*info, 1, infosize, fp) < infosize)
	{
		/* Couldn't read the bitmap header - return NULL... */
		free(*info);
		fclose(fp);
		return (NULL);
	}

	printf("biSize: %d\n", (*info)->bmiHeader.biSize);
	printf("biWidth: %d\n", (*info)->bmiHeader.biWidth);
	printf("biHeight: %d\n", (*info)->bmiHeader.biHeight);
	printf("biPlanes: %d\n", (*info)->bmiHeader.biPlanes);
	printf("biBitCount: %d\n", (*info)->bmiHeader.biBitCount);
	printf("biCompression: %d\n", (*info)->bmiHeader.biCompression);
	printf("biSizeImage: %d\n", (*info)->bmiHeader.biSizeImage);
	printf("biXPelsPerMeter: %d\n", (*info)->bmiHeader.biXPelsPerMeter);
	printf("biYPelsPerMeter: %d\n", (*info)->bmiHeader.biYPelsPerMeter);
	printf("biClrUsed: %d\n", (*info)->bmiHeader.biClrUsed);
	printf("biClrImportant: %d\n", (*info)->bmiHeader.biClrImportant);

	/* Now that we have all the header info read in, allocate memory for *
	* the bitmap and read *it* in...                                    */
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8 *
		abs((*info)->bmiHeader.biHeight);

	bits = (GLubyte *)malloc(bitsize * sizeof(GLubyte));
	if (bits == NULL)
		//    if ((bits = (GLubyte * ) malloc(bitsize)) == NULL)
	{
		/* Couldn't allocate memory - return NULL! */
		free(*info);
		fclose(fp);
		return (NULL);
	}

	if (fread(bits, 1, bitsize, fp) < bitsize)
	{
		/* Couldn't read bitmap - free memory and return NULL! */
		free(*info);
		free(bits);
		fclose(fp);
		return (NULL);
	}

	/* OK, everything went fine - return the allocated bitmap... */
	GLubyte *temp;
	temp = bits;

	for (int i = 0; i< bitsize; i = i + 3)
	{
		*temp = bits[i];

		bits[i] = bits[i + 2];
		bits[i + 2] = *temp;
	}

	fclose(fp);
	return (bits);
}


/*
* 'SaveDIBitmap()' - Save a DIB/BMP file to disk.
*
* Returns 0 on success or -1 on failure...
*/

int                                /* O - 0 = success, -1 = failure */
SaveDIBitmap(const char *filename, /* I - File to load */
BITMAPINFO *info,     /* I - Bitmap information */
GLubyte    *bits)     /* I - Bitmap data */
{


	FILE             *fp;          /* Open file pointer */
	unsigned int     size,         /* Size of file */
		infosize,     /* Size of bitmap info */
		bitsize;      /* Size of bitmap pixels */
	BITMAPFILEHEADER header;       /* File header */


	/* Try opening the file; use "wb" mode to write this *binary* file. */
	if ((fp = fopen(filename, "wb")) == NULL) {

		return (-1);
	}

	/* Figure out the bitmap size */
	if (info->bmiHeader.biSizeImage == 0) {
		bitsize = (info->bmiHeader.biWidth * info->bmiHeader.biBitCount + 7) / 8 * abs(info->bmiHeader.biHeight);

	}
	else
		bitsize = info->bmiHeader.biSizeImage;
	printf("biSizeImage = %d\n", bitsize);
	/* Figure out the header size */
	infosize = sizeof(BITMAPINFOHEADER);
	switch (info->bmiHeader.biCompression)
	{
	case BI_BITFIELDS:
		infosize += 12; /* Add 3 RGB doubleword masks */
		if (info->bmiHeader.biClrUsed == 0)
			break;
	case BI_RGB:
		if (info->bmiHeader.biBitCount > 8 &&
			info->bmiHeader.biClrUsed == 0)
			break;
	case BI_RLE8:
	case BI_RLE4:
		if (info->bmiHeader.biClrUsed == 0)
			infosize += (1 << info->bmiHeader.biBitCount) * 4;
		else
			infosize += info->bmiHeader.biClrUsed * 4;
		break;
	}

	size = sizeof(BITMAPFILEHEADER)+infosize + bitsize;

	/* Write the file header, bitmap information, and bitmap pixel data... */

	header.bfType = 'MB'; /* Non-portable... sigh */
	header.bfSize = size;
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = sizeof(BITMAPFILEHEADER)+infosize;

	if (fwrite(&header, 1, sizeof(BITMAPFILEHEADER), fp) < sizeof(BITMAPFILEHEADER))
	{

		/* Couldn't write the file header - return... */
		fclose(fp);
		return (-1);
	}

	if (fwrite(info, 1, infosize, fp) < infosize)
	{
		/* Couldn't write the bitmap header - return... */

		fclose(fp);
		return (-1);
	}

	if (fwrite(bits, 1, bitsize, fp) < bitsize)
	{
		/* Couldn't write the bitmap - return... */

		fclose(fp);
		return (-1);
	}
	printf("완벽하게 작성되었어!! ");
	/* OK, everything went fine - return... */
	fclose(fp);
	return (0);
}


/*
* 'write_word()' - Write a 16-bit unsigned integer.
*/

static int                     /* O - 0 on success, -1 on error */
write_word(FILE           *fp, /* I - File to write to */
unsigned short w)   /* I - Integer to write */
{
	putc(w, fp);
	return (putc(w >> 8, fp));
}


/*
* 'write_dword()' - Write a 32-bit unsigned integer.
*/

static int                    /* O - 0 on success, -1 on error */
write_dword(FILE         *fp, /* I - File to write to */
unsigned int dw)  /* I - Integer to write */
{
	putc(dw, fp);
	putc(dw >> 8, fp);
	putc(dw >> 16, fp);
	return (putc(dw >> 24, fp));
}


/*
* 'write_long()' - Write a 32-bit signed integer.
*/

static int           /* O - 0 on success, -1 on error */
write_long(FILE *fp, /* I - File to write to */
int  l)   /* I - Integer to write */
{
	putc(l, fp);
	putc(l >> 8, fp);
	putc(l >> 16, fp);
	return (putc(l >> 24, fp));
}

/*
* 'SaveDIBitmap()' - Save a DIB/BMP file to disk.
*
* Returns 0 on success or -1 on failure...
*/

int                                /* O - 0 = success, -1 = failure */
SaveDIBitmap2(const char *filename, /* I - File to load */
BITMAPINFO *info,     /* I - Bitmap information */
GLubyte    *bits)     /* I - Bitmap data */
{
	FILE             *fp;          /* Open file pointer */
	unsigned int     size,         /* Size of file */
		infosize,     /* Size of bitmap info */
		bitsize;      /* Size of bitmap pixels */
	BITMAPFILEHEADER header;       /* File header */


	/* Try opening the file; use "wb" mode to write this *binary* file. */
	if ((fp = fopen(filename, "wb")) == NULL)
		return (-1);

	/* Figure out the bitmap size */
	if (info->bmiHeader.biSizeImage == 0)
		bitsize = (info->bmiHeader.biWidth * info->bmiHeader.biBitCount + 7) / 8 * abs(info->bmiHeader.biHeight);
	else
		bitsize = info->bmiHeader.biSizeImage;

	/* Figure out the header size */
	infosize = sizeof(BITMAPINFOHEADER);
	switch (info->bmiHeader.biCompression)
	{
	case BI_BITFIELDS:
		infosize += 12; /* Add 3 RGB doubleword masks */
		if (info->bmiHeader.biClrUsed == 0)
			break;
	case BI_RGB:
		if (info->bmiHeader.biBitCount > 8 &&
			info->bmiHeader.biClrUsed == 0)
			break;
	case BI_RLE8:
	case BI_RLE4:
		if (info->bmiHeader.biClrUsed == 0)
			infosize += (1 << info->bmiHeader.biBitCount) * 4;
		else
			infosize += info->bmiHeader.biClrUsed * 4;
		break;
	}

	size = sizeof(BITMAPFILEHEADER)+infosize + bitsize;

	/* Write the file header, bitmap information, and bitmap pixel data... */
	header.bfType = 'MB'; /* Non-portable... sigh */
	header.bfSize = size;
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = sizeof(BITMAPFILEHEADER)+infosize;


	/* Write the file header, bitmap information, and bitmap pixel data... */
	write_word(fp, header.bfType);						/* bfType */
	write_dword(fp, header.bfSize);						/* bfSize */
	write_word(fp, header.bfReserved1);					/* bfReserved1 */
	write_word(fp, header.bfReserved2);					/* bfReserved2 */
	write_dword(fp, header.bfOffBits);					/* bfOffBits */

	write_dword(fp, info->bmiHeader.biSize);
	write_long(fp, info->bmiHeader.biWidth);
	write_long(fp, info->bmiHeader.biHeight);
	write_word(fp, info->bmiHeader.biPlanes);
	write_word(fp, info->bmiHeader.biBitCount);
	write_dword(fp, info->bmiHeader.biCompression);
	write_dword(fp, info->bmiHeader.biSizeImage);
	write_long(fp, info->bmiHeader.biXPelsPerMeter);
	write_long(fp, info->bmiHeader.biYPelsPerMeter);
	write_dword(fp, info->bmiHeader.biClrUsed);
	write_dword(fp, info->bmiHeader.biClrImportant);

	if (infosize > 40)
	if (fwrite(info->bmiColors, infosize - 40, 1, fp) < 1)
	{
		/* Couldn't write the bitmap header - return... */
		fclose(fp);
		return (-1);
	}
	/*	cout << " print !!" << endl << endl;
	for(int i =0; i < bitsize; i++)
	cout << (int)bits[i] << endl;
	*/

	if (fwrite(bits, 1, bitsize, fp) < bitsize)
	{
		/* Couldn't write the bitmap - return... */
		fclose(fp);
		return (-1);
	}


	/* OK, everything went fine - return... */
	fclose(fp);
	return (0);
}

void save_bitmap_file(char *fn, int W, int H, GLubyte *rpxls)
{
	BITMAPINFO *BitmapInfo = (BITMAPINFO *)malloc(sizeof(BITMAPINFO));

	BitmapInfo->bmiHeader.biSize = 40;
	BitmapInfo->bmiHeader.biWidth = W;
	BitmapInfo->bmiHeader.biHeight = H;
	BitmapInfo->bmiHeader.biPlanes = 1;
	BitmapInfo->bmiHeader.biBitCount = 24;
	BitmapInfo->bmiHeader.biCompression = 0;
	BitmapInfo->bmiHeader.biSizeImage = 3 * W * H;
	BitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	BitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	BitmapInfo->bmiHeader.biClrUsed = 0;
	BitmapInfo->bmiHeader.biClrImportant = 0;

	SaveDIBitmap2(fn, BitmapInfo, rpxls);

}
