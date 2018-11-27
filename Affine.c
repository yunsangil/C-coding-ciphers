#include <stdio.h> //scanf,printf 등을 사용하기 위해 선언 된 헤더
#include <string.h> //문자열 입,출력,반환을 위해 선언 된 헤더
#include <windows.h>  //system("cls")을 사용하기 위해 선언 된 헤더.

char* Encrypt(char *src, int key1, int key2);
char* Decrypt(char *src, int key1, int key2);
int inver(int key1, int mod);
void press_enter();
void menu();
void userselect(int select, char *src);


int main(void)
{
	char src[100]; //배열 src 선언
	int select; //select 변수 선언

	while (1)//이 일련의 과정을 계속해서 반복
	{
		menu();//메뉴함수 호출
		scanf_s("%d", &select);//이 때 입력한 값을 select에 저장

		while (getchar() != '\n');//버퍼 초기화

		userselect(select, src);//사용자가 선택한 select에 따라 암호화/복호화/종료 실행
	}

	return 0;
}

char* Encrypt(char *src, int key1, int key2) //암호화 함수
{
	int i; //for 문에 돌릴 변수 i 선언
	char temp[100] = { NULL }; //src[i] 값을 저장할 배열 temp 선언

	for (i = 0; i < strlen(src); i++) //i는 0에서부터 src의 길이까지 만큼 반복하는 for문
	{
		if (src[i] >= 'A' && src[i] <= 'Z')//대문자 일 때 암호화 과정
		{
			temp[i] = ((src[i] - 'A') * key1 + key2) % 26 + 'A';
				//src[i]에서 대문자 A를 빼준 값에 ax+b의 암호화 원리를 적용
		}
		else if (src[i] >= 'a' && src[i] <= 'z')//소문자 일 때 암호화 과정
		{
			temp[i] = ((src[i] - 'a') * key1 + key2) % 26 + 'a';
				//src[i]에서 소문자 a를 빼준 값에 ax+b의 암호화 원리를 적용
		}
		else// 알파벳이 아닌 문자는 그대로 반환
		{
			temp[i] = src[i];
		}
	}
	return temp; //최종적으로 temp 값 반환
}
char* Decrypt(char *src, int key1, int key2)//복호화 함수
{
	int i;
	int j = inver(key1, 26);//역함수 함수를 받는 변수 j를 선언
	char temp[100] = { NULL }; //src[i]값을 저장할 배열 temp 선언

	for (i = 0; i < strlen(src); i++) //i는 0에서부터 src의 길이까지 만큼 반복하는 for문
	{
		if (src[i] >= 'A' && src[i] <= 'Z')//대문자 일 때 복호화 과정
		{
			temp[i] = ((src[i] - 'A' - key2 + 26) * j) % 26 + 'A';
		}//src[i]에 -A를 해주고 -key 해준거에+26(음수값 출력 방지)하고 역함수 j를 곱해준것에 mod26을 해주고 +A하는 과정
		else if (src[i] >= 'a' && src[i] <= 'z')//소문자 일 때 복호화 과정
		{
			temp[i] = ((src[i] - 'a' - key2 + 26) * j) % 26 + 'a';
				//src[i]에 -a를 해주고 -key 해준거에+26(음수값 출력 방지)하고 역함수 j를 곱해준것에 mod26을 해주고 +a하는 과정
		}
		else//공백일 때는 그대로 반환한다
		{
			temp[i] = src[i];
		}
	}
	return temp; //최종적으로 temp 값 반환
}
int inver(int key1, int mod)
//곱셈 암호를 복호화 해주기 위해 함수의 역함수 a를 26과 서로소인 수이며 a^-1*a(mod26)=1을 만들어주기 위해 선언한 함수
{
	int i;
	for (i = 1; i <= 25; i += 2)//i는 1에서 25까지 홀수번호로 올라감.key1을 입력을 26과 서로소인 수(13을 제외한 홀수)를 입력하기 때문에 홀수로 받음.(mod26이 1이 나오게 하기 위해)
		if (key1 * i % mod == 1)
			break; // i가 a^-1*a(mod26)=1이 될 때 까지 반복 후 탈출
			return i; //이 때의 i 값을 반환
}

void press_enter()////엔터를 누를 때 까지 문자열을 입력 받는 함수를 만듦으로써, 엔터를 입력해야만 일련의 과정이 종료되게끔 만들었다.
{
	printf("엔터를 누르세요..\n");
	while (getchar() != '\n');

}

void menu() //메뉴함수. system("cls")로 일련의 과정 종료 후 화면 초기화를 해주고 있다.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" 아핀 암호/복호화 프로그램 ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. 암호화\n\t2. 복호화\n\t3. 종료\n");

}
void userselect(int select, char *src) //menu 함수에서 사용자가 선택한 대로 1,2,3번으로 넘어가게끔 하고, 참조하는 배열은 src로 함.
{
	int key1, key2;

	if (select == 1)
	{
		printf("암호화할 내용을 입력하세요 : ");
		gets(src); //src에 문자열 저장
		printf("암호화에 필요한 키1과 키2를 입력하세요(키1은 25 이하의 자연수 중 13을 제외한 홀수) : ");
		scanf_s("%d %d", &key1, &key2); //key1,key2값 저장
		strcpy_s(src, 100, Encrypt(src, key1, key2)); //src에 Encrypt함수의 문자열 복사
		printf("암호화한 결과는 %s입니다.\n", src);//src에 저장된 문자 출력
	}

	if (select == 2)
	{
		printf("복호화할 내용을 입력하세요 : ");
		gets(src);//src에 문자열 저장
		printf("복호화에 필요한 키1과 키2를 입력하세요(키1은 25 이하의 자연수 중 홀수) : ");
		scanf_s("%d %d", &key1, &key2);//key1,key2 값 저장
		strcpy_s(src, 100, Decrypt(src, key1, key2)); //src에 Decrypt함수의 문자열 복사
		printf("복호화한 결과는 %s입니다.\n", src); //src에 저장된 문자 출력
	}
	if (select == 3)
	{

		press_enter();
		exit(0); //강제 종료

	}
	while (getchar() != '\n');//버퍼 초기화
	press_enter();//enter를 입력할 때 까지 userselect를 계속 실행하게 하는 역할을 함.
}