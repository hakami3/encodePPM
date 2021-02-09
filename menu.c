#include "header.h"


void result(int result_num)
{
	char filename[230];						
	img_file img;


	if (result_num == 1)
	{
		printf("영상 반전을 선택했습니다.\n");
		printf("파일명 입력:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false) // 영상 읽기
		{
			printf("파일이 없습니다.\n");
			scanf("%s", filename);
		}
		if (Img_Reverse(filename, &img) == true) //  영상 반전
			printf("색반전 저장됨\n");
	}
	else if (result_num == 2)
	{
		printf("사각형 생성을 선택했습니다.\n");
		printf("파일명 입력:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false) 
		{
			printf("파일이 없습니다.\n");
			scanf("%s", &filename);
		}
		if (Img_Square(filename, &img) == true)  // 사각형 생성
				printf("사각형 생성됨\n");
	
	}
	else if (result_num == 3)
	{
		printf("영상 밝게 조절을 선택했습니다.\n");
		printf("파일명 입력:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false)
		{
			printf("파일이 없습니다.\n");
			scanf("%s", &filename);
		}
		if (Img_Brightness_Up(filename, &img) == true)  // 명도 어둡게
			printf("명도 밝게 조정 저장됨.\n");
	}
	else if (result_num == 4)
	{
		printf("영상 어둡게 조절을 선택했습니다.\n");
		printf("파일명 입력:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false)
		{
			printf("파일이 없습니다.\n");
			scanf("%s", &filename);
		}
		if (Img_Brightness_Down(filename, &img) == true)  // 명도 어둡게
			printf("명도 어둡게 조정 저장됨.\n");
	}

	else if (result_num == 5)
	{
		printf("PPM 영상 좌우대칭을 선택했습니다.\n");
		printf("파일명 입력:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false)
		{
			printf("파일이 없습니다.\n");
			scanf("%s", &filename);
		}
		if (PGM_Symmetry(filename, &img) == true)  // 좌우반전
			printf("좌우대칭 저장됨.\n");
	}

	else if (result_num == 6)
	{
		printf("프로그램 종료.\n");
		return false;
	}

}