#include <stdio.h>//printf,scanf등을 사용하기 위해 선언 된 헤더
#include <stdlib.h>//현재로썬 system()을 사용하기 위해 선언 된 헤더
#include <string.h>//문자의 입,출력,반환을 받기 위해 선언 된 헤더



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

void press_enter()//엔터를 누를 때 까지 문자열을 입력 받는 함수를 만듦으로써, 엔터를 입력해야만 일련의 과정이 종료되게끔 만들었다.
{
	printf("엔터를 누르세요..\n");
	while (getchar() != '\n');

}

void userselect(int select, unsigned char *src) //menu 함수에서 사용자가 선택한 대로 1,2,3번으로 넘어가게끔 하고, 참조하는 배열은 src로 함.
{
	int i, j, k; //반복문과 배열등에 사용할 변수
	char input[8]; //입력받은 평문을 저장할 변수
	int temp_bit[8]; //아스키 코드를 비트로 변환해줄 변수
	int temp_1[8];//역순으로 뽑힌 비트를 순방향으로 재정렬 해줄 변수
	int temp;//문자를 아스키코드로 받을 변수

	if (select == 1) // 메뉴에서 받은 select 변수가 1일때
	{
		printf("암호화할 내용을 입력하세요(8byte) ===> ");

		i = 0;
		do
		{
			gets(input);

			while (input[i])
			{
				i++;
			}
			if (i != 8) // 입력받은 문자가 8글자가 아닐 때 input의 값을 삭제하고 i를 0으로 초기화 후 다시
			{
				printf("암호화할 내용을 입력하세요(8byte) ===> ");
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
			//비트 생성
			for (int i = 0; i < 8; i++)    temp_bit[i] = (temp >> i) & 1;

			//거꾸로된 비트를 뒤집어줌
			for (int i = 0; i < 8; i++)    temp_1[i] = temp_bit[i];
			for (int i = 0; i < 8; i++)    temp_bit[i] = temp_1[7 - i];

			//생성된 비트를 src에 넣어줌
			for (int i = 0; i < 8; i++)   src[i + (8 * k)] = (char)temp_bit[i];
			i++;
			k++;
		}
		printf("\n->입력값은 2진수로    : ");


		for (i = 0; i<64; i++)
		{
			printf("%d", src[i]);

			if (i % 32 == 31) printf("\n"); //32번째 문자에서 \n출력
			if (i % 4 == 3) printf(" "); //4번째 문자에서 " " 출력
		}
		printf("\n->평문                : ");

		for (i = 0; i<64; i++)
		{
			printf("%d", src[i]);

			if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
			if (i % 8 == 7) printf(" ");//8번째 문자에서 " " 출력

		}

		Initial_permutation(src);

		printf("\n->초기 순열을 거친 후 : ");
		for (i = 0; i<64; i++)
		{
			printf("%d", src[i]);

			if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
			if (i % 8 == 7) printf(" ");//8번째 문자에서 " " 출력
		}
		printf("\n\n");


		printf("왼쪽 32비트 >> ");
		for (i = 0; i < 32; i++)
		{
			printf("%d", src[i]);


			if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
			if (i % 4 == 3)   printf(" "); //4번째 문자에서 " " 출력	
		}
		printf("\n");

		printf("오른쪽 32비트 >> ");
		for (i = 32; i < 64; i++)
		{
			printf("%d", src[i]);

			if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
			if (i % 4 == 3) printf(" ");//4번째 문자에서 " " 출력

		}
		printf("\n");
	}

	if (select == 2) //메뉴에서 받은 select 변수가 2일때.... 아직 구현안함..
	{
		printf("복호화할 내용을 입력하세요 : ");


		printf("복호화한 결과는 %s입니다.\n");


	}
	if (select == 3) //메뉴에서 받은 select 변수가 3일때
	{

		press_enter();
		exit(0); //강제 종료

	}
	while (getchar() != '\n');//버퍼 초기화
	press_enter();//enter를 입력할 때 까지 userselect를 계속 실행하게 하는 역할을 함.
}
void Initial_permutation(char *src) //초기순열 함수
{
	unsigned char cpy[64];//초기순열 값을 저장할 배열
	int i;

	char Initial_permutation[64] =                   //초기순열
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
		cpy[i] = src[Initial_permutation[i] - 1]; //총 src에 64비트에 해당되는 이진수가 저장되어있기 때문에 이를 초기순열표[i]에서 값을 가져오고, 0번쨰 방을 읽어주기 위해 -1을 해줌.
	}
	memcpy(src, cpy, 64); //이후 src에 cpy의 값을 복사해준다.
}


void menu(void) //메뉴함수. system("cls")로 일련의 과정 종료 후 화면 초기화를 해주고 있다.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" DES 암호/복호화 프로그램 ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. 암호화\n\t2. 복호화\n\t3. 종료\n");

}