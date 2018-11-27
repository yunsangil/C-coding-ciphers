#include <stdio.h> //scanf,printf ���� ����ϱ� ���� ���� �� ���
#include <string.h> //���ڿ� ��,���,��ȯ�� ���� ���� �� ���
#include <windows.h>  //system("cls")�� ����ϱ� ���� ���� �� ���.

char* Encrypt(char *src, int key1, int key2);
char* Decrypt(char *src, int key1, int key2);
int inver(int key1, int mod);
void press_enter();
void menu();
void userselect(int select, char *src);


int main(void)
{
	char src[100]; //�迭 src ����
	int select; //select ���� ����

	while (1)//�� �Ϸ��� ������ ����ؼ� �ݺ�
	{
		menu();//�޴��Լ� ȣ��
		scanf_s("%d", &select);//�� �� �Է��� ���� select�� ����

		while (getchar() != '\n');//���� �ʱ�ȭ

		userselect(select, src);//����ڰ� ������ select�� ���� ��ȣȭ/��ȣȭ/���� ����
	}

	return 0;
}

char* Encrypt(char *src, int key1, int key2) //��ȣȭ �Լ�
{
	int i; //for ���� ���� ���� i ����
	char temp[100] = { NULL }; //src[i] ���� ������ �迭 temp ����

	for (i = 0; i < strlen(src); i++) //i�� 0�������� src�� ���̱��� ��ŭ �ݺ��ϴ� for��
	{
		if (src[i] >= 'A' && src[i] <= 'Z')//�빮�� �� �� ��ȣȭ ����
		{
			temp[i] = ((src[i] - 'A') * key1 + key2) % 26 + 'A';
				//src[i]���� �빮�� A�� ���� ���� ax+b�� ��ȣȭ ������ ����
		}
		else if (src[i] >= 'a' && src[i] <= 'z')//�ҹ��� �� �� ��ȣȭ ����
		{
			temp[i] = ((src[i] - 'a') * key1 + key2) % 26 + 'a';
				//src[i]���� �ҹ��� a�� ���� ���� ax+b�� ��ȣȭ ������ ����
		}
		else// ���ĺ��� �ƴ� ���ڴ� �״�� ��ȯ
		{
			temp[i] = src[i];
		}
	}
	return temp; //���������� temp �� ��ȯ
}
char* Decrypt(char *src, int key1, int key2)//��ȣȭ �Լ�
{
	int i;
	int j = inver(key1, 26);//���Լ� �Լ��� �޴� ���� j�� ����
	char temp[100] = { NULL }; //src[i]���� ������ �迭 temp ����

	for (i = 0; i < strlen(src); i++) //i�� 0�������� src�� ���̱��� ��ŭ �ݺ��ϴ� for��
	{
		if (src[i] >= 'A' && src[i] <= 'Z')//�빮�� �� �� ��ȣȭ ����
		{
			temp[i] = ((src[i] - 'A' - key2 + 26) * j) % 26 + 'A';
		}//src[i]�� -A�� ���ְ� -key ���ذſ�+26(������ ��� ����)�ϰ� ���Լ� j�� �����ذͿ� mod26�� ���ְ� +A�ϴ� ����
		else if (src[i] >= 'a' && src[i] <= 'z')//�ҹ��� �� �� ��ȣȭ ����
		{
			temp[i] = ((src[i] - 'a' - key2 + 26) * j) % 26 + 'a';
				//src[i]�� -a�� ���ְ� -key ���ذſ�+26(������ ��� ����)�ϰ� ���Լ� j�� �����ذͿ� mod26�� ���ְ� +a�ϴ� ����
		}
		else//������ ���� �״�� ��ȯ�Ѵ�
		{
			temp[i] = src[i];
		}
	}
	return temp; //���������� temp �� ��ȯ
}
int inver(int key1, int mod)
//���� ��ȣ�� ��ȣȭ ���ֱ� ���� �Լ��� ���Լ� a�� 26�� ���μ��� ���̸� a^-1*a(mod26)=1�� ������ֱ� ���� ������ �Լ�
{
	int i;
	for (i = 1; i <= 25; i += 2)//i�� 1���� 25���� Ȧ����ȣ�� �ö�.key1�� �Է��� 26�� ���μ��� ��(13�� ������ Ȧ��)�� �Է��ϱ� ������ Ȧ���� ����.(mod26�� 1�� ������ �ϱ� ����)
		if (key1 * i % mod == 1)
			break; // i�� a^-1*a(mod26)=1�� �� �� ���� �ݺ� �� Ż��
			return i; //�� ���� i ���� ��ȯ
}

void press_enter()////���͸� ���� �� ���� ���ڿ��� �Է� �޴� �Լ��� �������ν�, ���͸� �Է��ؾ߸� �Ϸ��� ������ ����ǰԲ� �������.
{
	printf("���͸� ��������..\n");
	while (getchar() != '\n');

}

void menu() //�޴��Լ�. system("cls")�� �Ϸ��� ���� ���� �� ȭ�� �ʱ�ȭ�� ���ְ� �ִ�.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" ���� ��ȣ/��ȣȭ ���α׷� ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. ��ȣȭ\n\t2. ��ȣȭ\n\t3. ����\n");

}
void userselect(int select, char *src) //menu �Լ����� ����ڰ� ������ ��� 1,2,3������ �Ѿ�Բ� �ϰ�, �����ϴ� �迭�� src�� ��.
{
	int key1, key2;

	if (select == 1)
	{
		printf("��ȣȭ�� ������ �Է��ϼ��� : ");
		gets(src); //src�� ���ڿ� ����
		printf("��ȣȭ�� �ʿ��� Ű1�� Ű2�� �Է��ϼ���(Ű1�� 25 ������ �ڿ��� �� 13�� ������ Ȧ��) : ");
		scanf_s("%d %d", &key1, &key2); //key1,key2�� ����
		strcpy_s(src, 100, Encrypt(src, key1, key2)); //src�� Encrypt�Լ��� ���ڿ� ����
		printf("��ȣȭ�� ����� %s�Դϴ�.\n", src);//src�� ����� ���� ���
	}

	if (select == 2)
	{
		printf("��ȣȭ�� ������ �Է��ϼ��� : ");
		gets(src);//src�� ���ڿ� ����
		printf("��ȣȭ�� �ʿ��� Ű1�� Ű2�� �Է��ϼ���(Ű1�� 25 ������ �ڿ��� �� Ȧ��) : ");
		scanf_s("%d %d", &key1, &key2);//key1,key2 �� ����
		strcpy_s(src, 100, Decrypt(src, key1, key2)); //src�� Decrypt�Լ��� ���ڿ� ����
		printf("��ȣȭ�� ����� %s�Դϴ�.\n", src); //src�� ����� ���� ���
	}
	if (select == 3)
	{

		press_enter();
		exit(0); //���� ����

	}
	while (getchar() != '\n');//���� �ʱ�ȭ
	press_enter();//enter�� �Է��� �� ���� userselect�� ��� �����ϰ� �ϴ� ������ ��.
}