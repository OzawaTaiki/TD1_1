#include "gauge.h"

void GAUGE::draw(float t)
{
	float drawWidth = (1.0f - t) + 0 + t * size.x;

	Novice::DrawBox(int(pos.x), int(pos.y), int(drawWidth), int(size.y), 0, color, kFillModeSolid);
}
