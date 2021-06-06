#include <bangtal.h>
#include<stdio.h> 
#include<stdlib.h>
#include<time.h>

SceneID page1, page2, page3, page4;
ObjectID start, end, end2, restart, left1, right1, left2;
ObjectID lv1, lv2, lv3; // 상 중 하 이미지 
ObjectID lv1_stu[4][4], lv2_stu[6][6], lv3_stu[8][8]; // 난이도 별 학생 
ObjectID tutorial[9]; // 튜토리얼
TimerID covidTimer; // 감염 전파속도 타이머
TimerID lv1rand, lv2rand, lv3rand; // 난이도 랜덤 확진자 생성 타이머
TimerID sec1, sec2;

int n; // 난이도에 따른 n*n
int survive = 0; //생존 시간
int stux, stuy;

int lv1_covid[4][4] = { 0, }, lv2_covid[6][6] = { 0, }, lv3_covid[8][8] = { 0, }; //정상이면 0 감염이면 1 확산으로 감염이면 2

int check_loc(int a, int b, int n)
{
	if ((a > 0 && a < n - 1) && (b > 0 && b < n - 1)) return 1; // '+' 형태로 전염이 가능한 상태 
	else if ((a == 0) && (b == 0)) return 2; //'┍' 형태로 전염이 가능한 상태 
	else if ((a == 0) && (b == n - 1)) return 3; // 'ㄱ' 형태로 전염이 가능한 상태 
	else if ((a == n - 1) && (b == 0)) return 4; // 'ㄴ' 형태로 전염이 가능한 상태 
	else if ((a == n - 1) && (b == n - 1)) return 5; // '┘' 형태로 전염이 가능한 상태 
	else if ((a == 0) && (b > 0 && b < n - 1)) return 6; // 'ㅜ' 형태로 전염이 가능한 상태 
	else if ((a > 0 && a < n - 1) && (b == 0)) return 7; // 'ㅏ' 형태로 전염이 가능한 상태 
	else if ((a > 0 && a < n - 1) && (b == n - 1)) return 8; // 'ㅓ'형태로 전염이 가능한 상태
	else if ((a == n - 1) && (b > 0 && b < n - 1)) return 9; // 'ㅗ' 형태로 전염이 가능한 상태 
	else return 0;
}

void timerstop(void) {
	stopTimer(covidTimer);
	stopTimer(lv1rand);
	stopTimer(lv2rand);
	stopTimer(lv3rand);
	stopTimer(sec1);
	stopTimer(sec2);
}

void check_lv1_covid(int a, int b)
{
	if (lv1_covid[a][b] != 1)
	{
		setObjectImage(lv1_stu[a][b], "image/student_corona44.png");
		lv1_covid[a][b] = 2;
	}
}

void check_lv2_covid(int a, int b)
{
	if (lv2_covid[a][b] != 1)
	{
		setObjectImage(lv2_stu[a][b], "image/student_corona66.png");
		lv2_covid[a][b] = 2;
	}
}

void check_lv3_covid(int a, int b)
{
	if (lv3_covid[a][b] != 1)
	{
		setObjectImage(lv3_stu[a][b], "image/student_corona88.png");
		lv3_covid[a][b] = 2;
	}
}


ObjectID makeObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown)
	{
		showObject(object);
	}
	return object;
}


//바이러스 확산 함수
void spread(int n) {
	if (n == 4)
	{
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				if (lv1_covid[a][b] == 1)
				{
					if (check_loc(a, b, n) == 1) 
					{

						check_lv1_covid(a + 1, b);
						check_lv1_covid(a, b + 1);
						check_lv1_covid(a - 1, b);
						check_lv1_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 2) {

						check_lv1_covid(a + 1, b);
						check_lv1_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 3) {
	
						check_lv1_covid(a + 1, b);
						check_lv1_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 4) {

						check_lv1_covid(a, b + 1);
						check_lv1_covid(a - 1, b);
					}
					else if (check_loc(a, b, n) == 5) {

						check_lv1_covid(a - 1, b);
						check_lv1_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 6) {

						check_lv1_covid(a + 1, b);
						check_lv1_covid(a, b - 1);
						check_lv1_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 7) {

						check_lv1_covid(a + 1, b);
						check_lv1_covid(a - 1, b);
						check_lv1_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 8) {

						check_lv1_covid(a + 1, b);
						check_lv1_covid(a - 1, b);
						check_lv1_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 9) {

						check_lv1_covid(a - 1, b);
						check_lv1_covid(a, b - 1);
						check_lv1_covid(a, b + 1);
					}
				}
			}
		}
	}
	
	else if (n == 6)
	{
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				if (lv2_covid[a][b] == 1)
				{
					if (check_loc(a, b, n) == 1)
					{
						
						check_lv2_covid(a + 1, b);
						check_lv2_covid(a, b + 1);
						check_lv2_covid(a -1, b);
						check_lv2_covid(a, b - 1);

					}
					else if (check_loc(a, b, n) == 2) {

						check_lv2_covid(a + 1, b);
						check_lv2_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 3) {
						
						check_lv2_covid(a + 1, b);
						check_lv2_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 4) {

						check_lv2_covid(a, b + 1);
						check_lv2_covid(a - 1, b);
					}
					else if (check_loc(a, b, n) == 5) {

						check_lv2_covid(a - 1, b);
						check_lv2_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 6) {

						check_lv2_covid(a + 1, b);
						check_lv2_covid(a, b - 1);
						check_lv2_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 7) {

						check_lv2_covid(a + 1, b);
						check_lv2_covid(a - 1, b);
						check_lv2_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 8) {

						check_lv2_covid(a + 1, b);
						check_lv2_covid(a - 1, b);
						check_lv2_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 9) {

						check_lv2_covid(a - 1, b);
						check_lv2_covid(a, b -1);
						check_lv2_covid(a, b + 1);
					}
				}
			}
		}
	}
	else if (n == 8)
	{
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				if (lv3_covid[a][b] == 1)
				{
					if (check_loc(a, b, n) == 1)
					{
						
						check_lv3_covid(a + 1, b);
						check_lv3_covid(a, b + 1);
						check_lv3_covid(a - 1, b);
						check_lv3_covid(a, b - 1);
						
					}
					else if (check_loc(a, b, n) == 2) {

						check_lv3_covid(a + 1, b);
						check_lv3_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 3) {

						check_lv3_covid(a + 1, b);
						check_lv3_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 4) {

						check_lv3_covid(a, b + 1);
						check_lv3_covid(a - 1, b);
					}
					else if (check_loc(a, b, n) == 5) {

						check_lv3_covid(a - 1, b);
						check_lv3_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 6) {

						check_lv3_covid(a + 1, b);
						check_lv3_covid(a, b - 1);
						check_lv3_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 7) {

						check_lv3_covid(a + 1, b);
						check_lv3_covid(a - 1, b);
						check_lv3_covid(a, b + 1);
					}
					else if (check_loc(a, b, n) == 8) {

						check_lv3_covid(a + 1, b);
						check_lv3_covid(a - 1, b);
						check_lv3_covid(a, b - 1);
					}
					else if (check_loc(a, b, n) == 9) {

						check_lv3_covid(a - 1, b);
						check_lv3_covid(a, b - 1);
						check_lv3_covid(a, b + 1);
					}
				}
			}
		}
	}
}

void endcheck(int n) {
	int sum = 0;
	if (n == 4) {
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				sum += lv1_covid[a][b];
				if (sum == n * n) {
					showMessage("패배! 상단에 플레이타임이 있어요");
					timerstop();
					locateObject(end2, page4, 900, 350);
					showObject(end2);
					showObject(restart);
					for (int a = 0; a < n; a++) {
						for (int b = 0; b < n; b++) {
							lv1_covid[a][b] = 0;
						}
					}
				}
			}
		}
	}
	else if (n == 6) {
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				sum += lv2_covid[a][b];
				if (sum == n * n) {
					showMessage("패배! 상단에 플레이타임이 있어요");
					timerstop();
					locateObject(end2, page4, 900, 350);
					showObject(end2);
					showObject(restart);
					for (int a = 0; a < n; a++) {
						for (int b = 0; b < n; b++) {
							lv2_covid[a][b] = 0;
						}
					}
				}
			}
		}
	}
	else if (n == 8) {
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				sum += lv3_covid[a][b];
				if (sum == n * n) {
					showMessage("패배! 상단에 플레이타임이 있어요");
					timerstop();
					locateObject(end2, page4,900,350);
					showObject(end2);
					showObject(restart);
					for (int a = 0; a < n; a++) {
						for (int b = 0; b < n; b++) {
							lv3_covid[a][b] = 0;
						}
					}
				}
			}
		}
	}
}


//바이러스 확진자 생성 함수
void randvirus(int n) {
	if (n == 4) {
		for (int i = 0; i < (n * n);i++) {
			
			stux = rand() % 4;
			stuy = rand() % 4;
			if (lv1_covid[stux][stuy] ==0) {
				setObjectImage(lv1_stu[stux][stuy], "image/student_corona44.png");
				lv1_covid[stux][stuy] = 1;
				break;
			}
			
			
		}
		//코로나 확진 현황 확인
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				printf("%d", lv1_covid[a][b]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else if (n == 6) {
		for (int i = 0; i < (n * n); i++) {

			stux = rand() % 6;
			stuy = rand() % 6;
			if (lv2_covid[stux][stuy] ==0) {
				setObjectImage(lv2_stu[stux][stuy], "image/student_corona66.png");
				lv2_covid[stux][stuy] = 1;
				break;
			}
		}
		//코로나 확진 현황 확인
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				printf("%d", lv2_covid[a][b]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else if (n == 8) {
		for (int i = 0; i < (n * n); i++) {
			stux = rand() % 8;
			stuy = rand() % 8;
			if (lv3_covid[stux][stuy] ==0) {
				setObjectImage(lv3_stu[stux][stuy], "image/student_corona88.png");
				lv3_covid[stux][stuy] = 1;
				break;
			}
		}
		//코로나 확진 현황 확인
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				printf("%d", lv3_covid[a][b]);
			}
			printf("\n");
		}
		printf("\n");
	}
}


void timerCallback(TimerID timer) {
	if (timer == covidTimer) {/*감염자로부터 전염이 퍼지는 속도*/
		if (n == 4)
		{
			for (int a = 0; a < n; a++)
			{
				for (int b = 0; b < n; b++)
				{
					if (lv1_covid[a][b] == 2)
					{
						lv1_covid[a][b] = 1;
					}
				}
			}
		}
		else if (n == 6)
		{
			for (int a = 0; a < n; a++)
			{
				for (int b = 0; b < n; b++)
				{
					if (lv2_covid[a][b] == 2)
					{
						lv2_covid[a][b] = 1;
					}
				}
			}
		}
		else if (n == 8)
		{
			for (int a = 0; a < n; a++)
			{
				for (int b = 0; b < n; b++)
				{
					if (lv3_covid[a][b] == 2)
					{
						lv3_covid[a][b] = 1;
					}
				}
			}
		}
		endcheck(n);
		spread(n);
		setTimer(covidTimer,4.0f);
		startTimer(covidTimer);
	}
	else if (timer == lv1rand) {/*1단계에서 랜덤으로 감염자가 발생하는 속도*/
		
		randvirus(n);
		setTimer(lv1rand, 2.0f);
		if (survive < 30) {
			startTimer(lv1rand);
		}
		else {
			stopTimer(lv1rand);
			startTimer(lv2rand);
		}
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				if (lv1_covid[a][b] == 2)
				{
					lv1_covid[a][b] = 1;
				}
			}
		}
		endcheck(n);
	}
	else if (timer == lv2rand) {/*2단계에서 랜덤으로 감염자가 발생하는 속도*/
		
		randvirus(n);
		setTimer(lv2rand, 1.0f);
		if (survive < 30) {
			startTimer(lv2rand);
		}
		else {
			stopTimer(lv2rand);
			startTimer(lv3rand);
		}
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				if (lv2_covid[a][b] == 2)
				{
					lv2_covid[a][b] = 1;
				}
			}
		}
		endcheck(n);
	}
	else if (timer == lv3rand) {/*3단계에서 랜덤으로 감염자가 발생하는 속도*/
		
		randvirus(n);
		setTimer(lv3rand, 0.50f);
		startTimer(lv3rand);
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				if (lv3_covid[a][b] == 2)
				{
					lv3_covid[a][b] = 1;
				}
			}
		}
		endcheck(n);
	}
	else if (timer == sec1) {
		++survive;
		setTimer(sec1, 1.0f);
		startTimer(sec1);
		increaseTimer(sec2, 1.0f);
	}
}



void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == start)
	{
		enterScene(page2);
	}
	else if (object == left1)
	{
		enterScene(page1);
	}
	else if (object == right1)
	{
		enterScene(page3);
		showMessage("난이도 하 : 4X4 / 난이도 중 : 6X6 / 난이도 상 : 8X8");
	}
	else if (object == left2)
	{
		enterScene(page2);
	}
	else if (object == lv1)
	{
		n = 4;

		enterScene(page4);
		hideObject(end2);
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				lv1_stu[a][b] = makeObject("image/student44.png", page4, 350 + 100 * b, 575 - 120 * a, true);
				scaleObject(lv1_stu[a][b], 0.2f);
			}
		}
		startTimer(covidTimer);
		startTimer(lv1rand);
		startTimer(sec1);
		showTimer(sec2);
	}
	else if (object == lv2)
	{
		n = 6;

		enterScene(page4);
		hideObject(end2);
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				lv2_stu[a][b] = makeObject("image/student66.png", page4, 350 + 70 * b, 575 - 80 * a, true);
				scaleObject(lv2_stu[a][b], 0.2f);
			}
		}
		startTimer(covidTimer);
		startTimer(lv2rand);
		startTimer(sec1);
		showTimer(sec2);
	}
	else if (object == lv3)
	{
		n = 8;

		enterScene(page4);
		hideObject(end2);
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < n; b++)
			{
				lv3_stu[a][b] = makeObject("image/student88.png", page4, 300 + 60 * b, 600 - 65 * a, true);
				scaleObject(lv3_stu[a][b], 0.2f);
			}
		}
		startTimer(covidTimer);
		startTimer(lv3rand);
		startTimer(sec1);
		showTimer(sec2);
	}
	//난이도 상에서의 상호작용
	if (n == 8) {
		for (int objectX = 0; objectX < n; objectX++) {
			for (int objectY = 0; objectY < n; objectY++) {
				if (object == lv3_stu[objectX][objectY]) {
					setObjectImage(lv3_stu[objectX][objectY], "image/student88.png");
					lv3_covid[objectX][objectY] = 0;
				}
			}
		}
	}
	//난이도 중에서의 상호작용
	else if (n == 6) {
		for (int objectX = 0; objectX < n; objectX++) {
			for (int objectY = 0; objectY < n; objectY++) {
				if (object == lv2_stu[objectX][objectY]) {
					setObjectImage(lv2_stu[objectX][objectY], "image/student66.png");
					lv2_covid[objectX][objectY] = 0;
				}
			}
		}
	}
	//난이도 하에서의 상호작용
	else if (n == 4) {
		for (int objectX = 0; objectX < n; objectX++) {
			for (int objectY = 0; objectY < n; objectY++) {
				if (object == lv1_stu[objectX][objectY]) {
					setObjectImage(lv1_stu[objectX][objectY], "image/student44.png");
					lv1_covid[objectX][objectY] = 0;
				}
			}
		}
	}
	if (object == end) {
		endGame();
	}
	if (object == end2) {
		endGame();
	}
	if (object == restart) {
		enterScene(page1);
		setTimer(sec2, 0.0f);
		hideTimer();
		end = makeObject("image/end.png", page1, 375, 220, true);
		hideObject(restart);
		hideObject(end2);
		if (n == 4) {
			for (int a = 0; a < 4; a++)
			{
				for (int b = 0; b < 4; b++)
				{
					hideObject(lv1_stu[a][b]);
					scaleObject(lv1_stu[a][b], 0.2f);
				}
			}
		}
		if (n == 6) {
			for (int a = 0; a < 6; a++)
			{
				for (int b = 0; b < 6; b++)
				{
					hideObject(lv2_stu[a][b]);
					scaleObject(lv2_stu[a][b], 0.2f);
				}
			}
		}
		if (n == 8) {
			for (int a = 0; a < 8; a++)
			{
				for (int b = 0; b < 8; b++)
				{
					hideObject(lv3_stu[a][b]);
					scaleObject(lv3_stu[a][b], 0.2f);
				}
			}
		}

	}
}



int main()
{
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	page1 = createScene("초기 화면", "image/Background.png");
	page2 = createScene("게임 설명", "image/playBackground.png");
	page3 = createScene("난이도", "image/playBackground.png");
	page4 = createScene("게임 화면", "image/playBackground.png");
	

	start = makeObject("image/start.png", page1, 625, 220, true);
	end = makeObject("image/end.png", page1, 375, 220, true);
	end2 = makeObject("image/end.png", page4, 375, 220, false);
	left1 = makeObject("image/left.png", page2, 225, 200, true);
	right1 = makeObject("image/right.png", page2, 825, 200, true);
	left2 = makeObject("image/left.png", page3, 225, 200, true);
	restart = makeObject("image/left.png", page4, 100, 350, false);

	tutorial[0] = makeObject("image/tutorial1.png", page2, 0, 500, true);
	tutorial[1] = makeObject("image/tutorial2.png", page2, 500, 500, true);
	tutorial[2] = makeObject("image/tutorial3.png", page2, 150, 300, true);
	tutorial[3] = makeObject("image/tutorial4.png", page2, 450, 300, true);
	tutorial[4] = makeObject("image/tutorial5.png", page2, 750, 300, true);
	tutorial[5] = makeObject("image/tutorial6.png", page2, 375, 375, true);
	tutorial[6] = makeObject("image/tutorial7.png", page2, 675, 375, true);
	tutorial[7] = makeObject("image/explain1.png", page2, 140, 550, true);
	tutorial[8] = makeObject("image/explain2.png", page2, 650, 550, true);


	lv1 = makeObject("image/lv1.png", page3, 200, 500, true);
	lv2 = makeObject("image/lv2.png", page3, 500, 500, true);
	lv3 = makeObject("image/lv3.png", page3, 800, 500, true);

	covidTimer = createTimer(4.0f);

	lv1rand = createTimer(2.0f);
	lv2rand = createTimer(1.0f);
	lv3rand = createTimer(0.5f);

	sec1 = createTimer(1.0f);
	sec2 = createTimer(0.0f);

	srand(time(NULL));

	scaleObject(left1, 0.5f);
	scaleObject(right1, 0.5f);
	scaleObject(left2, 0.5f);
	scaleObject(lv1, 0.5f);
	scaleObject(lv2, 0.5f);
	scaleObject(lv3, 0.5f);
	scaleObject(tutorial[0], 0.4f);
	scaleObject(tutorial[1], 0.4f);
	scaleObject(tutorial[2], 0.4f);
	scaleObject(tutorial[3], 0.4f);
	scaleObject(tutorial[4], 0.4f);
	scaleObject(tutorial[5], 0.4f);
	scaleObject(tutorial[6], 0.4f);
	scaleObject(tutorial[7], 0.5f);
	scaleObject(tutorial[8], 0.5f);


	startGame(page1);
}