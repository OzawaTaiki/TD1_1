#pragma once

#include <Novice.h>
#include <Vector2Util.h>

class ENEMY {
public:
	Vector2 pos;
	Vector2 size;

	float speed;
	int slowTimer;

	int warningCountDown;
	int warningTimer;

	bool isMove;
	bool isSlow;
	bool isHit;
	bool isPopEffect;
	bool isWarning;

	Vector2 respawnPos;

	int enemyGH[2] = { 0 };


	int color = 0xf03c3cff;


	ENEMY()
	{
		pos = { -200.0f,3000.0f };
		size = { 128,128 };

		speed = 5.0f;
		slowTimer = 120;

		warningCountDown = 60;
		warningTimer = 70;

		isMove = false;
		isSlow = true;
		isHit = false;
		isPopEffect = false;

		respawnPos = pos;

		isWarning = true;
		isPopEffect = false;

		enemyGH[0] = Novice::LoadTexture("./Resources/images/Warning.png");
	};

	void draw(const Vector2& scroll);

	Vector2 getPos();

	Vector2 getSize();

	void Move(const Vector2& playerPos, bool isStun, bool isHitStop);

	void timeSlow(bool isJump, bool playerIsAlive);

	void CollisionToPlayer(const Vector2& playerPos, Vector2& playerSize);

	void setRespawnPos(bool isSet, const Vector2& PLYRPos, float PLYRDirection);

	void Warning(const Vector2& scroll, bool& playerIsAlive);

};