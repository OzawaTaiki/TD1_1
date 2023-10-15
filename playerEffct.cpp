#include "playerEffect.h"

void playerEffect::Move(const bool& isJump, const bool& isAlive, const Vector2& playerCPos) {
	if (isJump) {
		if (isAlive) {
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
				if (isDraw[i] == true &&
					isPawn[i] == true) {
					size[i] = static_cast<float>(rand() % 20 + 10);
					CPos[i].x = playerCPos.x;
					CPos[i].y = playerCPos.y;
					isPawn[i] = false;
				}

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
	}
}