#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Vector2.h>
#include <time.h>

#include "stage.h"
#include "player.h"
#include "scroll.h"
#include "gauge.h"

#include "enemy.h"

#include "TiTleBox.h"
#include "anotherScenePlayer.h"
#include "selectBox.h"
#include "sceneChange.h"
#include "score.h"

#include "jumpDirection.h"
#include "TitleJumpDirection.h"
#include "GameClearEffect.h"

const char kWindowTitle[] = "1105_オザワ_キョウ_ミカミ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	unsigned int currentTime = static_cast<int>(time(nullptr));
	srand(currentTime);

	/*シーンの変数*/
	/*--------------------------------------------------------------------*/
	enum SCENE {
		TITLE,
		SELECT,
		GAME,
		GAMEOVER,
		GAMECLEAR
	};
	SCENE scene = GAME;
	int SceneNo = 2;
	bool isChangeScene = false;

	/*--------------------------------------------------------------------*/

	STAGE STAGE;
	PLAYER PLYR;
	SCROLL SCROLL;
	GAUGE GAUGE;
	ENEMY ENEMY;

	jumpDirection JD;


	TjumpDirection TitleJD;
	TjumpDirection SelectJD;

	/*--------------------------------------------------------------------*/
	const int TITLEBOX_MAX = 2;
	Box TitleRogo;
	Box TitleBox[2];//[0]=セレクト画面へ[1]=ゲーム終了
	TitlePlayer TPlayer;
	//タイトルロゴ
	TitleRogo.Init(
		{ 640,150 },
		800,
		150,
		0x1B162CFF
	);
	//タイトル画面の選択肢（[0]セレクト[1]ゲーム終了）
	for (int i = 0; i < TITLEBOX_MAX; i++) {
		TitleBox[i].Init(
			{ (340.0f + 600.0f * i),450 },
			300,
			300,
			0x1B162CFF
		);
	}

	TPlayer.Init(
		{ 640,720 },
		100,
		0xFFFFFFFF
	);


	const int SELECTBOX_MAX = 10;
	Box SelectRogo;
	selectBox SelectBox[10];
	SelectBox[0].color = 0xFF0000FF;
	//[9]=操作説明[8]＝１面[7]＝２面[6]＝３面[5]＝next
	//[4]=戻る[3]＝４面[2]＝５面[1]＝６面[0]＝タイトルへ

	TitlePlayer SPlayer;
	//セレクトの文字
	SelectRogo.Init(
		{ 640,150 },
		800,
		150,
		0x1B162CFF
	);


	SPlayer.Init(//セレクト画面のプレイヤー
		{ 640,720 },
		100,
		0xFFFFFFFF
	);


	SceneChange changeUp;//シーンチェンジの上
	SceneChange changeLow;//シーンチェンジの下
	changeUp.Init(
		{ 640,-360 },
		360,
		-360
	);
	changeLow.Init(
		{ 640,1080 },
		360,
		1080
	);


	Score score;//スコア表示

	score.numberGH[0] = Novice::LoadTexture("./Resources/images/0.png");
	score.numberGH[1] = Novice::LoadTexture("./Resources/images/1.png");
	score.numberGH[2] = Novice::LoadTexture("./Resources/images/2.png");
	score.numberGH[3] = Novice::LoadTexture("./Resources/images/3.png");
	score.numberGH[4] = Novice::LoadTexture("./Resources/images/4.png");
	score.numberGH[5] = Novice::LoadTexture("./Resources/images/5.png");
	score.numberGH[6] = Novice::LoadTexture("./Resources/images/6.png");
	score.numberGH[7] = Novice::LoadTexture("./Resources/images/7.png");
	score.numberGH[8] = Novice::LoadTexture("./Resources/images/8.png");
	score.numberGH[9] = Novice::LoadTexture("./Resources/images/9.png");

	score.rankGH[0] = Novice::LoadTexture("./Resources/images/RankS.png");
	score.rankGH[1] = Novice::LoadTexture("./Resources/images/RankA.png");
	score.rankGH[2] = Novice::LoadTexture("./Resources/images/RankB.png");
	score.rankGH[3] = Novice::LoadTexture("./Resources/images/RankC.png");

	const int PAPER_MAX = 64;
	EffectPaper effectpaper[PAPER_MAX];


	bool isReset = false;//リセットフラグ

	/*--------------------------------------------------------------------*/

	//ステージのロード
	STAGE.loadStage(1);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (scene) {
		case TITLE:
#pragma region"タイトルの更新処理"
			/*半径ゼロまたは自機が画面の下の外にいったら元の位置に戻る*/
			TPlayer.ReturnPlayer();
			TitleJD.ButtonFlagReset(TPlayer.isJump, TPlayer.CPos.y, TPlayer.radius);//ボタン系のフラグを元に戻す
			//押すとその方向へ飛んでいく
			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				TitleJD.isReleaseFlag();
				TPlayer.jump(TitleJD.getNormalizeJumpVect());
			}

			TPlayer.Move();

			/*当たり判定用の四辺を求める*/
				//Playerの四辺
			VectorVertex(TPlayer.vertex, TPlayer.CPos, static_cast<float>(TPlayer.radius), static_cast<float>(TPlayer.radius));
			//選択肢のBoxの四辺
			for (int i = 0; i < TITLEBOX_MAX; i++) {
				VectorVertexS(TitleBox[i].vertex, TitleBox[i].CPos, static_cast<float>(TitleBox[i].Wsize), static_cast<float>(TitleBox[i].Hsize));
			}
			//当たり判定のフラグ
			for (int i = 0; i < TITLEBOX_MAX; i++) {
				if (TPlayer.radius <= 40.0f &&
					TPlayer.radius >= 20.0f) {
					if (!TitleBox[i].isHit &&
						TPlayer.isJump) {
						if (TPlayer.vertex[1].x >= TitleBox[i].vertex[0].x &&
							TPlayer.vertex[0].x <= TitleBox[i].vertex[1].x &&
							TPlayer.vertex[1].y <= TitleBox[i].vertex[3].y &&
							TPlayer.vertex[3].y >= TitleBox[i].vertex[1].y) {
							TitleBox[i].isHit = true;
							//当たったエフェクト表示（仮置き）
							TPlayer.canHit = false;//一つの選択肢に当たったあと、別の選択肢に当たらないようにするフラグ
							TPlayer.isRef = true;//当たった時跳ね返るフラグ
						}
					}
				}
			}
			Novice::ScreenPrintf(0, 100, "%d,%d", TitleBox[0].isHit, TitleBox[1].isHit);
			if (TitleBox[0].isHit) {
				SceneNo = 1;//セレクト画面へ移動
				isChangeScene = true;
			}

			if (TitleBox[1].isHit) {
				SceneNo = 5;//ゲームを終了させる
				isChangeScene = true;
			}
#pragma endregion
			break;
		case SELECT:
#pragma region"セレクトの更新処理"
			//SPlayer.acc.y = 0.1f;
			//リセット（タイトルと同じ）
			SPlayer.ReturnPlayer();
			SelectJD.ButtonFlagReset(SPlayer.isJump, SPlayer.CPos.y, SPlayer.radius);
			//選択画面の自機ジャンプ
			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				SelectJD.isReleaseFlag();
				SPlayer.jump(SelectJD.getNormalizeJumpVect());
			}
			//選択画面での自機の移動処理
			SPlayer.Move();

			//当たり判定用の四辺を求める
			VectorVertex(SPlayer.vertex, SPlayer.CPos, static_cast<float>(SPlayer.radius), static_cast<float>(SPlayer.radius));

			for (int i = 0; i < SELECTBOX_MAX; i++) {
				VectorVertexS(SelectBox[i].vertex, SelectBox[i].CPos, static_cast<float>(SelectBox[i].Wsize), static_cast<float>(SelectBox[i].Hsize));
			}

			//選択肢の角度を求める
			for (int i = 0; i < BOX_MAX; i++) {
				SelectBox[i].theta = SelectBox[0].theta + (-1.0f / 14.0f * float(M_PI)) * i;
			}
			//選択肢の座標を求める
			for (int i = 0; i < BOX_MAX; i++) {
				if (!SelectBox[i].isHit) {
					SelectBox[i].rotateLength = rotateVect(SelectBox[i].length, sinf(SelectBox[i].theta), cosf(SelectBox[i].theta));
					SelectBox[i].CPos = getVectAdd(SelectBox[i].rotateLength, SelectBox[i].originPos);
				}
			}
			//選択肢と自機の当たり判定
			for (int i = 0; i < SELECTBOX_MAX; i++) {
				if (SPlayer.radius <= 40.0f) {
					if (!SelectBox[i].isHit &&
						SPlayer.isJump &&
						SPlayer.canHit) {
						if (SPlayer.vertex[1].x >= SelectBox[i].vertex[0].x &&
							SPlayer.vertex[0].x <= SelectBox[i].vertex[1].x &&
							SPlayer.vertex[1].y <= SelectBox[i].vertex[3].y &&
							SPlayer.vertex[3].y >= SelectBox[i].vertex[1].y) {
							SelectBox[i].isHit = true;
							SPlayer.canHit = false;
							SPlayer.isRef = true;
							//当たったエフェクト表示（仮おき）
						}
					}
				}
			}
			//それぞれ当たった時の処理
			if (SelectBox[8].isHit) {
				SceneNo = 2;//ゲーム画面へ移動
				isChangeScene = true;
			}
			if (SelectBox[5].isHit) {
				SelectBox[0].isR = true;//回転
			}
			if (SelectBox[4].isHit) {
				SelectBox[0].isR = true;//回転
			}
			if (SelectBox[0].isHit) {
				SceneNo = 0;//タイトルに戻る
				isChangeScene = true;
			}
			/*選択肢に自機を当てると選択肢が落下する処理*/
			for (int i = 0; i < SELECTBOX_MAX; i++) {
				if (SelectBox[i].isHit) {
					SelectBox[i].velY += SelectBox[i].accY;
					SelectBox[i].CPos.y += SelectBox[i].velY;
					//isChangeScene = true;
					//SPlayer.radius += static_cast<int>(0.0f);
				}
			}
			//各々の当たった時の処理ここまで
			//[4][5]に当たった場合イージング
			if (SelectBox[0].isR == true) {
				SelectBox[0].t += 0.028f * SelectBox[0].dir;
			}
			//最大で停止
			if (SelectBox[0].t >= 1.00f) {
				SelectBox[0].t = 1.0f;
				SelectBox[0].isR = false;
				SelectBox[0].dir *= -1;
				SelectBox[5].isHit = false;
			}
			//最小で停止
			if (SelectBox[0].t <= 0.00f) {
				SelectBox[0].t = 0.0f;
				SelectBox[0].isR = false;
				SelectBox[0].dir *= -1;
				SelectBox[4].isHit = false;
			}
			//当たったあと、タイマーを減らし、０になったら選択肢再生
			for (int i = 4; i < 6; i++) {
				if (SelectBox[i].isHit) {
					SelectBox[i].timer -= 1;
					if (SelectBox[i].timer == 0) {
						SelectBox[i].isDraw = true;
						SPlayer.canHit = true;
						SelectBox[i].isHit = false;
						SelectBox[i].timer = 35;//このタイマーはずらすと復活する瞬間が回転中に見えてしまうので注意
					}
				}
			}
			//イージング
			SelectBox[0].theta = (1.0f - SelectBox[0].t) * SelectBox[0].minTheta + SelectBox[0].t * SelectBox[0].maxTheta;
			break;
#pragma endregion
		case GAME:

			//プレイヤーのリスポーン
			PLYR.Respawn();

			if (PLYR.isGoal)
			{
				return 0;
			}

			if (keys[DIK_R])
				PLYR.isAlive = false;

			//プレイヤーの操作	
			if (keys[DIK_SPACE])
			{
				JD.isPressFlag();
				PLYR.gaugeControl();
			}

			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE])
			{
				JD.isReleaseFlag();
				PLYR.jump(JD.getNormalizeJumpVect());
			}
			//プレイヤーの座標更新
			PLYR.dirUpdate();
			if (!PLYR.isBlasted) {
				PLYR.Move();	
			} else if (PLYR.isBlasted && PLYR.blastCountDwon >= 0) {
				STAGE.blasterPosSet(PLYR.pos, PLYR.size);
			}

			//プレイヤーの衝突判定
			PLYR.hitAction(STAGE.collisionCheck(PLYR.pos, PLYR.size), STAGE.getmapChipsize());

			ENEMY.Move(PLYR.pos, PLYR.isStun);
			ENEMY.timeSlow(PLYR.isJump);

			SCROLL.update(PLYR.getPos(), PLYR.isShake);
			JD.ButtonFlagReset(PLYR.isJump);

			//リザルトの時間測定する
			score.TimeCount();
			//仮置き、ゲームオーバー
			if (keys[DIK_3] && !preKeys[DIK_3]) {
				SceneNo = 3;
				isChangeScene = true;
			}
			//仮置きゲームクリア
			if (keys[DIK_4] && !preKeys[DIK_4]) {
				SceneNo = 4;
				isChangeScene = true;
			}
			break;
#pragma endregion
		case GAMEOVER:
			//セレクト画面へ戻る
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				SceneNo = 1;
				isChangeScene = true;
			}
			break;
		case GAMECLEAR:

			for (int i = 0; i < PAPER_MAX;i++) {
				effectpaper[i].rotate();
				effectpaper[i].Move();
				VectorVertexS(effectpaper[i].vertex, effectpaper[i].CPos, effectpaper[i].size, effectpaper[i].size);
			}

			//時間に応じてスコアを表示
			score.result();
			SCROLL.update(PLYR.getPos(), PLYR.isShake);	//セレクト画面へ戻る
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				SceneNo = 1;
				isChangeScene = true;
			}
			break;
		}
		//シーン切り替えしたときの処理
#pragma region"シーン切り替え"
//フラグが立つとイージング開始
		if (isChangeScene) {
			changeUp.t += 0.02f * changeUp.dir;
			changeLow.t += 0.02f * changeLow.dir;
			changeLow.easeT = 1.0f - powf(1.0f - changeLow.t, 3.0f);
			changeUp.easeT = 1.0f - powf(1.0f - changeUp.t, 3.0f);
			changeLow.CPos.y = (1.0f - changeLow.easeT) * changeLow.minPos + changeLow.easeT * changeLow.maxPos;
			changeUp.CPos.y = (1.0f - changeUp.easeT) * changeUp.minPos + changeUp.easeT * changeUp.maxPos;
			//最大で停止
			if (changeUp.t >= 1.00f) {
				changeUp.t = 1.0f;
				changeUp.timer -= 1;
				if (changeUp.timer == 0) {
					changeUp.dir *= -1;
					changeUp.timer = 10;//閉じてからタイマーの時間分停止
				}
			}
			if (changeLow.t >= 1.00f) {
				changeLow.t = 1.0f;
				changeLow.timer -= 1;
				if (changeLow.timer == 0) {
					changeLow.dir *= -1;
					changeLow.timer = 10;//閉じてからタイマーの時間分停止
				}
				//閉じている間に行われる処理ここから
				if (SceneNo == 0) {
					scene = TITLE;
				}
				if (SceneNo == 1) {
					scene = SELECT;
				}
				if (SceneNo == 2) {
					scene = GAME;
				}
				if (SceneNo == 3) {
					scene = GAMEOVER;
				}
				if (SceneNo == 4) {
					scene = GAMECLEAR;
				}
				if (SceneNo == 5) {
					return 0;
				}
				isReset = true;//ここでリセット
				//ここまで
			}
			//最小で停止
			if (changeUp.t <= 0.00f) {
				changeUp.t = 0.0f;
				changeUp.dir *= -1;
			}
			if (changeLow.t <= 0.00f) {
				changeLow.t = 0.0f;
				changeLow.dir *= -1;
				isChangeScene = false;
			}
		}
#pragma endregion
		//リセットの中身
#pragma region"リセット"
		if (isReset) {
			for (int i = 0; i < 2; i++) {
				TitleBox[i].isHit = false;
				JD.ButtonFlagReset(PLYR.isJump);	TitleBox[i].vel = { 0,0 };
			}
			TPlayer.isJump = false;
			TPlayer.isRef = false;
			TPlayer.canHit = true;
			TPlayer.Init(
				{ 640,720 },
				100,
				0xFFFFFFFF
			);
			SPlayer.Init(
				{ 640,720 },
				100,
				0xFFFFFFFF
			);
			SPlayer.isJump = false;
			SPlayer.isRef = false;
			SPlayer.canHit = true;
			for (int i = 0; i < BOX_MAX; i++) {
				SelectBox[i].isHit = false;
				SelectBox[i].velY = 0;
			}
			if (scene == SELECT) {//GAMEとCLEARの間でリセットするとスコアを表示できないため
				score.ClearTimer = 0;
				score.ClearTimerS = 0;
				score.ClearTimerM = 0;
			}
			isReset = false;//フラグを下す
		}

#pragma endregion

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (scene)
		{
		case TITLE:
#pragma region"タイトルの描画処理"
			for (int i = 0; i < TITLEBOX_MAX; i++) {
				TitleBox[i].DrawUpDate();
			}
			TitleJD.rotate(TPlayer.CPos, TPlayer.dir);
			TPlayer.draw();
			TitleRogo.DrawUpDate();
#pragma endregion
			break;
		case SELECT:
#pragma region"セレクトの描画処理"
			for (int i = 0; i < SELECTBOX_MAX; i++) {
				SelectBox[i].DrawUpDate();
			}
			SelectJD.rotate(SPlayer.CPos, SPlayer.dir);
			SelectRogo.DrawUpDate();
			SPlayer.draw();
#pragma endregion
			break;
		case GAME:
#pragma region"ゲームの描画処理"
			STAGE.draw(SCROLL.getScroll());
			ENEMY.draw(SCROLL.getScroll());
			PLYR.draw(SCROLL.getScroll());
			GAUGE.draw(PLYR.getPressT());

			JD.rotate(PLYR.pos, PLYR.dir, SCROLL.getScroll());
			PLYR.debugPrint();
			score.DrawTimer();

#pragma endregion

			break;
		case GAMEOVER:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x006600FF, kFillModeSolid);
			break;
		case GAMECLEAR:

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
			score.result();//rank表示
			score.DrawResultTimer();//クリアタイム表示
			for (int i = 0; i < PAPER_MAX; i++) {
				effectpaper[i].DrawUpDate();
			}
			break;
		}


		//シーンチェンジの上
		changeUp.DrawSpriteUpdate(changeUp.sceneChangeUpGH);
		//シーンチェンジの下
		changeLow.DrawSpriteUpdate(changeUp.sceneChangeLowGH);


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}


