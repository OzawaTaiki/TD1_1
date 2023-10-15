#pragma once
#include <Novice.h>
#include <Vector2Util.h>
#include <Vector2.h>
#define _USE_MATH_DEFINES
#include<math.h>

//2x2の行列を表す
struct Matrix2x2 {
	float m[2][2];
};

//ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 vector2;
	vector2.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	vector2.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];

	return vector2;
}

Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 rotateMatrix;
	rotateMatrix.m[0][0] = cosf(theta);
	rotateMatrix.m[0][1] = sinf(theta);
	rotateMatrix.m[1][0] = -sinf(theta);
	rotateMatrix.m[1][1] = cosf(theta);

	return rotateMatrix;
}

struct EffectPaper {
	float moveSpeed = static_cast<float>(rand() % 110 + 30) * 0.1f;
	Vector2 CPos = { static_cast<float>(rand() % 1280),static_cast<float>(rand() % 300-500) };//static_cast<float>(rand() % 22-200)
	Vector2 vertex[4] = { 0 };
	float size= static_cast<float>(rand() % 31 + 10); 
	float rotateTheta = 0;
	float theta = (1.0f / static_cast<int>(rand() % 101 + 30) * float(M_PI));
	Matrix2x2 rotateMatrix = MakeRotateMatrix(theta);
	Vector2 leftTop = { (-size / 2),(-size / 2) };
	Vector2 rightTop = { (size / 2), (-size / 2) };
	Vector2 leftBottom = { (-size / 2),(size / 2) };
	Vector2 rightBottom = { (size / 2),(size / 2) };

	Vector2 rotateLeftTop;
	Vector2 rotateRightTop;
	Vector2 rotateLeftBottom;
	Vector2 rotateRightBottom;

	int colorRandNum = rand() % 5;
	unsigned int color =  0 ;

	int whiteGH = Novice::LoadTexture("./NoviceResources/white1x1.png");
	
	void rotate() {
		rotateTheta += theta;

		rotateMatrix = MakeRotateMatrix(rotateTheta);

		rotateLeftTop = Multiply(leftTop, rotateMatrix);
		rotateRightTop = Multiply(rightTop, rotateMatrix);
		rotateLeftBottom = Multiply(leftBottom, rotateMatrix);
		rotateRightBottom = Multiply(rightBottom, rotateMatrix);

		rotateLeftTop.x += CPos.x;
		rotateLeftTop.y += CPos.y;
		rotateRightTop.x += CPos.x;
		rotateRightTop.y += CPos.y;
		rotateLeftBottom.x += CPos.x;
		rotateLeftBottom.y += CPos.y;
		rotateRightBottom.x += CPos.x;
		rotateRightBottom.y += CPos.y;

	};

	void Move() {

		CPos.y += moveSpeed;

		if (CPos.y >= 1380) {
			CPos.x = static_cast<float>(rand() % 1280);
			CPos.y = -100;
			size = static_cast<float>(rand() % 51 + 10);
			moveSpeed = static_cast<float>(rand() % 11 + 1);

		};
	};

	void Color() {


	}

	void DrawUpDate() {
		Novice::DrawQuad(static_cast<int>(rotateLeftTop.x), static_cast<int>(rotateLeftTop.y),
			static_cast<int>(rotateRightTop.x), static_cast<int>(rotateRightTop.y),
			static_cast<int>(rotateLeftBottom.x), static_cast<int>(rotateLeftBottom.y),
			static_cast<int>(rotateRightBottom.x), static_cast<int>(rotateRightBottom.y),
			0, 0, 1, 1, whiteGH, 0xFFFF00FF);
	}
};