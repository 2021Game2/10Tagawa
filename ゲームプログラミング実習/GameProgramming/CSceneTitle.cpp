#include "CSceneTitle.h"
#include "CKey.h"

CSceneTitle::CSceneTitle()
{

}

void CSceneTitle::Init()
{
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);
	mScene = ETITLE;

}

void CSceneTitle::Update() {
	mFont.DrawString("TITLE", -200, 0, 50, 50);
	mFont.DrawString("Push ENTER Key", -200, 100, 16, 16);

	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EGAME;
	}

}

//次のシーンの取得
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}



