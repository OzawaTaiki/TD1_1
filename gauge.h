#pragma once

#include <Novice.h>
#include <Vector2.h>

class GAUGE
{
	Vector2 pos;
	Vector2 size;

	unsigned int color;

public:

	GAUGE() {
		pos = { 16,16 };
		size = { 256,48 };

		color = 0x0040ddff;
	};

	void draw(float t);

};
