#include <stdio.h> //printf, scanf등을 사용하기 위해 선언 된 헤더
#include <ctype.h> //toupper을 사용하기 위해 선언 된 헤더.
#include <string.h> //문자의 입,출력,반환을 받기 위해 선언 된 헤더
#include <windows.h>  //system("cls")을 사용하기 위해 선언 된 헤더.

void playfair(int select, char *key, char *pt, char *ct);
void menu(); //메뉴 함수
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
void userselect(int select, char *key) //menu 함수에서 사용자가 선택한 대로 1,2,3번으로 넘어가게끔 하고, 참조하는 배열은 src로 함.
{
	char src[100];
	char ct[100];

	if (select == 1) // 메뉴에서 받은 select 변수가 1일때
	{
		printf("암호화할 내용을 입력하세요 : ");
		gets(src); //src에 문자열 저장

		if (strlen(src) % 2 == 1)
		{
			strcat_s(src, sizeof(src), "X"); // 문자가 홀수면 src 뒤에 'X'를 붙임.
		}

		printf("암호화에 필요한 키를 입력하세요: ");
		gets(key); //key1,key2값 저장

		printf("입력하신 문자는 %s\n\n문자가 홀수인 경우 뒤에 x를 추가합니다.\n\n", src);
		playfair(select, key, src, ct); //플레이페어 함수. 최종적으로 ct라는 배열에 결과값을 저장함.
		printf("암호화된 결과는 %s\n입니다", ct); //저장된 값 ct 출력




	}

	if (select == 2) //메뉴에서 받은 select 변수가 2일때
	{
		printf("복호화할 내용을 입력하세요 : ");
		gets(src);//src에 문자열 저장

		printf("복호화에 필요한 키를 입력하세요: ");
		gets(key);

		playfair(select, key, src, ct);
		printf("복호화한 결과는 %s입니다.\n", ct); //src에 저장된 문자 출력

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
	printf(" Playfair 암호/복호화 프로그램 ");
	printf("||");
	printf("\n");
	printf("\n");
	printf(" ------------------------------\n");

	printf("\t1. 암호화\n\t2. 복호화\n\t3. 종료\n");

}
void press_enter()////엔터를 누를 때 까지 문자열을 입력 받는 함수를 만듦으로써, 엔터를 입력해야만 일련의 과정이 종료되게끔 만들었다.
{
	printf("엔터를 누르세요..\n");
	while (getchar() != '\n');

}

void playfair(int select, char *key, char *pt, char *ct)
{
	char *alph = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; //대문자 알파벳 A-Z까지의 값을 담은 포인터 배열 alph 선언
	char savekey[25], pt0, pt1; //키값을 저장할 25자리의 배열 savekey를 선언
	char *savept = ct; // ct 값을 savept에 저장
	int i, j, k, lp, rpt0, rpt1, cpt0, cpt1;
	int alphabet[25], row[25], col[25]; //키값을 저장할 행,렬 선언

	for (i = 0; i < 25; i++)
		alphabet[i] = -1; //알파벳[i]에 -1이라는 값을 채워넣는다. (입력한 키와 그를 제외한 알파벳들을 구분 지을 변수

	j = 0;
	for (i = 0; i < strlen(key); i++)//키의 길이까지 반복
	{


		k = toupper(key[i]); //소문자를 대문자로 바꿔주고, key[i]에 있는 값을 숫자로 변환하는 값을 받는 변수 k

		if (k == 'J')
			k = 'I'; //키가 j일때 i로 받음.(플레이페어 암호 표는 5x5의 표이기 때문에 중간값인 J를 I로 치환)

		k = strchr(alph, k) - alph; //Key의 문자열을 검색하고 그 문자열에 포인트 배열 alph를 빼준다.(key-A)

		alphabet[k] = j;
		savekey[j++] = alph[k]; //savekey에 [0]에서부터 strlen(key)까지 j값을 올려주고 alph[k]를 저장하고있다.

	}

	for (i = 0; i < 25; i++)
	{
		if (alphabet[i] == -1) //위에서 알파벳이 j로 채워넣어지지 않을 경우,
		{
			alphabet[i] = j; //알파벳 배열에 j를 채워넣음. 앞서 savekey[j]에 입력받은 키의 알파벳을 채워넣고, 이후 이를 제외한 알파벳 순서대로 채워넣음.

			savekey[j++] = alph[i]; //위와 똑같음.
		}
	}

	for (i = 0; i < 25; i++)
	{
		row[i] = alphabet[i] / 5;
		col[i] = alphabet[i] % 5; //5x5 행렬의 구조를 잡아줌. 행이 1일때 열 0,1,2,3,4, 2일때 열 0,1,2,3,4 ....
	}

	j = 0; //위에서 올라간 j값을 다시 0으로 초기화

	for (i = 0; i < strlen(pt); i++)
	{
		savept[j++] = toupper(pt[i]); //입력받은 평문을 대문자화
	}


	savept[j] = '\0'; //j가 평문의 길이로 savept[평문길이]값에 NULL값을 집어넣어줌.(문장의 끝을 알림)
	for (i = 0; i < j; i += 2) //i는 2씩 평문의길이까지만큼 증가.
	{
		pt0 = strchr(alph, savept[i]) - alph; //평문 -a,alph 배열에서 savept[i]의 값을 검색해서 출력한 값에 -a를 해줌.(alph의 시작은 a이기 때문)
		pt1 = strchr(alph, savept[i + 1]) - alph;//평문 -a,alph 배열에서 savept[i]의 값을 검색해서 출력한 값에 -a를 해줌.(alph의 시작은 a이기 때문), 단. i+1이니 홀수
		cpt0 = col[pt0];
		cpt1 = col[pt1];
		rpt0 = row[pt0];
		rpt1 = row[pt1];

		if (pt0 == pt1) //2개씩 짝을 이룬 평문이 서로 같을 경우
		{
			if (select == 1)//암호화
			{
				ct[i] = ct[i + 1] = savekey[(cpt0 + 5 * rpt0 + 1) % 25]; //행에서 문자를 한칸씩 이동
			}
			else if (select == 2)//복호화
			{
				ct[i] = ct[i + 1] = savekey[(cpt0 + 5 * rpt0 + 24) % 25]; //행에서 문자를 뒤로 한칸 이동
			}
		}
		if (rpt0 == rpt1) //같은 행인 경우
		{
			if (select == 1)
			{
				ct[i] = savekey[(cpt0 + 1) % 5 + 5 * rpt0];  //행에서 문자를 한칸씩 이동
				ct[i + 1] = savekey[(cpt1 + 1) % 5 + 5 * rpt1]; //같은 짝인 문자 역시 행에서 문자를 한칸 이동
			}
			else if (select == 2)
			{
				ct[i] = savekey[(cpt0 + 4) % 5 + 5 * rpt0];  //행에서 문자를 뒤로 한칸 이동
				ct[i + 1] = savekey[(cpt1 + 4) % 5 + 5 * rpt1];//같은 짝인 문자 역시 행에서 문자를 한칸 이동
			}
		}
		else if (cpt0 == cpt1) //같은 열인 경우
		{
			if (select == 1)
			{
				ct[i] = savekey[cpt0 + 5 * ((rpt0 + 1) % 5)]; //열에서 문자를 한칸 씩 이동
				ct[i + 1] = savekey[cpt1 + 5 * ((rpt1 + 1) % 5)]; //같은 짝인 문자 역시 열에서 문자를 한칸 이동
			}
			else if (select == 2)
			{
				ct[i] = savekey[cpt0 + 5 * ((rpt0 + 4) % 5)]; //열에서 문자를 뒤로 한칸 이동
				ct[i + 1] = savekey[cpt1 + 5 * ((rpt1 + 4) % 5)];//같은 짝인 문자 역시 열에서 문자를 한칸 이동
			}
		}
		else //문자가 사각형을 이뤄 대각선인 경우
		{
			ct[i] = savekey[cpt1 + 5 * rpt0]; //행 문자에 5 곱한 값을 열 문자에 더함.
			ct[i + 1] = savekey[cpt0 + 5 * rpt1]; //마찬가지로 행문자에 5 곱한 값을 열문자에 더함.
		}

	}

	for (i = 0; i < 5; i++)  //savekey를 0에서 5까지, 5에서 10까지, 10에서 15까지 ....를 해주는 이중 for문. 키의 표
	{
		for (j = 5 * i; j < 5 * (i + 1); j++)
		{
			printf(" %c ", savekey[j]);
		}
		printf("\n");
	}
}