#pragma once

#include<Novice.h>
#define _USE_MATH_DEFINES
#include"vector2Util.h"

class TjumpDirection
{
	float directionX;
	Vector2 EndLinePos;

	const Vector2 kJumpDirectionVect = { 100,0 };
	Vector2 RotateJumpDirectionVect;
	Vector2 normalizeJumpDirectionVect;

	float theta;
	const float kMaxTheta = -(160.0f / 180.0f) * (float)M_PI;
	const float kMinTheta = -(25.0f / 180.0f) * (float)M_PI;

	float t;
	float addT;

	float margin = 50.0f;
	int Num = 10;

	bool isPress;
	bool isRelease;

	int circleGH = Novice::LoadTexture("./Resources/images/circle.png");
	float circleGHSize = 32.0f;
	float circleRadius = 20.0f;


public:

	TjumpDirection() {
		directionX = 0;
		EndLinePos = { 0,0 };

		RotateJumpDirectionVect = { 0,0 };
		normalizeJumpDirectionVect = { 0,0 };

		theta = -(1.0f / 4.0f) * (float)M_PI;

		t = 0.2f;
		addT = 1.0f / (120.0f * 0.80f);
		isPress = false;
		isRelease = false;

		circleGH = Novice::LoadTexture("./Resources/images/circle.png");
		circleGHSize = 32.0f;
		circleRadius = 5.0f;
	};

	void rotate(const Vector2& pos, float direction, const bool& Reload);

	Vector2 getNormalizeJumpVect();

	void ButtonFlagReset(bool isJump, float CPosY, int radius);

	void isReleaseFlag();

	void isPressFlag();
};