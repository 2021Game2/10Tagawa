//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"
//
#include "CBullet.h"
//
#include "CTaskManager.h"
//
#include "CCollisionManager.h"
//
#include "CUtil.h"
//
#include "CEffect.h"

#include "CCharacter.h"

#include "CEnemy.h"


CPlayer *CPlayer::spThis = 0;

#define _USE_MATH_DEFINES
#include <math.h>

#include "CEffect.h"
#define G -0.5	//重力
#define HP 10	//HP
#define INITIALIZE 0	//初期化


CPlayer::CPlayer(CModel* model, CVector position,
	CVector rotation, CVector scale)
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f)
, mCount(0)
, mHp(HP)

{
	mTag = EPLAYER;	//タグの設定
	spThis = this;
	//テクスチャファイルの読み込み（1行64列）
	mText.LoadTexture("FontWhite.tga", 1, 64);


}

//更新処理
void CPlayer::Update() {
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation.mY += 1;
	}
	if (CKey::Push('D')) {
		//Y軸の回転値を増加
		mRotation.mY -= 1;
	}
	//上矢印キー入力で前進
	if (CKey::Push(VK_UP)) {
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}




	if (mCount > 0)
	{
		mCount--;
	}

	mPosition.mY -= 0.03f;

	//CTransformの更新
	CTransform::Update();
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
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
				if (o->mpParent->mTag == EENEMY) {
					mHp -= HP;
					if (mHp == 0) {
						mEnabled = false;
					}
				}
				if (o->mpParent->mTag == EROCK) {
					mPosition = mPosition + adjust;
				}
				if (o->mpParent->mTag == EENEMY) {
					mPosition = mPosition + adjust;
				}

			}
		}
		//相手のコライダが三角コライダの時
		else if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と球の衝突判定
			CCollider::CollisionTriangleSphere(o, m, &adjust);

			//位置の更新(mPosition + adjust)

			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}
		break;
	}
}


//衝突処理
void CPlayer::TaskCollision()
{
	//コライダの優先度変更
	mColSphereHead.ChangePriority();
	mColSphereBody.ChangePriority();

	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mColSphereHead, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereBody, COLLISIONRANGE);
}

void CPlayer::Render()
{
	//親の描画処理
	CCharacter::Render();

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	//文字列編集エリアの作成
	char buf[64];

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "PY:%7.2f", mPosition.mY);
	//文字列の描画
	mText.DrawString(buf, 100, 30, 8, 16);

	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "RX:%7.2f", mRotation.mX);
	//文字列の描画
	mText.DrawString(buf, 100, 0, 8, 16);
	
	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "RY:%7.2f", mRotation.mY);
	//文字列の描画
	mText.DrawString(buf, 100, -100, 8, 16);

	//2Dの描画終了
	CUtil::End2D();

}