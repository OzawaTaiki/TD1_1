#include "checkPoint.h"
#define _USE_MATH_DEFINES
#include <math.h>

void checkPoint::isDrawFlag(bool isCheck)
{
	if (isCheck)
	{
		isDraw = true;
	}
}

void checkPoint::draw()
{
	if (isDraw)
		update();

	Novice::DrawSprite(int(pos.x), int(pos.y), GH, 200, 50, 0, WHITE);
}

void checkPoint::update()
{
	t += addT;

	if (t >= 1)
	{
		t = 1;
		countTimer--;
	}
	if (countTimer <= 0)
	{
		countTimer = time;
		addT *= -1;
	}
	if (t <= 0 && isDraw)
	{
		isDraw = false;
		t = 0;
	}

	float easedT = -(cosf(float(M_PI) * t) - 1.0f) / 2.0f;
	pos.x = (1.0f - easedT) * kMinPos.x + easedT * kMaxPos.x;

}
