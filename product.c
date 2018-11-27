#include <stdio.h> //printf,scanf등을 사용하기 위해 선언 된 헤더
#include <stdlib.h> //rand(),system()을 사용하기 위해 선언 된 헤더
#include <string.h> //문자의 입,출력,반환을 받기 위해 선언 된 헤더

/* 곱(ADFGVX) 암호 */
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
void menu(); //메뉴 함수
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
void ADFGVX_code(int c, char code[2]) //입력받은 평문을 ADFGVX의 주소로 변환
{
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (ADFGVX_table[i][j] == c) {
				code[0] = ADFGVX[i];
				code[1] = ADFGVX[j];
				printf("평문->ADFGVX 대입 %c-> %c %c\n", c, ADFGVX[i], ADFGVX[j]);
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

	for (i = 0; i < 6; i++) // 키에서 중복문자 제거 
	{
		do {
			for (j = 0; j < i; j++)
			{
				if (rek[j] == *key) break; // 중복이면 
			}
			if (j == i) { // 중복이 없으면
				rek[i] = *key;
			}
			key++;
		} while (i != j && *key);

		if (!*key && i < j) {
			printf("키 오류\n");
			exit(1);
		}
	}
}

void arraykey(char *rek, char *ark) //키를 재정렬 하는 역할.
{
	int i, j;
	char c;

	for (i = 0; i < 6; i++)
		ark[i] = rek[i]; //ark[i]에 rek[i]를 저장

	for (i = 0; i < 5; i++) //bubble sort
	{
		for (j = i + 1; j < 6; j++)
		{
			if (ark[i] > ark[j]) //ark[i]가 ark[j]보다 클 때
			{
				c = ark[j];
				ark[j] = ark[i]; //ark[j]에 ark[i]를 저장
				ark[i] = c; //call by pointer 로 ark[j]를 ark[i]로 정렬
			}
		}
	}
}

char *ADFGVX_encode(char *plain, char *code, const char *key) //입력된 평문 , 암호문이 저장될 배열, key
{
	int i, j, k, a;
	int n;//줄 수
	char c;// 사용자가 입력한 평문을 저장할 변수
	char rek[30], ark[30];// 중복된 문자가 제거된 키가 입력될 배열,
	char *temp[6]; // 복사할때 사용될 버퍼

				   // 키를 중복없이 6문자만 추출  
	rekey(key, rek);

	arraykey(rek, ark);
	i = 0;
	while (*plain)
	{
		c = *plain; //c에 사용자가 입력한 평문 값 저장

			if ('a' <= c && c <= 'z')//소문자를 대문자 화 하고 밑의 if문으로 넘김
			{
				c += 'A' - 'a';
			}
		if (('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'))  //c가 대문자or 숫자의 경우
		{
			ADFGVX_code(c, code + i); //한 문자를 2개의 adfgvx 문자로 바꿔주기 때문에 code +i 값에 +2를 해줌.
			i += 2;
		}
		plain++;
	}
	// 암호문을 6의 배수로 맞춤.
	while (i % 6) {  // 암호문의 수가 6의 배수가 아니면.. 
		code[i] = ADFGVX[rand() % 6]; // 부족분은 임의문자로 채움. 
		i++;
	}

	// 암호문을 세로로 저장 
	n = i / 6; // 줄 수 
	for (a = 0; a < 6 * n; a++)
	{
		printf("%c", code[a]);
	}
	printf("\n에서 세로 줄 출력->\n");


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

	//key를 기준으로 암호문을 정렬하여 1차원 배열로 재정렬 

	// 1 차원 배열로 재정렬
	for (i = 0; i < 6; i++)
	{

		printf("입력받은 키에서 a-z순서대로 변경 %c->", rek[i]);
		for (k = 0; k < 6; k++)
		{
			if (ark[i] == rek[k])
				break; // 찾음. 
		}
		printf("%c\n", ark[i]);
		for (j = 0; j < n; j++) // n개 복사 
		{
			code[i*n + j] = temp[k][j];
		}
	}
	code[6 * n] = '\0'; //문자열 끝 지정



		return code;
}

char *ADFGVX_decode(const char *code, char *plain, const char *key)
{
	int i, j, k, row, col;
	int n = strlen(code) / 6; //줄 수
	char c;
	char rek[6], ark[6];
	char *temp[6];


	rekey(key, rek);   // 키를 중복없이 6문자만 추출
	arraykey(rek, ark); // 키 정렬 

	for (i = 0; i < 6; i++) // 6개의 키에 대해서 
	{
		printf("다시 원래의 본래 저장되 있던 순서대로 변경 %c->", ark[i]);
		for (k = 0; k < 6; k++) // 원래 키의 문자 위치 찾음. 
		{
			if (ark[i] == rek[k])
				break;
		}
		printf("%c\n", rek[i]);
		temp[k] = (char *)calloc(sizeof(char), n);

		for (j = 0; j < n; j++) // code에서 n개씩 끊어서 저장 
		{
			temp[k][j] = code[i*n + j];
		}
	}

	// 복원
	k = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 6; )
		{
			row = ADFGVX_rowcol(temp[j++][i]);//TEMP는 CODE의 ADFGVX의 위치를 저장한 값

			col = ADFGVX_rowcol(temp[j++][i]);
			printf("문자의 행->%d 열->%d\n", row + 1, col + 1);
			plain[k++] = ADFGVX_table[row][col]; //ADFGVX_rowcol가 리턴하는 값은 ADFGVX에서 A면 1, ...X면 6으로, 즉 행과 열을 리턴함.
												 //이를 처음 선언한 ADFGVX_TABLE에 적용시키면 평문의 문자 plain[k]가 나옴
		}
	}

	plain[k] = '\0';

		return plain;
}
void table() //ADFGVX 테이블을 출력하는 함수
{
	printf("\t┏━━━━━━━━━━━━┓\n");
	printf("\t┃  ┃  A  D  F  G  V  X  ┃\n");
	printf("\t┃━┃━━━━━━━━━━┃\n");
	printf("\t┃ A┃  A  B  C  D  E  F  ┃\n");
	printf("\t┃  ┃                    ┃\n");
	printf("\t┃ D┃  G  H  I  J  K  L  ┃\n");
	printf("\t┃  ┃                    ┃\n");
	printf("\t┃ F┃  M  N  O  P  Q  R  ┃\n");
	printf("\t┃  ┃                    ┃\n");
	printf("\t┃ G┃  S  T  U  V  W  X  ┃\n");
	printf("\t┃  ┃                    ┃\n");
	printf("\t┃ V┃  Y  Z  0  1  2  3  ┃\n");
	printf("\t┃  ┃                    ┃\n");
	printf("\t┃ X┃  4  5  6  7  8  9  ┃\n");
	printf("\t┗━━━━━━━━━━━━┛\n");
}

void press_enter()////엔터를 누를 때 까지 문자열을 입력 받는 함수를 만듦으로써, 엔터를 입력해야만 일련의 과정이 종료되게끔 만들었다.
{
	printf("엔터를 누르세요..\n");
	while (getchar() != '\n');

}
void userselect(int select, char *key) //menu 함수에서 사용자가 선택한 대로 1,2,3번으로 넘어가게끔 하고, 참조하는 배열은 src로 함.
{

	char plain[81];
	char code[81];

	if (select == 1) // 메뉴에서 받은 select 변수가 1일때
	{
		table();
		printf("암호화할 내용을 입력하세요 : ");
		gets(plain); //src에 문자열 저장

		printf("암호화에 필요한 키를 입력하세요: ");
		gets(key); //key1,key2값 저장

		printf("암호화된 결과는 %s\n입니다", ADFGVX_encode(plain, code, key)); //저장된 값 ct 출력




	}

	if (select == 2) //메뉴에서 받은 select 변수가 2일때
	{

		table();
		printf("복호화할 내용을 입력하세요 : ");
		gets(code);//src에 문자열 저장

		printf("복호화에 필요한 키를 입력하세요: ");
		gets(key);

		printf("복호화한 결과는 %s입니다.\n", ADFGVX_decode(code, plain, key)); //src에 저장된 문자 출력


	}
	if (select == 3) //메뉴에서 받은 select 변수가 3일때
	{

		press_enter();
		exit(0); //강제 종료

	}
	while (getchar() != '\n');//버퍼 초기화
	press_enter();//enter를 입력할 때 까지 userselect를 계속 실행하게 하는 역할을 함.
}

void menu(void) //메뉴함수. system("cls")로 일련의 과정 종료 후 화면 초기화를 해주고 있다.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" product 암호/복호화 프로그램 ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. 암호화\n\t2. 복호화\n\t3. 종료\n");

}