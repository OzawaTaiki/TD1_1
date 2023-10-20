#include "enemy.h"

void ENEMY::draw(const Vector2& scroll, bool& playerIsAlive) {

	if (playerIsAlive) {
		animationTimer++;

		if (animationTimer % 8 == 0) {
			animationCounter += 256;
		}
	}
	else {
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
	}
	else if (moveDirX < 0) {
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

void ENEMY::OVERDraw() {
	animationTimer++;

	if (animationTimer % 8 == 0) {
		animationCounter += 256;
	}


	if (animationCounter >= 1024) {
		animationCounter = 0;
	}

	if (moveDirX > 0) {
		Novice::DrawSpriteRect(
			int(pos.x - size.x), int(pos.y - size.y),
			animationCounter, 0,
			256, 256,
			enemyGH[1],
			((float)256 / (float)1024), 1,
			0,
			0xffffffff);
	}
	else if (moveDirX < 0) {
		Novice::DrawSpriteRect(
			int(pos.x - size.x), int(pos.y - size.y),
			animationCounter, 0,
			256, 256,
			enemyGH[2],
			((float)256 / (float)1024), 1,
			0,
			0xffffffff);
	}
}


void ENEMY::OVERUp(bool& isAlive, int& BoundCount) {
	if (SCGO) {
		pos = { -500,360 };
		isAlive = true;
		BoundCount = 0;
		isHit = false;
		isPopEffect = false;

		SCGO = false;
	}
	pos.x += speed;

	if (pos.x >= 1680) {
		SCGO = true;
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
	}
	else if (isStun) {
		color = 0xf03c3cff;
	}
}

void ENEMY::timeSlow(bool& isJump, bool& playerIsAlive)
{

	if (playerIsAlive) {
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
			slowTimer = 150;
		}

	}
	else {
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
	}
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
		}
		else
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
}

void ENEMY::enemyToPlayerDistance(const Vector2& playerPos, const Vector2& scroll)
{
	Vector2 scsPlayerPos = getVectSub(scroll, playerPos);
	Vector2 scsEnemyPos = getVectSub(scroll, pos);

	Vector2 EtoPDis = getVectSub(scsPlayerPos, scsEnemyPos);

	//敵が画面外にいるとき描画フラグを立てる
	if ((scsEnemyPos.x + size.x <= 0 || scsEnemyPos.x - size.x >= 1280) ||
		(scsEnemyPos.y + size.y <= 0 || scsEnemyPos.y - size.y >= 720))
	{
		Novice::ScreenPrintf(500, 100, "true");

		//倍率計算
		float maxSize = 64;
		float minSize = 4;

		Vector2 localSize = { 32,32 };

		Vector2 normalizeEtoP = getNormalizeVect(EtoPDis);
		Vector2 max = getVectMultiply(normalizeEtoP, 1000.0f);
		float localT = getDot(EtoPDis, normalizeEtoP) / getLength(max);

		localT = localT > 1 ? 1 : (localT < 0 ? 0 : localT);

		Vector2 drawSize;
		drawSize.x = (1.0f - localT) * maxSize + localT * minSize;
		drawSize.y = (1.0f - localT) * maxSize + localT * minSize;

		Vector2 vertex[4] =
		{
			{-drawSize.x / 2,-drawSize.y / 2 },
			{drawSize.x / 2 ,-drawSize.y / 2},
			{-drawSize.x / 2 ,drawSize.y / 2},
			{drawSize.x / 2,drawSize.y / 2},
		};

		//交差判定，交点計算

		Vector2 windowPos[4] = {
			{0,0},
			{1280,0},
			{0,720},
			{1280,720}
		};

		int crossDir = 0;
		Vector2 drawPos = { 0,0 };

		if (drawPos.x == 0 && drawPos.y == 0)
		{//left
			drawPos = getCrossPos(scsPlayerPos, scsEnemyPos, windowPos[0], windowPos[2]);
			crossDir = 1;
		}

		if (drawPos.x == 0 && drawPos.y == 0)
		{//up
			drawPos = getCrossPos(scsPlayerPos, scsEnemyPos, windowPos[0], windowPos[1]);
			crossDir = 2;
		}

		if (drawPos.x == 0 && drawPos.y == 0)
		{//right
			drawPos = getCrossPos(scsPlayerPos, scsEnemyPos, windowPos[1], windowPos[3]);
			crossDir = 3;
		}

		if (drawPos.x == 0 && drawPos.y == 0)
		{//bottom
			drawPos = getCrossPos(scsPlayerPos, scsEnemyPos, windowPos[2], windowPos[3]);
			crossDir = 4;
		}

		switch (crossDir)
		{
		case 1:
			Novice::DrawEllipse(int(drawPos.x + drawSize.x), int(drawPos.y), (int)drawSize.x, (int)drawSize.y, 0, RED, kFillModeSolid);
			break;
		case 2:
			Novice::DrawEllipse(int(drawPos.x), int(drawPos.y + drawSize.y), (int)drawSize.x, (int)drawSize.y, 0, RED, kFillModeSolid);
			break;
		case 3:
			Novice::DrawEllipse(int(drawPos.x - drawSize.x), int(drawPos.y), (int)drawSize.x, (int)drawSize.y, 0, RED, kFillModeSolid);
			break;
		case 4:
			Novice::DrawEllipse(int(drawPos.x), int(drawPos.y - drawSize.y), (int)drawSize.x, (int)drawSize.y, 0, RED, kFillModeSolid);
			break;
		default:
			break;
		}
		//Novice::DrawEllipse(int(drawPos.x), int(drawPos.y), (int)drawSize.x, (int)drawSize.y, 0, RED, kFillModeSolid);
		//Novice::DrawQuad(int(pos.x+vertex[0].x),int(pos.y+vertex[0].y))

		Novice::ScreenPrintf(500, 120, "%.1f,%.1f", drawSize.x, drawSize.y);
	}
	Novice::ScreenPrintf(500, 160, "scroll = %.1f,%.1f", scroll.x, scroll.y);
}






void ENEMY::debugPrint()
{
	//Novice::ScreenPrintf(500, 80, "warningTimer = %d", warningTimer);
	//Novice::ScreenPrintf(500, 60, "warningCountDown = %d", warningCountDown);
	//Novice::ScreenPrintf(500, 40, "isWarning = %d", isWarning);
	//Novice::ScreenPrintf(0, 700, "%d", slowTimer);
	Novice::ScreenPrintf(500, 140, "enemyPos = %.1f,%.1f", pos.x, pos.y);

}
