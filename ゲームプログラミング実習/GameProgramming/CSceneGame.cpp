#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "Ckey.h"
//
#include "CMaterial.h"
//
#include "CCollisionManager.h"

#include"CEnemy.h"

#include "CEnemy2.h"

#include "CSea.h"

#include "CTrash.h"

#include "CRock4.h"

#include "CRock5.h"

#include "CRock6.h"

#include "CSeaweed.h"

#include "CColliderTriangle.h"

#include "CText.h"

#include "CScore.h"

#include "CPlayer.h"

//CMatrix Matrix;

int Time = 30 * 60;

CSceneGame::~CSceneGame()

 {

}

void CSceneGame::Init()
{
	mJump.Load("jump.wav");

//	mBillBoard.Set(CVector(0.0f, 5.0f, 0.0f), 1.0f, 1.0f);

	//テキストフォントの読み込みと設定
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	CRes::sModelX.Load(MODEL_FILE);



	mModel.Load("resorce\\sphere.obj","resorce\\sphere.mtl");
	mModel2.Load("resorce\\sea OBJ.obj", "resorce\\sea MTL.mtl");
	mModel3.Load("resorce\\trash.obj", "resorce\\trash.mtl");
	mModel4.Load("resorce\\rock1.obj", "resorce\\rock1.mtl");
	mModel5.Load("resorce\\rock2.obj", "resorce\\rock2.mtl");
	mModel6.Load("resorce\\rock3.obj", "resorce\\rock3.mtl");
	mModel7.Load("resorce\\SeaWeed.obj", "resorce\\SeaWeed.mtl");
	mModel8.Load("resorce\\Submarine1.obj", "resorce\\Submarine1.mtl");

	new CPlayer(&mModel8, CVector(0, 10, 0), CVector(0, 0, 0), CVector(0.09, 0.09, 0.09));



						//(右左 上下 前後ろ)
	new CEnemy(&mModel, CVector(0, 120, -100), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(50, 12, -100), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy(&mModel, CVector(80, 4, 80), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(80, 9, 50), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy(&mModel, CVector(-20, 20, -50), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(20, 10, -50), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy(&mModel, CVector(40, 15, 50), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(-40, 5, 50), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy(&mModel, CVector(-200, 5, 200), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(-260, 0, 180), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy(&mModel, CVector(-100, 5, -50), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(100, 50, -50), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy(&mModel, CVector(80, 40, -100), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(80, 4, -150), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy(&mModel, CVector(-20, 10, -250), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy(&mModel, CVector(20, 10, -250), CVector(0, 0, 0), CVector(8, 8, 8));

	//球　上下
	new CEnemy2(&mModel, CVector(-60, 100, 120), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy2(&mModel, CVector(60, 100, 120), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy2(&mModel, CVector(0, 50, 65), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy2(&mModel, CVector(10, 0, 30), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy2(&mModel, CVector(100, 200, 90), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy2(&mModel, CVector(-100, 10, 90), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy2(&mModel, CVector(-150, 80, 20), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy2(&mModel, CVector(-15, 8, 20), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy2(&mModel, CVector(-10, 100, 120), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy2(&mModel, CVector(10, 10, 12), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy2(&mModel, CVector(10, 50, 250), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy2(&mModel, CVector(10, 12, 250), CVector(0, 0, 0), CVector(8, 8, 8));

	new CEnemy2(&mModel, CVector(200, 150, 110), CVector(0, 0, 0), CVector(8, 8, 8));
	new CEnemy2(&mModel, CVector(20, 50, 11), CVector(0, 0, 0), CVector(8, 8, 8));




	//ゴミ袋
	new CTrash(&mModel3, CVector(0,100, 50), CVector(0, 0, 0), CVector(1, 1, 1));
	new CTrash(&mModel3, CVector(50, 50, 0), CVector(0, 0, 0), CVector(3, 3, 3));
	new CTrash(&mModel3, CVector(100, 120, 100), CVector(0, 0, 0), CVector(1, 1, 1));
	new CTrash(&mModel3, CVector(150, 10, -30), CVector(0, 0, 0), CVector(5, 5, 5));

	
	new CRock4(&mModel4, CVector(0, 3, 0), CVector(0, 0, 0), CVector(5, 5, 5));
	new CRock4(&mModel4, CVector(50, 3, 0), CVector(0, 0, 0), CVector(5, 5, 5));
	new CRock4(&mModel4, CVector(100, 3, 0), CVector(0, 0, 0), CVector(5, 5, 5));
	new CRock4(&mModel4, CVector(150, 3, 0), CVector(0, 0, 0), CVector(5, 5, 5));
	new CRock4(&mModel4, CVector(200, 3, 0), CVector(0, 0, 0), CVector(5, 5, 5));


	new CRock5(&mModel5, CVector(50, 10, 70), CVector(0, 0, 0), CVector(3, 3, 3));
	new CSeaweed(&mModel7, CVector(50, 4, 70), CVector(0, 0, 0), CVector(2, 2, 2));

	new CRock5(&mModel5, CVector(50, 0, 50), CVector(0, 0, 0), CVector(5, 5, 5));
	new CSeaweed(&mModel7, CVector(40, 3, 50), CVector(0, 0, 0), CVector(2, 2, 2));


	new CRock6(&mModel6, CVector(-25, 3, 60), CVector(0, 0, 0), CVector(15, 15, 15));
	new CRock6(&mModel6, CVector(-50, 3, -100), CVector(0, 0, 0), CVector(10, 15, 15));


	//背景モデルから三角コライダを生成
	//親インスタンスと親行列はなし

	//カメラ初期化
	Camera.Init();

	//ステージ
//new CSea(&mModel2, CVector(0, -3.3, 0), CVector(0, 0, 0), CVector(25, 25, 25));

}


void CSceneGame::Update() {

	if (CKey::Push(VK_ESCAPE)) {
		exit(0);
	}

	if (Time > 0) {
		Time--;
	}
	char buf[10];


	//更新
	CTaskManager::Get()->Update();
	//衝突処理
	CTaskManager::Get()->TaskCollision();


	Camera.Update();


	//mJump.Play();
//	mBillBoard.Update();
	return;
}

void CSceneGame::Render() {
//	mBillBoard.Render();
	
	Camera.Render();

	//タスクの描画
	CTaskManager::Get()->Render();
	CTaskManager::Get()->Render2D();

	//コライダの描画
	CCollisionManager::Get()->Render();
	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);


	//水
	glColor4f(0.0f, 0.7f, 0.9f, 0.4f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glVertex2d(0, 600);
	glVertex2d(0, 0);
	glVertex2d(800, 0);
	glVertex2d(800, 600);
	glEnd();

	glDisable(GL_BLEND);

	//文字列の描画
	//mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//スコア
	mFont.DrawString("SCORE", 20, 550, 10, 20);
	sprintf(buf, "%d", CScore::mScore);
	mFont.DrawString(buf, 20, 500, 10, 20);

	//タイム
	mFont.DrawString("TIME", 725, 550, 10, 20);
	sprintf(buf, "%d", Time/60);
	mFont.DrawString(buf, 750, 500, 10, 20);

	if (Time == 0) {
		mFont.DrawString("GAME OVER", 200, 150, 15, 15);
	}


	//2Dの描画終了
	CUtil::End2D();

}
