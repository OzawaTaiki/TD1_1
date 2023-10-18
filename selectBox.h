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
	unsigned int color = 0xFFFFFFFF;
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


	void DrawUpDate() {

		if (isDraw) {
			Novice::DrawBox(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2),
				Wsize, Hsize, 0.0f, color, kFillModeSolid);
			/*
			Novice::DrawQuad(static_cast<int>(vertex[0].x), static_cast<int>(vertex[0].y),
				static_cast<int>(vertex[1].x), static_cast<int>(vertex[1].y),
				static_cast<int>(vertex[2].x), static_cast<int>(vertex[2].y),
				static_cast<int>(vertex[3].x), static_cast<int>(vertex[3].y),
				0, 0, 256, 256, selectBigGH, 0xFFFFFFFF);
		*/
		}
	}

};

