#include "header.h"
#pragma warning(disable:4996)
#include <windows.h>


int main()
{
	int a;
	printf("영상 처리 프로그램\n");
	printf("1. 영상 반전\n");
	printf("2. 사각형 생성\n");
	printf("3. 영상 밝게\n");
	printf("4. 영상 어둡게\n");
	printf("5. 영상 좌우대칭(PGM ONLY)\n");
	printf("6. 종료\n");
	printf("선택:");

	scanf("%d", &a);
	if (a < 1 || a > 6)   //메뉴 숫자 범위 오탈시
	{
		printf("메뉴 다시 선택:");
		scanf("%d", &a);
	}
	result(a);
	system("pause");
	return 0;
}