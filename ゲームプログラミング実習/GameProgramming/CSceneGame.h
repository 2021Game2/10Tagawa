#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CBillBoard.h"
#include "CBillBoard2.h"
#include "CSound.h"
#include "CMap.h"
#include "CModel.h"
#include "CColliderTriangle.h"
/*
ゲームのシーン
*/
class CSceneGame : public CScene {
	CSound mJump;
//	CBillBoard mBillBoard;
public:
	//マップのインスタンス
	CMap mMap;


	CModel mModel;
	CModel mModel2;
	CModel mModel3;
	CModel mModel4;
	CModel mModel5;
	CModel mModel6;
	CModel mModel7;
	CModel mModel8;

	CColliderTriangle mColliderTriangle;



	char buf[10];


	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//描画処理
	void Render();

};

#endif
