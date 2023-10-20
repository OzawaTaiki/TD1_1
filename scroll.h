#pragma once

#include <Novice.h>
#include <Vector2.h>

class SCROLL {

	int scrollXAxis;
	int scrollYAxis;

	int scrollXRand;
	int scrollYRand;

	Vector2 scroll;

public:
	SCROLL() {

		scrollXAxis = 700;
		scrollYAxis = 164;
		scrollXRand = 0;;
		scrollYRand = 0;;

		scroll = { 0,0 };

	};

	void update(const Vector2 &pos, bool isShake);

	Vector2 getScroll();

	void debugPrint();

};
