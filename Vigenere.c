#include <stdio.h> //scanf,printf 등을 사용하기 위해 선언 된 헤더
#include <string.h> //문자열 입,출력,반환을 위해 선언 된 헤더
#include <windows.h> //system("cls")을 사용하기 위해 선언 된 헤더.

void menu(); //메뉴 함수, 1번 암호화,2번 복호화, 3번 종료 로 구성
void Press_Enter(); //일련의 과정이 끝나고 Enter를 누르시오
void input_User(int select, char * src, char * key); //메뉴를 선택하고, src,key값을 입력하는 데 사용한 함수
void Encrypt(int i, int j, char *src, char *key); //암호화 함수.i,j는 배열의 주소 참조를 위해 선언됬고, src,key는 배열로 저장했음.
void Decrypt(int i, int j, char *src, char *key);//복호화 함수. 위의 설명과 같다.

int main() {

	int i = 0; //for문에 사용되는 src배열의 인덱스	
	int j = 0; // for문에서 사용되는 key배열의 인덱스 
	int keyleng = 0; // strlen(key)=키의 문자열의 길이를 정수로 변환한 값을 받는 정수
	int srcleng = 0; // strlen(src)=평문의 문자열의 길이를 정수로 변환한 값을 받는 정수
	int select = 1; // 메뉴함수에서 각 1,2,3번의 변수 값 저장

	char src[100] = { NULL, }; //입력한 평문을 저장할 src 배열 선언
	char key[100] = { NULL, };//입력한 키를 저장할 key 배열 선언

	while (1) // 메뉴에서 3을 만나 exit(0)이 될때 까지 반복
	{
		menu(); //메뉴함수 호출
		scanf_s("%d", &select); //메뉴 선택

		while (getchar() != '\n'); //버퍼 정리

		input_User(select, src, key); // 메뉴 선택 및 평문or암호문,키값 입력

		for (i = 0; i < strlen(src); i++) //strlen(src) = 입력한 src의 길이 ex)abcd=4
		{
			j = i % strlen(key);       //모듈러 연산을 통한 키값 순환 ex) j = 키의 길이가 3일때 0,1,2를 계속 순환 하게 됨

			if (select == 1) // 암호화
				Encrypt(i, j, src, key);

			else if (select == 2) // 복호화
				Decrypt(i, j, src, key);
		}

		printf("\n결과 >> ");
		puts(src); //src에 저장된 내용 문자열 출력

		Press_Enter(); // 엔터를 누르면 일련의 과정 종료(system("cls")를 메뉴함수에서 계속 호출해주기 때문에 이를 방지하기 위함.

	}

	return 0;
}
void Encrypt(int i, int j, char *src, char *key) // i와 j는 메인함수에서 참조받고 src,key는 input_user에서 참조받는다.
{


	if ((src[i] >= 'a') && (src[i] <= 'z'))
	{

		src[i] -= 'a'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌.
		key[j] -= 'a'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌.

		src[i] = (src[i] + key[j]) % 26;    //비즈네르 표 적용,src[i]에 (src[i]-a+key[j]-a)mod 26을 저장한다
		src[i] += 'a'; //나머지 연산의 값을 더해주면 결과적으로 평문 +key가 됨
		key[j] += 'a'; //key는 암호화 하는 내용이 아니므로 빼준 것을 다시 더해준다.(원문을 유지하기 위해)
	}
	else if ((src[i] >= 'A') && (src[i] <= 'Z')) // 대문자 암호화 내용
	{
		src[i] -= 'A'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌
		key[i] -= 'A'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌

		src[i] = (src[i] + key[j]) % 26;    //비즈네르 표 적용,src[i]에 (src[i]-a+key[j]-a)mod 26을 저장한다
		src[i] += 'A'; //나머지 연산의 값을 더해주면 결과적으로 평문 +key가 됨
		key[j] += 'A'; //key는 암호화 하는 내용이 아니므로 빼준 것을 다시 더해준다.(원문을 유지하기 위해)
	}
}
void Decrypt(int i, int j, char *src, char *key) // 암호화와 마찬가지의 내용.
{
	if ((src[i] >= 'a') && (src[i] <= 'z'))
	{
		src[i] -= 'a'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌
		key[j] -= 'a'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌.

		src[i] = (src[i] - key[j]) % 26;    //비즈네르 표 적용,src[i]에 (src[i]-a+key[j]-a)mod 26을 저장한다
		src[i] += 'a';
		key[j] += 'a';
	}
	else if ((src[i] >= 'A') && (src[i] <= 'Z'))
	{
		src[i] -= 'A'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌
		key[j] -= 'A'; //알파벳 숫자 26으로 모듈러 연산을 해주기 위해 빼줌.

		src[i] = (src[i] - key[j]) % 26;     //비즈네르 표 적용,src[i]에 (src[i]-a+key[j]-a)mod 26을 저장한다
		src[i] += 'A'; //나머지 연산의 값을 더해주면 결과적으로 평문 +key가 됨
		key[j] += 'A'; //key는 암호화 하는 내용이 아니므로 빼준 것을 다시 더해준다.(원문을 유지하기 위해)
	}

}

void menu(void) //메뉴함수. system("cls")로 일련의 과정 종료 후 화면 초기화를 해주고 있다.
{
	system("cls");
	printf(" ------------------------------\n");
	printf("||");
	printf(" 비즈네르 암호/복호화 프로그램 ");
	printf("||");
	printf("\n");
	printf("\n");
	printf("공백은 지원하지 않습니다.\n");
	printf(" ------------------------------\n");

	printf("\t1. 암호화\n\t2. 복호화\n\t3. 종료\n");

}

void input_User(int select, char * src, char * key) //사용자가 입력한 내용을 저장하기 위해 만든 함수. 
													//배열 src와 key에 입력한 문자를 저장한다
{
	if (select == 1)
	{
		printf("평문을 입력하시오 >> ");
	}
	else if (select == 2)
	{
		printf("암호문을 입력하시오 >> ");
	}
	else if (select == 3)
	{
		printf("종료..\n");
		exit(0);
	}
	else
	{
		printf("잘못된 입력입니다.\n");
		Press_Enter();
	}
	gets(src);
	printf("키를 입력하시오 >> ");
	gets(key);
}
void Press_Enter() //엔터를 누를 때 까지 문자열을 입력 받는 함수를 만듦으로써, 엔터를 입력해야만 일련의 과정이 종료되게끔 만들었다.
{
	printf("엔터를 누르세요..\n");
	while (getchar() != '\n');
}