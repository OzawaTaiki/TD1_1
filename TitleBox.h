#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <Vector2.h>


struct Box {
	Vector2 CPos = { 0 };
	Vector2 vertex[4] = { 0 };
	Vector2 vel = { 0 };
	int Wsize = 0;
	int Hsize = 0;
	unsigned int color = 0;
	bool isDraw = true;
	bool isHit = false;
	int GH[10] = { Novice::LoadTexture("./Resources/images/GAMEOVER.png"),
	 Novice::LoadTexture("./Resources/images/PRESSSPACE.png"),
	};

	int timer = 60;

	void Init(Vector2 cpos, int WSize, int HSize, unsigned int Color) {
		CPos = cpos;
		Wsize = WSize;
		Hsize = HSize;
		color = Color;
	}

	void HitBox(Vector2 playerVertex[4], Vector2 boxVertex[4]) {
		if (!isHit) {
			if (playerVertex[1].x >= boxVertex[0].x &&
				playerVertex[0].x <= boxVertex[1].x &&
				playerVertex[1].y <= boxVertex[3].y &&
				playerVertex[3].y >= boxVertex[1].y) {
				isHit = true;
			}

		}

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

	void DrawSpriteUpdate(int& DrawGH) {
		Novice::DrawSprite(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2),
			DrawGH, 1.0f, 1.0f, 0.0f, color);
	}

	void DrawSpriteUpdateT(int& DrawGH) {
		timer -= 1;
		if (timer <= 0) {
			timer = 60;
		}
		if (timer >= 10) {
			Novice::DrawSprite(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2),
				DrawGH, 1.0f, 1.0f, 0.0f, color);
		}
	}

};