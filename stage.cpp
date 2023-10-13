#include "stage.h"

int STAGE::getmapChipsize()
{
	return mapchipsize;
}

void STAGE::loadStage(int stageNum)
{
	stageNum = 0;

	for (int i = 0; i < kStageSizeY; i++)
	{
		for (int j = 0; j < kStageSizeX; j++)
		{
			field[i][j] = stage[i][j];
		}
	}
}

void STAGE::draw(const Vector2& scroll)
{
	//Novice::DrawSprite(int(mapchipsize), int(mapchipsize), GH, 32.0f, 32.0f, 0, BLACK);

	for (int i = 0; i < kStageSizeY; i++)
	{
		for (int j = 0; j < kStageSizeX; j++)
		{
			if (field[i][j] < 10 && field[i][j] != 3)//空気
			{
				//Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[2], 1.0f, 1.0f, 0, color[field[i][j]]);
			}
			else if (field[i][j] == 3)
			{
				Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[1], 31.0f, 31.0f, 0, color[field[i][j]]-0x55);
			}
			else if (field[i][j] < 20)//ブロック
			{
				if (field[i][j] == 12)
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[2], 1.0f, 1.0f, 0, color[field[i][j]]);
				else
					Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[1], 31.0f, 31.0f, 0, color[field[i][j] - 10]);
			}
			else if (field[i][j] < 30)//アイテム
			{
				//Novice::DrawSprite(int(mapchipsize * j - scroll.x), int(mapchipsize * i - scroll.y), GH[1], 31.0f, 31.0f, 0, color[field[i][j]]);
			}
		}
	}
}

int STAGE::collisionCheck(const Vector2& pos, const Vector2& size)
{
	unsigned int returnHitArr = 0;		//当たったブロック番号格納
	int multiplyNum = 100000000;		//計算用

	Vector2 vertex[5] =
	{
		{0,0},
		{0.0f,-size.y },
		{-size.x ,0.0f},
		{size.x ,0.0f},
		{0.0f,size.y},
	};

	for (int i = 0; i < 5; i++)
	{
		int x = int((pos.x + vertex[i].x) / mapchipsize);
		int y = int((pos.y + vertex[i].y) / mapchipsize);

		returnHitArr += field[y][x] * multiplyNum;
		multiplyNum /= 100;

		//アイテム撮ったとき消す
		if (field[y][x] == 20 || field[y][x] == 21) {
			field[y][x] = 0;
		}
	}

	return returnHitArr;

}

