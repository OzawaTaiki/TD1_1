#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <Vector2.h>
#include"vector2Util.h"


struct TitlePlayer {
	Vector2 CPos = { 0 };
	Vector2 vertex[4] = { 0 };
	Vector2 vel = { 0 };
	Vector2 acc = { 0.0 };
	int radius = 0;
	unsigned int color=0;
	float dir = 1;
	bool isJump = false;
	bool isRef = false;
	bool canHit = true;
	bool isReload = false;
	int selectBigGH = Novice::LoadTexture("./Resources/images/select1.png");
	int JumpTimer = 10;			//まっすぐ飛んでいく時間
	void Init(Vector2 playerCenterPos, int playerRadius, unsigned int playerColor) {
		CPos = playerCenterPos;
		radius = playerRadius;
		color = playerColor;
	}

	void jump(const Vector2& kJumpVect,bool isSceneChange) {
		if (!isSceneChange) {
			if (!isJump) {
				if (!isReload) {
					vel = { kJumpVect.x * 14 ,kJumpVect.y * 14 };

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
			} else {
				radius += 3;

			}

			if (isRef) {
				vel.x *= 1.0f;
				vel.y *= -1.0f;
				isRef = false;
			}

		}

		if (CPos.y >= 1400 &&
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
			CPos.y >= 900 ||
			radius <= 0) {
			CPos = { 640.0f ,899.0f };
			radius = 100;
			JumpTimer = 10;
			isRef = false;
			isReload = true;
		}
		if (isReload) {
			if (CPos.y<=720) {
				CPos.y = 720;
				canHit = true;
				isReload = false;
			} else {
				CPos.y -= 3;

			}
		}
	}

	void draw() {
		Novice::DrawEllipse(static_cast<int>(CPos.x), static_cast<int>(CPos.y), radius, radius, 0.0f, color, kFillModeSolid);
		/*
		Novice::DrawQuad(static_cast<int>(vertex[0].x), static_cast<int>(vertex[0].y),
			static_cast<int>(vertex[1].x), static_cast<int>(vertex[1].y),
			static_cast<int>(vertex[2].x), static_cast<int>(vertex[2].y),
			static_cast<int>(vertex[3].x), static_cast<int>(vertex[3].y),
			0, 0, 256, 256, selectBigGH, 0xFFFFFFFF);
			*/

	}

};