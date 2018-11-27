#include <stdio.h> //scanf,printf ���� ����ϱ� ���� ���� �� ���
#include <string.h> //���ڿ� ��,���,��ȯ�� ���� ���� �� ���
#include <windows.h> //system("cls")�� ����ϱ� ���� ���� �� ���.

void menu(); //�޴� �Լ�, 1�� ��ȣȭ,2�� ��ȣȭ, 3�� ���� �� ����
void Press_Enter(); //�Ϸ��� ������ ������ Enter�� �����ÿ�
void input_User(int select, char * src, char * key); //�޴��� �����ϰ�, src,key���� �Է��ϴ� �� ����� �Լ�
void Encrypt(int i, int j, char *src, char *key); //��ȣȭ �Լ�.i,j�� �迭�� �ּ� ������ ���� �������, src,key�� �迭�� ��������.
void Decrypt(int i, int j, char *src, char *key);//��ȣȭ �Լ�. ���� ����� ����.

int main() {

	int i = 0; //for���� ���Ǵ� src�迭�� �ε���	
	int j = 0; // for������ ���Ǵ� key�迭�� �ε��� 
	int keyleng = 0; // strlen(key)=Ű�� ���ڿ��� ���̸� ������ ��ȯ�� ���� �޴� ����
	int srcleng = 0; // strlen(src)=���� ���ڿ��� ���̸� ������ ��ȯ�� ���� �޴� ����
	int select = 1; // �޴��Լ����� �� 1,2,3���� ���� �� ����

	char src[100] = { NULL, }; //�Է��� ���� ������ src �迭 ����
	char key[100] = { NULL, };//�Է��� Ű�� ������ key �迭 ����

	while (1) // �޴����� 3�� ���� exit(0)�� �ɶ� ���� �ݺ�
	{
		menu(); //�޴��Լ� ȣ��
		scanf_s("%d", &select); //�޴� ����

		while (getchar() != '\n'); //���� ����

		input_User(select, src, key); // �޴� ���� �� ��or��ȣ��,Ű�� �Է�

		for (i = 0; i < strlen(src); i++) //strlen(src) = �Է��� src�� ���� ex)abcd=4
		{
			j = i % strlen(key);       //��ⷯ ������ ���� Ű�� ��ȯ ex) j = Ű�� ���̰� 3�϶� 0,1,2�� ��� ��ȯ �ϰ� ��

			if (select == 1) // ��ȣȭ
				Encrypt(i, j, src, key);

			else if (select == 2) // ��ȣȭ
				Decrypt(i, j, src, key);
		}

		printf("\n��� >> ");
		puts(src); //src�� ����� ���� ���ڿ� ���

		Press_Enter(); // ���͸� ������ �Ϸ��� ���� ����(system("cls")�� �޴��Լ����� ��� ȣ�����ֱ� ������ �̸� �����ϱ� ����.

	}

	return 0;
}
void Encrypt(int i, int j, char *src, char *key) // i�� j�� �����Լ����� �����ް� src,key�� input_user���� �����޴´�.
{


	if ((src[i] >= 'a') && (src[i] <= 'z'))
	{

		src[i] -= 'a'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����.
		key[j] -= 'a'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����.

		src[i] = (src[i] + key[j]) % 26;    //����׸� ǥ ����,src[i]�� (src[i]-a+key[j]-a)mod 26�� �����Ѵ�
		src[i] += 'a'; //������ ������ ���� �����ָ� ��������� �� +key�� ��
		key[j] += 'a'; //key�� ��ȣȭ �ϴ� ������ �ƴϹǷ� ���� ���� �ٽ� �����ش�.(������ �����ϱ� ����)
	}
	else if ((src[i] >= 'A') && (src[i] <= 'Z')) // �빮�� ��ȣȭ ����
	{
		src[i] -= 'A'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����
		key[i] -= 'A'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����

		src[i] = (src[i] + key[j]) % 26;    //����׸� ǥ ����,src[i]�� (src[i]-a+key[j]-a)mod 26�� �����Ѵ�
		src[i] += 'A'; //������ ������ ���� �����ָ� ��������� �� +key�� ��
		key[j] += 'A'; //key�� ��ȣȭ �ϴ� ������ �ƴϹǷ� ���� ���� �ٽ� �����ش�.(������ �����ϱ� ����)
	}
}
void Decrypt(int i, int j, char *src, char *key) // ��ȣȭ�� ���������� ����.
{
	if ((src[i] >= 'a') && (src[i] <= 'z'))
	{
		src[i] -= 'a'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����
		key[j] -= 'a'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����.

		src[i] = (src[i] - key[j]) % 26;    //����׸� ǥ ����,src[i]�� (src[i]-a+key[j]-a)mod 26�� �����Ѵ�
		src[i] += 'a';
		key[j] += 'a';
	}
	else if ((src[i] >= 'A') && (src[i] <= 'Z'))
	{
		src[i] -= 'A'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����
		key[j] -= 'A'; //���ĺ� ���� 26���� ��ⷯ ������ ���ֱ� ���� ����.

		src[i] = (src[i] - key[j]) % 26;     //����׸� ǥ ����,src[i]�� (src[i]-a+key[j]-a)mod 26�� �����Ѵ�
		src[i] += 'A'; //������ ������ ���� �����ָ� ��������� �� +key�� ��
		key[j] += 'A'; //key�� ��ȣȭ �ϴ� ������ �ƴϹǷ� ���� ���� �ٽ� �����ش�.(������ �����ϱ� ����)
	}

}

void menu(void) //�޴��Լ�. system("cls")�� �Ϸ��� ���� ���� �� ȭ�� �ʱ�ȭ�� ���ְ� �ִ�.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" ����׸� ��ȣ/��ȣȭ ���α׷� ");
	printf("||");
	printf("\n");
	printf("\n");
	printf("������ �������� �ʽ��ϴ�.\n");
	printf(" ------------------------------\n");

	printf("\t1. ��ȣȭ\n\t2. ��ȣȭ\n\t3. ����\n");

}

void input_User(int select, char * src, char * key) //����ڰ� �Է��� ������ �����ϱ� ���� ���� �Լ�. 
													//�迭 src�� key�� �Է��� ���ڸ� �����Ѵ�
{
	if (select == 1)
	{
		printf("���� �Է��Ͻÿ� >> ");
	}
	else if (select == 2)
	{
		printf("��ȣ���� �Է��Ͻÿ� >> ");
	}
	else if (select == 3)
	{
		printf("����..\n");
		exit(0);
	}
	else
	{
		printf("�߸��� �Է��Դϴ�.\n");
		Press_Enter();
	}
	gets(src);
	printf("Ű�� �Է��Ͻÿ� >> ");
	gets(key);
}
void Press_Enter() //���͸� ���� �� ���� ���ڿ��� �Է� �޴� �Լ��� �������ν�, ���͸� �Է��ؾ߸� �Ϸ��� ������ ����ǰԲ� �������.
{
	printf("���͸� ��������..\n");
	while (getchar() != '\n');
}