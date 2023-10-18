#include "jumpDirection.h"

void jumpDirection::rotate(const Vector2& pos, float direction, const Vector2& scroll, const bool& isAlive, float numT)
{//矢印の回転

	//押してないとき    
	if (!isPress)
	{
		RotateJumpDirectionVect = rotateVect(kJumpDirectionVect, sinf(theta), cosf(theta));

		t += addT;
		theta = (1.0f - t) * kMinTheta + t * kMaxTheta;
		if (t >= 1.0f || t <= 0.0f)
			addT *= -1;

		normalizeJumpDirectionVect = getNormalizeVect(RotateJumpDirectionVect);
		normalizeJumpDirectionVect.x *= direction;
	}

	//離してないときは描画する
	if (!isRelease)
	{
		Num = int((1.0f - numT) * kminNum + numT * kMaxNum);

		if (isAlive) {
			for (int i = 0; i < Num; i++)
			{
				Novice::DrawSprite(int((normalizeJumpDirectionVect.x * i * margin) + pos.x - circleRadius - scroll.x), int((normalizeJumpDirectionVect.y * i * margin) + pos.y- circleRadius - scroll.y), circleGH, circleRadius * 2 / circleGHSize, circleRadius * 2 / circleGHSize, 0, 0xff0000ff);
				//Novice::DrawEllipse(int((normalizeJumpDirectionVect.x * i * margin) + pos.x - scroll.x), int((normalizeJumpDirectionVect.y * i * margin) + pos.y - scroll.y), 3, 3, 0, 0xdd5050ff, kFillModeSolid);
			}
		}
		Novice::ScreenPrintf(0, 300, "%.1f,%.1f", normalizeJumpDirectionVect.x, normalizeJumpDirectionVect.y);
	}
}


Vector2 jumpDirection::getNormalizeJumpVect()
{
	return normalizeJumpDirectionVect;
}

void jumpDirection::ButtonFlagReset(bool isJump)
{//プレイヤーがジャンプしてない＆＆離したとき
	if (!isJump && isRelease)
	{//ボタンの入力リセット
		isRelease = false;
		isPress = false;
	}
}

void jumpDirection::isReleaseFlag()
{
	isRelease = true;
}

void jumpDirection::isPressFlag()
{
	isPress = true;
}


