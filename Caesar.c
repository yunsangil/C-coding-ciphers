/* ���� ��ȣȭ �˰��� (��ȣȭ,��ȣȭ)*/
/* ��,�ҹ��� ��/��ȣȭ ���� */
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define SIZE 26
void encrypt(char *s, int n, int key)
{
	int i;
	for (i = 0; i<n; i++) {
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = (s[i] - 'a' + key) % SIZE + 'a';
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = (s[i] - 'A' + key) % SIZE + 'A';
	}
}
void decrypt(char *s, int n, int key)
{
	int i;
	for (i = 0; i<n; i++) {
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = (s[i] - 'a' + 26 - key) % SIZE + 'a';
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = (s[i] - 'A' + 26 - key) % SIZE + 'A';
	}
}

int main()
{
	int key;
	int select;
	char src[100] = { NULL, };

	while (1) /*if�� 3���� break �� �� ���� �ݺ� */
	{
		system("cls"); /* �Ϸ��� ���� �� ȭ�� �ʱ�ȭ */
		printf("1. ��ȣȭ\n2. ��ȣȭ\n3. ����\n�Է� >> ");
		scanf_s("%d", &select);
		if (select == 1)
		{
			printf("���� �Է��Ͻÿ� >> ");
			while (getchar() != '\n'); /*���� �ʱ�ȭ, ��Ʃ�� ��������*/
			gets_s(src, sizeof(src));
			printf("Ű�� �Է��Ͻÿ� >> ");
			scanf_s("%d", &key);

			printf("��ȣȭ >> ");
			encrypt(src, strlen(src), key);
			puts(src); // src�� ���
			printf("\n");
		}
		else if (select == 2)
		{
			printf("��ȣ�� �Է��Ͻÿ� >> ");
			while (getchar() != '\n'); /*���� �ʱ�ȭ, ��Ʃ�� ��������*/
			gets_s(src, sizeof(src));
			printf("Ű�� �Է��Ͻÿ� >> ");
			scanf_s("%d", &key);
			printf("��ȣȭ >> ");
			decrypt(src, strlen(src), key);
			puts(src);
			printf("\n");
		}

		else if (select == 3)
		{
			break;
		}
		getch();
	}

	return 0;
}