#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <Vector2Util.h>

const int BOX_MAX = 10;
struct selectBox {
	Vector2 CPos = { -1000,-1000 };
	Vector2 vertex[4] = { 0 };
	int Wsize = 128;//150
	int Hsize = 128;//150
	unsigned int color = 0xfc21c6ff;
	float dir = 1;
	float theta = 0.0f;
	Vector2 originPos = { 640,1590 };//{640,1490}
	Vector2 length = { 1250,0 };//{1150,0}
	Vector2 rotateLength = { 0 };
	float t = 0.0f;
	float maxTheta = (-5.0f / 14.0f * float(M_PI));
	float minTheta = 0;
	bool isR = false;
	bool isHit = false;
	bool isDraw = true;
	int timer = 35;
	float velY = 0;
	float accY = 1.4f;
	int GH[10] = {
		Novice::LoadTexture("./Resources/images/select1.png"),

	};


	void DrawUpDate(int Num) {

		if (isDraw) {
			Novice::DrawBox(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2), Wsize, Hsize, 0.0f, 0xFFFFFFFF, kFillModeSolid);
			Novice::DrawSprite(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2), GH[Num], 1.0f, 1.0f, 0.0f, color);
		}
	}

};