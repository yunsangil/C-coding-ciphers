#include <stdio.h>//printf,scanf등을 사용하기 위해 선언 된 헤더
#include <stdlib.h>//현재로썬 system()을 사용하기 위해 선언 된 헤더
#include <string.h>//문자의 입,출력,반환을 받기 위해 선언 된 헤더
#define XOR(a, b) (a || b) && !(a && b)


void press_enter();
void userselect(int select, unsigned char *src, unsigned char *src_2);
void menu();
void Initial_permutation(char *src);
void step1(unsigned char *src, unsigned char *src_2);

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

void press_enter()//엔터를 누를 때 까지 문자열을 입력 받는 함수를 만듦으로써, 엔터를 입력해야만 일련의 과정이 종료되게끔 만들었다.
{
	printf("엔터를 누르세요..\n");
	while (getchar() != '\n');

}

void userselect(int select, unsigned char *src, unsigned char *src_2) //menu 함수에서 사용자가 선택한 대로 1,2,3번으로 넘어가게끔 하고, 참조하는 배열은 src로 함.
{

	if (select == 1) // 메뉴에서 받은 select 변수가 1일때
	{
		step1(src, src_2);
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

void pc_1(char *src_2) //압축순열 함수
{
	unsigned char cpy[56];//압축순열 값을 저장할 배열
	int i;

	char PC_1[56] =                   //압축순열
	{
		57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,          //좌측 28비트
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4,         //우측 28비트
	};

	for (i = 0; i<56; i++)
	{
		cpy[i] = src_2[PC_1[i] - 1]; //총 src에 64비트에 해당되는 이진수가 저장되어있기 때문에 이를 압축순열표[i]에서 값을 가져오고, 0번쨰 방을 읽어주기 위해 -1을 해줌.
	}
	memcpy(src_2, cpy, 56); //이후 src_2에 cpy의 값을 복사해준다.
}



unsigned char DES_shift[] =
{
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

void step1(unsigned char *src, unsigned char *src_2)
{
	int i, j, k; //반복문과 배열등에 사용할 변수
	char input[48]; //입력받은 평문을 저장할 변수
	int temp_bit[8]; //아스키 코드를 비트로 변환해줄 변수
	int ini_copy[64]; //src를 초기순열을 해준 후 64비트 이후의 나머지 쓰레기값을 없애기 위해 평문을 새로 복사하기 위해 선언된 변수
	int temp_1[8];//역순으로 뽑힌 비트를 순방향으로 재정렬 해줄 변수
	int temp;//문자를 아스키코드로 받을 변수
	int keyleft[32];
	int keyright[32];

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


	for (i = 0; i < 64; i++)
	{
		printf("%d", src[i]);

		if (i % 32 == 31) printf("\n"); //32번째 문자에서 \n출력
		if (i % 4 == 3) printf(" "); //4번째 문자에서 " " 출력
	}
	printf("\n->평문                : ");

	for (i = 0; i < 64; i++)
	{
		printf("%d", src[i]);

		if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
		if (i % 8 == 7) printf(" ");//8번째 문자에서 " " 출력

	}

	Initial_permutation(src);

	for (i = 0; i < 56; i++)
	{
		ini_copy[i] = src[i]; //ini_copy에 src값을 복사
	}


	printf("\n->초기 순열을 거친 후 : ");
	for (i = 0; i < 64; i++)
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
		keyleft[i] = src[i];

		if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
		if (i % 4 == 3)   printf(" "); //4번째 문자에서 " " 출력   
	}
	printf("\n");

	printf("오른쪽 32비트 >> ");
	for (i = 32; i < 64; i++)
	{
		printf("%d", src[i]);
		keyright[i - 32] = src[i];
		if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
		if (i % 4 == 3) printf(" ");//4번째 문자에서 " " 출력

	}
	printf("\n");

	//체크포인트, 키

	int tmp1, tmp2, h, z; //반복문과 배열등에 사용할 변수
	char input_2[48]; //입력받은 키를 저장할 변수
	int temp_bit_2[8]; //아스키 코드를 비트로 변환해줄 변수
	int key_copy[56]; //src_2를 압축순열을 해준 후 56비트 이후의 나머지 쓰레기값을 없애기 위해 키를 새로 복사하기 위해 선언된 변수
	int temp_2[8];//역순으로 뽑힌 비트를 순방향으로 재정렬 해줄 변수
	int temp2;//문자를 아스키코드로 받을 변수
	int shiftkey[16][56];
	unsigned char pckey[16][48];
	int keyright_copy[48];

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


	int EXP[48] =
	{ 32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1 };

	printf("키를 입력하세요(8byte) ===> ");

	i = 0;
	do
	{
		gets(input_2);

		while (input_2[i])
		{
			i++;
		}
		if (i != 8) // 입력받은 문자가 8글자가 아닐 때 input의 값을 삭제하고 i를 0으로 초기화 후 다시
		{
			printf("키를 입력하세요(8byte) ===> ");
			for (i = 0; i < 8; i++)
			{
				input_2[i] = (char)NULL;
			}
			i = 0;
		}
	} while (i != 8);
	i = 0; k = 0;

	while (input_2[i]) {

		temp2 = (int)input_2[i];
		//비트 생성
		for (int i = 0; i < 8; i++)    temp_bit_2[i] = (temp2 >> i) & 1;

		//거꾸로된 비트를 뒤집어줌
		for (int i = 0; i < 8; i++)    temp_2[i] = temp_bit_2[i];
		for (int i = 0; i < 8; i++)    temp_bit_2[i] = temp_2[7 - i];

		//생성된 비트를 src에 넣어줌
		for (int i = 0; i < 8; i++)   src_2[i + (8 * k)] = (char)temp_bit_2[i];
		i++;
		k++;
	}
	printf("\n->입력값은 2진수로    : ");


	for (i = 0; i < 64; i++)
	{
		printf("%d", src_2[i]);

		if (i % 32 == 31) printf("\n"); //32번째 문자에서 \n출력
		if (i % 4 == 3) printf(" "); //4번째 문자에서 " " 출력
	}
	printf("\n->키                : ");

	for (i = 0; i < 64; i++)
	{
		printf("%d", src_2[i]);

		if (i % 32 == 31) printf("\n");//32번째 문자에서 \n출력
		if (i % 8 == 7) printf(" ");//8번째 문자에서 " " 출력

	}

	pc_1(src_2);

	for (i = 0; i < 56; i++)
	{
		key_copy[i] = src_2[i]; //key_copy에 src_2의 값을 복사
	}

	printf("\n->압축 순열을 거친 후 : ");
	for (i = 0; i < 56; i++)
	{
		printf("%d", key_copy[i]);

		if (i % 28 == 27) printf("\n");//28번째 문자에서 \n출력
		if (i % 8 == 7) printf(" ");//8번째 문자에서 " " 출력
	}
	printf("\n\n");


	printf("왼쪽 28비트 >> ");
	for (i = 0; i < 28; i++)
	{
		printf("%d", key_copy[i]);


		if (i % 28 == 27) printf("\n");//28번째 문자에서 \n출력
		if (i % 4 == 3)   printf(" "); //4번째 문자에서 " " 출력   
	}
	printf("\n");

	printf("오른쪽 28비트 >> ");
	for (i = 28; i < 56; i++)
	{
		printf("%d", key_copy[i]);

		if (i % 28 == 27) printf("\n");//28번째 문자에서 \n출력
		if (i % 4 == 3) printf(" ");//4번째 문자에서 " " 출력

	}
	printf("\n");

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < DES_shift[i]; j++)
		{
			tmp1 = key_copy[0];
			tmp2 = key_copy[28];

			for (k = 1; k < 28; k++) {
				key_copy[k - 1] = key_copy[k];
				key_copy[k + 27] = key_copy[k + 28];
			}
			key_copy[27] = tmp1;
			key_copy[55] = tmp2;
		}



		printf("\n%d 번째 %d 만큼 shift >>\n ", i + 1, DES_shift[i]);
		{

			printf("좌측 >>\n");
			for (h = 0; h < 28; h++)
			{
				printf("%d", key_copy[h]);

				if (h % 28 == 27) printf("\n");//28번째 문자에서 \n출력
				if (h % 4 == 3) printf(" ");//4번째 문자에서 " " 출력
			}
			printf("우측 >>\n");
			for (h = 28; h < 56; h++)
			{

				printf("%d", key_copy[h]);

				if (h % 56 == 55) printf("\n\n");//28번째 문자에서 \n출력
				if (h % 4 == 3) printf(" ");//4번째 문자에서 " " 출력
			}
			printf("%d 번째 shift key >>\n ", i + 1);

			for (z = 0; z < 56; z++)
			{
				shiftkey[i][z] = key_copy[z];

				printf("%d", shiftkey[i][z]);

				if (z % 28 == 27) printf("\n");//28번째 문자에서 \n출력
				if (z % 56 == 55) printf("\n");//28번째 문자에서 \n출력
				if (z % 4 == 3) printf(" ");//4번째 문자에서 " " 출력
			}

		}



		for (j = 0; j < 48; j++)
		{

			pckey[i][j] = shiftkey[i][PC_2[j] - 1];
		}

		printf("\n->PC-2 적용 후 : ");

		for (j = 0; j < 48; j++)
		{
			printf("%d", pckey[i][j]);

			if (j % 24 == 23) printf("\n");//24번째 문자에서 \n출력
			if (j % 8 == 7) printf(" ");//8번째 문자에서 " " 출력
		}
		printf("\n");

	}


	unsigned char Right[32];       // 오른쪽 32비트
	unsigned char Expansion[48];      // 확장p박스 저장 변수
	unsigned char S_result[32];       // Sbox결과 2진수 저장
	unsigned char Straight[32];       // 치환p박스 저장 변수
	unsigned char printstay[6];
	unsigned char row, row1, row2, col, col1, col2, col3, col4;
	unsigned char sbox[8];
	unsigned char last[64];

	//확장 P-박스 
	char InitialPermutationTable[48] = { 32,  1,  2,  3,  4,  5,
		4,  5,  6,  7,  8,  9,
		8,  9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1 };


	//단순 P-박스(단순치환)
	char FinalPermutationTable[32] = { 16,  7, 20, 21, 29, 12, 28, 17,
		1, 15, 23, 26,  5, 18, 31, 10,
		2,  8, 24, 14, 32, 27,  3,  9,
		19, 13, 30,  6, 22, 11,  4, 25 };
	char FinalPermutation[64] = {
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25 };


	//64비트로 이루어진 8개의 S-박스 
	char S[8][4][16] = {

		//S-박스1
		{ { 14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7 },
		{ 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8 },
		{ 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0 },
		{ 15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13 } },

		//S-박스2
		{ { 15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10 },
		{ 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5 },
		{ 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15 },
		{ 13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9 } },

		//S-박스3
		{ { 10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8 },
		{ 13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1 },
		{ 13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7 },
		{ 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12 } },


		//S-박스4
		{ { 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15 },
		{ 13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9 },
		{ 10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4 },
		{ 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14 } },

		//S-박스5
		{ { 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9 },
		{ 14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6 },
		{ 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14 },
		{ 11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3 } },


		//S-박스6
		{ { 12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11 },
		{ 10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8 },
		{ 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6 },
		{ 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13 } },


		//S-박스7
		{ { 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1 },
		{ 13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6 },
		{ 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2 },
		{ 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12 } },


		//S-박스8
		{ { 13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7 },
		{ 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2 },
		{ 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8 },
		{ 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11 } }
	};

	//라운드 16번만큼 반복하는 for문
	for (k = 0; k<16; k++)
	{
		printf("\n =========================================================== round %d ===========================================================", k + 1);

		//오른쪽의 32비트만 저장한다
		memcpy(Right, &src[32], 32);

		//확장 p박스를 이용
		for (i = 0; i<48; i++)
		{
			Expansion[i] = src[InitialPermutationTable[i] - 1 + 32];
		}

		printf("\n->Expansion-p(확장순열) : ");
		for (i = 0; i<48; i++)
		{
			printf("%d", Expansion[i]); if (i % 8 == 7) printf(" ");
		}

		//키 값과 확장-p를 나온 값을 XOR한다.
		for (i = 0; i<48; i++)
		{
			Expansion[i] = XOR(Expansion[i], pckey[k][i]);
		}

		printf("\n->Round Key             : ");
		for (i = 0; i<48; i++)
		{
			printf("%d", pckey[k][i]); if (i % 8 == 7) printf(" ");
		}

		printf("\n->XOR값                 : ");
		for (i = 0; i<48; i++)
		{
			printf("%d", Expansion[i]); if (i % 8 == 7) printf(" ");
		}

		//s-박스를 처리하는 루틴
		for (i = 0; i<8; i++)
		{
			for (j = 0; j<6; j++)
			{
				printstay[j] = Expansion[6 * i + j];
			}

			row1 = printstay[0];
			row2 = printstay[5];
			col1 = printstay[1];
			col2 = printstay[2];
			col3 = printstay[3];
			col4 = printstay[4];

			row = (row1 << 1) | row2;
			col = (col1 << 3) | (col2 << 2) | (col3 << 1) | col4;
			sbox[i] = S[i][row][col];
		}
		printf("\n->S-박스                : ");
		for (i = 0; i<8; i++)
		{
			printf("[S%d: %d] ", i, sbox[i]);
		}

		//16진수 -> 2진수
		for (i = 0; i<8; i++)
		{
			S_result[i * 4 + 0] = 0x01 & (sbox[i] >> 3);
			S_result[i * 4 + 1] = 0x01 & (sbox[i] >> 2);
			S_result[i * 4 + 2] = 0x01 & (sbox[i] >> 1);
			S_result[i * 4 + 3] = 0x01 & (sbox[i] >> 0);
		}

		for (i = 0; i<32; i++)
		{
			printf("%d", S_result[i]); if (i % 8 == 7) printf(" ");
		}

		for (i = 0; i<32; i++)
		{
			Straight[i] = S_result[FinalPermutationTable[i] - 1]; //순열함수
		}

		printf("\n->F-함수(순열결과)    : ");
		for (i = 0; i<32; i++)
		{
			printf("%d", Straight[i]); if (i % 8 == 7) printf(" ");
		}

		for (i = 0; i<32; i++)
		{
			src[i] = XOR(src[i], Straight[i]);
		}

		memcpy(&src[32], Right, 32);

		if (k <= 14)
		{
			memcpy(&src[32], src, 32);
			memcpy(src, Right, 32);
		}

		printf("\n->src값                : ");
		if (k == 15)
		{
			for (i = 0; i < 64; i++)
			{
				printf("%d", src[i]);
				if (i % 4 == 3) printf(" ");
			}
			printf("\n");

			printf("(최종 순열을 거친 후)\n");
			for (i = 0; i < 64; i++)
			{
				last[i] = src[FinalPermutation[i] - 1];
				printf("%d", last[i]); if (i % 4 == 3) printf(" ");
			}
			printf("\n");
		}
		else
		{
			for (i = 0; i < 64; i++)
			{
				printf("%d", src[i]);
				if (i % 4 == 3) printf(" ");
			}
			printf("\n");
		}
	}
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