#pragma once

#include <Novice.h>
#include <Vector2.h>

class PLAYER {

public:

	Vector2 pos;
	Vector2 size;
	Vector2 acceleration;
	Vector2 velocity;
	float jumpVel;

	float drawDir;

	bool isJump;
	bool isAlive;
	bool isGoal;
	bool isHitToge;

	int GH;
	int lives;
	const int maxLives = 3;
	int crossGH;

	Vector2 livesDrawPos;
	Vector2 livesDrawSize;
	float livesGHMargin;

	bool isStun;
	bool isShake;
	bool isBlasted;
	bool isHitStop;
	bool isSetBlastPos;

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

	int boundCount;

	Vector2 respawnPos;
	bool isSetRespawnPos;

	Vector2 startPos[7];

	PLAYER()
	{
		pos = { 300.0f,3000.0f };
		size = { 16.0f,16.0f };
		acceleration = { 0.00f,0.5f };
		velocity = { 0,0 };

		jumpVel = 0;
		drawDir = 1.0f;

		GH = Novice::LoadTexture("./Resources/images/player.png");
		lives = 3;
		crossGH = Novice::LoadTexture("./Resources/images/redCross.png");

		livesDrawPos = { 1114,20 };
		livesDrawSize = { 32,32 };
		livesGHMargin = 10;

		isJump = false;
		isAlive = true;
		isGoal = false;
		isHitStop = false;
		isHitToge = false;

		MoveDir = { 1,0 };

		PressT = 0.5f;
		addT = 0.02f;
		maxVelocity = 30.0f;
		minVelocity = 1.0f;
		hitStopTimer = 5;
		hitStopVelocity = 1.0f;

		boundCount = 0;
		isStun = false;
		isShake = false;
		isBlasted = false;
		isSetBlastPos = false;


		stunTimer = 120;
		blastTimer = 120;
		shakeTimer = 15;
		respawnTimer = 120;

		blastCountDwon = 30;
		blastDistance = 0;

		respawnPos = pos;

		isSetRespawnPos = false;

		startPos[0] = { 300,3000 };
		startPos[1] = { 300,3000 };
		startPos[2] = { 300,3000 };
		startPos[3] = { 300,3000 };
		startPos[4] = { 300,3000 };
		startPos[5] = { 300,3000 };
		startPos[6] = { 300,3000 };

	};

	void draw(const Vector2& scroll);

	void SetStartPos(int stageNum);

	void scoreDraw();
	void OverDraw();
	void OverUpdate(bool& isHit);
	void score();

	Vector2 getPos();

	Vector2 getDir();

	Vector2 getSize();

	float getPressT();

	void Move();

	void antiMove();

	void Respawn(bool& isHit, Vector2& enemyPos, const Vector2& enemyRespawnPos);

	void gaugeControl();

	void jump(const Vector2& kJumpVect);

	void dirUpdate();

	void hitAction(unsigned int  hitBlock, int maptchipSize, bool isHitPoint[], bool& isDraw);

	void debugPrint();


};