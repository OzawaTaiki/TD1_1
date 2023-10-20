#include "vector2Util.h"


float getLength(Vector2 a)
{
	return sqrtf((a.x * a.x) + (a.y * a.y));
}

Vector2 getVectAdd(Vector2 a, Vector2 b)
{
	return { a.x + b.x,a.y + b.y };
}

Vector2 getVectSub(Vector2 a, Vector2 b)
{
	return { b.x - a.x, b.y - a.y };
}

Vector2 getVectMultiply(Vector2 a, float num)
{

	return { a.x * num,a.y * num };

}

Vector2 getVectMultiply(Vector2 a, Vector2 b)
{

	return { a.x * b.x,a.y * b.y };

}

float getDot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

float getCross(Vector2 a, Vector2 b)
{
	return  a.x * b.y - a.y * b.x;
}

Vector2 getNormalizeVect(Vector2 a)
{
	float length = sqrtf(a.x * a.x + a.y * a.y);
	if (length != 0)
		return { a.x / length,a.y / length };

	return { 0,0 };
}

Vector2 rotateVect(Vector2 a, float aSin, float aCos)
{
	return { a.x * aCos - a.y * aSin,a.x * aSin + a.y * aCos };
}

bool crossCheck(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d)
{
	float e = getCross(getVectSub(a, b), getVectSub(a, c));
	float f = getCross(getVectSub(a, b), getVectSub(a, d));
	float g = getCross(getVectSub(c, d), getVectSub(c, a));
	float h = getCross(getVectSub(c, d), getVectSub(c, b));

	if (e * f > 0 || g * h > 0)
		return false;

	return true;
}

Vector2 getCrossPos(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2 d)
{
	if (!crossCheck(a, b, c, d))
		return{ 0,0 };

	Vector2 ab = getVectSub(a, b);
	Vector2 cd = getVectSub(c, d);
	float g = getCross(ab, cd);
	if (g == 0)
		return{ 0,0 };


	float e, f;

	e = getCross(getVectSub(a, c), getVectSub(c, d)) / g;
	f = getCross(getVectSub(a, b), getVectSub(c, a)) / g;

	if (e < 0 || e>1 || f < 0 || f>1)
		return{ 0,0 };


	Vector2 result;

	result.x = a.x + e * ab.x;
	result.y = a.y + e * ab.y;

	return result;
}

void VectorVertex(Vector2 vertex[4], Vector2 CPos, float Wradius, float Hradius) {
	vertex[0].x = CPos.x - Wradius;
	vertex[0].y = CPos.y - Hradius;
	vertex[1].x = CPos.x + Wradius;
	vertex[1].y = CPos.y - Hradius;
	vertex[2].x = CPos.x - Wradius;
	vertex[2].y = CPos.y + Hradius;
	vertex[3].x = CPos.x + Wradius;
	vertex[3].y = CPos.y + Hradius;
};
void VectorVertexS(Vector2 vertex[4], Vector2 CPos, float Wradius, float Hradius) {
	vertex[0].x = CPos.x - Wradius / 2;
	vertex[0].y = CPos.y - Hradius / 2;
	vertex[1].x = CPos.x + Wradius / 2;
	vertex[1].y = CPos.y - Hradius / 2;
	vertex[2].x = CPos.x - Wradius / 2;
	vertex[2].y = CPos.y + Hradius / 2;
	vertex[3].x = CPos.x + Wradius / 2;
	vertex[3].y = CPos.y + Hradius / 2;
};