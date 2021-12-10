#ifndef CROCK5_H
#define CROCK5_H
//コライダクラスのインクルード
#include "CCollider.h"
#include "CColliderMesh.h"

class CRock5 : public CCharacter {

	//CText mFont;

public:
	//コライダ
	CColliderMesh mCollider1;

	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CRock5(CModel* model, CVector position, CVector rotation, CVector scale);


	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};

#endif

