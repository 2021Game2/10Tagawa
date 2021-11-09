#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter
{
public:
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭

	float mVj; //ジャンプ用変数
	int mJump; ///ジャンプ位置記憶
	bool mJflag;	//ジャンプフラグ(falseなら可能,trueなら不可)
	static bool CXPlayer::mJumping;	//プレイヤージャンプ中フラグ


	CXPlayer();

	/*
	初期化(Xモデルクラスのポインタ)
	*/
	void Init(CModelX* model);

	void Update();
};

#endif
