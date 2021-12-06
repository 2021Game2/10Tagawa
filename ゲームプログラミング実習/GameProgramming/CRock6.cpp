#include "CRock6.h"
#include "CCollisionManager.h"

//コンストラクタ
//CTrash(モデル, 位置, 回転, 拡縮)
CRock6::CRock6(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f),18.0f)
{

	mTag = EROCK;

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
void CRock6::Update() {
	mTag = EENEAT;
	CTransform::Update();	//行列更新
	return;	//呼び元へ戻す

//行列を更新
	CTransform::Update();
}


//衝突処理
//Collision(コライダ1, コライダ2)
void CRock6::Collision(CCollider* m, CCollider* o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}

	//相手のコライダタイプの判定
	CVector adjust; //調整値
	switch (o->mType)
	{
	case CCollider::ESPHERE: //球コライダの時

		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			if (o->mpParent->mTag == EPLAYER)
			{
				mPosition = mPosition + adjust;
			}
		}
		break;
	case CCollider::ETRIANGLE: //三角コライダの時
		//CVector adjust; //調整値
		//三角コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//衝突しない位置まで戻す
			mPosition = mPosition + adjust;
		}
		break;
	}

	//mCollider1.mpMatrix = &mpCombinedMatrix[1];
}

void CRock6::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
