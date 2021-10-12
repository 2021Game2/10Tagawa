#ifndef CMINE_H
#define CMINE_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CMine : public CCharacter {
public:
	static int sCount;	//インスタンス数
	int mHp;	//ヒットポイント

	//コライダ
	CCollider mCollider1;


	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CMine(CModel* model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();
	////確認用メソッド　削除予定
	//void CEnemy::Render() {
	//	CCharacter::Render();
	//	mCollider1.Render();
	//	mCollider2.Render();
	//	mCollider3.Render();
	//}
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};

#endif
