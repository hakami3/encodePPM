#include "header.h"
#pragma once


int Img_Read(char* filename, img_file* img)
{
	int i, j;
	FILE *fp = fopen(filename, "rb");

	if (fp == NULL)
	{
		printf("파일이 없습니다.\n");
		return false;
	}

	fscanf(fp, "%c%c", &img->a, &img->b);				//식별자 읽기
	if (!(img->a == 'P' && (img->b == '6' || img->b == '5')))
	{
		printf("PGM 또는 PPM파일이 아닙니다.\n");
		return false;
	}


	fscanf(fp, "%d %d", &img->width, &img->height);			//가로 세로 넓이 읽기
	fscanf(fp, "%d", &img->max_brightness);					//최대 밝기 읽기

	img->pixel = (unsigned char**)malloc(sizeof(unsigned char*)*img->height);

	if (img->b == '6') // ppm 파일 처리
	{
		for (int i = 0; i < img->height; i++)
			img->pixel[i] = (unsigned char*)calloc(img->width * 3, sizeof(unsigned char));		//R,G,B 3가지 값이 필요


		for (int i = 0; i < img->height; i++)
		{
			for (int j = 0; j < img->width * 3; j++)
				fread(&img->pixel[i][j], sizeof(unsigned char), 1, fp);						//픽셀값 메모리에 읽기
		}
	}

	else  // pgm 파일 처리
	{
		for (int i = 0; i < img->height; i++)
			img->pixel[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));			//RGB 값이 한개 필요

		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width; j++)
				fread(&img->pixel[i][j], sizeof(unsigned char), 1, fp);
	}
	fclose(fp);				//파일 닫아주기

	return true;

}

int Img_Reverse(char *filename, img_file* img)
{
	int i, j;
	char new_filename[255] = "reversed.ppm";	
	FILE *fp = fopen(new_filename, "w");


	if (fp == NULL)
	{
		printf("파일생성 실패!\n");
		return false;
	}
	if (img->b == '6')
	{

		fprintf(fp, "%c%c\n", 'P', '3');            // PPM 파일의 ASCII
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);


		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width * 3; j += 3)		//RGB 값이 3개므로 3씩 증가
			{
				img->pixel[i][j] = 255 - img->pixel[i][j];		// (255-픽셀값)은 영상 반전값
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
		fprintf(fp, "%c%c\n", 'P', '2');          //PGM 파일의 ASCII
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
		printf("파일생성 실패");
		return false;
	}

	printf("width:%d , height:%d\n", img->width, img->height);			

	printf("x,y 시작점 입력:");											//사용자로부터 좌표 입력을 받음
	scanf("%d %d", &x1, &y1);
	printf("x,y 끝점 입력:");
	scanf("%d %d", &x2, &y2);

	if (x1 > x2)			//두번째 입력이 첫번째 입력값 초과시 값 교환
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

				if (j >= x1 * 3 && j <= x2 * 3 && i >= y1 && i <= y2)  //RGB 때문에 *3
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
		printf("파일생성 실패!\n");
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
				if (img->pixel[i][j] < 0)							//최소 RGB값 0 미만시 0으로 만들어줌
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
		printf("파일생성 실패!\n");
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

				img->pixel[i][j] = img->pixel[i][j] + 30;			//최대 RGB값 255초과시 255로 만들어줌
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
		printf("파일생성 실패!\n");
		return false;
	}
	if((img->b == '5'))			//PGM파일일때
	{
		fprintf(fp, "%c%c\n", 'P', '2');         
		fprintf(fp, "%d %d\n", img->width, img->height);
		fprintf(fp, "%d\n", img->max_brightness);


		for (i = 0; i < img->height; i++)
		{
			for (j = 0; j < img->width; j++)
			{
				x = img->width - j - 1;					// 배열은 0부터 시작하므로 1을 빼준다
				img->pixel[i][x] = img->pixel[i][j];		//y축은 그대로 두고 x좌표만 변경
				fprintf(fp, "%d ", img->pixel[i][j]);
			}
		}
	}

	fclose(fp);
	return true;
}

