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

	bool isStun;
	bool isShake;
	bool isBlasted;

	int stunTimer;
	int blastTimer;
	int shakeTimer;
	int blastCountDwon;
	int blastDistance;

	Vector2 MoveDir;

	float PressT;
	float addT;
	float maxVelocity;
	float minVelocity;

	float dir = 1;

	int boundCount;

	PLAYER()
	{
		pos = { 300.0f,1500.0f };
		size = { 16,16 };
		acceleration = { 0.00f,0.5f };
		velocity = { 0,0 };
		isJump = false;
		isAlive = true;
		isGoal = false;


		MoveDir = { 1,0 };

		PressT = 0;
		addT = 0.02f;
		maxVelocity = 30.0f;
		minVelocity = 1.0f;

		boundCount = 0;
		isStun = false;
		isShake = false;
		isBlasted = false;


		stunTimer = 120;
		blastTimer = 120;
		shakeTimer = 15;
		blastCountDwon = 30;
		blastDistance = 0;

	};

	void draw(const Vector2& scroll);

	Vector2 getPos();

	Vector2 getDir();

	Vector2 getSize();

	float getPressT();

	void Move();

	void antiMove();

	void Respawn();

	void gaugeControl();

	void jump(const Vector2& kJumpVect);

	void dirUpdate();

	void hitAction(int hitBlock, int maptchipSize);

	void debugPrint();


};
