#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <Vector2.h>
#include <Vector2Util.h>

struct RefEffect {
	Vector2 CPos = { 0.0 };
	Vector2 vertex[4] = { 0.0 };
	float Hsize = { 200 };
	float Wsize = { 200 };
	int GH = Novice::LoadTexture("./Resources/images/RefEffect.png");
	bool isDraw = { false };
	bool isHitPoint[4] = { 0 };
	int timerMax = 10;
	int timer = { 0 };


	void Draw(const Vector2& scroll) {
		if (isDraw) {
			Novice::DrawQuad(static_cast<int>(vertex[0].x - scroll.x), static_cast<int>(vertex[0].y - scroll.y),
				static_cast<int>(vertex[1].x - scroll.x), static_cast<int>(vertex[1].y - scroll.y),
				static_cast<int>(vertex[2].x - scroll.x), static_cast<int>(vertex[2].y - scroll.y),
				static_cast<int>(vertex[3].x - scroll.x), static_cast<int>(vertex[3].y - scroll.y),
				0, 0, 32, 32, GH, 0xFFFFFFFF);

		}
	}

	void Appear(const float jumpvel ,const Vector2& playerpos) {
		
		if (isDraw) {
			Hsize = 50 + (jumpvel - jumpvel);
			Wsize = 50;

			if (isHitPoint[0]) {
			CPos = playerpos;
				vertex[0].x = CPos.x + Wsize / 2;
				vertex[0].y = CPos.y + Hsize / 2;
				vertex[1].x = CPos.x - Wsize / 2;
				vertex[1].y = CPos.y + Hsize / 2;
				vertex[2].x = CPos.x + Wsize / 2;
				vertex[2].y = CPos.y - Hsize / 2;
				vertex[3].x = CPos.x - Wsize / 2;
				vertex[3].y = CPos.y - Hsize / 2;
				isHitPoint[0] = false;

			}
			if (isHitPoint[1]) {
				CPos = playerpos;
				vertex[0].x = CPos.x + Wsize / 2;
				vertex[0].y = CPos.y - Hsize / 2;
				vertex[1].x = CPos.x + Wsize / 2;
				vertex[1].y = CPos.y + Hsize / 2;
				vertex[2].x = CPos.x - Wsize / 2;
				vertex[2].y = CPos.y - Hsize / 2;
				vertex[3].x = CPos.x - Wsize / 2;
				vertex[3].y = CPos.y + Hsize / 2;


				isHitPoint[1] = false;
			}
			if (isHitPoint[2]) {
				CPos = playerpos;
				vertex[0].x = CPos.x - Wsize / 2;
				vertex[0].y = CPos.y + Hsize / 2;
				vertex[1].x = CPos.x - Wsize / 2;
				vertex[1].y = CPos.y - Hsize / 2;
				vertex[2].x = CPos.x + Wsize / 2;
				vertex[2].y = CPos.y + Hsize / 2;
				vertex[3].x = CPos.x + Wsize / 2;
				vertex[3].y = CPos.y - Hsize / 2;
				isHitPoint[2] = false;
			}
			if (isHitPoint[3]) {
				CPos = playerpos;
				vertex[0].x = CPos.x - Wsize / 2;
				vertex[0].y = CPos.y - Hsize / 2;
				vertex[1].x = CPos.x + Wsize / 2;
				vertex[1].y = CPos.y - Hsize / 2;
				vertex[2].x = CPos.x - Wsize / 2;
				vertex[2].y = CPos.y + Hsize / 2;
				vertex[3].x = CPos.x + Wsize / 2;
				vertex[3].y = CPos.y + Hsize / 2;
				isHitPoint[3] = false;
			}
		}
	}

	void DrawTimer() {
		if (isDraw) {
			timer -= 1;
			if (timer <= 0)
			{
				isDraw = false;
				for (int i = 0; i < 4; i++)
				{
					isHitPoint[i] = false;

				}

			}
		} else {
			timer = timerMax;
		}
	}


};