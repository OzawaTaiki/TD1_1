#pragma once
#include <Novice.h>
#include <Vector2.h>
#include"vector2Util.h"
struct Score {
	int ClearTimer = 0;
	int ClearTimerS = 0;//秒
	int ClearTimerM = 0;//分

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
			Novice::ScreenPrintf(640, 360, "S");//S
		}
		if (ClearTimerS > 4 &&
			ClearTimerS <= 6) {
			Novice::ScreenPrintf(640, 360, "A");//A
		}
		if (ClearTimerS > 6 &&
			ClearTimerS <= 10) {
			Novice::ScreenPrintf(640, 360, "B");//B
		}
		if (ClearTimerS > 10) {
			Novice::ScreenPrintf(640, 360, "C");//C
		}
	}

	void DrawTimer() {
		Novice::ScreenPrintf(640, 360, "%d:%d:%d",ClearTimerM, ClearTimerS, ClearTimer);
	}


};