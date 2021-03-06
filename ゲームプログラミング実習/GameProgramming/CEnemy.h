#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
#include "CText.h"

/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy : public CCharacter {

	//CText mFont;

public:
	static int sCount;	//インスタンス数
	int mHp;	//ヒットポイント
	int mAttack;	//攻撃フラグ
	int mAttackLag;		//攻撃フラグが立った後の攻撃開始までのラグ
	int mCnt;
	bool mMoving;			//移動状態かどうか返すフラグ

	//乱数
	float ran;	//乱数の値
	int max;	//最大
	int min;	//最小

	//コライダ
	CCollider mCollider1;

	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CEnemy(CModel *model, CVector position, CVector rotation, CVector scale);


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
	void Collision(CCollider *m, CCollider *o);
	void TaskCollision();
	//void Render2D();
};

#endif
