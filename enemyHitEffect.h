#pragma once
#include <Novice.h>
#include <Vector2Util.h>

const int EEFFECT_MAX = 8;
class EnemyHitEffect {
public:
	Vector2 CPos[EEFFECT_MAX];
	float size[EEFFECT_MAX];
	Vector2 vel[EEFFECT_MAX];
	Vector2 acc[EEFFECT_MAX];

	bool isAppear[EEFFECT_MAX] = { 0 };


	unsigned int color = 0xFFFFFFFF;

public:
	void UpDate(const bool& isHit, const Vector2& playerCPos);

	void Draw(const Vector2& scroll);

};