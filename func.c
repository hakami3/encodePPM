#include "header.h"
#pragma once


int Img_Read(char* filename, img_file* img)
{
	int i, j;
	FILE *fp = fopen(filename, "rb");

	if (fp == NULL)
	{
		printf("������ �����ϴ�.\n");
		return false;
	}

	fscanf(fp, "%c%c", &img->a, &img->b);				//�ĺ��� �б�
	if (!(img->a == 'P' && (img->b == '6' || img->b == '5')))
	{
		printf("PGM �Ǵ� PPM������ �ƴմϴ�.\n");
		return false;
	}


	fscanf(fp, "%d %d", &img->width, &img->height);			//���� ���� ���� �б�
	fscanf(fp, "%d", &img->max_brightness);					//�ִ� ��� �б�

	img->pixel = (unsigned char**)malloc(sizeof(unsigned char*)*img->height);

	if (img->b == '6') // ppm ���� ó��
	{
		for (int i = 0; i < img->height; i++)
			img->pixel[i] = (unsigned char*)calloc(img->width * 3, sizeof(unsigned char));		//R,G,B 3���� ���� �ʿ�


		for (int i = 0; i < img->height; i++)
		{
			for (int j = 0; j < img->width * 3; j++)
				fread(&img->pixel[i][j], sizeof(unsigned char), 1, fp);						//�ȼ��� �޸𸮿� �б�
		}
	}

	else  // pgm ���� ó��
	{
		for (int i = 0; i < img->height; i++)
			img->pixel[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));			//RGB ���� �Ѱ� �ʿ�

		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				fread(&img->pixel[i][j], sizeof(unsigned char), 1, fp);
	}
	fclose(fp);				//���� �ݾ��ֱ�

	return true;

}

int Img_Reverse(char *filename, img_file* img)
{
	int i, j;
	char new_filename[255] = "reversed.ppm";	
	FILE *fp = fopen(new_filename, "w");


	if (fp == NULL)
	{
		printf("���ϻ��� ����!\n");
		return false;
	}
	if (img->b == '6')
	{

		fprintf(fp, "%c%c\n", 'P', '3');            // PPM ������ ASCII
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);


		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width * 3; j += 3)		//RGB ���� 3���Ƿ� 3�� ����
			{
				img->pixel[i][j] = 255 - img->pixel[i][j];		// (255-�ȼ���)�� ���� ������
				fprintf(fp, "%d ", img->pixel[i][j]);
				img->pixel[i][j+1] = 255 - img->pixel[i][j+1];
				fprintf(fp, "%d ", img->pixel[i][j+1]);
				img->pixel[i][j+2] = 255 - img->pixel[i][j+2];
				fprintf(fp, "%d ", img->pixel[i][j+2]);
			}
		}
	}
	else
	{
		fprintf(fp, "%c%c\n", 'P', '2');          //PGM ������ ASCII
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);

		for (i = 0; i < img->height; i++)
			for (j = 0; j < img->width; j++)
			{
					img->pixel[i][j] = 255 - img->pixel[i][j];
					fprintf(fp, "%d ", img->pixel[i][j]);
			}
	}

	fclose(fp);
	return true;
}

int Img_Square(char* filename, img_file* img)
{
	int i, j;
	int temp;
	int x1, x2, y1, y2;
	char new_filename[255] = "square.ppm";
	FILE *fp = fopen(new_filename, "w");

	if (fp == NULL)
	{
		printf("���ϻ��� ����");
		return false;
	}

	printf("width:%d , height:%d\n", img->width, img->height);			

	printf("x,y ������ �Է�:");											//����ڷκ��� ��ǥ �Է��� ����
	scanf("%d %d", &x1, &y1);
	printf("x,y ���� �Է�:");
	scanf("%d %d", &x2, &y2);

	if (x1 > x2)			//�ι�° �Է��� ù��° �Է°� �ʰ��� �� ��ȯ
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	if (img->b == '6')
	{
		fprintf(fp, "%c%c\n", 'P', '3');
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);
		for (i = 0; i < img->height; i++)
			for (j = 0; j < img->width * 3; j += 3)
			{

				if (j >= x1 * 3 && j <= x2 * 3 && i >= y1 && i <= y2)  //RGB ������ *3
				{
					fprintf(fp, "%d ", 0);
					fprintf(fp, "%d ", 0);
					fprintf(fp, "%d ", 0);
				}
				else {
					fprintf(fp, "%d ", img->pixel[i][j]);
					fprintf(fp, "%d ", img->pixel[i][j + 1]);
					fprintf(fp, "%d ", img->pixel[i][j + 2]);
				}
			}

	}
	else
	{
		fprintf(fp, "%c%c\n", 'P', '2');
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);

		for (i = 0; i < img->height; i++)
			for (j = 0; j < img->width; j++)
			{
				if (j >= x1 && j <= x2 && i >= y1 && i <= y2)
					fprintf(fp, "%d ", 0);
				else
					fprintf(fp, "%d ", img->pixel[i][j]);
			}
	}

	fclose(fp);
	return true;
}

int Img_Brightness_Down(char* filename, img_file* img)
{
	int i, j;
	char new_filename[255] = "brightnessdown.ppm";
	FILE *fp = fopen(new_filename, "w");

	if (fp == NULL)
	{
		printf("���ϻ��� ����!\n");
		return false;
	}
	if (img->b == '6')
	{
		fprintf(fp, "%c%c\n", 'P', '3');            
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);

		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width * 3; j += 3)
			{

				img->pixel[i][j] = img->pixel[i][j] - 30;
				if (img->pixel[i][j] < 0)							//�ּ� RGB�� 0 �̸��� 0���� �������
					img->pixel[i][j] = 0;
				fprintf(fp, "%d ", img->pixel[i][j]);
				img->pixel[i][j + 1] = img->pixel[i][j + 1] - 30;
				if (img->pixel[i][j+1] < 0)
					img->pixel[i][j+1] = 0;
				fprintf(fp, "%d ", img->pixel[i][j + 1]);
				img->pixel[i][j + 2] = img->pixel[i][j + 2] - 30;
				if (img->pixel[i][j+2] < 0)
					img->pixel[i][j+2] = 0;
				fprintf(fp, "%d ", img->pixel[i][j + 2]);

			}
		}
	}
	else
	{
		fprintf(fp, "%c%c\n", 'P', '2');          
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);

		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width; j++)
			{
				img->pixel[i][j] = img->pixel[i][j] - 30;
				if (img->pixel[i][j] < 0)
					img->pixel[i][j] = 0;
				fprintf(fp, "%d ", img->pixel[i][j]);
			}
		}
	}

	fclose(fp);
	return true;
}

int Img_Brightness_Up(char* filename, img_file* img)
{
	int i, j;
	char new_filename[255] = "brightnessup.ppm";
	FILE *fp = fopen(new_filename, "w");

	if (fp == NULL)
	{
		printf("���ϻ��� ����!\n");
		return false;
	}
	if (img->b == '6')
	{
		fprintf(fp, "%c%c\n", 'P', '3');            
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);


		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width * 3; j += 3)
			{

				img->pixel[i][j] = img->pixel[i][j] + 30;			//�ִ� RGB�� 255�ʰ��� 255�� �������
				if (img->pixel[i][j] > 255)
					img->pixel[i][j] = 255;
				fprintf(fp, "%d ", img->pixel[i][j]);
				img->pixel[i][j + 1] = img->pixel[i][j + 1] + 30;
				if (img->pixel[i][j + 1] > 255)
					img->pixel[i][j + 1] = 255;
				fprintf(fp, "%d ", img->pixel[i][j + 1]);
				img->pixel[i][j + 2] = img->pixel[i][j + 2] + 30;
				if (img->pixel[i][j + 2] > 255)
					img->pixel[i][j + 2] = 255;
				fprintf(fp, "%d ", img->pixel[i][j + 2]);

			}
		}
	}
	else
	{
		fprintf(fp, "%c%c\n", 'P', '2');        
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);


		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width; j++)
			{
				img->pixel[i][j] = img->pixel[i][j] + 30;
				fprintf(fp, "%d ", img->pixel[i][j]);
			}
		}
	}

	fclose(fp);
	return true;
}

int PGM_Symmetry(char* filename, img_file* img)
{
	int i, j;
	int x;
	char new_filename[255] = "symmetry.pgm";
	FILE *fp = fopen(new_filename, "w");

	if (fp == NULL)
	{
		printf("���ϻ��� ����!\n");
		return false;
	}
	if((img->b == '5'))			//PGM�����϶�
	{
		fprintf(fp, "%c%c\n", 'P', '2');         
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);


		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width; j++)
			{
				x = img->width - j - 1;					// �迭�� 0���� �����ϹǷ� 1�� ���ش�
				img->pixel[i][x] = img->pixel[i][j];		//y���� �״�� �ΰ� x��ǥ�� ����
				fprintf(fp, "%d ", img->pixel[i][j]);
			}
		}
	}

	fclose(fp);
	return true;
}

