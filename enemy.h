#pragma once

#include <Novice.h>
#include <Vector2Util.h>

class ENEMY {
public:
	Vector2 pos;
	Vector2 size;

	float speed;
	int slowTimer;

	float moveDirX;
	float moveDirY;

	int warningCountDown;
	int warningTimer;
	int animationTimer;
	int animationCounter;

	bool isMove;
	bool isSlow;
	bool isHit;
	bool isPopEffect;
	bool isWarning;
	bool animSwitcher;
	bool SCGO;

	Vector2 respawnPos;
	bool isSetRespawnPos;

	Vector2 startPos[7];

	int enemyGH[4] = { 0 };


	int color = 0xf03c3cff;
	int stuntimer;


	ENEMY()
	{
		pos = { -500.0f,3000.0f };
		size = { 128,128 };

		speed = 5.0f;
		slowTimer = 150;

		moveDirX = 0.0f;
		moveDirY = 0.0f;

		warningCountDown = 60;
		warningTimer = 70;
		animationTimer = 0;
		animationCounter = 0;

		isMove = false;
		isSlow = true;
		isHit = false;
		isPopEffect = false;
		isWarning = false;
		animSwitcher = false;

		respawnPos = pos;
		isSetRespawnPos = false;

		isWarning = true;
		isPopEffect = false;
		animSwitcher = false;
		SCGO = true;

		startPos[0] = { -500.0f,3000.0f };
		startPos[1] = { -500.0f,3000.0f };
		startPos[2] = { -500.0f,3000.0f };
		startPos[3] = { -500.0f,3000.0f };
		startPos[4] = { -500.0f,3000.0f };
		startPos[5] = { -500.0f,3000.0f };
		startPos[6] = { -500.0f,3000.0f };


		enemyGH[0] = Novice::LoadTexture("./Resources/images/Warning.png");
		enemyGH[1] = Novice::LoadTexture("./Resources/images/enemyLeft.png");
		enemyGH[2] = Novice::LoadTexture("./Resources/images/enemyRight.png");
		enemyGH[3] = Novice::LoadTexture("./Resources/images/stunIcon.png");

		stuntimer = 0;
	};

	void SetStartPos(int stageNum);

	void draw(const Vector2& scroll, bool& playerIsAlive, bool isJump, bool isStun);

	void OVERDraw();

	void TitleDraw();

	void OVERUp(bool& isAlive, int& BoundCount);

	void TitleUp();

	Vector2 getPos();

	Vector2 getSize();

	void Move(const Vector2& playerPos, bool isStun, bool isHitStop);

	void timeSlow(bool& isJump, bool& playerIsAlive);

	void CollisionToPlayer(const Vector2& playerPos, Vector2& playerSize);

	void setRespawnPos(bool isSet, const Vector2& PLYRPos, float PLYRDirection);

	void Warning(const Vector2& scroll, bool& playerIsAlive);

	void enemyToPlayerDistance(const Vector2 &playerPos, const Vector2& scroll, bool isStun);


};