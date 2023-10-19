#include "stage.h"
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

void STAGE::draw(const Vector2& pos, const Vector2& scroll)
{
	int drawCenterX = (int)pos.x / mapchipsize;
	int drawCenterY = (int)pos.y / mapchipsize;

	int drawMinX = drawCenterX - drawMapchipX / 2;
	drawMinX = drawMinX < 0 ? 0 : (drawMinX + drawMapchipX > kStageSizeX[loadStageNum] ? kStageSizeX[loadStageNum] - drawMapchipX : drawMinX);
	int drawMinY = drawCenterY - drawMapchipY / 2;
	drawMinY = drawMinY < 0 ? 0 : (drawMinY + drawMapchipY > kStageSizeY[loadStageNum] ? kStageSizeY[loadStageNum] - drawMapchipY : drawMinY);

	for (int i = drawMinY; i < drawMinY + drawMapchipY; i++)
	{
		for (int j = drawMinX; j < drawMinX + drawMapchipX; j++)
		{
			if (field[i][j] >= 2)
			{
				if (field[i][j] == 2)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, WHITE);
				else if (field[i][j] <= 17 || field[i][j] == 24 || field[i][j] == 25)//ブロック 大砲
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, stageColor);

				else if (field[i][j] == 18)//加速
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, WHITE);

				else if (field[i][j] <= 20)//トゲ
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, stageColor);

				else if (field[i][j] <= 22)//アイテム
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, WHITE);

				else if (field[i][j] <= 24)//大砲
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, WHITE);

				else if (field[i][j] == 25)//チェックポイント
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, nowCheckPointColor);
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
			if (field[i][j] == 23 || field[i][j] == 24)
			{ //大砲
				pos.x = float(mapchipsize * j + size.x);
				pos.y = float(mapchipsize * i + size.y);

			}
		}
	}
}

int STAGE::collisionCheck(Vector2& pos, const Vector2& size, const Vector2& velocity)//変更
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

	unsigned int itemHitPoint = 0;
	unsigned int itemHitSubNum = 0;
	bool isGetItem = false;
	unsigned int getItemNum = 0;

	for (int i = 0; i < num; i++)
	{
		int multiplyNum = 100000000;		//計算用
		bool isContinue = true;
		returnHitArr = 0;

		prePos = getVectAdd(prePos, addVelo[i]);

		for (int j = 0; j < 5; j++)
		{
			int x = int((prePos.x + vertex[j].x) / mapchipsize);
			int y = int((prePos.y + vertex[j].y) / mapchipsize);

			returnHitArr += field[y][x] * multiplyNum;

			if (field[y][x] >= 3 && field[y][x] < 19)
			{
				isContinue = false;
				pos = prePos;
			}

			//アイテム取ったとき座標を保存
			if (field[y][x] >= 21 && field[y][x] < 25) {

				isGetItem = true;

				getItemNum = field[y][x];
				itemHitPoint = field[y][x] * multiplyNum;
				itemHitSubNum = multiplyNum;

				if (field[y][x] == 25)
				{
					nowCheckPointColor = CheckPointColor[1];
				}


			}
			multiplyNum /= 100;
		}

		if (isGetItem)
		{
			unsigned int a = returnHitArr / itemHitSubNum;
			unsigned int b = a / 100;
			b *= 100;
			unsigned int c = a - b;

			returnHitArr -= c * itemHitSubNum;
			returnHitArr += itemHitPoint;
		}

		if (!isContinue)
			break;
	}

	return returnHitArr;

}