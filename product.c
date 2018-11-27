#include <stdio.h> //printf,scanf���� ����ϱ� ���� ���� �� ���
#include <stdlib.h> //rand(),system()�� ����ϱ� ���� ���� �� ���
#include <string.h> //������ ��,���,��ȯ�� �ޱ� ���� ���� �� ���

/* ��(ADFGVX) ��ȣ */
const char ADFGVX[] = "ADFGVX";
char ADFGVX_table[6][6] = {
	'A','B','C','D','E','F',
	'G','H','I','J','K','L',
	'M','N','O','P','Q','R',
	'S','T','U','V','W','X',
	'Y','Z','0','1','2','3',
	'4','5','6','7','8','9', };
void ADFGVX_code(int c, char code[2]);
void table();
int ADFGVX_rowcol(char c);
void rekey(char *key, char *rek);
void arraykey(char *rek, char *ark);
char *ADFGVX_encode(char *plain, char *code, const char *key);
char *ADFGVX_decode(char *code, char *plain, const char *key);
void menu(); //�޴� �Լ�
void userselect(int select, char*key);
void press_enter();


int main()
{
	int select = 0;

	char key[21];
	int  n;


	while (1) {
		menu();


		scanf_s("%d", &select);
		while (getchar() != '\n');

		userselect(select, key);
	}
}
void ADFGVX_code(int c, char code[2]) //�Է¹��� ���� ADFGVX�� �ּҷ� ��ȯ
{
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (ADFGVX_table[i][j] == c) {
				code[0] = ADFGVX[i];
				code[1] = ADFGVX[j];
				printf("��->ADFGVX ���� %c-> %c %c\n", c, ADFGVX[i], ADFGVX[j]);
				return;
			}
		}
	}
}

int ADFGVX_rowcol(char c)
{
	switch (c)
	{
	case 'A': return 0;
	case 'D': return 1;
	case 'F': return 2;
	case 'G': return 3;
	case 'V': return 4;
	case 'X': return 5;
	}
}

void rekey(char *key, char *rek)
{
	int i, j;

	for (i = 0; i < 6; i++) // Ű���� �ߺ����� ���� 
	{
		do {
			for (j = 0; j < i; j++)
			{
				if (rek[j] == *key) break; // �ߺ��̸� 
			}
			if (j == i) { // �ߺ��� ������
				rek[i] = *key;
			}
			key++;
		} while (i != j && *key);

		if (!*key && i < j) {
			printf("Ű ����\n");
			exit(1);
		}
	}
}

void arraykey(char *rek, char *ark) //Ű�� ������ �ϴ� ����.
{
	int i, j;
	char c;

	for (i = 0; i < 6; i++)
		ark[i] = rek[i]; //ark[i]�� rek[i]�� ����

	for (i = 0; i < 5; i++) //bubble sort
	{
		for (j = i + 1; j < 6; j++)
		{
			if (ark[i] > ark[j]) //ark[i]�� ark[j]���� Ŭ ��
			{
				c = ark[j];
				ark[j] = ark[i]; //ark[j]�� ark[i]�� ����
				ark[i] = c; //call by pointer �� ark[j]�� ark[i]�� ����
			}
		}
	}
}

char *ADFGVX_encode(char *plain, char *code, const char *key) //�Էµ� �� , ��ȣ���� ����� �迭, key
{
	int i, j, k, a;
	int n;//�� ��
	char c;// ����ڰ� �Է��� ���� ������ ����
	char rek[30], ark[30];// �ߺ��� ���ڰ� ���ŵ� Ű�� �Էµ� �迭,
	char *temp[6]; // �����Ҷ� ���� ����

				   // Ű�� �ߺ����� 6���ڸ� ����  
	rekey(key, rek);

	arraykey(rek, ark);
	i = 0;
	while (*plain)
	{
		c = *plain; //c�� ����ڰ� �Է��� �� �� ����

			if ('a' <= c && c <= 'z')//�ҹ��ڸ� �빮�� ȭ �ϰ� ���� if������ �ѱ�
			{
				c += 'A' - 'a';
			}
		if (('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'))  //c�� �빮��or ������ ���
		{
			ADFGVX_code(c, code + i); //�� ���ڸ� 2���� adfgvx ���ڷ� �ٲ��ֱ� ������ code +i ���� +2�� ����.
			i += 2;
		}
		plain++;
	}
	// ��ȣ���� 6�� ����� ����.
	while (i % 6) {  // ��ȣ���� ���� 6�� ����� �ƴϸ�.. 
		code[i] = ADFGVX[rand() % 6]; // �������� ���ǹ��ڷ� ä��. 
		i++;
	}

	// ��ȣ���� ���η� ���� 
	n = i / 6; // �� �� 
	for (a = 0; a < 6 * n; a++)
	{
		printf("%c", code[a]);
	}
	printf("\n���� ���� �� ���->\n");


	for (i = 0; i < 6; i++)
	{
		temp[i] = (char *)calloc(sizeof(char), n);

		for (j = 0; j < n; j++)
		{
			temp[i][j] = code[j * 6 + i];
			printf("%c", temp[i][j]);
		}
	}
	printf("->\n");

	//key�� �������� ��ȣ���� �����Ͽ� 1���� �迭�� ������ 

	// 1 ���� �迭�� ������
	for (i = 0; i < 6; i++)
	{

		printf("�Է¹��� Ű���� a-z������� ���� %c->", rek[i]);
		for (k = 0; k < 6; k++)
		{
			if (ark[i] == rek[k])
				break; // ã��. 
		}
		printf("%c\n", ark[i]);
		for (j = 0; j < n; j++) // n�� ���� 
		{
			code[i*n + j] = temp[k][j];
		}
	}
	code[6 * n] = '\0'; //���ڿ� �� ����



		return code;
}

char *ADFGVX_decode(const char *code, char *plain, const char *key)
{
	int i, j, k, row, col;
	int n = strlen(code) / 6; //�� ��
	char c;
	char rek[6], ark[6];
	char *temp[6];


	rekey(key, rek);   // Ű�� �ߺ����� 6���ڸ� ����
	arraykey(rek, ark); // Ű ���� 

	for (i = 0; i < 6; i++) // 6���� Ű�� ���ؼ� 
	{
		printf("�ٽ� ������ ���� ����� �ִ� ������� ���� %c->", ark[i]);
		for (k = 0; k < 6; k++) // ���� Ű�� ���� ��ġ ã��. 
		{
			if (ark[i] == rek[k])
				break;
		}
		printf("%c\n", rek[i]);
		temp[k] = (char *)calloc(sizeof(char), n);

		for (j = 0; j < n; j++) // code���� n���� ��� ���� 
		{
			temp[k][j] = code[i*n + j];
		}
	}

	// ����
	k = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 6; )
		{
			row = ADFGVX_rowcol(temp[j++][i]);//TEMP�� CODE�� ADFGVX�� ��ġ�� ������ ��

			col = ADFGVX_rowcol(temp[j++][i]);
			printf("������ ��->%d ��->%d\n", row + 1, col + 1);
			plain[k++] = ADFGVX_table[row][col]; //ADFGVX_rowcol�� �����ϴ� ���� ADFGVX���� A�� 1, ...X�� 6����, �� ��� ���� ������.
												 //�̸� ó�� ������ ADFGVX_TABLE�� �����Ű�� ���� ���� plain[k]�� ����
		}
	}

	plain[k] = '\0';

		return plain;
}
void table() //ADFGVX ���̺��� ����ϴ� �Լ�
{
	printf("\t����������������������������\n");
	printf("\t��  ��  A  D  F  G  V  X  ��\n");
	printf("\t����������������������������\n");
	printf("\t�� A��  A  B  C  D  E  F  ��\n");
	printf("\t��  ��                    ��\n");
	printf("\t�� D��  G  H  I  J  K  L  ��\n");
	printf("\t��  ��                    ��\n");
	printf("\t�� F��  M  N  O  P  Q  R  ��\n");
	printf("\t��  ��                    ��\n");
	printf("\t�� G��  S  T  U  V  W  X  ��\n");
	printf("\t��  ��                    ��\n");
	printf("\t�� V��  Y  Z  0  1  2  3  ��\n");
	printf("\t��  ��                    ��\n");
	printf("\t�� X��  4  5  6  7  8  9  ��\n");
	printf("\t����������������������������\n");
}

void press_enter()////���͸� ���� �� ���� ���ڿ��� �Է� �޴� �Լ��� �������ν�, ���͸� �Է��ؾ߸� �Ϸ��� ������ ����ǰԲ� �������.
{
	printf("���͸� ��������..\n");
	while (getchar() != '\n');

}
void userselect(int select, char *key) //menu �Լ����� ����ڰ� ������ ��� 1,2,3������ �Ѿ�Բ� �ϰ�, �����ϴ� �迭�� src�� ��.
{

	char plain[81];
	char code[81];

	if (select == 1) // �޴����� ���� select ������ 1�϶�
	{
		table();
		printf("��ȣȭ�� ������ �Է��ϼ��� : ");
		gets(plain); //src�� ���ڿ� ����

		printf("��ȣȭ�� �ʿ��� Ű�� �Է��ϼ���: ");
		gets(key); //key1,key2�� ����

		printf("��ȣȭ�� ����� %s\n�Դϴ�", ADFGVX_encode(plain, code, key)); //����� �� ct ���




	}

	if (select == 2) //�޴����� ���� select ������ 2�϶�
	{

		table();
		printf("��ȣȭ�� ������ �Է��ϼ��� : ");
		gets(code);//src�� ���ڿ� ����

		printf("��ȣȭ�� �ʿ��� Ű�� �Է��ϼ���: ");
		gets(key);

		printf("��ȣȭ�� ����� %s�Դϴ�.\n", ADFGVX_decode(code, plain, key)); //src�� ����� ���� ���


	}
	if (select == 3) //�޴����� ���� select ������ 3�϶�
	{

		press_enter();
		exit(0); //���� ����

	}
	while (getchar() != '\n');//���� �ʱ�ȭ
	press_enter();//enter�� �Է��� �� ���� userselect�� ��� �����ϰ� �ϴ� ������ ��.
}

void menu(void) //�޴��Լ�. system("cls")�� �Ϸ��� ���� ���� �� ȭ�� �ʱ�ȭ�� ���ְ� �ִ�.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" product ��ȣ/��ȣȭ ���α׷� ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. ��ȣȭ\n\t2. ��ȣȭ\n\t3. ����\n");

}