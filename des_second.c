#include <stdio.h>//printf,scanf���� ����ϱ� ���� ���� �� ���
#include <stdlib.h>//����ν� system()�� ����ϱ� ���� ���� �� ���
#include <string.h>//������ ��,���,��ȯ�� �ޱ� ���� ���� �� ���



void press_enter();
void userselect(int select, unsigned char *src, unsigned char *src_2);
void menu();
void Initial_permutation(char *src);
void step1(unsigned char *src);
void step2(unsigned char *src_2);

int main()
{
	unsigned char src[64];
	unsigned char src_2[64];

	int select = 0;

	while (1) {
		menu();


		scanf_s("%d", &select);
		while (getchar() != '\n');

		userselect(select, src, src_2);
	}
}

void press_enter()//���͸� ���� �� ���� ���ڿ��� �Է� �޴� �Լ��� �������ν�, ���͸� �Է��ؾ߸� �Ϸ��� ������ ����ǰԲ� �������.
{
	printf("���͸� ��������..\n");
	while (getchar() != '\n');

}

void userselect(int select, unsigned char *src, unsigned char *src_2) //menu �Լ����� ����ڰ� ������ ��� 1,2,3������ �Ѿ�Բ� �ϰ�, �����ϴ� �迭�� src�� ��.
{

	if (select == 1) // �޴����� ���� select ������ 1�϶�
	{
		step1(src);

		step2(src_2);
	}



	if (select == 2) //�޴����� ���� select ������ 2�϶�.... ���� ��������..
	{
		printf("��ȣȭ�� ������ �Է��ϼ��� : ");


		printf("��ȣȭ�� ����� %s�Դϴ�.\n");


	}
	if (select == 3) //�޴����� ���� select ������ 3�϶�
	{

		press_enter();
		exit(0); //���� ����

	}
	while (getchar() != '\n');//���� �ʱ�ȭ
	press_enter();//enter�� �Է��� �� ���� userselect�� ��� �����ϰ� �ϴ� ������ ��.
}
void Initial_permutation(char *src) //�ʱ���� �Լ�
{
	unsigned char cpy[64];//�ʱ���� ���� ������ �迭
	int i;

	char Initial_permutation[64] =                   //�ʱ����
	{ 58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7 };

	for (i = 0; i<64; i++)
	{
		cpy[i] = src[Initial_permutation[i] - 1]; //�� src�� 64��Ʈ�� �ش�Ǵ� �������� ����Ǿ��ֱ� ������ �̸� �ʱ����ǥ[i]���� ���� ��������, 0���� ���� �о��ֱ� ���� -1�� ����.
	}
	memcpy(src, cpy, 64); //���� src�� cpy�� ���� �������ش�.
}

void pc_1(char *src_2) //������� �Լ�
{
	unsigned char cpy[56];//������� ���� ������ �迭
	int i;

	char PC_1[56] =                   //�������
	{
		57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,          //���� 28��Ʈ
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4,         //���� 28��Ʈ
	};

	for (i = 0; i<56; i++)
	{
		cpy[i] = src_2[PC_1[i] - 1]; //�� src�� 64��Ʈ�� �ش�Ǵ� �������� ����Ǿ��ֱ� ������ �̸� �������ǥ[i]���� ���� ��������, 0���� ���� �о��ֱ� ���� -1�� ����.
	}
	memcpy(src_2, cpy, 56); //���� src_2�� cpy�� ���� �������ش�.
}



void pc_2(char *src_2) //S-Box �Լ�
{
	//1,2,9,16��°���� ����Ʈ�� �ѹ�, �������� �ι���

	unsigned char cpy[48];//S-Box�� ��ġ�� �� ���� ���� ������ �迭
	int i;

	char PC_2[48] =                   //S-Box
	{
		14,17,11,24,1,5,
		3,28,15,6,21,10,
		23,19,12,4,26,8,
		16,7,27,20,13,2,
		41,52,31,37,47,55,
		30,40,51,45,33,48,
		44,49,39,56,34,53,
		46,42,50,36,29,32
	};

	for (i = 0; i<56; i++)
	{
		cpy[i] = src_2[PC_2[i] - 1];
	}
	memcpy(src_2, cpy, 56); //���� src_2�� cpy�� ���� �������ش�.
}

void step1(unsigned char *src)
{
	int i, j, k; //�ݺ����� �迭� ����� ����
	char input[48]; //�Է¹��� ���� ������ ����
	int temp_bit[8]; //�ƽ�Ű �ڵ带 ��Ʈ�� ��ȯ���� ����
	int ini_copy[64]; //src�� �ʱ������ ���� �� 64��Ʈ ������ ������ �����Ⱚ�� ���ֱ� ���� ���� ���� �����ϱ� ���� ����� ����
	int temp_1[8];//�������� ���� ��Ʈ�� ���������� ������ ���� ����
	int temp;//���ڸ� �ƽ�Ű�ڵ�� ���� ����

	printf("��ȣȭ�� ������ �Է��ϼ���(8byte) ===> ");

	i = 0;
	do
	{
		gets(input);

		while (input[i])
		{
			i++;
		}
		if (i != 8) // �Է¹��� ���ڰ� 8���ڰ� �ƴ� �� input�� ���� �����ϰ� i�� 0���� �ʱ�ȭ �� �ٽ�
		{
			printf("��ȣȭ�� ������ �Է��ϼ���(8byte) ===> ");
			for (i = 0; i < 8; i++)
			{
				input[i] = (char)NULL;
			}
			i = 0;
		}
	} while (i != 8);
	i = 0; k = 0;

	while (input[i]) {

		temp = (int)input[i];
		//��Ʈ ����
		for (int i = 0; i < 8; i++)    temp_bit[i] = (temp >> i) & 1;

		//�Ųٷε� ��Ʈ�� ��������
		for (int i = 0; i < 8; i++)    temp_1[i] = temp_bit[i];
		for (int i = 0; i < 8; i++)    temp_bit[i] = temp_1[7 - i];

		//������ ��Ʈ�� src�� �־���
		for (int i = 0; i < 8; i++)   src[i + (8 * k)] = (char)temp_bit[i];
		i++;
		k++;
	}
	printf("\n->�Է°��� 2������    : ");


	for (i = 0; i < 64; i++)
	{
		printf("%d", src[i]);

		if (i % 32 == 31) printf("\n"); //32��° ���ڿ��� \n���
		if (i % 4 == 3) printf(" "); //4��° ���ڿ��� " " ���
	}
	printf("\n->��                : ");

	for (i = 0; i < 64; i++)
	{
		printf("%d", src[i]);

		if (i % 32 == 31) printf("\n");//32��° ���ڿ��� \n���
		if (i % 8 == 7) printf(" ");//8��° ���ڿ��� " " ���

	}

	Initial_permutation(src);

	for (i = 0; i<56; i++)
	{
		ini_copy[i] = src[i]; //ini_copy�� src���� ����
	}


	printf("\n->�ʱ� ������ ��ģ �� : ");
	for (i = 0; i < 64; i++)
	{
		printf("%d", src[i]);

		if (i % 32 == 31) printf("\n");//32��° ���ڿ��� \n���
		if (i % 8 == 7) printf(" ");//8��° ���ڿ��� " " ���
	}
	printf("\n\n");


	printf("���� 32��Ʈ >> ");
	for (i = 0; i < 32; i++)
	{
		printf("%d", src[i]);


		if (i % 32 == 31) printf("\n");//32��° ���ڿ��� \n���
		if (i % 4 == 3)   printf(" "); //4��° ���ڿ��� " " ���	
	}
	printf("\n");

	printf("������ 32��Ʈ >> ");
	for (i = 32; i < 64; i++)
	{
		printf("%d", src[i]);

		if (i % 32 == 31) printf("\n");//32��° ���ڿ��� \n���
		if (i % 4 == 3) printf(" ");//4��° ���ڿ��� " " ���

	}
	printf("\n");
}

void step2(unsigned char *src_2)
{
	int i, j, k; //�ݺ����� �迭� ����� ����
	char input[48]; //�Է¹��� Ű�� ������ ����
	int temp_bit[8]; //�ƽ�Ű �ڵ带 ��Ʈ�� ��ȯ���� ����
	int key_copy[56]; //src_2�� ��������� ���� �� 56��Ʈ ������ ������ �����Ⱚ�� ���ֱ� ���� Ű�� ���� �����ϱ� ���� ����� ����
	int temp_1[8];//�������� ���� ��Ʈ�� ���������� ������ ���� ����
	int temp;//���ڸ� �ƽ�Ű�ڵ�� ���� ����
	int pckey[16][48];


	printf("Ű�� �Է��ϼ���(8byte) ===> ");

	i = 0;
	do
	{
		gets(input);

		while (input[i])
		{
			i++;
		}
		if (i != 8) // �Է¹��� ���ڰ� 8���ڰ� �ƴ� �� input�� ���� �����ϰ� i�� 0���� �ʱ�ȭ �� �ٽ�
		{
			printf("Ű�� �Է��ϼ���(8byte) ===> ");
			for (i = 0; i < 8; i++)
			{
				input[i] = (char)NULL;
			}
			i = 0;
		}
	} while (i != 8);
	i = 0; k = 0;

	while (input[i]) {

		temp = (int)input[i];
		//��Ʈ ����
		for (int i = 0; i < 8; i++)    temp_bit[i] = (temp >> i) & 1;

		//�Ųٷε� ��Ʈ�� ��������
		for (int i = 0; i < 8; i++)    temp_1[i] = temp_bit[i];
		for (int i = 0; i < 8; i++)    temp_bit[i] = temp_1[7 - i];

		//������ ��Ʈ�� src�� �־���
		for (int i = 0; i < 8; i++)   src_2[i + (8 * k)] = (char)temp_bit[i];
		i++;
		k++;
	}
	printf("\n->�Է°��� 2������    : ");


	for (i = 0; i < 64; i++)
	{
		printf("%d", src_2[i]);

		if (i % 32 == 31) printf("\n"); //32��° ���ڿ��� \n���
		if (i % 4 == 3) printf(" "); //4��° ���ڿ��� " " ���
	}
	printf("\n->Ű                : ");

	for (i = 0; i < 64; i++)
	{
		printf("%d", src_2[i]);

		if (i % 32 == 31) printf("\n");//32��° ���ڿ��� \n���
		if (i % 8 == 7) printf(" ");//8��° ���ڿ��� " " ���

	}

	pc_1(src_2);

	for (i = 0; i<56; i++)
	{
		key_copy[i] = src_2[i]; //key_copy�� src_2�� ���� ����
	}

	printf("\n->���� ������ ��ģ �� : ");
	for (i = 0; i < 56; i++)
	{
		printf("%d", key_copy[i]);

		if (i % 28 == 27) printf("\n");//28��° ���ڿ��� \n���
		if (i % 8 == 7) printf(" ");//8��° ���ڿ��� " " ���
	}
	printf("\n\n");


	printf("���� 28��Ʈ >> ");
	for (i = 0; i < 28; i++)
	{
		printf("%d", key_copy[i]);


		if (i % 28 == 27) printf("\n");//28��° ���ڿ��� \n���
		if (i % 4 == 3)   printf(" "); //4��° ���ڿ��� " " ���	
	}
	printf("\n");

	printf("������ 28��Ʈ >> ");
	for (i = 28; i < 56; i++)
	{
		printf("%d", key_copy[i]);

		if (i % 28 == 27) printf("\n");//28��° ���ڿ��� \n���
		if (i % 4 == 3) printf(" ");//4��° ���ڿ��� " " ���

	}
	printf("\n");
}


void menu(void) //�޴��Լ�. system("cls")�� �Ϸ��� ���� ���� �� ȭ�� �ʱ�ȭ�� ���ְ� �ִ�.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" DES ��ȣ/��ȣȭ ���α׷� ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. ��ȣȭ\n\t2. ��ȣȭ\n\t3. ����\n");

}