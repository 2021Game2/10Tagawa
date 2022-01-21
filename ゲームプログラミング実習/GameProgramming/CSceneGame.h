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


	CModel mModel;	//sphere
	CModel mModel2;	//sea
	CModel mModel3;	//trash
	CModel mModel4;	//rock1
	CModel mModel5;	//rock2
	CModel mModel6;	//rock3
	CModel mModel7;	//SeaWeed
	CModel mModel8;	//Submarine1
	CModel mModel9;	//trash2


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
