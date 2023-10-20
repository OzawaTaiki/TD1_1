#pragma once
#include <Novice.h>
#include <vector2Util.h>

class checkPoint
{
public:

	Vector2 pos;
	Vector2 size = { 200,50 };
	bool isDraw;
	int GH;
	float t;
	float addT;
	int time;
	int countTimer;


	const Vector2 kMaxPos = { 1280.0f - size.x,64 };
	const Vector2 kMinPos = { 1280.0f,64 };


	checkPoint() {

		pos = { 1280,64 };
		isDraw = false;
		GH = Novice::LoadTexture("white1x1.png");
		t = 0;
		addT = 0.04f;
		time = 120;
		countTimer = time;

	};

	void isDrawFlag(bool isCheck);

	void draw();

	void update();

};
