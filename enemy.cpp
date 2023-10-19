#include "enemy.h"

void ENEMY::draw(const Vector2& scroll, bool& playerIsAlive) {

	if (playerIsAlive) {
		
		animationTimer++;
		if (isSlow) {
			if (animationTimer % 16 == 0) {
				animationCounter += 256;
			}
		} else {
			if (animationTimer % 8 == 0) {
				animationCounter += 256;
			}
		}
	} else {
		animationTimer = 0;
	}

	if (animationCounter >= 1024) {
		animationCounter = 0;
	}

	if (moveDirX > 0) {
		Novice::DrawSpriteRect(
			int(pos.x - scroll.x - size.x), int(pos.y - scroll.y - size.y),
			animationCounter, 0,
			256, 256,
			enemyGH[1],
			((float)256 / (float)1024), 1,
			0,
			0xffffffff);
	} else if (moveDirX < 0) {
		Novice::DrawSpriteRect(
			int(pos.x - scroll.x - size.x), int(pos.y - scroll.y - size.y),
			animationCounter, 0,
			256, 256,
			enemyGH[2],
			((float)256 / (float)1024), 1,
			0,
			0xffffffff);
	}


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
	moveDirX = cosf(atan2f(pos.y - playerPos.y, pos.x - playerPos.x));
	moveDirY = sinf(atan2f(pos.y - playerPos.y, pos.x - playerPos.x));

	//敵の移動
	if (!isStun && !isHitStop) {
		pos.x -= float(moveDirX) * speed;
		pos.y -= float(moveDirY) * speed;

		color = 0x00ff00ff;
	} else if (isStun) {
		color = 0xf03c3cff;
	}
}

void ENEMY::timeSlow(bool& isJump, bool& playerIsAlive)
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
		slowTimer = 120;
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

void ENEMY::setRespawnPos(bool& isSet, const Vector2& PLYRPos, float& PLYRDirection)
{
	if (isSet)
	{
		float respwnDistance = 200.0f;

		if (fabsf(PLYRPos.x - pos.x) <= respwnDistance)
		{//敵と自機のｘ距離が respwnDistance より小さいとき
			//リスポーンposXを respwnDistance 分だけ離す
			//YはPLYRと同じに
			respawnPos.x = respwnDistance * PLYRDirection;
			respawnPos.y = PLYRPos.y;
		} else
		{
			respawnPos = pos;
		}
	}
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
