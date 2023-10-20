#include "enemyHitEffect.h"

void EnemyHitEffect::UpDate(bool& isHit, const bool& isHitToge, const Vector2& playerCPos) {
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
void  EnemyHitEffect::Reset() {
	for (int i = 0; i < 8; i++) {

		if (CPos[i].y >= 1380) {
			CPos[i] = { 0,0 };
			size[i] = 0;
			vel[i] = { 0,0 };
			acc[i] = { 0,0.8f };
			isAppear[i] = false;

		}
	}

}

void EnemyHitEffect::Draw(const Vector2& scroll) {
	for (int i = 1; i < EEFFECT_MAX; i++) {
		Novice::DrawSprite(static_cast<int>((CPos[i].x - size[i] / 2) - scroll.x), static_cast<int>((CPos[i].y - size[i] / 2) - scroll.y), GH, 1.0f, 1.0f, 0.0f, 0xffffffff);
	}
}

void EnemyHitEffect::OverDraw() {
	for (int i = 0; i < EEFFECT_MAX; i++) {
		if (isAppear[i]) {
			Novice::DrawSprite(static_cast<int>((CPos[i].x - size[i] / 2)), static_cast<int>((CPos[i].y - size[i] / 2)), GH, 1.0f, 1.0f, 0.0f, 0xffffffff);
		}
	}
}