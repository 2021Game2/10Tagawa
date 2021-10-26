#include "CXEnemy.h"
#include "main.h"
#include "CCamera.h"
#include "CUtil.h"
CXEnemy::CXEnemy()
	:mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 1.5f)
{
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[1];

//	mText.LoadTexture("FontWhite.tga", 1, 64);

}

void CXEnemy::Update() {

	//行列を更新
	CXCharacter::Update();

}
void CXEnemy::Render() {

	CXCharacter::Render();


}
void CXEnemy::Render2D()
{
	CVector ret;

	Camera.WorldToScreen(&ret, mPosition);

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	//文字列の描画
	mFont.DrawString("TEST", ret.mX, ret.mY, 8, 16);


	//2Dの描画終了
	CUtil::End2D();
}
void CXEnemy::Collision(CCollider* m, CCollider* o)
{
	if (m->mType == CCollider::ESPHERE)
	{
		if (o->mType == CCollider::ESPHERE)
		{
			if (o->mpParent->mTag == EPLAYER)
			{
				if (o->mTag == CCollider::ESWORD)
				{
					if (CCollider::Collision(m, o))
					{
						//30フレームかけてダウンし、繰り返さない
						ChangeAnimation(11, false, 30);
					}
				}
			}
		}
	}
}
