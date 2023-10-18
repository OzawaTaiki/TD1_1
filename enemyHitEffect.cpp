#include "enemyHitEffect.h"

void EnemyHitEffect::UpDate(const bool& isHit, const bool& isHitToge, const Vector2& playerCPos) {
	if (isHit || isHitToge) {
		for (int i = 0; i < EEFFECT_MAX; i++) {
			if (!isAppear[i]) {
				CPos[i] = playerCPos;
				acc[i] = { 0.0f,0.8f };
				vel[i].x = static_cast<float>(rand() % 31 - 15);
				vel[i].y = static_cast<float>(rand() % 31 - 15);
				size[i] = static_cast<float>(20.0f);
				isAppear[i] = true;
			}
		}
		for (int i = 0; i < EEFFECT_MAX; i++) {
			if (isAppear[i]) {
				vel[i].x += acc[i].x;
				vel[i].y += acc[i].y;
				CPos[i].x += vel[i].x;
				CPos[i].y += vel[i].y;
			}
		}
	}
}


void EnemyHitEffect::Draw(const Vector2& scroll) {
	for (int i = 1; i < EEFFECT_MAX; i++) {

		Novice::DrawBox(static_cast<int>((CPos[i].x - size[i] / 2) - scroll.x), static_cast<int>((CPos[i].y - size[i] / 2) - scroll.y),
			static_cast<int>(size[i]), static_cast<int>(size[i]), 0.0f, color, kFillModeSolid);
	}
}