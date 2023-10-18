#pragma once
#include <Novice.h>
#include <Vector2Util.h>

const int EEFFECT_MAX = 8;
class EnemyHitEffect {
public:
	Vector2 CPos[EEFFECT_MAX] = { 0 };
	float size[EEFFECT_MAX] = { 0 };
	Vector2 vel[EEFFECT_MAX] = { 0 };
	Vector2 acc[EEFFECT_MAX] = { 0 };

	bool isAppear[EEFFECT_MAX] = { 0 };


	unsigned int color = 0xFF0000FF;

public:
	void UpDate(const bool& isHit, const bool& isHitToge, const Vector2& playerCPos);

	void Draw(const Vector2& scroll);

};