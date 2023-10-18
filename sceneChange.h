#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <Vector2.h>


struct SceneChange {
	Vector2 CPos = { 0,0 };
	int Wsize = 1280;
	int Hsize = 720;
	unsigned int color = 0xFFFFFFFF;
	bool isDraw = true;
	bool ischange = false;
	float t = 0.0f;
	float easeT = 0.0f;
	float maxPos = 0;
	float minPos = 0;
	float dir = 1;
	int timer = 10;


	int sceneChangeUpGH = Novice::LoadTexture("./Resources/images/fangUp.png");
	int sceneChangeLowGH = Novice::LoadTexture("./Resources/images/fangLow.png");

	void Init(Vector2 cpos, float MaxPos, float MinPos) {
		CPos = cpos;
		maxPos = MaxPos;
		minPos = MinPos;
	}

	void ChangeScene() {

	}

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

	void DrawSpriteUpdate(int GH) {
		Novice::DrawSprite(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2),
			GH, 4.0f, 4.0f, 0.0f, color);
	}

};