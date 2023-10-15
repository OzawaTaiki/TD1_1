#include "playerEffect.h"

void playerEffect::Move(const bool& isJump, const Vector2& playerCPos) {
	if (isJump) {
		isDraw[0] = true;

		for (int i = 1; i < EFFECT_MAX; i++) {
			if (isDraw[i - 1] == true &&
				isDraw[i] == false) {
				timer[i] += 1;
				if (timer[i] == 10) {
					isDraw[i] = true;
					isPawn[i] = true;
					timer[i] = 0;
				}
			}
		}

		for (int i = 0; i < EFFECT_MAX; i++) {
			if (isDraw[i] == true&&
				isPawn[i]==true) {
				size[i] = static_cast<float>(rand() % 25 + 10);
				CPos[i].x = playerCPos.x;
				CPos[i].y = playerCPos.y;
				isPawn[i] = false;
			}
			
		}
	}
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (isDraw[i] == true) {
			size[i] -= 0.5f;
			if (size[i] <= 0) {
				isDraw[i] = false;
			}
		}
	}
}


void playerEffect::Draw(const Vector2& scroll) {
	for (int i = 1; i < EFFECT_MAX; i++) {

		Novice::DrawBox(static_cast<int>((CPos[i].x - size[i] / 2) - scroll.x), static_cast<int>((CPos[i].y - size[i] / 2) - scroll.y),
			static_cast<int>(size[i]), static_cast<int>(size[i]), 0.0f, color, kFillModeSolid);

		Novice::ScreenPrintf(700, 360, "Draw[1]=%d,%d,%d,%d", isDraw[0], isDraw[1], isDraw[2], isDraw[3]);
		Novice::ScreenPrintf(700, 380, "Draw[1]x=%f,%f,%f,%f", CPos[0].x, CPos[1].x, CPos[2].x, CPos[3].x);
		Novice::ScreenPrintf(700, 380, "Draw[1]y=%f,%f,%f,%f", CPos[0].y, CPos[1].y, CPos[2].y, CPos[3].y);
		Novice::ScreenPrintf(700, 400, "Draw[1]size=%f,%f,%f,%f", size[0], size[1], size[2], size[3]);
	}
}