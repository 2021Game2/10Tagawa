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
	//キャラクタのインスタンス
	CXPlayer mPlayer;
	//敵のインスタンス
	CXEnemy mEnemy;

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//描画処理
	void Render();

};

#endif
