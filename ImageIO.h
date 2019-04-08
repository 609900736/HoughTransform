#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef unsigned char UCHAR;

//bmp���
typedef struct  
{  
	//unsigned short    bfType;  
	unsigned long    bfSize;  
	unsigned short    bfReserved1;  
	unsigned short    bfReserved2;  
	unsigned long    bfOffBits;  
} ClBitMapFileHeader;  

typedef struct  
{  
	unsigned long  biSize;   
	long   biWidth;   
	long   biHeight;   
	unsigned short   biPlanes;   
	unsigned short   biBitCount;  
	unsigned long  biCompression;   
	unsigned long  biSizeImage;   
	long   biXPelsPerMeter;   
	long   biYPelsPerMeter;   
	unsigned long   biClrUsed;   
	unsigned long   biClrImportant;   
} ClBitMapInfoHeader;  

typedef struct   
{  
	unsigned char rgbBlue; //����ɫ����ɫ����  
	unsigned char rgbGreen; //����ɫ����ɫ����  
	unsigned char rgbRed; //����ɫ�ĺ�ɫ����  
	unsigned char rgbReserved; //����ֵ  
} ClRgbQuad;  

//��������

UCHAR *cpy_image(UCHAR *, int, int);
UCHAR *read_bmp(const char* , int , int);
bool read_image(const char *,  UCHAR *, int, int);
bool write_image(UCHAR *, int, int, const char * );
bool write_image(short *, int, int, const char * );
bool write_bmp(UCHAR *, char *,  int, int);
bool write_data(double *data, int width, int height, const char * name);
