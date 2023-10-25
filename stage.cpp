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
	cpNum = 0;

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
				else if (field[i][j] == 3)//真っ黒
					Novice::DrawBox(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), mapchipsize, mapchipsize, 0, 0x000000ff, kFillModeSolid);
				else if (field[i][j] <= 17 || field[i][j] == 24 || field[i][j] == 23)//ブロック 大砲
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
				{
					if (loadStageNum == 5)
						if (i > 70)
							cpNum = 0;
						else
							cpNum = 1;

					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[field[i][j]], 1.0f, 1.0f, 0, nowCheckPointColor[cpNum]);
				}
			}
		}
	}
}

void STAGE::blasterPosSet(Vector2& pos, const Vector2& size)
{
	//大砲
	pos.x = float(mapchipsize * blastX + size.x);
	pos.y = float(mapchipsize * blastY + size.y);

}

void STAGE::blastPosReset()
{
	blastX = -1;
	blastY = -1;
}

int STAGE::collisionCheck(Vector2& pos, const Vector2& size, const Vector2& velocity, float dir)//変更
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

			if ((x < 0 || x >= 200) && (y < 0 || y >= 100))
			{
				x = 199;
				y = 99;
			}

			returnHitArr += field[y][x] * multiplyNum;



			if (field[y][x] >= 3 && field[y][x] < 19)
			{
				isContinue = false;
				pos = prePos;
			}

			//アイテム取ったとき座標を保存
			if (field[y][x] >= 21 && field[y][x] < 26) {

				isGetItem = true;

				getItemNum = field[y][x];
				itemHitPoint = field[y][x] * multiplyNum;
				itemHitSubNum = multiplyNum;

				if (field[y][x] == 23 || field[y][x] == 24)
				{
					if (blastX == -1)
					{
						blastX = x;
						blastY = y;
					}
				}
				if (field[y][x] == 25)
				{
					if (posy == -1)
					{
						nowCheckPointColor[0] = CheckPointColor[1];
						posy = y;
					}
					else if (!(y >= posy - 5 && y <= posy + 5))
					{
						nowCheckPointColor[1] = CheckPointColor[1];
					}

				}
				else if (field[y][x] == 21 || field[y][x] == 22)
				{
					field[y][x] = (int)dir < 0 ? 0 : 1;
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

void STAGE::reset()
{
	blastX = -1;
	blastY = -1;
	nowCheckPointColor[0] = CheckPointColor[0];
	nowCheckPointColor[1] = CheckPointColor[0];
	posy = -1;
}
