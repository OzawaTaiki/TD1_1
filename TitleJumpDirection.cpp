#include "TitlejumpDirection.h"

void TjumpDirection::rotate(const Vector2& pos, float direction)
{
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

	//Novice::DrawEllipse(int(RotateJumpDirectionVect.x + pos.x - scroll.x), int(RotateJumpDirectionVect.y + pos.y - scroll.y), 3, 3, 0, RED, kFillModeSolid);

	if (!isRelease) {
		for (int i = 0; i < Num; i++)
		{
			Novice::DrawEllipse(int((normalizeJumpDirectionVect.x * i * margin) + pos.x), int((normalizeJumpDirectionVect.y * i * margin) + pos.y), 20, 20, 0, 0xdd5050ff, kFillModeSolid);
		}
	}
	

	Novice::ScreenPrintf(0, 300, "%.1f,%.1f", normalizeJumpDirectionVect.x, normalizeJumpDirectionVect.y);
	Novice::ScreenPrintf(0, 320, "%.1f,%.1f", pos.x, pos.y);

}

Vector2 TjumpDirection::getNormalizeJumpVect()
{
	return normalizeJumpDirectionVect;
}

void TjumpDirection::ButtonFlagReset(bool isJump, float CPosY, int radius){
	if (!isJump && isRelease||
		CPosY >= 1200 ||
		radius <= 0){
		isRelease = false;
	}
}

void TjumpDirection::isReleaseFlag()
{
	isRelease = true;
}

void TjumpDirection::isPressFlag()
{
	isPress = true;
}


