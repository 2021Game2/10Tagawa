#ifndef CTREASURE_H
#define CTREASURE_H

//コライダクラスのインクルード
#include "CCollider.h"

class CTreasure : public CCharacter {

	//CText mFont;

public:
	//コライダ
	CCollider mCollider1;

	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CTreasure(CModel* model, CVector position, CVector rotation, CVector scale);


	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};
#endif