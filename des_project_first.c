#include <stdio.h>//printf,scanf���� ����ϱ� ���� ���� �� ���
#include <stdlib.h>//����ν� system()�� ����ϱ� ���� ���� �� ���
#include <string.h>//������ ��,���,��ȯ�� �ޱ� ���� ���� �� ���



void press_enter();
void userselect(int select, unsigned char *src);
void menu();
void Initial_permutation(char *src);

int main()
{
	unsigned char src[64];

	int select = 0;

	while (1) {
		menu();


		scanf_s("%d", &select);
		while (getchar() != '\n');

		userselect(select, src);
	}
}

void press_enter()//���͸� ���� �� ���� ���ڿ��� �Է� �޴� �Լ��� �������ν�, ���͸� �Է��ؾ߸� �Ϸ��� ������ ����ǰԲ� �������.
{
	printf("���͸� ��������..\n");
	while (getchar() != '\n');

}

void userselect(int select, unsigned char *src) //menu �Լ����� ����ڰ� ������ ��� 1,2,3������ �Ѿ�Բ� �ϰ�, �����ϴ� �迭�� src�� ��.
{
	int i, j, k; //�ݺ����� �迭� ����� ����
	char input[8]; //�Է¹��� ���� ������ ����
	int temp_bit[8]; //�ƽ�Ű �ڵ带 ��Ʈ�� ��ȯ���� ����
	int temp_1[8];//�������� ���� ��Ʈ�� ���������� ������ ���� ����
	int temp;//���ڸ� �ƽ�Ű�ڵ�� ���� ����

	if (select == 1) // �޴����� ���� select ������ 1�϶�
	{
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
				for (i = 0; i<8; i++)
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


		for (i = 0; i<64; i++)
		{
			printf("%d", src[i]);

			if (i % 32 == 31) printf("\n"); //32��° ���ڿ��� \n���
			if (i % 4 == 3) printf(" "); //4��° ���ڿ��� " " ���
		}
		printf("\n->��                : ");

		for (i = 0; i<64; i++)
		{
			printf("%d", src[i]);

			if (i % 32 == 31) printf("\n");//32��° ���ڿ��� \n���
			if (i % 8 == 7) printf(" ");//8��° ���ڿ��� " " ���

		}

		Initial_permutation(src);

		printf("\n->�ʱ� ������ ��ģ �� : ");
		for (i = 0; i<64; i++)
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