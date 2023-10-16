#include "enemy.h"

void ENEMY::draw(const Vector2& scroll)
{
	Novice::ScreenPrintf(0, 600, "%.1f,%.1f", pos.x, pos.y);

	Novice::DrawEllipse(int(pos.x - scroll.x), int(pos.y - scroll.y), int(size.x), int(size.y), 0, color, kFillModeSolid);
}

Vector2 ENEMY::getPos()
{
	return pos;
}

Vector2 ENEMY::getSize()
{
	return size;
}

void ENEMY::Move(const Vector2& playerPos, bool isStun, bool isHitStop)
{
	//敵の移動角度の計算
	float moveDirX = cosf(atan2f(pos.y - playerPos.y, pos.x - playerPos.x));
	float moveDirY = sinf(atan2f(pos.y - playerPos.y, pos.x - playerPos.x));

	/*float mCos = getDot({ 1,0 }, getNormalizeVect(getVectSub(pos, playerPos)));
	float mSin = getCross({ 1,0 }, getNormalizeVect(getVectSub(pos, playerPos)));

	pos.x += mCos * speed;
	pos.y -= mSin * speed;*/

	//敵の移動
	if (!isStun && !isHitStop) {
		pos.x -= float(moveDirX) * speed;
		pos.y -= float(moveDirY) * speed;

		color = 0x00ff00ff;
	}
	else if (isStun) {
		color = 0xf03c3cff;
	}

}

void ENEMY::timeSlow(bool isJump)
{

	if (slowTimer <= 0) {
		isSlow = false;
	}
	else if (isJump) {
		isSlow = true;
	}

	if (!isJump && isSlow) {
		speed = 0.5f;
		slowTimer--;
	}
	else {
		speed = 5.0f;
		slowTimer = 120;
	}


	Novice::ScreenPrintf(600, 0, "slowTimer = %d", slowTimer);
}

void ENEMY::CollisionToPlayer(const Vector2& playerPos, Vector2& playerSize) {
	float distance = 0.0f;

	distance = sqrtf((playerPos.x - pos.x) * (playerPos.x - pos.x) + (playerPos.y - pos.y) * (playerPos.y - pos.y));

	if(distance <= size.x + playerSize.x) {
		isHit = true;
	}
	else {
		isHit = false;
	}

	Novice::ScreenPrintf(1000, 40, "isHit = %d", isHit);
}



