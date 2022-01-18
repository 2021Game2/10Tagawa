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

#include "CCamera.h"


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

	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定


	mTag = EPLAYER;	//タグの設定
	spThis = this;
	//テクスチャファイルの読み込み（1行64列）
	mText.LoadTexture("FontWhite.tga", 1, 64);

	mpModel = model;

	CTransform::Update();

}

//更新処理
void CPlayer::Update() {

	//カメラの左右と前後のベクトルを取得
	CVector SideVec = Camera.GetMat().GetXVec();
	CVector FrontVec = Camera.GetMat().GetZVec();
	//高さ移動はカットする
	//SideVec.mY = 0.0f;
	//FrontVec.mY = 0.0f;
	//正規化する
	SideVec.Normalize();
	FrontVec.Normalize();


	float speed = 0.3f;
	CVector Move(0, 0, 0);



	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		//mPosition.mX += 1;
		Move -= SideVec;

	}
	if (CKey::Push('D')) {
		//Y軸の回転値を増加
		//mPosition.mX -= 1;
		Move += SideVec;

	}
	//Wキー入力で回転
	if (CKey::Push('W')) {
		//Y軸の回転値を増加
		//mPosition.mY += 1;
		Move += FrontVec;

	}
	if (CKey::Push('S')) {
		//Y軸の回転値を増加
		//mPosition.mY -= 1;
		Move -= FrontVec;

	}

	//上矢印キー入力で前進
	if (CKey::Push(VK_UP)) {
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	//移動量正規化　これをしないと斜め移動が早くなってしまうので注意
//ジャンプ時などはY軸を正規化しないよう注意
	Move.Normalize();
	//平行移動量
	Move = Move * speed;


	//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
	//擬似ベクトル計算
	Check tCheck = CUtil::GetCheck2D(Move.mX, Move.mZ, 0, 0, mRotation.mY * (M_PI / 180.0f));

	//回転速度　degreeに直す
	float turnspeed = (180.0f / M_PI) * 0.5f;

	//急な振り返りを抑制
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//移動方向へキャラを向かせる
	if (tCheck.cross > 0.0f) {
		mRotation.mY += tCheck.turn * turnspeed;
	}
	if (tCheck.cross < 0.0f) {
		mRotation.mY -= tCheck.turn * turnspeed;
	}

	//座標移動
	mPosition += Move;


	mPosition += Move;


	if (mCount > 0)
	{
		mCount--;
	}

	//mPosition.mY -= 0.03f;

	Camera.SetTarget(mPosition);


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
					mHp -= 2;
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