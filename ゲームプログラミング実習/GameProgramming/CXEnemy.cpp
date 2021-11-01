#include "CXEnemy.h"
#include "main.h"
#include "CCamera.h"
#include "CUtil.h"

int CXEnemy::mCount;

CXEnemy::CXEnemy()
	:mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 5.0f)
	, mCflag(false)

{
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	//��
	mColSphereHead.mpMatrix = &mpCombinedMatrix[1];

//	mText.LoadTexture("FontWhite.tga", 1, 64);

}

void CXEnemy::Update() {

	//�s����X�V
	CXCharacter::Update();

}
void CXEnemy::Render() {

	CXCharacter::Render();


}
void CXEnemy::Render2D()
{
	CVector ret;

	Camera.WorldToScreen(&ret, mPosition);

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	//������̕`��
	mFont.DrawString("TEST", ret.mX, ret.mY, 8, 16);


	//2D�̕`��I��
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
				if (CCollider::Collision(m, o))
				{
					////�U���t���O������
					//mAttack == true;
					//mAttackLag--;
					//if (mAttack == true && mAttackLag == 0) {


					//}
					//return;
				}
			}
		}
	}
}
