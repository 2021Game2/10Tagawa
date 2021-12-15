#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "CCamera.h"
#include "CUtil.h"


#define HP 10	//耐久値

int CEnemy2::sCount = 0;	//インスタンス数

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy2::CEnemy2(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 0.5f, 0.0f), 2.0f)
	, mHp(HP)
	, mAttack(false)
	, mCnt(20)
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
void CEnemy2::Update() {
	//HPが0の時　撃破
	if (mHp = 0)
	{
		mTag = EENEAT;

			//エフェクト生成
		new CEffect(mPosition, 5.0f, 5.0f, "exp.tga", 4, 4, 2);

		CTransform::Update();	//行列更新
		//return;	//呼び元へ戻す

		
	}

	int i;
	srand((unsigned)time(NULL)); //乱数の仕組みを初期化

	for (i = 0; i <= 1; i++)	//1回繰り返す
	{
		ran = ((rand() % (max - min + 1)) / 4.0 - 0.25) / 10; //乱数の生成

		mPosition.mY += ran;
		//mPosition.mX += ran;
		//mPosition.mZ += ran;

		CEnemy2::mMoving = true;

		if (mPosition.mX > 10) {
			mPosition.mX - 1;
		}
	}


	//行列を更新
	CTransform::Update();
	//位置を移動
	//mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;
}


//衝突処理
//Collision(コライダ1, コライダ2)
void CEnemy2::Collision(CCollider* m, CCollider* o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//相手のコライダタイプの判定
	switch (o->mType)
	{
	case CCollider::ESPHERE: //球コライダの時
		//if (o->mpParent->mTag == EENEMY)
		//	return;
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			if (o->mpParent->mTag == EPLAYER)
			{
				//2秒後に爆発
				//mCnt -= 1;
				//if (mCnt == 0) {
					mHp -= HP;
				//	mCnt = 20;
				//}
				//return;
					//mEnabled = false;

			}

			//else {
			//	mCnt = 20;
			//	mHp = 10;
			//}
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


void CEnemy2::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
