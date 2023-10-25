#include "scroll.h"

void SCROLL::update(const Vector2& pos, bool isShake)
{
	scrollXRand = rand() % 5 - 2;
	scrollYRand = rand() % 5 - 2;


	if (!isShake) {
		scroll.x = float(pos.x - scrollXAxis);
		scroll.y = float(pos.y - scrollYAxis);

		scroll.x = scroll.x < 0 ? 0 : scroll.x;
		scroll.y = scroll.y < 0 ? 0 : scroll.y;

		scroll.x = scroll.x > (6400 - 1280) ? (6400 - 1280) : scroll.x;
		scroll.y = scroll.y > (3200 - 720) ? (3200 - 720) : scroll.y;
	}
	else {

		scroll.x = float(pos.x - scrollXAxis + scrollXRand);
		scroll.y = float(pos.y - scrollYAxis + scrollYRand);

		scroll.x = scroll.x < 0 ? 0 : scroll.x;
		scroll.y = scroll.y < 0 ? 0 : scroll.y;

		scroll.x = scroll.x > (6400 - 1280) ? (6400 - 1280) : scroll.x;
		scroll.y = scroll.y > (3200 - 720) ? (3200 - 720) : scroll.y;

		scroll.x += float(scrollXRand);
		scroll.y += float(scrollYRand);

	}


}

Vector2 SCROLL::getScroll()
{
	return scroll;
}
