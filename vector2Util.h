#pragma once
#include<math.h>
#include<Vector2.h>

float getLength(Vector2 a);

Vector2 getVectAdd(Vector2 a, Vector2 b);

Vector2 getVectSub(Vector2 a, Vector2 b);

Vector2 getVectMultiply(Vector2 a, float num);

Vector2 getVectMultiply(Vector2 a, Vector2 b);

float getDot(Vector2 a, Vector2 b);

float getCross(Vector2 a, Vector2 b);

Vector2 getNormalizeVect(Vector2 a);

Vector2 rotateVect(Vector2 a, float aSin, float aCos);

bool crossCheck(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d);

Vector2 getCrossPos(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2 d);

/*追加したもの*/
void VectorVertex(Vector2 vertex[4], Vector2 CPos, float Wradius, float Hradius);
void VectorVertexS(Vector2 vertex[4], Vector2 CPos, float Wradius, float Hradius);