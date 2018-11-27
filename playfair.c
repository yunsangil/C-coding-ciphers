#include <stdio.h> //printf, scanf���� ����ϱ� ���� ���� �� ���
#include <ctype.h> //toupper�� ����ϱ� ���� ���� �� ���.
#include <string.h> //������ ��,���,��ȯ�� �ޱ� ���� ���� �� ���
#include <windows.h>  //system("cls")�� ����ϱ� ���� ���� �� ���.

void playfair(int select, char *key, char *pt, char *ct);
void menu(); //�޴� �Լ�
void userselect(int select, char*key);
void press_enter();


void main() {
	char key[20];
	int select = 0;

	while (1) {
		menu();


		scanf_s("%d", &select);
		while (getchar() != '\n');

		userselect(select, key);
	}
}
void userselect(int select, char *key) //menu �Լ����� ����ڰ� ������ ��� 1,2,3������ �Ѿ�Բ� �ϰ�, �����ϴ� �迭�� src�� ��.
{
	char src[100];
	char ct[100];

	if (select == 1) // �޴����� ���� select ������ 1�϶�
	{
		printf("��ȣȭ�� ������ �Է��ϼ��� : ");
		gets(src); //src�� ���ڿ� ����

		if (strlen(src) % 2 == 1)
		{
			strcat_s(src, sizeof(src), "X"); // ���ڰ� Ȧ���� src �ڿ� 'X'�� ����.
		}

		printf("��ȣȭ�� �ʿ��� Ű�� �Է��ϼ���: ");
		gets(key); //key1,key2�� ����

		printf("�Է��Ͻ� ���ڴ� %s\n\n���ڰ� Ȧ���� ��� �ڿ� x�� �߰��մϴ�.\n\n", src);
		playfair(select, key, src, ct); //�÷������ �Լ�. ���������� ct��� �迭�� ������� ������.
		printf("��ȣȭ�� ����� %s\n�Դϴ�", ct); //����� �� ct ���




	}

	if (select == 2) //�޴����� ���� select ������ 2�϶�
	{
		printf("��ȣȭ�� ������ �Է��ϼ��� : ");
		gets(src);//src�� ���ڿ� ����

		printf("��ȣȭ�� �ʿ��� Ű�� �Է��ϼ���: ");
		gets(key);

		playfair(select, key, src, ct);
		printf("��ȣȭ�� ����� %s�Դϴ�.\n", ct); //src�� ����� ���� ���

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
	printf(" Playfair ��ȣ/��ȣȭ ���α׷� ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. ��ȣȭ\n\t2. ��ȣȭ\n\t3. ����\n");

}
void press_enter()////���͸� ���� �� ���� ���ڿ��� �Է� �޴� �Լ��� �������ν�, ���͸� �Է��ؾ߸� �Ϸ��� ������ ����ǰԲ� �������.
{
	printf("���͸� ��������..\n");
	while (getchar() != '\n');

}

void playfair(int select, char *key, char *pt, char *ct)
{
	char *alph = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; //�빮�� ���ĺ� A-Z������ ���� ���� ������ �迭 alph ����
	char savekey[25], pt0, pt1; //Ű���� ������ 25�ڸ��� �迭 savekey�� ����
	char *savept = ct; // ct ���� savept�� ����
	int i, j, k, lp, rpt0, rpt1, cpt0, cpt1;
	int alphabet[25], row[25], col[25]; //Ű���� ������ ��,�� ����

	for (i = 0; i < 25; i++)
		alphabet[i] = -1; //���ĺ�[i]�� -1�̶�� ���� ä���ִ´�. (�Է��� Ű�� �׸� ������ ���ĺ����� ���� ���� ����

	j = 0;
	for (i = 0; i < strlen(key); i++)//Ű�� ���̱��� �ݺ�
	{


		k = toupper(key[i]); //�ҹ��ڸ� �빮�ڷ� �ٲ��ְ�, key[i]�� �ִ� ���� ���ڷ� ��ȯ�ϴ� ���� �޴� ���� k

		if (k == 'J')
			k = 'I'; //Ű�� j�϶� i�� ����.(�÷������ ��ȣ ǥ�� 5x5�� ǥ�̱� ������ �߰����� J�� I�� ġȯ)

		k = strchr(alph, k) - alph; //Key�� ���ڿ��� �˻��ϰ� �� ���ڿ��� ����Ʈ �迭 alph�� ���ش�.(key-A)

		alphabet[k] = j;
		savekey[j++] = alph[k]; //savekey�� [0]�������� strlen(key)���� j���� �÷��ְ� alph[k]�� �����ϰ��ִ�.

	}

	for (i = 0; i < 25; i++)
	{
		if (alphabet[i] == -1) //������ ���ĺ��� j�� ä���־����� ���� ���,
		{
			alphabet[i] = j; //���ĺ� �迭�� j�� ä������. �ռ� savekey[j]�� �Է¹��� Ű�� ���ĺ��� ä���ְ�, ���� �̸� ������ ���ĺ� ������� ä������.

			savekey[j++] = alph[i]; //���� �Ȱ���.
		}
	}

	for (i = 0; i < 25; i++)
	{
		row[i] = alphabet[i] / 5;
		col[i] = alphabet[i] % 5; //5x5 ����� ������ �����. ���� 1�϶� �� 0,1,2,3,4, 2�϶� �� 0,1,2,3,4 ....
	}

	j = 0; //������ �ö� j���� �ٽ� 0���� �ʱ�ȭ

	for (i = 0; i < strlen(pt); i++)
	{
		savept[j++] = toupper(pt[i]); //�Է¹��� ���� �빮��ȭ
	}


	savept[j] = '\0'; //j�� ���� ���̷� savept[�򹮱���]���� NULL���� ����־���.(������ ���� �˸�)
	for (i = 0; i < j; i += 2) //i�� 2�� ���Ǳ��̱�����ŭ ����.
	{
		pt0 = strchr(alph, savept[i]) - alph; //�� -a,alph �迭���� savept[i]�� ���� �˻��ؼ� ����� ���� -a�� ����.(alph�� ������ a�̱� ����)
		pt1 = strchr(alph, savept[i + 1]) - alph;//�� -a,alph �迭���� savept[i]�� ���� �˻��ؼ� ����� ���� -a�� ����.(alph�� ������ a�̱� ����), ��. i+1�̴� Ȧ��
		cpt0 = col[pt0];
		cpt1 = col[pt1];
		rpt0 = row[pt0];
		rpt1 = row[pt1];

		if (pt0 == pt1) //2���� ¦�� �̷� ���� ���� ���� ���
		{
			if (select == 1)//��ȣȭ
			{
				ct[i] = ct[i + 1] = savekey[(cpt0 + 5 * rpt0 + 1) % 25]; //�࿡�� ���ڸ� ��ĭ�� �̵�
			}
			else if (select == 2)//��ȣȭ
			{
				ct[i] = ct[i + 1] = savekey[(cpt0 + 5 * rpt0 + 24) % 25]; //�࿡�� ���ڸ� �ڷ� ��ĭ �̵�
			}
		}
		if (rpt0 == rpt1) //���� ���� ���
		{
			if (select == 1)
			{
				ct[i] = savekey[(cpt0 + 1) % 5 + 5 * rpt0];  //�࿡�� ���ڸ� ��ĭ�� �̵�
				ct[i + 1] = savekey[(cpt1 + 1) % 5 + 5 * rpt1]; //���� ¦�� ���� ���� �࿡�� ���ڸ� ��ĭ �̵�
			}
			else if (select == 2)
			{
				ct[i] = savekey[(cpt0 + 4) % 5 + 5 * rpt0];  //�࿡�� ���ڸ� �ڷ� ��ĭ �̵�
				ct[i + 1] = savekey[(cpt1 + 4) % 5 + 5 * rpt1];//���� ¦�� ���� ���� �࿡�� ���ڸ� ��ĭ �̵�
			}
		}
		else if (cpt0 == cpt1) //���� ���� ���
		{
			if (select == 1)
			{
				ct[i] = savekey[cpt0 + 5 * ((rpt0 + 1) % 5)]; //������ ���ڸ� ��ĭ �� �̵�
				ct[i + 1] = savekey[cpt1 + 5 * ((rpt1 + 1) % 5)]; //���� ¦�� ���� ���� ������ ���ڸ� ��ĭ �̵�
			}
			else if (select == 2)
			{
				ct[i] = savekey[cpt0 + 5 * ((rpt0 + 4) % 5)]; //������ ���ڸ� �ڷ� ��ĭ �̵�
				ct[i + 1] = savekey[cpt1 + 5 * ((rpt1 + 4) % 5)];//���� ¦�� ���� ���� ������ ���ڸ� ��ĭ �̵�
			}
		}
		else //���ڰ� �簢���� �̷� �밢���� ���
		{
			ct[i] = savekey[cpt1 + 5 * rpt0]; //�� ���ڿ� 5 ���� ���� �� ���ڿ� ����.
			ct[i + 1] = savekey[cpt0 + 5 * rpt1]; //���������� �๮�ڿ� 5 ���� ���� �����ڿ� ����.
		}

	}

	for (i = 0; i < 5; i++)  //savekey�� 0���� 5����, 5���� 10����, 10���� 15���� ....�� ���ִ� ���� for��. Ű�� ǥ
	{
		for (j = 5 * i; j < 5 * (i + 1); j++)
		{
			printf(" %c ", savekey[j]);
		}
		printf("\n");
	}
}