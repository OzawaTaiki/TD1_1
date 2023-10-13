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