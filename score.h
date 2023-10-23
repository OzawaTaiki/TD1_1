#pragma once
#include <Novice.h>
#include <Vector2.h>
#include"vector2Util.h"
struct Score {
	int ClearTimer = 0;
	int ClearTimerS = 0;//秒
	int ClearTimerM = 0;//分

	int RClearTimer = 0;
	int RClearTimerS = 0;//秒
	int RClearTimerM = 0;//分
	//秒
	//S,A,B
	int kCheckRankTimeS[7][3] = {
		{17,25,40},
		{17,20,25},
		{17,20,25},
		{17,20,25},
		{17,20,25},
		{17,20,25},
		{17,20,25}
	};
	//分
	//S,A,B
	int kCheckRankTimeM[7][3] = {
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0}
	};

	int eachNumber[8];
	Vector2 numberPos[8] = { 0,0 };
	Vector2 resultRankCPos = { 640,400 };
	int rankSize = 225;
	/*画像の読み込み*/
	int numberGH[10] = { Novice::LoadTexture("./Resources/images/0.png"),
		Novice::LoadTexture("./Resources/images/1.png"),
		Novice::LoadTexture("./Resources/images/2.png"),
		Novice::LoadTexture("./Resources/images/3.png"),
		Novice::LoadTexture("./Resources/images/4.png"),
		Novice::LoadTexture("./Resources/images/5.png"),
		Novice::LoadTexture("./Resources/images/6.png"),
		Novice::LoadTexture("./Resources/images/7.png"),
		Novice::LoadTexture("./Resources/images/8.png"),
		Novice::LoadTexture("./Resources/images/9.png")
	};

	int rankGH[4] = { Novice::LoadTexture("./Resources/images/RankS.png"),
	Novice::LoadTexture("./Resources/images/RankA.png"),
	Novice::LoadTexture("./Resources/images/RankB.png"),
	Novice::LoadTexture("./Resources/images/RankC.png")
	};

	unsigned int color[4] = {
		0xffff00ff,
		0xff0000ff,
		0x0000ffff,
		0x00ff00ff

	};

	int tentenGH = Novice::LoadTexture("./Resources/images/tenten.png");

	void TimeCount(bool playerAlive, bool isGoal) {
		if (playerAlive && !isGoal) {
			ClearTimer += 1;
			if (ClearTimer == 60) {
				ClearTimerS++;
				ClearTimer = 0;
			}
			if (ClearTimerS == 60) {
				ClearTimerM++;
				ClearTimerS = 0;
			}
		}
	}


	void result(int loadStage) {
		//ランクを出す
		for (int i = 0; i < 3; i++)
			if (ClearTimerS <= kCheckRankTimeS[loadStage][i] && ClearTimerM <= kCheckRankTimeM[loadStage][i])
			{
				Novice::DrawSprite(static_cast<int>(resultRankCPos.x - rankSize), static_cast<int>(resultRankCPos.y - rankSize), rankGH[i], 1.5f, 1.5f, 0.0f, color[i]);
				break;
			}
			else if (i == 2)
			{
				Novice::DrawSprite(static_cast<int>(resultRankCPos.x - rankSize), static_cast<int>(resultRankCPos.y - rankSize), rankGH[3], 1.5f, 1.5f, 0.0f, color[3]);
			}
	}

	void DrawTimer() {

		Novice::ScreenPrintf(640, 360, "%d:%d:%d", ClearTimerM, ClearTimerS, ClearTimer);

	}


	void DrawBGTimer() {
		RClearTimerM = ClearTimerM;
		RClearTimerS = ClearTimerS;
		RClearTimer = ClearTimer;

		//分１０の位
		eachNumber[0] = RClearTimerM / 10;
		RClearTimerM = RClearTimerM % 10;
		//分１の位
		eachNumber[1] = RClearTimerM / 1;
		RClearTimerM = RClearTimerM % 1;
		//秒１0の位
		eachNumber[3] = RClearTimerS / 10;
		RClearTimerS = RClearTimerS % 10;
		//秒１の位
		eachNumber[4] = RClearTimerS / 1;
		RClearTimerS = RClearTimerS % 1;
		//フレーム１０の位
		eachNumber[6] = RClearTimer / 10;
		RClearTimer = RClearTimer % 10;
		//フレーム１の位
		eachNumber[7] = RClearTimer / 1;
		RClearTimer = RClearTimer % 1;

		for (int i = 1; i < 8; i++) {
			numberPos[i].x = 64.0f + (static_cast<int>(i - 1) * 70 * 2.5f);
			numberPos[i].y = 100.0f;
			if (i != 2 && i != 5) {
				Novice::DrawSprite(static_cast<int>(numberPos[i].x), static_cast<int>(numberPos[i].y), numberGH[eachNumber[i]], 2.5f, 4.0f, 0.0f, 0x333333ff);
			}
			else {
				Novice::DrawSprite(static_cast<int>(numberPos[i].x), static_cast<int>(numberPos[i].y), tentenGH, 2.5f, 4.0f, 0.0f, 0x333333ff);
			}
		}
	}

	void DrawResultTimer() {
		RClearTimerM = ClearTimerM;
		RClearTimerS = ClearTimerS;
		RClearTimer = ClearTimer;

		//分１０の位
		eachNumber[0] = RClearTimerM / 10;
		RClearTimerM = RClearTimerM % 10;
		//分１の位
		eachNumber[1] = RClearTimerM / 1;
		RClearTimerM = RClearTimerM % 1;
		//秒１0の位
		eachNumber[3] = RClearTimerS / 10;
		RClearTimerS = RClearTimerS % 10;
		//秒１の位
		eachNumber[4] = RClearTimerS / 1;
		RClearTimerS = RClearTimerS % 1;
		//フレーム１０の位
		eachNumber[6] = RClearTimer / 10;
		RClearTimer = RClearTimer % 10;
		//フレーム１の位
		eachNumber[7] = RClearTimer / 1;
		RClearTimer = RClearTimer % 1;

		for (int i = 0; i < 8; i++) {
			numberPos[i].x = 446.0f + (static_cast<int>(i - 1) * 71);
			numberPos[i].y = 100.0f;
			if (i != 2 && i != 5) {
				Novice::DrawSprite(static_cast<int>(numberPos[i].x), static_cast<int>(numberPos[i].y), numberGH[eachNumber[i]], 1, 1, 0.0f, 0xffffffff);
			}
			else {
				Novice::DrawSprite(static_cast<int>(numberPos[i].x), static_cast<int>(numberPos[i].y), tentenGH, 1, 1, 0.0f, 0xffffffff);
			}
		}

	}
};