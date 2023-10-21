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
#include "playerEffect.h"
#include "enemyHitEffect.h"
#include "RefEffect.h"
#include "checkPoint.h"

const char kWindowTitle[] = "1105_オザワ_キョウ_ミカミ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	/*乱数生成*/
	unsigned int currentTime = static_cast<int>(time(nullptr));
	srand(currentTime);

#pragma region"変数"

	/*シーンの変数*/
	/*--------------------------------------------------------------------*/
	enum SCENE {
		TITLE,
		SELECT,
		GAME,
		GAMEOVER,
		GAMECLEAR
	};
	SCENE scene = TITLE;
	int SceneNo = 0;
	bool isChangeScene = false;
	bool isChangeSceneGame = false;

	/*--------------------------------------------------------------------*/

	STAGE STAGE;
	PLAYER PLYR;
	SCROLL SCROLL;
	GAUGE GAUGE;
	ENEMY ENEMY;
	ENEMY.moveDirX=-1.0f;
	jumpDirection JD;

	playerEffect PEffect;

	TjumpDirection TitleJD;
	TjumpDirection SelectJD;

	EnemyHitEffect enemyHitEffect;
	RefEffect refEffect;
	checkPoint checkpoint;

	refEffect.timer = refEffect.timerMax;

	/*--------------------------------------------------------------------*/
	const int TITLEBOX_MAX = 2;
	Box TitleRogo;
	Box Smail;
	Box TitleBox[2];//[0]=セレクト画面へ[1]=ゲーム終
	Box Line[2];

	TitlePlayer TPlayer;
	//タイトルロゴ
	TitleRogo.Init(
		{ 640,50 },
		800,
		150,
		0xfc21c6cc
	);
	//タイトル画面の選択肢（[0]セレクト[1]ゲーム終了）
	for (int i = 0; i < TITLEBOX_MAX; i++) {
		TitleBox[i].Init(
			{ (340.0f + 600.0f * i),450 },
			300,
			300,
			0xfc21c6cc
		);
	}

	TPlayer.Init(
		{ 640,720 },
		100,
		0xFFFFFFFF
	);
	/*Smail.Init(
		{ 1000,150 },
		150,
		150,
		0xfc21c6cc
	);
	*/

	Line[0].Init(
	{ 640,308 },
	1280,
	3,
	0xfc21c666
);
	Line[1].Init(
		{ 640,591 },
		1280,
		3,
		0xfc21c666
	);

	const int SELECTBOX_MAX = 10;
	Box SelectRogo;
	Box gameOverRogo;
	Box PressSpace;
	Box Manual;
	Box turnLeft;//1~3	
	Box turnRight;//4~6
	selectBox SelectBox[10];
	//SelectBox[0].color = 0xFF0000FF;
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

	gameOverRogo.Init(
		{ 640,160 },
		720,
		120,
		0xFF1111FF
	);

	Manual.Init(
		{ SelectBox[9].CPos.x,SelectBox[9].CPos.y - 200 },
		256,
		64,
		0xfc21c6cc
	);
	turnLeft.Init(
		{ SelectBox[5].CPos.x,SelectBox[5].CPos.y - 200 },
		256,
		64,
		0xfc21c6cc
	);
	turnRight.Init(
		{ SelectBox[4].CPos.x,SelectBox[4].CPos.y - 200 },
		256,
		64,
		0xfc21c6cc
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


	const int PAPER_MAX = 32;
	EffectPaper effectpaper[PAPER_MAX];


	bool isReset = false;//リセットフラグ
	bool isResetGame = false;//残機ありのリセットフラグ

	/*--------------------------------------------------------------------*/
#pragma endregion

	//ステージのロード
	STAGE.loadStage(0);

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

		if (keys[DIK_1] && preKeys[DIK_1]) {
			Line[0].CPos.y -= 1;
		}
		if (keys[DIK_2] && preKeys[DIK_2]) {
			Line[0].CPos.y += 1;
		}
		if (keys[DIK_3] && preKeys[DIK_3]) {
			Line[1].CPos.y -= 1;
		}
		if (keys[DIK_4] && preKeys[DIK_4]) {
			Line[1].CPos.y += 1;
		}
		if (keys[DIK_5] && preKeys[DIK_5]) {
			ENEMY.pos.y -= 1;
		}
		if (keys[DIK_6] && preKeys[DIK_6]) {
			ENEMY.pos.y += 1;
		}

		switch (scene) {
		case TITLE:
#pragma region"タイトルの更新処理"
			/*半径ゼロまたは自機が画面の下の外にいったら元の位置に戻る*/
			TPlayer.ReturnPlayer();
			TitleJD.ButtonFlagReset(TPlayer.isJump, TPlayer.CPos.y, TPlayer.radius);//ボタン系のフラグを元に戻す
			//押すとその方向へ飛んでいく
			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				TitleJD.isReleaseFlag();
				TPlayer.jump(TitleJD.getNormalizeJumpVect(), isChangeScene);
			}

			TPlayer.Move();
			ENEMY.TitleUp();//試し
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
			Novice::ScreenPrintf(0, 100, "[0]%f,[1]%f,enemy%f", Line[0].CPos.y, Line[1].CPos.y,ENEMY.pos.y);
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

			Manual.CPos = { SelectBox[9].CPos.x, SelectBox[9].CPos.y - 100 };
			turnLeft.CPos = { SelectBox[4].CPos.x, SelectBox[4].CPos.y - 100 };
			turnRight.CPos = { SelectBox[5].CPos.x, SelectBox[5].CPos.y - 100 };

			//選択画面の自機ジャンプ
			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				SelectJD.isReleaseFlag();
				SPlayer.jump(SelectJD.getNormalizeJumpVect(), isChangeScene);
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
				SceneNo = 2;//1ゲーム画面へ移動
				STAGE.loadStageNum = 0;
				isChangeScene = true;
			}
			if (SelectBox[7].isHit) {
				SceneNo = 2;//1ゲーム画面へ移動
				STAGE.loadStageNum = 1;

				isChangeScene = true;
			}
			if (SelectBox[6].isHit) {
				SceneNo = 2;//1ゲーム画面へ移動
				STAGE.loadStageNum = 0;
				isChangeScene = true;
			}

			if (SelectBox[5].isHit) {
				SelectBox[0].isR = true;//回転
			}
			if (SelectBox[4].isHit) {
				SelectBox[0].isR = true;//回転
			}
			if (SelectBox[3].isHit) {
				STAGE.loadStageNum = 0;
				STAGE.loadStageNum = 0;
				SceneNo = 2;//1ゲーム画面へ移動
				isChangeScene = true;
			}
			if (SelectBox[2].isHit) {
				STAGE.loadStageNum = 0;
				SceneNo = 2;//1ゲーム画面へ移動
				isChangeScene = true;
			}
			if (SelectBox[1].isHit) {
				STAGE.loadStageNum = 0;
				SceneNo = 2;//1ゲーム画面へ移動
				isChangeScene = true;
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
						SelectBox[i].velY = 0.0f;
						SelectBox[i].isDraw = true;
						SPlayer.canHit = true;
						SelectBox[i].color = 0xfc21c6FF;
						SelectBox[i].isHit = false;
						SelectBox[i].timer = 35;//このタイマーはずらすと復活する瞬間が回転中に見えてしまうので注意
					}
				}
			}
			STAGE.loadStage(STAGE.loadStageNum);

			//イージング
			SelectBox[0].theta = (1.0f - SelectBox[0].t) * SelectBox[0].minTheta + SelectBox[0].t * SelectBox[0].maxTheta;
			break;
#pragma endregion
		case GAME:
		case GAMEOVER:
		case GAMECLEAR:
#pragma region"ゲームの更新処理"


			if (scene == GAME) {

				if (keys[DIK_R] && !preKeys[DIK_R])
				{
					PLYR.isAlive = false;
					ENEMY.isHit = true;
					PLYR.lives++;
				}
				if (keys[DIK_Q])
				{
					ENEMY.pos = { 3929.408203f,2767 };
					//      STAGE.loadStage(0);
					PLYR.respawnPos = { 0,0 };
				}

				//プレイヤーのリスポーン
				PLYR.Respawn(ENEMY.isHit, ENEMY.pos, ENEMY.respawnPos);
				if (PLYR.respawnTimer == 60 && PLYR.lives > 0) {
					isChangeSceneGame = true;
				}

				if (PLYR.isGoal)
				{
					SceneNo = 4;
					isChangeScene = true;
				}

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
					if (PLYR.respawnTimer >= 120) {
						PLYR.Move();
					}
				} else if (PLYR.isBlasted && PLYR.blastCountDwon >= 0) {
					if (!PLYR.isSetBlastPos)
					{
						STAGE.blasterPosSet(PLYR.pos, PLYR.size);
						PLYR.isSetBlastPos = true;
					}
				}

				//プレイヤーの衝突判定
				if (!PLYR.isHitStop)
					PLYR.hitAction(STAGE.collisionCheck(PLYR.pos, PLYR.size, PLYR.velocity, PLYR.dir), STAGE.getmapChipsize(), refEffect.isHitPoint, refEffect.isDraw);
				else
					PLYR.hitAction(0, STAGE.getmapChipsize(), refEffect.isHitPoint, refEffect.isDraw);

				if (!PLYR.isBlasted)//撃たれたらblastPosをリセット
					STAGE.blastPosReset();

				checkpoint.isDrawFlag(PLYR.isSetRespawnPos);

				refEffect.Appear(PLYR.jumpVel, PLYR.pos);
				refEffect.DrawTimer();

				PEffect.Move(PLYR.isJump, PLYR.isAlive, PLYR.pos);

				//敵の移動処理
				if (PLYR.respawnTimer >= 120) {
					ENEMY.Move(PLYR.pos, PLYR.isStun, PLYR.isHitStop);
				}
				//敵のリスポーンPos更新
				ENEMY.setRespawnPos(PLYR.isSetRespawnPos, PLYR.pos, PLYR.dir);

				ENEMY.timeSlow(PLYR.isJump, PLYR.isAlive);
				ENEMY.CollisionToPlayer(PLYR.pos, PLYR.size);
				enemyHitEffect.UpDate(ENEMY.isHit, PLYR.isHitToge, PLYR.pos);

				SCROLL.update(PLYR.getPos(), PLYR.isShake);
				JD.ButtonFlagReset(PLYR.isJump);


				if (scene == GAME) {
					//リザルトの時間測定する
					score.TimeCount(PLYR.isAlive, PLYR.isGoal);
					//仮置き、ゲームオーバー
					if (keys[DIK_3] && !preKeys[DIK_3]) {
						SceneNo = 3;
						isChangeScene = true;

					}
					if (PLYR.respawnTimer <= 60 &&//ここの秒数弄るとゲームオーバー前だけ時間を長くすることができる
						PLYR.lives <= 0) {
						SceneNo = 3;
						isChangeScene = true;
					}
					//仮置きゲームクリア
					if (keys[DIK_4] && !preKeys[DIK_4]) {
						SceneNo = 4;
						isChangeScene = true;
					}
				}
			}
#pragma endregion

#pragma region"ゲームオーバーの更新処理"

			if (scene == GAMEOVER) {
				ENEMY.CollisionToPlayer(PLYR.pos, PLYR.size);
				enemyHitEffect.UpDate(ENEMY.isHit, PLYR.isHitToge, PLYR.pos);
				enemyHitEffect.Reset();
				PLYR.OverUpdate(ENEMY.isHit);
				ENEMY.OVERUp(PLYR.isAlive, PLYR.boundCount);
				PressSpace.Init({ 640,560 }, 640, 100, 0xFFFFFFFF);
				//セレクト画面へ戻る
				if (!isChangeScene) {
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
						SceneNo = 1;
						isChangeScene = true;
					}
				}
			}
#pragma endregion

#pragma region"ゲームクリアの更新処理"

			if (scene == GAMECLEAR) {
				for (int i = 0; i < PAPER_MAX; i++) {
					PLYR.score();
					effectpaper[i].rotate();
					effectpaper[i].Move();
					VectorVertexS(effectpaper[i].vertex, effectpaper[i].CPos, effectpaper[i].size, effectpaper[i].size);
					effectpaper[i].Color();
				}

				//時間に応じてスコアを表示
				score.result(STAGE.loadStageNum);
				SCROLL.update(PLYR.getPos(), PLYR.isShake);	//セレクト画面へ戻る
				PressSpace.Init({ 640,610 }, 640, 100, 0xFFFFFFFF);
				if (!isChangeScene) {
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
						SceneNo = 1;
						isChangeScene = true;
					}
				}
			}
			break;
		}
#pragma endregion


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


		if (isChangeSceneGame) {
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
				isResetGame = true;//ここでリセット
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
				isChangeSceneGame = false;
			}
		}
#pragma endregion
		//リセットの中身
#pragma region"リセット"
		if (isReset) {

			/*タイトルで必要なリセット*/
			for (int i = 0; i < 2; i++) {
				TitleBox[i].isHit = false;
				JD.ButtonFlagReset(PLYR.isJump);	TitleBox[i].vel = { 0,0 };
			}
			TPlayer.isJump = false;
			TPlayer.isRef = false;
			TPlayer.canHit = true;
			TPlayer.DrawAria = 0;
			TPlayer.Init(
				{ 640,720 },
				100,
				0xFFFFFFFF
			);


			/*セレクトで必要なリセット*/
			SPlayer.Init(
				{ 640,720 },
				100,
				0xFFFFFFFF
			);
			SPlayer.isJump = false;
			SPlayer.isRef = false;
			SPlayer.canHit = true;
			SPlayer.DrawAria = 0;
			for (int i = 0; i < BOX_MAX; i++) {
				SelectBox[i].isHit = false;
				SelectBox[i].velY = 0;
				SelectBox[i].theta = 0.0f;
				SelectBox[i].t = 0.0f;
			}


			/*ゲームで必要なリセット*/
			PLYR.pos = { 300.0f,3000.0f };
			PLYR.SetStartPos(STAGE.loadStageNum);
			PLYR.size = { 16,16 };
			PLYR.acceleration = { 0.00f,0.5f };
			PLYR.velocity = { 0,0 };
			PLYR.lives = 3;
			PLYR.isJump = false;
			PLYR.isAlive = true;
			PLYR.isGoal = false;
			PLYR.isHitToge = false;
			PLYR.MoveDir = { 1,0 };
			PLYR.PressT = 0.35f;
			PLYR.addT = 0.02f;
			PLYR.maxVelocity = 30.0f;
			PLYR.minVelocity = 1.0f;
			PLYR.hitStopTimer = 5;
			PLYR.hitStopVelocity = 1.0f;
			PLYR.boundCount = 0;
			PLYR.isStun = false;
			PLYR.isShake = false;
			PLYR.isBlasted = false;
			PLYR.stunTimer = 120;
			PLYR.blastTimer = 120;
			PLYR.shakeTimer = 15;
			PLYR.respawnTimer = 120;
			PLYR.blastCountDwon = 30;
			PLYR.blastDistance = 0;
			PLYR.respawnPos = { 300,3000 };

			ENEMY.pos = { -500.0f,3000.0f };
			ENEMY.size = { 128,128 };
			ENEMY.speed = 5.0f;
			ENEMY.slowTimer = 150;
			ENEMY.warningCountDown = 60;
			ENEMY.warningTimer = 70;
			ENEMY.isMove = false;
			ENEMY.isSlow = true;
			ENEMY.isHit = false;
			ENEMY.isPopEffect = false;
			ENEMY.moveDirX = -1.0f;
			ENEMY.respawnPos = ENEMY.pos;
			for (int i = 0; i < 8; i++) {
				enemyHitEffect.CPos[i] = { 0,0 };
				enemyHitEffect.size[i] = 0;
				enemyHitEffect.vel[i] = { 0,0 };
				enemyHitEffect.acc[i] = { 0,0.8f };
				enemyHitEffect.isAppear[i] = false;
			}
			if (scene == GAMEOVER) {//GAMEOVER時に	
				ENEMY.SCGO = true;
				ENEMY.pos = { -500.0f,360.0f };
				PLYR.pos = { 640.0f,-50.0f };
				PLYR.isAlive = true;
				ENEMY.isHit = false;
			}

			if (scene == SELECT) {//GAMEとCLEARの間でリセットするとスコアを表示できないため
				score.ClearTimer = 0;
				score.ClearTimerS = 0;
				score.ClearTimerM = 0;

				PLYR.lives = 3;
				PLYR.livesDrawPos = { 1114,20 };
				PLYR.livesDrawSize = { 32,32 };
				PLYR.livesGHMargin = 10;

			}
			isReset = false;//フラグを下す
		}


		if (isResetGame) {
			for (int i = 0; i < 8; i++) {
				enemyHitEffect.CPos[i] = { 0,0 };
				enemyHitEffect.size[i] = 0;
				enemyHitEffect.vel[i] = { 0,0 };
				enemyHitEffect.acc[i] = { 0,0.8f };
				enemyHitEffect.isAppear[i] = false;
				isResetGame = false;
			}

		}
#pragma endregion

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);

		switch (scene)
		{
		case TITLE:
#pragma region"タイトルの描画処理"
			Line[0].DrawSpriteUpdate(Line[0].GH[10]);
			Line[1].DrawSpriteUpdate(Line[0].GH[10]);
			ENEMY.TitleDraw();//試し

			TitleBox[0].DrawSpriteUpdateSELECT(TitleBox[0].GH[4]);
			TitleBox[1].DrawSpriteUpdateSELECT(TitleBox[1].GH[5]);
		//	Smail.DrawSpriteUpdate(Smail.GH[9]);


			TitleJD.rotate(TPlayer.CPos, TPlayer.dir, TPlayer.isReload);
			TPlayer.draw();
			TitleRogo.DrawSpriteUpdate(TitleRogo.GH[6]);

#pragma endregion
			break;
		case SELECT:
#pragma region"セレクトの描画処理"
			Line[0].DrawSpriteUpdate(Line[0].GH[10]);
			Line[1].DrawSpriteUpdate(Line[0].GH[10]);
			
			for (int i = 0; i < SELECTBOX_MAX; i++) {
				SelectBox[i].DrawUpDate(i);
			}


			Manual.DrawSpriteUpdate(Manual.GH[3]);


			turnLeft.DrawSpriteUpdate(Manual.GH[7]);
			turnRight.DrawSpriteUpdate(Manual.GH[8]);
			SelectJD.rotate(SPlayer.CPos, SPlayer.dir, SPlayer.isReload);
			SelectRogo.DrawSpriteUpdateSELECT(SelectRogo.GH[2]);
			SPlayer.draw();
#pragma endregion
			break;
		case GAME:
		case GAMEOVER:
		case GAMECLEAR:
#pragma region"ゲームの描画処理"

			//Novice::DrawBox(0, 0, 1280, 720, 0, 0x000000ff, kFillModeSolid);
			score.DrawBGTimer();
			STAGE.draw(PLYR.pos, SCROLL.getScroll());
			if (scene == GAME) {
				PEffect.Draw(SCROLL.getScroll());
				enemyHitEffect.Draw(SCROLL.getScroll());

				refEffect.Draw(SCROLL.getScroll());

				ENEMY.draw(SCROLL.getScroll(), PLYR.isAlive);
				ENEMY.Warning(SCROLL.getScroll(), PLYR.isAlive);

				JD.rotate(PLYR.pos, PLYR.dir, SCROLL.getScroll(), PLYR.isAlive, PLYR.getPressT());
				PEffect.Draw(SCROLL.getScroll());
				PLYR.draw(SCROLL.getScroll());
				score.DrawTimer();
				enemyHitEffect.Draw(SCROLL.getScroll());
				checkpoint.draw();
				ENEMY.enemyToPlayerDistance(PLYR.pos, SCROLL.getScroll());

				PLYR.debugPrint();
				ENEMY.debugPrint();


			}
#pragma endregion

#pragma region"ゲームオーバーの描画処理"
			if (scene == GAMEOVER) {
				Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000F0, kFillModeSolid);
				gameOverRogo.DrawSpriteUpdate(gameOverRogo.GH[0]);
				ENEMY.OVERDraw();
				PLYR.OverDraw();
				PressSpace.DrawSpriteUpdateT(PressSpace.GH[1]);
				enemyHitEffect.OverDraw();

			}
#pragma endregion

#pragma region"ゲームクリアの描画処理"

			if (scene == GAMECLEAR) {
				Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000EE, kFillModeSolid);
				score.result(STAGE.loadStageNum);//rank表示
				PLYR.scoreDraw();
				score.DrawResultTimer();//クリアタイム表示
				for (int i = 0; i < PAPER_MAX; i++) {
					effectpaper[i].DrawUpDate();
				}
				PressSpace.DrawSpriteUpdateT(PressSpace.GH[1]);
			}
			break;
		}
#pragma endregion

		//Novice::ScreenPrintf(1000, 80, "isHit = %d", PLYR.lives);
		//Novice::ScreenPrintf(1000, 100, "timer = %d", PLYR.respawnTimer);

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



