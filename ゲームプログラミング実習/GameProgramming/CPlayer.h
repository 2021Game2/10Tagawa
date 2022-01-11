#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//
#include "CBullet.h"
//
#include "CColliderLine.h"
//
#include "CText.h"
/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CCharacter {
public:

	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	float mVj; //ジャンプ用変数
	int mJump; ///ジャンプ位置記憶

	bool mJflag;	//ジャンプフラグ(falseなら可能,trueなら不可)
	static bool CPlayer::mJumping;	//プレイヤージャンプ中フラグ

	int mCount;
	int mHp;	//ヒットポイント

	CCollider mCollider;
	CText mText;
	static CPlayer *spThis;

	CPlayer(CModel* model, CVector position, CVector rotation, CVector scale);

	 
	//デフォルトコンストラクタ
	CPlayer();
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider *m, CCollider *o);
	//衝突処理
	void TaskCollision();
	//描画処理
	void Render();

};

#endif

