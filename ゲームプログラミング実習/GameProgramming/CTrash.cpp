#include "CTrash.h"
#include "CCollisionManager.h"
#include "CSceneGame.h"
#include "CScore.h"


#define SCORE 100			//スコア

//コンストラクタ
//CTrash(モデル, 位置, 回転, 拡縮)
CTrash::CTrash(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider1(this, &mMatrix, CVector(0.5f, 0.5f, 0.0f), 1.5f)
	, mCnt(60)
{


	mTag = EITEM;

	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定

	//優先度を1に変更する
	mPriority = 1;

	//mFont.LoadTexture("FontG.png", 1, 4096 / 64);



}

//更新処理
void CTrash::Update() {
	mTag = EITEM;

	mPosition.mY -= 0.1;
	if (mPosition.mY < 1) {
		mPosition.mY = 150;

		//	mCnt -= 1;
		//if (mCnt == 0) {
		//	mEnabled;
		//	}

	}
	CTransform::Update();	//行列更新
	return;	//呼び元へ戻す

//行列を更新
	CTransform::Update();
}


//衝突処理
//Collision(コライダ1, コライダ2)
void CTrash::Collision(CCollider* m, CCollider* o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//自身のコライダタイプの判定
	switch (m->mType) {
	case CCollider::ESPHERE:
		//相手のコライダが球コライダの時
		CVector adjust;
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				mPosition = mPosition + adjust;

				if (o->mpParent->mTag == EPLAYER) {
					CScore::mScore += SCORE;
					mPosition.mY = 150;

				}
			}
		}


		//相手のコライダが三角コライダの時
		else if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と球の衝突判定
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}
		break;
	}
}

void CTrash::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
