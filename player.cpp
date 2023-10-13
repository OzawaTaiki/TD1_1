#include "player.h"


void PLAYER::draw(const Vector2& scroll)
{
	Novice::DrawEllipse(int(pos.x - scroll.x), int(pos.y - scroll.y), int(size.x), int(size.y), 0, WHITE, kFillModeSolid);
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
	float absVeloX = velocity.x < 0 ? -velocity.x : velocity.x;
	float absVeloY = velocity.y < 0 ? -velocity.y : velocity.y;

	if (isJump)
	{
		velocity.x -= acceleration.x * MoveDir.x;
		//if (absVeloY > 0.5f)
		velocity.y += acceleration.y;

	}
	else
	{
		velocity.y += acceleration.y;
	}

	//velocity.x = absVeloX < 0.075f ? 0 : velocity.x;

	if ((absVeloX < 0.05f && absVeloY < 0.5f) && isJump)
	{
		isJump = false;
		velocity = { 0,0 };
	}

	pos.x += velocity.x;
	pos.y += velocity.y;

}

void PLAYER::antiMove()
{
	pos.x -= velocity.x;
	pos.y -= velocity.y;
}

void PLAYER::Respawn()
{
	if (!isAlive)
	{
		isAlive = true;
		pos = { 3000.0f,1500.0f };
		velocity = { 0,0 };
		MoveDir = { 0,0 };
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
		float localVelo = (1.0f - PressT) * minVelocity + PressT * maxVelocity;

		velocity = { kJumpVect.x * localVelo,kJumpVect.y * localVelo };

		PressT = 0;
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

void PLAYER::hitAction(int hitBlock, int maptchipSize)
{
	Novice::ScreenPrintf(0, 100, "%d", hitBlock);

	int localHit[5];

	int divisor = 100000000;
	for (int i = 0; i < 5; i++)
	{
		localHit[i] = hitBlock / divisor;
		hitBlock = hitBlock % divisor;
		divisor /= 100;

		if (localHit[i] == 12)//hari no toki death
		{
			isAlive = false;
		}
		else if (localHit[i] == 0)
			dir = -1;
		else if (localHit[i] == 1)
			dir = 1;
		if (localHit[i] == 3)
			isGoal = true;
	}

	if ((dir < 0 && localHit[3] == 3) || (dir > 0 && localHit[2] == 3))
	{
		isGoal = true;
	}

	for (int i = 0; i < 5; i++)
	{
		if (localHit[i] >= 10 && localHit[i] < 20)
		{
			if (i == 0)
			{
				if (MoveDir.y != 0 && (localHit[1] == 1 || localHit[4] == 1 || localHit[1] == 0 || localHit[4] == 0))
				{
					int a = int((pos.y / maptchipSize) - MoveDir.y);
					pos.y = a * maptchipSize + size.y;

					int HitCopy = localHit[0];
					if (MoveDir.y < 0)
					{
						localHit[0] = 0;
						localHit[1] = HitCopy;
						localHit[2] = 0;
						localHit[3] = 0;
						localHit[4] = 0;
					}
					else if (MoveDir.y > 0)
					{

						localHit[0] = 0;
						localHit[1] = 0;
						localHit[2] = 0;
						localHit[3] = 0;
						localHit[4] = HitCopy;
					}
				}
				else if (MoveDir.x != 0 && (localHit[2] == 1 || localHit[3] == 1 || localHit[2] == 0 || localHit[3] == 0))
				{
					int a = int((pos.x / maptchipSize) - MoveDir.x);
					pos.x = a * maptchipSize + size.x;

					int HitCopy = localHit[0];

					if (MoveDir.x < 0)
					{
						localHit[0] = 0;
						localHit[1] = 0;
						localHit[2] = HitCopy;
						localHit[3] = 0;
						localHit[4] = 0;
					}
					else if (MoveDir.x > 0)
					{

						localHit[0] = 0;
						localHit[1] = 0;
						localHit[2] = 0;
						localHit[3] = HitCopy;
						localHit[4] = 0;
					}
				}
			}

			if (MoveDir.x != 0 && (i == 2 || i == 3))
			{
				int a = int((pos.x / maptchipSize));
				pos.x = a * maptchipSize + size.x;
				if (isJump)
				{
					switch (localHit[i])
					{
					case 10:
						velocity.x *= -0.3f;
						break;
					case 11:
						velocity.x *= -1.1f;
						velocity.y *= 1.1f;
						break;
					default:
						break;
					}
				}
				break;
			}
			if (MoveDir.y != 0 && (i == 1 || i == 4))
			{
				int a = int((pos.y / maptchipSize));
				pos.y = a * maptchipSize + size.y;
				if (isJump)
				{
					switch (localHit[i])
					{
					case 10:
						velocity.y *= -(0.9f - (0.25f * boundCount));

						if (i == 4)
						{
							boundCount++;

							if (boundCount > 2)
							{
								velocity = { 0,0 };
								boundCount = 0;
								isJump = false;
							}
						}
						break;
					case 11:
						velocity.x *= 1.1f;
						velocity.y *= -1.1f;
						break;
					}
				}
				else
				{
					antiMove();
					velocity.y = 0;
				}

				break;
			}
		}
		else if (localHit[i] >= 20 && localHit[i] < 30)
		{
			if (localHit[i] == 20) { // 加速アイテム
				velocity.x *= 1.3f;
				velocity.y *= 1.3f;
			}

			if (localHit[i] == 21) { // 敵スタンアイテム
				isStun = true;
			}
		}
	}

	if (isStun && stunTimer >= 0)
	{
		stunTimer--;
	}
	else
	{
		isStun = false;
		stunTimer = 120;
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
}
