/* 시저 암호화 알고리즘 (암호화,복호화)*/
/* 대,소문자 암/복호화 가능 */
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

	while (1) /*if가 3으로 break 될 때 까지 반복 */
	{
		system("cls"); /* 일련의 과정 후 화면 초기화 */
		printf("1. 암호화\n2. 복호화\n3. 종료\n입력 >> ");
		scanf_s("%d", &select);
		if (select == 1)
		{
			printf("평문을 입력하시오 >> ");
			while (getchar() != '\n'); /*버퍼 초기화, 유튜브 참조했음*/
			gets_s(src, sizeof(src));
			printf("키를 입력하시오 >> ");
			scanf_s("%d", &key);

			printf("암호화 >> ");
			encrypt(src, strlen(src), key);
			puts(src); // src를 출력
			printf("\n");
		}
		else if (select == 2)
		{
			printf("암호를 입력하시오 >> ");
			while (getchar() != '\n'); /*버퍼 초기화, 유튜브 참조했음*/
			gets_s(src, sizeof(src));
			printf("키를 입력하시오 >> ");
			scanf_s("%d", &key);
			printf("복호화 >> ");
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