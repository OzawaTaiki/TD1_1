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


	int eachNumber[8];
	Vector2 numberPos[8] = { 0,0 };
	/*画像の読み込み*/
	int numberGH[10] = { 0 };
	int tentenGH = Novice::LoadTexture("./Resources/images/tenten.png");

	void TimeCount() {
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


	void result() {
		//ランクを出す
		if (ClearTimerS <= 4) {
			Novice::ScreenPrintf(640, 340, "S");//S
		}
		if (ClearTimerS > 4 &&
			ClearTimerS <= 6) {
			Novice::ScreenPrintf(640, 340, "A");//A
		}
		if (ClearTimerS > 6 &&
			ClearTimerS <= 10) {
			Novice::ScreenPrintf(640, 340, "B");//B
		}
		if (ClearTimerS > 10) {
			Novice::ScreenPrintf(640, 340, "C");//C
		}
	}

	void DrawTimer() {
		Novice::ScreenPrintf(640, 360, "%d:%d:%d", ClearTimerM, ClearTimerS, ClearTimer);

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
			numberPos[i].x = 356.0f + (static_cast<int>(i) * 71);
			numberPos[i].y = 150.0f;
			if (i != 2 && i != 5) {
				Novice::DrawSprite(static_cast<int>(numberPos[i].x), static_cast<int>(numberPos[i].y), numberGH[eachNumber[i]], 1, 1, 0.0f, 0xFFFFFFFF);
			} else {
				Novice::DrawSprite(static_cast<int>(numberPos[i].x), static_cast<int>(numberPos[i].y), tentenGH, 1, 1, 0.0f, 0xFFFFFFFF);
			}
		}

	}
};