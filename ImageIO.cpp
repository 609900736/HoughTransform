#include "ImageIO.h"

UCHAR *cpy_image(UCHAR *data, int width, int height)//Uchar�������ݸ���
{
	//copy

	UCHAR *cpy_data = (UCHAR *)malloc(sizeof(UCHAR) * width * height);
	memcpy(cpy_data, data, sizeof(UCHAR) * width * height);

	return cpy_data;

}

UCHAR * read_bmp(const char* path, int inwidth, int inheight) //8λλͼ��ȡ��32λλͼ��ȡ��ͨ��
{  
    UCHAR* bmpImg = NULL;  
    FILE* pFile;  
    unsigned short fileType;  
    ClBitMapFileHeader bmpFileHeader;  
    ClBitMapInfoHeader bmpInfoHeader;  
    int channels = 1;  
    int width = 0;  
    int height = 0;  
    int step = 0;  
    int offset = 0;  
    unsigned char pixVal;  
    ClRgbQuad* quad;  
    int i, j, k;  
      
    pFile = fopen(path, "rb");  
    if (!pFile)  
    {  
        return NULL;  
    }  
  
    fread(&fileType, sizeof(unsigned short), 1, pFile);  
    if (fileType == 0x4D42)  
    {  
        //printf("bmp file! \n");  
  
        fread(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);  
        /*printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n"); 
        printf("bmp�ļ�ͷ��Ϣ��\n"); 
        printf("�ļ���С��%d \n", bmpFileHeader.bfSize); 
        printf("�����֣�%d \n", bmpFileHeader.bfReserved1); 
        printf("�����֣�%d \n", bmpFileHeader.bfReserved2); 
        printf("λͼ����ƫ���ֽ�����%d \n", bmpFileHeader.bfOffBits);*/  
  
        fread(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);  
        /*printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n"); 
        printf("bmp�ļ���Ϣͷ\n"); 
        printf("�ṹ�峤�ȣ�%d \n", bmpInfoHeader.biSize); 
        printf("λͼ��ȣ�%d \n", bmpInfoHeader.biWidth); 
        printf("λͼ�߶ȣ�%d \n", bmpInfoHeader.biHeight); 
        printf("λͼƽ������%d \n", bmpInfoHeader.biPlanes); 
        printf("��ɫλ����%d \n", bmpInfoHeader.biBitCount); 
        printf("ѹ����ʽ��%d \n", bmpInfoHeader.biCompression); 
        printf("ʵ��λͼ����ռ�õ��ֽ�����%d \n", bmpInfoHeader.biSizeImage); 
        printf("X����ֱ��ʣ�%d \n", bmpInfoHeader.biXPelsPerMeter); 
        printf("Y����ֱ��ʣ�%d \n", bmpInfoHeader.biYPelsPerMeter); 
        printf("ʹ�õ���ɫ����%d \n", bmpInfoHeader.biClrUsed); 
        printf("��Ҫ��ɫ����%d \n", bmpInfoHeader.biClrImportant); 
        printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");*/  
  
        if (bmpInfoHeader.biBitCount == 8)  
        {  
			bmpImg = (UCHAR*)malloc(inwidth * inheight * sizeof(UCHAR));  
            //printf("���ļ��е�ɫ�壬����λͼΪ�����ɫ\n\n");  
            channels = 1;  
            width = bmpInfoHeader.biWidth;  
            height = bmpInfoHeader.biHeight;  
            offset = (channels*width)%4;  
            if (offset != 0)  
            {  
                offset = 4 - offset;  
            }  
            //bmpImg->mat = kzCreateMat(height, width, 1, 0);  
            //bmpImg->width = width;  
            //bmpImg->height = height;  
            //bmpImg->channels = 1;  
            //bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*height);  
            step = channels*width;  
  
            quad = (ClRgbQuad*)malloc(sizeof(ClRgbQuad)*256);  
            fread(quad, sizeof(ClRgbQuad), 256, pFile);  
            free(quad);  
  
            for (i=0; i<height; i++)  
            {  
                for (j=0; j<width; j++)  
                {  
                    fread(&pixVal, sizeof(unsigned char), 1, pFile);  
                    bmpImg[(height-1-i)*step+j] = pixVal;  
                }  
                if (offset != 0)  
                {  
                    for (j=0; j<offset; j++)  
                    {  
                        fread(&pixVal, sizeof(unsigned char), 1, pFile);  
                    }  
                }  
            }             
        }  
        else if (bmpInfoHeader.biBitCount == 32)  
        {  
			//printf("��λͼΪλ���ɫ\n\n");  
			channels = 4;  
			width = bmpInfoHeader.biWidth;  
			height = bmpInfoHeader.biHeight;  

			bmpImg = (unsigned char*)malloc(sizeof(unsigned char)*width*height);  
			step = width;  

            
			offset = (channels*width)%4;  
			if (offset != 0)  
			{  
				offset = 4 - offset;  
			}  

			for (i=0; i<height; i++)  
			{  
				for (j=0; j<width; j++)  
				{  
					for (k=0; k<4; k++)  
					{  
						fread(&pixVal, sizeof(unsigned char), 1, pFile);  
						if(k == 0)
						bmpImg[(height-1-i)*step+j] = pixVal;  
					}  
					
				}  
				if (offset != 0)  
				{  
					for (j=0; j<offset; j++)  
					{  
						fread(&pixVal, sizeof(unsigned char), 1, pFile);  
					}  
				}  
			}  
		}  
	} 
  
    return bmpImg;  
}  

bool read_image(const char *path,  UCHAR *data, int width, int height)//��txt�ж�ȡ8λλͼ����
{
	int i, j;
	FILE *fp = NULL;
	errno_t err;

	UCHAR *buf = (UCHAR *)malloc(sizeof(UCHAR) * 4);
	UCHAR *temp = (UCHAR *)malloc(sizeof(UCHAR));//����


	if( (err = fopen_s (&fp, path, "rb+" )) == 0)  // �����ȡ����
	{
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{
				fread( temp, sizeof(UCHAR), 1, fp );
				fread( buf, sizeof(UCHAR), 4, fp );
				data[i * width + j]= (char)atoi((char *)buf);
			}
			fread( temp, sizeof(UCHAR), 1, fp );
			fread( temp, sizeof(UCHAR), 1, fp );
		}
	}
	free(buf);
	free(temp);
	fclose(fp);
	return true;
}

bool write_image(UCHAR *data, int width, int height, const char * name)//д8λͼ�����ݵ�txt��
{
		int i, j;
		errno_t err;
		char c2 = '\n';
		char c3 = '\r';

		char c_temp[5] = {' ',' ',' ',' ',' '};//���ݻ���

		FILE * wfp = NULL;

		if((err = fopen_s (&wfp,  name , "wb+" )) == 0)//�ļ���
		{
			for(i = 0; i < height; i++)
			{
					for(j = 0; j < width; j++)
					{     
						sprintf_s(c_temp, sizeof(c_temp), "%4d", data[i * width + j]);
						fwrite(c_temp, sizeof(c_temp), 1, wfp);
					}

				fwrite (&c3 , sizeof(char), 1 , wfp );
				fwrite (&c2 , sizeof(char), 1 , wfp );//��ĩ����\r\n
			}
		}
		
		fclose (wfp);//�ļ��ر�
		return true;
}

bool write_image(short *data, int width, int height, const char * name)//д8λͼ�����ݵ�txt��
{
	int i, j;
	errno_t err;
	char c2 = '\n';
	char c3 = '\r';

	char c_temp[5] = {' ',' ',' ',' ',' '};//���ݻ���

	FILE * wfp = NULL;

	if((err = fopen_s (&wfp,  name , "wb+" )) == 0)//�ļ���
	{
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{     
				sprintf_s(c_temp, sizeof(c_temp), "%4d", data[i * width + j]);
				fwrite(c_temp, sizeof(c_temp), 1, wfp);
			}

			fwrite (&c3 , sizeof(char), 1 , wfp );
			fwrite (&c2 , sizeof(char), 1 , wfp );//��ĩ����\r\n
		}
	}

	fclose (wfp);//�ļ��ر�
	return true;
}

bool write_data(double *data, int width, int height, const char * name)//д64λͼ�����ݵ�txt��
{
	int i, j;
	errno_t err;
	char c1 = '\0';
	char c2 = '\n';
	char c3 = '\r';

	char c_temp[12] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};//���ݻ���
	
	FILE * wfp = NULL;

	if((err = fopen_s (&wfp,  name , "wb+" )) == 0)//�ļ���
	{
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{     
				memset(c_temp, 0, 12);
				sprintf_s(c_temp, sizeof(c_temp), "%11.5lf", data[i * width + j]);
				fwrite(c_temp, sizeof(c_temp), 1, wfp);
				fwrite (&c1 , sizeof(char), 1 , wfp );
			}

			fwrite (&c3 , sizeof(char), 1 , wfp );
			fwrite (&c2 , sizeof(char), 1 , wfp );//��ĩ����\r\n
		}
	}

	fclose (wfp);//�ļ��ر�
	return true;
}



bool write_bmp(UCHAR *data, char *path,  int width, int height)//8λλͼ�洢
{
	FILE *pFile;  
	errno_t err;
    unsigned short fileType;  
    ClBitMapFileHeader bmpFileHeader;  
    ClBitMapInfoHeader bmpInfoHeader;  
    int step;  
    int offset;  
    unsigned char pixVal = '\0';  
    int i, j;  
    ClRgbQuad* quad;  
  
    if((err = fopen_s(&pFile, path, "wb")) == 0)
	{    
		fileType = 0x4D42;  
		fwrite(&fileType, sizeof(unsigned short), 1, pFile);  
	  
	  
		step = width;  
		offset = step % 4;  
		if (offset != 4)  
		{  
			step += 4 - offset;  
		}  

		bmpFileHeader.bfSize = 54 + 256*4 + width;  
		bmpFileHeader.bfReserved1 = 0;  
		bmpFileHeader.bfReserved2 = 0;  
		bmpFileHeader.bfOffBits = 54 + 256 * 4;  
		fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);  

		bmpInfoHeader.biSize = 40;  
		bmpInfoHeader.biWidth = width;  
		bmpInfoHeader.biHeight = height;  
		bmpInfoHeader.biPlanes = 1;  
		bmpInfoHeader.biBitCount = 8;  
		bmpInfoHeader.biCompression = 0;  
		bmpInfoHeader.biSizeImage = height * step;  
		bmpInfoHeader.biXPelsPerMeter = 0;  
		bmpInfoHeader.biYPelsPerMeter = 0;  
		bmpInfoHeader.biClrUsed = 256;  
		bmpInfoHeader.biClrImportant = 256;  
		fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);  

		quad = (ClRgbQuad*)malloc(sizeof(ClRgbQuad)*256);  
		for (i=0; i < 256; i++)  
		{  
			quad[i].rgbBlue = i;  
			quad[i].rgbGreen = i;  
			quad[i].rgbRed = i;  
			quad[i].rgbReserved = 0;  
		}  
		fwrite(quad, sizeof(ClRgbQuad), 256, pFile);  
		free(quad);  

		for (i = height - 1; i > -1; i--)  
		{  
			for (j = 0; j < width; j++)  
			{  
				pixVal = data[i*width+j];  
				fwrite(&pixVal, sizeof(UCHAR), 1, pFile);  
			}  
			if (offset!=0)  
			{  
				for (j = 0; j < 4 - offset; j++)  
				{  
					pixVal = 0;  
					fwrite(&pixVal, sizeof(UCHAR), 1, pFile);  
				}  
			}  
		}  
	}
  fclose(pFile);  
    return true;  
}


