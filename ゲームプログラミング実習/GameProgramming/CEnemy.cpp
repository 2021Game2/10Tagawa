#include "CEnemy.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "CCamera.h"
#include "CUtil.h"


int CEnemy::sCount = 0;	//インスタンス数
#define HP 10

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel *model, CVector position,
	CVector rotation, CVector scale)
: mCollider1(this, &mMatrix, CVector(0.0f, 0.5f, 0.0f), 2.0f)
, mHp(HP)
, mAttack(false)
,mCnt(30)
, max(2)
, min(0)
{
	sCount++;

	mTag = EENEMY;

	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定

	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する

	//mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

//更新処理
void CEnemy::Update() {

	//HPが0以下の時　撃破
	if (mHp = 0)
	{

			//エフェクト生成
			new CEffect(mPosition, 5.0f, 5.0f, "exp.tga", 4, 4, 2);

		CTransform::Update();	//行列更新
		return;	//呼び元へ戻す
	}



	int i;
	srand((unsigned)time(NULL)); //乱数の仕組みを初期化

	for (i = 0; i <= 1; i++)	//1回繰り返す
	{
		ran = ((rand() % (max - min + 1)) / 4.0 - 0.25)/10; //乱数の生成

		//mPosition.mY += ran;
		mPosition.mX += ran;
		//mPosition.mZ += ran;

		CEnemy::mMoving = true;

		if (mPosition.mX > 10) {
			mPosition.mX - 1;
		}
	}

	//行列を更新
	CTransform::Update();
}


//衝突処理
//Collision(コライダ1, コライダ2)
void CEnemy::Collision(CCollider *m, CCollider *o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//相手のコライダタイプの判定
	switch (o->mType)
	{	
	case CCollider::ESPHERE: //球コライダの時
//		if (o->mpParent->mTag == EENEMY)
//			return;
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			if (o->mpParent->mTag == EPLAYER) 
			{
				//3秒後に爆発
				//mCnt -=1;
				//if (mCnt == 0) {
					mHp -= HP;
				//	mCnt = 30;
				//}
				//return;
					mEnabled = false;

			}

		//else {
		//		mCnt = 30;
		//		mHp = 10;
		//	}
		}
		break;
	case CCollider::ETRIANGLE: //三角コライダの時
		CVector adjust; //調整値
		//三角コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//衝突しない位置まで戻す
			mPosition = mPosition + adjust;
			//撃破で地面に衝突すると無効
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}

	//mCollider1.mpMatrix = &mpCombinedMatrix[1];
}


void CEnemy::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}


//void Render2D() {
//	CVector ret;
//	Camera.WorldToScreen(&ret, mPosition);
//
//	//2D描画開始
//	CUtil::Start2D(0, 800, 0, 600);
//
//	//文字列の描画
//	mFont.DrawString("TEST", ret.mX, ret.mY, 8, 16);
//
//
//	//2Dの描画終了
//	CUtil::End2D();
//
//}
