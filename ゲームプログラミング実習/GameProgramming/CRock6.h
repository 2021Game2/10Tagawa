#ifndef CROCK6_H
#define CROCK6_H
//コライダクラスのインクルード
#include "CCollider.h"

class CRock6 : public CCharacter {

	//CText mFont;

public:
	//コライダ
	CCollider mCollider1;

	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CRock6(CModel* model, CVector position, CVector rotation, CVector scale);


	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};

#endif


