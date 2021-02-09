#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
#define true 1
#define false 0


typedef struct {
	char a, b; // ���� �ĺ���
	int width; // ���α���
	int height; // ���α���
	int max_brightness; // �ִ���
	unsigned char** pixel; // RGB �ȼ���
}img_file;


void result(int result_num);
int Img_Read(char* filename, img_file* img);
int Img_Reverse(char* filename, img_file* img);
int Img_Square(char* filename, img_file* img);
int Img_Brightness_Down(char* filename, img_file* img);
int Img_Brightness_Up(char* filename, img_file* img);
int PGM_Symmetry(char* filename, img_file* img);

