#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <Vector2.h>
#include"vector2Util.h"

	const int EFFECT_MAX = 32;
class playerEffect {

	Vector2 CPos[EFFECT_MAX] = { 0 };
	float size[EFFECT_MAX] = { 0 };
	int whiteGH = Novice::LoadTexture("./NoviceResources/white1x1.png");
	unsigned int color = 0xFFFFFFFF;
	bool isDraw[EFFECT_MAX] = { 0 };
	bool isPawn[EFFECT_MAX] = { 0 };
	int timer[EFFECT_MAX] = { 0 };

	public:
	
	void Move(const bool& isJump, const Vector2& playerCPos);
	void Draw(const Vector2& scroll);
};