#include "TitlejumpDirection.h"

void TjumpDirection::rotate(const Vector2& pos, float direction, const bool& isReload)
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

	if (!isRelease) {
		if (!isReload) {
			for (int i = 3; i < Num; i++)
			{
				Novice::DrawSprite(int((normalizeJumpDirectionVect.x * i * margin) + pos.x - circleRadius), int((normalizeJumpDirectionVect.y * i * margin) + pos.y - circleRadius), circleGH, circleRadius * 6 / circleGHSize, circleRadius * 6 / circleGHSize, 0, 0xffffffff);
			}
		}
	}

}

Vector2 TjumpDirection::getNormalizeJumpVect()
{
	return normalizeJumpDirectionVect;
}

void TjumpDirection::ButtonFlagReset(bool isJump, float CPosY, int radius) {
	if (!isJump && isRelease ||
		CPosY >= 1200 ||
		radius <= 0) {
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