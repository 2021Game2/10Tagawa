#include "CXPlayer.h"
#include "CKey.h"
#include "CCamera.h"
#include "CUtil.h"
#include "CCollisionManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "CEffect.h"
#define G -1	//重力
#define VJ0 10	//ジャンプ力
#define HP 10	//耐久値


bool CXPlayer::mJumping;

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mJump(0)
	, mJflag(false)
	, mCount(0)
	, mHp(HP)

{
	//タグにプレイヤーを設定します
	mTag = EPLAYER;

	mJumping = false;

}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpMatrix = &mpCombinedMatrix[9];
	////頭
	//mColSphereHead.mpMatrix = &mpCombinedMatrix[12];

	mRotation.mY = 0.01f;
}

void CXPlayer::Update()
{
	if (mAnimationIndex == 3)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(4, false, 30);
		}
	}
	else if (mAnimationIndex == 4)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(0, true, 60);
		}
	}
	else
	{


		//回転移動 通称バイオ移動

		//if (CKey::Push('A'))
		//{
		//	mRotation.mY += 2.0f;
		//}
		//if (CKey::Push('D'))
		//{
		//	mRotation.mY -= 2.0f;
		//}
		//if (CKey::Push(' '))
		//{
		//	ChangeAnimation(3, true, 30);
		//}
		//else if (CKey::Push('W'))
		//{
		//	ChangeAnimation(1, true, 60);
		//	mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		//}
		//else {
		//	ChangeAnimation(0, true, 60);
		//}

		//カメラ視点移動　通称無双移動

		//カメラの左右と前後のベクトルを取得
		CVector SideVec = Camera.GetMat().GetXVec();
		CVector FrontVec = Camera.GetMat().GetZVec();
		//高さ移動はカットする
		SideVec.mY = 0.0f;
		FrontVec.mY = 0.0f;
		//正規化する
		SideVec.Normalize();
		FrontVec.Normalize();

		float speed = 0.5f;
		CVector Move(0, 0, 0);


		if (CKey::Push('A'))
		{
			//			mRotation.mY += 2.0f;
			Move -= SideVec;
		}
		else if (CKey::Push('D'))
		{
			//			mRotation.mY -= 2.0f;
			Move += SideVec;
		}
		if (CKey::Push('W'))
		{
			Move += FrontVec;
			//			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		}
		else if (CKey::Push('S'))
		{
			Move -= FrontVec;
			//			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		}

		if (CKey::Push(' '))
		{
			//位置調整
			CVector tpos = mPosition;
			tpos.mY += 2.0f;
			//new CEffect(tpos, 2.0f, 0.0f, "exp.tga", 4, 4, 2);
			mVj = VJ0;
			mJflag = true;
			mJumping = true;

			ChangeAnimation(3, true, 30);
		}else if (Move.Length() != 0.0f){
			ChangeAnimation(1, true, 60);
		}else {
			ChangeAnimation(0, true, 60);
		}

		//移動量正規化　これをしないと斜め移動が早くなってしまうので注意
		//ジャンプ時などはY軸を正規化しないよう注意
		Move.Normalize();
		//平行移動量
		Move = Move*speed;

		
		//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
		//擬似ベクトル計算
		Check tCheck = CUtil::GetCheck2D(Move.mX,Move.mZ,0,0, mRotation.mY*(M_PI/180.0f));
		
		//回転速度　degreeに直す
		float turnspeed = (180.0f / M_PI)*0.5f;

		//急な振り返りを抑制
		if (tCheck.turn > 1.5f) tCheck.turn =1.5f;

		//移動方向へキャラを向かせる
		if (tCheck.cross > 0.0f) {
			mRotation.mY += tCheck.turn * turnspeed;
		}
		if (tCheck.cross < 0.0f) {
			mRotation.mY -= tCheck.turn * turnspeed;
		}

		//座標移動
		mPosition += Move;


	}
	//注視点設定
	Camera.SetTarget(mPosition);

	CXCharacter::Update();
}


void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//自身のコライダタイプの判定
	switch (m->mType) {
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition - adjust * -1;
			//行列の更新
			CTransform::Update();
		}
		break;
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
			}
		}
		break;
	}
}

//衝突処理
void CXPlayer::TaskCollision()
{
	//コライダの優先度変更
	//mLine.ChangePriority();
	//mLine2.ChangePriority();
	//mLine3.ChangePriority();
	mCollider.ChangePriority();
	//衝突処理を実行
	//CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	//CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	//CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

void CXPlayer::Render()
{
	////親の描画処理
	//CCharacter::Render();

	////2Dの描画開始
	//CUtil::Start2D(-400, 400, -300, 300);
	////描画色の設定（緑色の半透明）
	//glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	////文字列編集エリアの作成
	//char buf[64];

	////Y座標の表示
	////文字列の設定
	//sprintf(buf, "PY:%7.2f", mPosition.mY);
	////文字列の描画
	//mText.DrawString(buf, 100, 30, 8, 16);

	////X軸回転値の表示
	////文字列の設定
	//sprintf(buf, "RX:%7.2f", mRotation.mX);
	////文字列の描画
	//mText.DrawString(buf, 100, 0, 8, 16);

	////Y軸回転値の表示
	////文字列の設定
	//sprintf(buf, "RY:%7.2f", mRotation.mY);
	////文字列の描画
	//mText.DrawString(buf, 100, -100, 8, 16);

	////2Dの描画終了
	//CUtil::End2D();

}