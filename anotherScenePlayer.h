#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Vector2.h>
#include"vector2Util.h"


struct TitlePlayer {
	Vector2 CPos = { 0 };
	Vector2 vertex[4] = { 0 };
	Vector2 vel = { 0 };
	Vector2 acc = { 0.0 };
	int radius = 0;
	unsigned int color = 0;
	float dir = 1;
	bool isJump = false;
	bool isRef = false;
	bool canHit = true;
	bool isReload = false;
	int JumpTimer = 10;			//まっすぐ飛んでいく時間

	int GH = Novice::LoadTexture("./Resources/images/player-sheet.png");
	int DrawAria = 0;

	void Init(Vector2 playerCenterPos, int playerRadius, unsigned int playerColor) {
		CPos = playerCenterPos;
		radius = playerRadius;
		color = playerColor;
	}

	void jump(const Vector2& kJumpVect, bool isSceneChange) {
		if (!isSceneChange) {
			if (!isJump) {
				if (!isReload) {
					vel = { kJumpVect.x * 14 ,kJumpVect.y * 14 };

					if (vel.x >= 3.0f) {
						DrawAria = 200;
					}
					else if (vel.x <= -3.0f) {
						DrawAria = 400;
					}
					isJump = true;

				}
			}
		}
	}



	void Move()
	{
		if (isJump)
		{
			//減らしていき
			JumpTimer -= 1;
			//０になったら重力
			if (JumpTimer <= 15) {
				JumpTimer = 0;
				vel.x += acc.x;
				vel.y += acc.y;
				CPos.x += vel.x;
				CPos.y += vel.y;
			}

			if (canHit) {
				radius -= 2;
			}
			else {
				radius += 3;

			}

			if (isRef) {
				vel.x *= 1.0f;
				vel.y *= -1.0f;

				DrawAria = 600;


				isRef = false;
			}

		}

		if (CPos.y >= 850 &&
			isJump) {
			isJump = false;
			vel = { 0,0 };
		}

		if (radius <= 0) {
			radius = 0;
			isJump = false;
			vel = { 0,0 };
		}
	}

	void ReturnPlayer() {
		if (!isJump &&
			CPos.y >= 850 ||
			radius <= 0) {
			CPos = { 640.0f ,849.0f };
			radius = 100;
			JumpTimer = 10;
			isRef = false;
			isReload = true;
			DrawAria = 0;
		}

		if (isReload) {
			if (CPos.y <= 720) {
				CPos.y = 720;
				canHit = true;
				isReload = false;
			}
			else {
				CPos.y -= 3;

			}
		}
	}

	void draw() {
		//Novice::DrawEllipse(static_cast<int>(CPos.x), static_cast<int>(CPos.y), radius, radius, 0.0f, color, kFillModeSolid);
		Novice::DrawSpriteRect(static_cast<int>(CPos.x - radius), static_cast<int>(CPos.y - radius), DrawAria, 0, 200, 200, GH, float(radius / 400.0f), float(radius / 100.0f), 0.0f, 0xFFFFFFFF);
		Novice::ScreenPrintf(1000, 40, "vel.x= %f,vel.y=%f", vel.x, vel.y);
	}

};