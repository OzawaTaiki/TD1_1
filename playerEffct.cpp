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
					size[i] = static_cast<float>(rand() % 23 + 12);
					CPos[i].x = playerCPos.x;
					CPos[i].y = playerCPos.y;
					isPawn[i] = false;
				}

			}
		}
	}
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (isDraw[i] == true) {
			size[i] -= 1;
			vertex[0][i].y = CPos[i].y - size[i] / 2;
			vertex[0][i].x = CPos[i].x - size[i] / 2;
			vertex[1][i].x = CPos[i].x + size[i] / 2;
			vertex[1][i].y = CPos[i].y - size[i] / 2;
			vertex[2][i].x = CPos[i].x - size[i] / 2;
			vertex[2][i].y = CPos[i].y + size[i] / 2;
			vertex[3][i].x = CPos[i].x + size[i] / 2;
			vertex[3][i].y = CPos[i].y + size[i] / 2;

			if (size[i] <= 0) {
				isDraw[i] = false;
			}
		}
	}

}


void playerEffect::Draw(const Vector2& scroll) {
	for (int i = 1; i < EFFECT_MAX; i++) {
		Novice::DrawQuad(static_cast<int>(vertex[0][i].x - scroll.x), static_cast<int>(vertex[0][i].y - scroll.y),
			static_cast<int>(vertex[1][i].x - scroll.x), static_cast<int>(vertex[1][i].y - scroll.y),
			static_cast<int>(vertex[2][i].x - scroll.x), static_cast<int>(vertex[2][i].y - scroll.y),
			static_cast<int>(vertex[3][i].x - scroll.x), static_cast<int>(vertex[3][i].y - scroll.y),
			0, 0, 32, 32, whiteGH, 0xFFFFFFFF);
	}
}