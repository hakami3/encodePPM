#include "header.h"


void result(int result_num)
{
	char filename[230];						
	img_file img;


	if (result_num == 1)
	{
		printf("���� ������ �����߽��ϴ�.\n");
		printf("���ϸ� �Է�:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false) // ���� �б�
		{
			printf("������ �����ϴ�.\n");
			scanf("%s", filename);
		}
		if (Img_Reverse(filename, &img) == true) //  ���� ����
			printf("������ �����\n");
	}
	else if (result_num == 2)
	{
		printf("�簢�� ������ �����߽��ϴ�.\n");
		printf("���ϸ� �Է�:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false) 
		{
			printf("������ �����ϴ�.\n");
			scanf("%s", &filename);
		}
		if (Img_Square(filename, &img) == true)  // �簢�� ����
				printf("�簢�� ������\n");
	
	}
	else if (result_num == 3)
	{
		printf("���� ��� ������ �����߽��ϴ�.\n");
		printf("���ϸ� �Է�:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false)
		{
			printf("������ �����ϴ�.\n");
			scanf("%s", &filename);
		}
		if (Img_Brightness_Up(filename, &img) == true)  // �� ��Ӱ�
			printf("�� ��� ���� �����.\n");
	}
	else if (result_num == 4)
	{
		printf("���� ��Ӱ� ������ �����߽��ϴ�.\n");
		printf("���ϸ� �Է�:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false)
		{
			printf("������ �����ϴ�.\n");
			scanf("%s", &filename);
		}
		if (Img_Brightness_Down(filename, &img) == true)  // �� ��Ӱ�
			printf("�� ��Ӱ� ���� �����.\n");
	}

	else if (result_num == 5)
	{
		printf("PPM ���� �¿��Ī�� �����߽��ϴ�.\n");
		printf("���ϸ� �Է�:");
		scanf("%s", filename);
		while (Img_Read(filename, &img) == false)
		{
			printf("������ �����ϴ�.\n");
			scanf("%s", &filename);
		}
		if (PGM_Symmetry(filename, &img) == true)  // �¿����
			printf("�¿��Ī �����.\n");
	}

	else if (result_num == 6)
	{
		printf("���α׷� ����.\n");
		return false;
	}

}