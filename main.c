#include "header.h"
#pragma warning(disable:4996)
#include <windows.h>


int main()
{
	int a;
	printf("���� ó�� ���α׷�\n");
	printf("1. ���� ����\n");
	printf("2. �簢�� ����\n");
	printf("3. ���� ���\n");
	printf("4. ���� ��Ӱ�\n");
	printf("5. ���� �¿��Ī(PGM ONLY)\n");
	printf("6. ����\n");
	printf("����:");

	scanf("%d", &a);
	if (a < 1 || a > 6)   //�޴� ���� ���� ��Ż��
	{
		printf("�޴� �ٽ� ����:");
		scanf("%d", &a);
	}
	result(a);
	system("pause");
	return 0;
}