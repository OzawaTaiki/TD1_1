﻿#include "stage.h"
#include <stdio.h>

int STAGE::getmapChipsize()
{
	return mapchipsize;
}

void STAGE::loadStage(int stageNum)
{
	loadStageNum = stageNum;

	for (int i = 0; i < kStageSizeY[loadStageNum]; i++)
	{
		for (int j = 0; j < kStageSizeX[loadStageNum]; j++)
		{
			field[i][j] = stage[loadStageNum][i][j];
		}
	}

}

void STAGE::draw(const Vector2& scroll)
{
	//Novice::DrawSprite(int(mapchipsize), int(mapchipsize), GH, 32.0f, 32.0f, 0, BLACK);

	for (int i = 0; i < kStageSizeY[loadStageNum]; i++)
	{
		for (int j = 0; j < kStageSizeX[loadStageNum]; j++)
		{
			if (field[i][j] < 3 && field[i][j] != 3) { //空気
				//Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[2], 1.0f, 1.0f, 0, color[field[i][j]]);
			} else if (field[i][j] == 3) {

				Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[1], 31.0f, 31.0f, 0, color[field[i][j]] - 0x55);

			} else if (field[i][j] < 20) {//ブロック

				//壁
				if (field[i][j] == 4)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[3], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 5)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[4], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 6)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[5], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 7)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[6], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 8)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[7], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 9)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[8], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 10)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[9], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 11)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[10], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 12)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[11], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 13)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[12], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 14)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[13], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 15)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[14], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 16)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[15], 1.0f, 1.0f, 0, 0xffffffff);
				if (field[i][j] == 17)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[16], 1.0f, 1.0f, 0, 0xffffffff);

				if (field[i][j] == 18)//加速する壁
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[1], 31.0f, 31.0f, 0, color[field[i][j] - 10]);

				if (field[i][j] == 19)//トゲ
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[2], 1.0f, 1.0f, 0, color[field[i][j]]);

			} else if (field[i][j] < 30) { //アイテム
				//Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[1], 31.0f, 31.0f, 0, color[field[i][j]]);

				if (field[i][j] == 20)//加速アイテム
					Novice::DrawBox(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), 20, 20, 0.0f, BLUE, kFillModeSolid);

				if (field[i][j] == 21)//スタンアイテム
					Novice::DrawBox(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), 20, 20, 0.0f, RED, kFillModeSolid);

				if (field[i][j] == 22)//大砲
					Novice::DrawBox(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), 20, 20, 0.0f, GREEN, kFillModeSolid);
			}
		}
	}
}

void STAGE::blasterPosSet(Vector2& pos, const Vector2& size)
{
	for (int i = 0; i < kStageSizeY[loadStageNum]; i++)
	{
		for (int j = 0; j < kStageSizeX[loadStageNum]; j++)
		{
			if (field[i][j] == 22)
			{ //大砲
				pos.x = float(mapchipsize * j + size.x);
				pos.y = float(mapchipsize * i + size.y);
			}
		}
	}
}

int STAGE::collisionCheck(Vector2& pos, const Vector2& size, const Vector2& velocity)
{
	unsigned int returnHitArr = 0;		//当たったブロック番号格納

	Vector2 prePos = getVectSub(velocity, pos); //前フレームのpos

	const int num = 3;

	Vector2 addVelo[num];			//カプセル途中判定用
	for (int i = 1; i < num + 1; i++)
	{
		addVelo[i - 1] = getVectMultiply(velocity, (float)i / (float)num);
	}

	Vector2 vertex[5] =
	{
		{0,0},
		{0.0f,-size.y },
		{-size.x ,0.0f},
		{size.x ,0.0f},
		{0.0f,size.y},
	};

	int itemHitPoint = 0;
	int itemHitSubNum = 0;
	for (int i = 0; i < num; i++)
	{
		int multiplyNum = 100000000;		//計算用
		bool isContinue = true;
		bool isGetItem = false;
		returnHitArr = 0;

		prePos = getVectAdd(prePos, addVelo[i]);

		for (int j = 0; j < 5; j++)
		{
			int x = int((prePos.x + vertex[j].x) / mapchipsize);
			int y = int((prePos.y + vertex[j].y) / mapchipsize);

			returnHitArr += field[y][x] * multiplyNum;

			if (field[y][x] >= 10 && field[y][x] < 20)
			{
				isContinue = false;
				pos = prePos;
			}

			//アイテム取ったとき座標を保存
			if (field[y][x] >= 20 && field[y][x] < 30) {
				isGetItem = true;
				itemHitPoint = field[y][x] * multiplyNum;
				itemHitSubNum = multiplyNum;
				if (field[y][x] != 22)
					field[y][x] = 0;

			}
			multiplyNum /= 100;
		}
		if (!isContinue)
		{
			if (isGetItem)
			{
				returnHitArr -= returnHitArr / itemHitSubNum;
				returnHitArr += itemHitPoint;
			}
			break;
		}
	}

	return returnHitArr;

}