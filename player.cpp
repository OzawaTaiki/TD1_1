#include "player.h"



void PLAYER::draw(const Vector2& scroll)
{
	if (MoveDir.x != 0)
		drawDir = MoveDir.x;
	else
		drawDir = dir;

	if (isAlive) {
		Novice::DrawSprite(int(pos.x - (size.x * drawDir) - scroll.x), int(pos.y - size.y - scroll.y), GH, drawDir, 1, 0, WHITE);
		//Novice::DrawEllipse(int(pos.x - scroll.x), int(pos.y - scroll.y), int(size.x), int(size.y), 0, WHITE, kFillModeSolid);
	}

	for (int i = 0; i < maxLives; i++)
	{
		Novice::DrawSprite(int(livesDrawPos.x + i * (livesDrawSize.x + livesGHMargin)), int(livesDrawPos.y), GH, 1, 1, 0, WHITE);
	}
	for (int i = 0; i < (maxLives - lives); i++)
	{
		Novice::DrawSprite(int(livesDrawPos.x + i * (livesDrawSize.x + livesGHMargin)), int(livesDrawPos.y), crossGH, 1, 1, 0, WHITE);
	}
}

Vector2 PLAYER::getPos()
{
	return pos;
}

Vector2 PLAYER::getDir()
{
	return MoveDir;
}

Vector2 PLAYER::getSize()
{
	return size;
}

float PLAYER::getPressT()
{
	return PressT;
}

void PLAYER::Move()
{
	//float absVeloX = velocity.x < 0 ? -velocity.x : velocity.x;
	//float absVeloY = velocity.y < 0 ? -velocity.y : velocity.y;

	//if (isJump)
	//{
	//	velocity.x -= acceleration.x * MoveDir.x;
	//	//if (absVeloY > 0.5f)
	//	velocity.y += acceleration.y;

	//}
	//else
	//{
	velocity.y += acceleration.y;
	//}

	//velocity.x = absVeloX < 0.075f ? 0 : velocity.x;

	/*if ((absVeloX < 0.05f && absVeloY < 0.5f) && isJump)
	{
		isJump = false;
		velocity = { 0,0 };
	}*/

	pos.x += velocity.x * hitStopVelocity;
	pos.y += velocity.y * hitStopVelocity;

}

void PLAYER::antiMove()
{
	pos.x -= velocity.x;
	pos.y -= velocity.y;
}

void PLAYER::Respawn(bool& isHit, Vector2& enemyPos, const Vector2& enemyRespawnPos)
{
	if (isHit && lives >= 0) {
		isAlive = false;
		isBlasted = false;
		blastTimer = 120;
		blastCountDwon = 30;
		blastDistance = 0;


		if (!isAlive)
		{
			respawnTimer--;
		}

		if (respawnTimer <= 0 && lives > 0) {
			isAlive = true;
			isHit = false;
			lives -= 1;
			pos = respawnPos;
			enemyPos = enemyRespawnPos;
			velocity = { 0,0 };
			MoveDir = { 0,0 };

			respawnTimer = 120;
		}
	}
}

void PLAYER::gaugeControl()
{
	if (!isJump)
	{
		PressT += addT;

		if (PressT > 0.99 || PressT < 0.01f)
		{
			addT *= -1;
		}
	}
}

void PLAYER::jump(const Vector2& kJumpVect)
{
	if (!isJump)
	{
		jumpVel = (1.0f - PressT) * minVelocity + PressT * maxVelocity;

		velocity = { kJumpVect.x * jumpVel ,kJumpVect.y * jumpVel };

		PressT = 0.35f;
		addT *= addT < 0 ? -1 : 1;

		isJump = true;
	}
}

void PLAYER::dirUpdate()
{
	MoveDir = { 0,0 };

	if (velocity.x != 0)
		MoveDir.x = velocity.x < 0 ? -1.0f : 1.0f;
	if (velocity.y != 0)
		MoveDir.y = velocity.y < 0 ? -1.0f : 1.0f;
}

void PLAYER::hitAction(unsigned int  hitBlock, int maptchipSize, bool isHitPoint[], bool& isDraw)
{
	Novice::ScreenPrintf(0, 100, "%d", hitBlock);

	isSetRespawnPos = false;

	int localHit[5];

	int divisor = 100000000;
	for (int i = 0; i < 5; i++)
	{
		localHit[i] = hitBlock / divisor;
		hitBlock = hitBlock % divisor;
		divisor /= 100;

		if (localHit[i] == 19 || localHit[i] == 20)//hari no toki death
		{
			isAlive = false;
		} else if (localHit[i] == 0)
			dir = -1;
		else if (localHit[i] == 1)
			dir = 1;
		if (localHit[i] == 2)
			isGoal = true;
	}
	int HitCopy = localHit[0];

	if (isJump) {
		for (int i = 1; i < 5; i++)
		{
			if (localHit[i] >= 3 && localHit[i] <= 18)
			{
				isHitPoint[i - 1] = true;
				isDraw = true;
			}
		}
	}

	if ((dir < 0 && localHit[3] == 2) || (dir > 0 && localHit[2] == 2))
	{
		isGoal = true;
	}


	if (!isHitStop)
	{
		for (int i = 0; i < 5; i++)
		{
			if (localHit[i] >= 3 && localHit[i] < 19)
			{
				if (i == 0)
				{//埋まってるとき
					if (MoveDir.y != 0 && (localHit[1] == 1 || localHit[4] == 1 || localHit[1] == 0 || localHit[4] == 0))
					{
						int a = int((pos.y / maptchipSize) - MoveDir.y);
						pos.y = a * maptchipSize + size.y;

						if (MoveDir.y < 0)
						{
							localHit[0] = 0;
							localHit[1] = HitCopy;
							localHit[2] = 0;
							localHit[3] = 0;
							localHit[4] = 0;
						} else if (MoveDir.y > 0)
						{

							localHit[0] = 0;
							localHit[1] = 0;
							localHit[2] = 0;
							localHit[3] = 0;
							localHit[4] = HitCopy;
						}
					} else if (MoveDir.x != 0 && (localHit[2] == 1 || localHit[3] == 1 || localHit[2] == 0 || localHit[3] == 0))
					{
						int a = int((pos.x / maptchipSize) - MoveDir.x);
						pos.x = a * maptchipSize + size.x;

						if (MoveDir.x < 0)
						{
							localHit[0] = 0;
							localHit[1] = 0;
							localHit[2] = HitCopy;
							localHit[3] = 0;
							localHit[4] = 0;
						} else if (MoveDir.x > 0)
						{
							localHit[0] = 0;
							localHit[1] = 0;
							localHit[2] = 0;
							localHit[3] = HitCopy;
							localHit[4] = 0;
						}
					} else if (localHit[2] >= 3 && localHit[2] < 19 &&
						localHit[3] >= 4 && localHit[3] < 19)
					{
						if (localHit[1] >= 3 && localHit[1] < 19 ||
							localHit[4] >= 3 && localHit[4] < 19)
						{
							if (MoveDir.x < 0)
							{
								pos.x += 30.0f;
								localHit[0] = 0;
								localHit[1] = 0;
								localHit[2] = HitCopy;
								localHit[3] = 0;
								localHit[4] = 0;
							} else if (MoveDir.x > 0)
							{
								pos.x -= 30.0f;
								localHit[0] = 0;
								localHit[1] = 0;
								localHit[2] = 0;
								localHit[3] = HitCopy;
								localHit[4] = 0;
							}
						}
					} else if (localHit[1] >= 3 && localHit[1] < 19 &&
						localHit[4] >= 3 && localHit[4] < 19)
					{
						if (localHit[2] >= 3 && localHit[2] < 19 ||
							localHit[3] >= 3 && localHit[3] < 19)
						{
							if (MoveDir.y < 0)
							{
								pos.y += 30.0f;

								localHit[0] = 0;
								localHit[1] = HitCopy;
								localHit[2] = 0;
								localHit[3] = 0;
								localHit[4] = 0;
							} else if (MoveDir.y > 0)
							{
								pos.y -= 30.0f;

								localHit[0] = 0;
								localHit[1] = 0;
								localHit[2] = 0;
								localHit[3] = 0;
								localHit[4] = HitCopy;
							}
						}

					}
				}


				//埋まってないときの処理
				if (MoveDir.x != 0 && (i == 2 || i == 3))
				{//左右の点があたっているとき
					int a = int((pos.x / maptchipSize));
					pos.x = a * maptchipSize + size.x;

					if (isJump)
					{
						if (abs(int(velocity.x)) >= 15 || abs(int(velocity.y)) >= 15) {
							isShake = true;
							isHitStop = true;
							hitStopVelocity = 0.0f;
						} else {
							isShake = false;
							isHitStop = false;
							hitStopVelocity = 1.0f;
						}

						if (localHit[i] >= 3 && localHit[i] < 18)
						{
							velocity.x *= -0.3f;
						} else if (localHit[i] == 18)
						{
							if (abs(int(velocity.x)) <= 30.0f && abs(int(velocity.y)) <= 30.0f) {
								velocity.x *= -1.1f;
								velocity.y *= 1.1f;
							} else {
								velocity.x *= -1.0f;
							}
						}
					} else {
						isShake = false;
						isHitStop = false;
						hitStopVelocity = 1.0f;
					}
					break;
				}

				if (MoveDir.y != 0 && (i == 1 || i == 4))
				{//上下の点があたっているとき
					int a = int((pos.y / maptchipSize));
					pos.y = a * maptchipSize + size.y;

					if (isJump)
					{
						if (abs(int(velocity.x)) >= 15 || abs(int(velocity.y)) >= 15) {
							isShake = true;
							isHitStop = true;
							hitStopVelocity = 0.0f;
						} else {
							isShake = false;
							isHitStop = false;
							hitStopVelocity = 1.0f;
						}


						if (localHit[i] >= 3 && localHit[i] < 18)
						{
							velocity.y *= -(0.9f - (0.25f * boundCount));
						} else if (localHit[i] == 18)
						{
							if (abs(int(velocity.x)) <= 30.0f && abs(int(velocity.y)) <= 30.0f) {
								velocity.x *= 1.1f;
								velocity.y *= -1.1f;
							} else {
								velocity.y *= -1.0f;
							}
						}
					} else
					{
						antiMove();
						velocity.y = 0;
						isShake = false;
						isHitStop = false;
						hitStopVelocity = 1.0f;
					}

					break;
				}

			} else if (localHit[i] >= 21 && localHit[i] < 30)
			{
				if (localHit[i] == 21) { // 加速アイテム
					velocity.x *= 1.3f;
					velocity.y *= 1.3f;
				}

				if (localHit[i] == 22) { // 敵スタンアイテム
					isStun = true;
				}

				if (localHit[i] == 23 || localHit[i] == 24) { //大砲
					velocity.x = 0.0f;
					velocity.y = 0.0f;
					boundCount = 3;
					isBlasted = true;
				}
				if (localHit[i] == 25)
				{
					isSetRespawnPos = true;
					respawnPos = pos;
				}
			}
		}
	}

	if (localHit[4] >= 4 && localHit[4] < 19 && isJump)
	{
		boundCount++;

		if (boundCount > 2)
		{
			velocity = { 0,0 };
			boundCount = 0;
			isJump = false;
		}
	}

	if (isHitStop)
	{
		hitStopTimer--;
	}
	if (hitStopTimer <= 0)
	{
		isHitStop = false;
		hitStopVelocity = 1.0f;
		hitStopTimer = 5;
	}

	//画面揺れの時間制限処理
	if (isShake) {
		shakeTimer--;
	}

	if (shakeTimer <= 0) {
		isShake = false;
		shakeTimer = 15;
	}

	// 敵スタンアイテムの時間制限処理
	if (isStun && stunTimer >= 0)
	{
		stunTimer--;
	} else
	{
		isStun = false;
		stunTimer = 120;
	}

	// 大砲の時間制限と移動処理
	if (isBlasted && blastTimer >= 0 && blastDistance <= 1000)
	{
		blastCountDwon--;
		isJump = true;

		if (blastCountDwon <= 0) {
			if (dir >= 1) {
				pos.x += 25.0f;
			} else if (dir < 1) {
				pos.x -= 25.0f;
			}
			blastDistance += 25;
			blastTimer--;
			velocity.x = 5.0f;
		}

	} else
	{
		isBlasted = false;
		blastTimer = 120;
		blastCountDwon = 30;
		blastDistance = 0;
	}


}

void PLAYER::debugPrint()
{
	Novice::ScreenPrintf(0, 0, "%f,%f", pos.x, pos.y);
	Novice::ScreenPrintf(0, 40, "%f", PressT);

	Novice::ScreenPrintf(0, 200, "%s", isJump ? "true" : "false");

	Novice::ScreenPrintf(0, 220, "%.0f,%.0f", MoveDir.x, MoveDir.y);
	Novice::ScreenPrintf(0, 240, "%4.1f,%4.1f", velocity.x, velocity.y);
	Novice::ScreenPrintf(0, 260, "%d", boundCount);
	Novice::ScreenPrintf(0, 280, "%4.1f,%4.1f", respawnPos.x, respawnPos.y);
}