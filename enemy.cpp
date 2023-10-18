#include "enemy.h"

void ENEMY::draw(const Vector2& scroll){
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

void ENEMY::timeSlow(bool isJump, bool playerIsAlive)
{

	if (playerIsAlive) {
		if (slowTimer <= 0) {
			isSlow = false;
		} else if (isJump) {
			isSlow = true;
		}

		if (!isJump && isSlow) {
			speed = 0.5f;
			slowTimer--;
		} else {
			speed = 5.0f;
			slowTimer = 120;
		}

	} else {
		speed = 0.0f;
		isSlow = true;
		slowTimer = 150;
	}
}
void ENEMY::CollisionToPlayer(const Vector2& playerPos, Vector2& playerSize) {
	float distance = 0.0f;
	distance = sqrtf((playerPos.x - pos.x) * (playerPos.x - pos.x) + (playerPos.y - pos.y) * (playerPos.y - pos.y));
	if (distance <= size.x + playerSize.x) {
		isHit = true;
		isPopEffect = true;
	} else {
		isHit = false;
	}
	Novice::ScreenPrintf(1000, 40, "isHit = %d", isHit);

}

void ENEMY::Warning(const Vector2& scroll, bool& playerIsAlive) {
	if (!playerIsAlive) {
		isWarning = true;
	}

	if (isWarning) {
		warningCountDown--;
	}

	if (warningCountDown <= 0 && isWarning) {
		warningTimer--;

		if (warningCountDown % 6 == 0) {
		Novice::DrawSprite(int(40 - scroll.x), int(2900 - scroll.y), enemyGH[0], 1.0f, 1.0f, 0.0f, 0xffffffff);
		}

		if (warningTimer <= 0) {
			isWarning = false;
			warningCountDown = 170;
			warningTimer = 70;
		}
	}
	Novice::ScreenPrintf(500, 40, "isWarning = %d", isWarning);
	Novice::ScreenPrintf(500, 60, "warningCountDown = %d", warningCountDown);
	Novice::ScreenPrintf(500, 80, "warningTimer = %d", warningTimer);
}


