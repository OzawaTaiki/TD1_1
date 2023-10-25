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
	int GH[13] = { Novice::LoadTexture("./Resources/images/GAMEOVER.png"),
	 Novice::LoadTexture("./Resources/images/PRESSSPACE.png"),
	 Novice::LoadTexture("./Resources/images/stageSelect.png"),
	 Novice::LoadTexture("./Resources/images/Manual.png"),
	 Novice::LoadTexture("./Resources/images/start.png"),
	 Novice::LoadTexture("./Resources/images/Exit.png"),
	 Novice::LoadTexture("./Resources/images/gameTitle.png"),

	 Novice::LoadTexture("./Resources/images/1~3.png"),
	 Novice::LoadTexture("./Resources/images/4~6.png"),
	 Novice::LoadTexture("./Resources/images/smail.png"),
	 Novice::LoadTexture("./Resources/images/tittleLine.png"),
	 Novice::LoadTexture("./Resources/images/PlayerManual.png"),
	 Novice::LoadTexture("./Resources/images/ItemManual.png"),

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

	void DrawSpriteUpdateManual(int& DrawGH, bool& isEase) {
		timer -= 1;
		if (timer <= 0) {
			timer = 60;
		}
		if (!isEase) {
			if (timer >= 10) {
				Novice::DrawSprite(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2),
					DrawGH, 1.0f, 1.0f, 0.0f, color);
			}
		}
	}

	void DrawSpriteUpdateSELECT(int& DrawGH) {
		int shineColor = 0xfc21c6cc;
		int saveColor = 0x1B162CFF;
		timer -= 1;
		if (timer <= 0) {
			timer = 600;
		}
		color = saveColor;
		if ((timer <= 600 && timer >= 520) ||
			(timer <= 500 && timer >= 480) ||
			(timer <= 450 && timer >= 430) ||
			(timer <= 420 && timer >= 45)
			) {
			color = shineColor;
		}
		Novice::DrawSprite(static_cast<int>(CPos.x - Wsize / 2), static_cast<int>(CPos.y - Hsize / 2),
			DrawGH, 1.0f, 1.0f, 0.0f, color);
	}

};