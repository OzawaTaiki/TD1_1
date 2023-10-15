#pragma once

#include <Novice.h>
#include <Vector2Util.h>

class ENEMY {

	Vector2 pos;
	Vector2 size;

	float speed;
	int slowTimer;

	bool isMove;
	bool isSlow;
	int color = 0xf03c3cff;


public:

	ENEMY()
	{
		pos = { -200.0f,3000.0f };
		size = { 128,128 };

		speed = 5.0f;
		slowTimer = 120;

		isMove = false;
		isSlow = true;

	};

	void draw(const Vector2 &scroll);

	Vector2 getPos();

	Vector2 getSize();

	void Move(const Vector2& playerPos,bool isStun);

	void timeSlow(bool isJump);

};