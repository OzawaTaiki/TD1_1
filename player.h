#pragma once

#include <Novice.h>
#include <Vector2.h>

class PLAYER {

public:

	Vector2 pos;
	Vector2 size;
	Vector2 acceleration;
	Vector2 velocity;
	bool isJump;
	bool isAlive;
	bool isGoal;
	float jumpVel;
	int lives;

	bool isStun;
	bool isShake;
	bool isBlasted;
	bool isHitStop;

	int stunTimer;
	int blastTimer;
	int shakeTimer;
	int respawnTimer;

	int blastCountDwon;
	int blastDistance;
	float hitStopTimer;

	Vector2 MoveDir;

	float PressT;
	float addT;
	float maxVelocity;
	float minVelocity;
	float hitStopVelocity;

	float dir = 1;
	int GH;
	int boundCount;

	PLAYER()
	{
		pos = { 300.0f,3000.0f };
		size = { 16,16 };
		acceleration = { 0.00f,0.5f };
		velocity = { 0,0 };
		jumpVel = 0;
		lives = 3;

		isJump = false;
		isAlive = true;
		isGoal = false;


		MoveDir = { 1,0 };

		PressT = 0;
		addT = 0.02f;
		maxVelocity = 30.0f;
		minVelocity = 1.0f;
		hitStopTimer = 5;
		hitStopVelocity = 1.0f;

		boundCount = 0;
		isStun = false;
		isShake = false;
		isBlasted = false;
		isHitStop = false;

		stunTimer = 120;
		blastTimer = 120;
		shakeTimer = 15;
		respawnTimer = 120;

		blastCountDwon = 30;
		blastDistance = 0;

		GH = Novice::LoadTexture("./Resources/images/player.png");
	};

	void draw(const Vector2& scroll);

	Vector2 getPos();

	Vector2 getDir();

	Vector2 getSize();

	float getPressT();

	void Move();


	void antiMove();

	void Respawn(bool& isHit, Vector2& enemyPos);

	void gaugeControl();

	void jump(const Vector2& kJumpVect);

	void dirUpdate();

	void hitAction(int hitBlock, int maptchipSize, bool isHitPoint[],bool& isDraw);

	void debugPrint();


};