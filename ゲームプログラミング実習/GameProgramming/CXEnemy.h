#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CText.h"

class CXEnemy : public CXCharacter
{
	CText mFont;


public:
	//コライダの宣言
	CCollider mColSphereHead;	//頭

	CXEnemy();
	static int mCount;			//攻撃までのラグ
	bool mCflag;	//フラグ(falseなら可能,trueなら不可)


	/*
	初期化(Xモデルクラスのポインタ)
	*/
	void Init(CModelX* model);
	void Update();
	void Render();
	void Render2D();
	//衝突処理
	//m:自分のコライダ o:相手のコライダ
	void Collision(CCollider* m, CCollider* o);


};

#endif
