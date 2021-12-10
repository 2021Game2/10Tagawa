#include "CRock5.h"
#include "CCollisionManager.h"

//コンストラクタ
//CTrash(モデル, 位置, 回転, 拡縮)
CRock5::CRock5(CModel* model, CVector position,
	CVector rotation, CVector scale)
	//: mCollider1(this, &mMatrix, CVector(0.0f, -0.1f, 0.0f), 7.7f)
{

	mTag = EROCK;

	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定

	//優先度を1に変更する
	mPriority = 1;

	CTransform::Update();

	//mFont.LoadTexture("FontG.png", 1, 4096 / 64);
	mCollider1.Set(this, &mMatrix, mpModel);


}

//更新処理
void CRock5::Update() {
	mTag = EENEAT;
	CTransform::Update();	//行列更新
	return;	//呼び元へ戻す

//行列を更新
	CTransform::Update();
}


//衝突処理
//Collision(コライダ1, コライダ2)
void CRock5::Collision(CCollider* m, CCollider* o) {

}

void CRock5::TaskCollision()
{
}
