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

//CMatrix Matrix;

CSceneGame::~CSceneGame()

 {

}

void CSceneGame::Init()
{
	mJump.Load("jump.wav");

//	mBillBoard.Set(CVector(0.0f, 5.0f, 0.0f), 1.0f, 1.0f);

	//テキストフォントの読み込みと設定
	//mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	CRes::sModelX.Load(MODEL_FILE);
	CRes::sKnight.Load("knight\\knight_low.x");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:移動
	CRes::sKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:待機
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	CRes::sKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:ダウン

	//キャラクターにモデルを設定
	mPlayer.Init(&CRes::sModelX);
	mPlayer.mPosition = CVector(0.0f, 0.0f, 0.0f);

	mModel.Load("sphere.obj","sphere.mtl");
	mModel2.Load("sea OBJ.obj", "sea MTL.mtl");

						//(右左 上下 前後ろ)
	new CEnemy(&mModel, CVector(0, 0, 0), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(5, 4, 5), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(20, 0, 20), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(-20, 2, 10), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(20, 0, 0), CVector(0, 0, 0), CVector(1, 1, 1));

	new CEnemy2(&mModel, CVector(-10, 0, -20), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy2(&mModel, CVector(-20, 5, -10), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy2(&mModel, CVector(20, 5, -10), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy2(&mModel, CVector(10, 0, -10), CVector(0, 0, 0), CVector(1, 1, 1));

	new CSea(&mModel2, CVector(0, -1, 0), CVector(0, 0, 0), CVector(10, 10, 10));

	////敵の初期設定
	//mEnemy.Init(&CRes::sKnight);
	//mEnemy.mAnimationFrameSize = 1024;
	////敵の配置
	//mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
	//mEnemy.ChangeAnimation(2, true, 200);

	//カメラ初期化
	Camera.Init();

}


void CSceneGame::Update() {

	if (CKey::Push(VK_ESCAPE)) {
		exit(0);
	}

	//更新
	CTaskManager::Get()->Update();

	//衝突処理
	CCollisionManager::Get()->Collision();

	Camera.Update();

	//mJump.Play();


//	mBillBoard.Update();




	return;
}

void CSceneGame::Render() {
//	mBillBoard.Render();

	//モデル描画
//	CRes::sModelX.Render();
	//mPlayer.Render();
	////敵描画
	//mEnemy.Render();

	
	Camera.Render();

	//タスクの描画
	CTaskManager::Get()->Render();
	CTaskManager::Get()->Render2D();

	//コライダの描画
	CCollisionManager::Get()->Render();
	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();

}
