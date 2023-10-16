#pragma once

#include<Novice.h>
#define _USE_MATH_DEFINES
#include"vector2Util.h"

class jumpDirection
{
	float directionX;
	Vector2 EndLinePos;

	const Vector2 kJumpDirectionVect = { 100,0 };
	Vector2 RotateJumpDirectionVect;
	Vector2 normalizeJumpDirectionVect;

	float theta;
	const float kMaxTheta = -(75.0f / 180.0f) * (float)M_PI;
	const float kMinTheta = -(15.0f / 180.0f) * (float)M_PI;

	float t;
	float addT;

	float margin = 15.0f;
	int Num = 15;

	bool isPress;
	bool isRelease;

public:

	jumpDirection() {
		directionX = 0;
		EndLinePos = { 0,0 };

		RotateJumpDirectionVect = { 0,0 };
		normalizeJumpDirectionVect = { 0,0 };

		theta = -(1.0f / 4.0f) * (float)M_PI;

		t = 0.5f;
		addT = 1.0f / (60.0f * 0.80f);
		isPress = false;
		isRelease = false;
	};

	void rotate(const Vector2& pos, float direction, const Vector2& scroll, const bool& isAlive);

	Vector2 getNormalizeJumpVect();

	void ButtonFlagReset(bool isJump);

	void isReleaseFlag();

	void isPressFlag();

};
