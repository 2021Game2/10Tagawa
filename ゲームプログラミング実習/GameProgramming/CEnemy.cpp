#include "CEnemy.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "CCamera.h"
#include "CUtil.h"


int CEnemy::sCount = 0;	//�C���X�^���X��
#define HP 10

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy::CEnemy(CModel *model, CVector position,
	CVector rotation, CVector scale)
: mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 8.0f)
, mHp(HP)
, mAttack(false)
,mCnt(30)
, max(2)
, min(0)
{
	sCount++;

	mTag = EENEMY;

	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�

	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����

	//mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

//�X�V����
void CEnemy::Update() {

	//HP��0�ȉ��̎��@���j
	if (mHp = 0)
	{

			//�G�t�F�N�g����
			new CEffect(mPosition, 5.0f, 5.0f, "exp.tga", 4, 4, 2);
			mTag == EENEAT;

		CTransform::Update();	//�s��X�V
		return;	//�Ăь��֖߂�
	}



	int i;
	srand((unsigned)time(NULL)); //�����̎d�g�݂�������

	for (i = 0; i <= 1; i++)	//1��J��Ԃ�
	{
		ran = ((rand() % (max - min + 1)) / 4.0 - 0.25)/5; //�����̐���

		//mPosition.mY += ran;
		mPosition.mX += ran;
		//mPosition.mZ += ran;

		CEnemy::mMoving = true;

		if (mPosition.mX > 10) {
			mPosition.mX - 1;
		}
	}

	//�s����X�V
	CTransform::Update();
}


//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy::Collision(CCollider* m, CCollider* o) {
	//���肪�T�[�`�̎��͖߂�
	//if (o->mTag == CCollider::ESEARCH)
	//{
	//	return;
	//}
	//����̃R���C�_�^�C�v�̔���
	switch (m->mType) {
	case CCollider::ESPHERE:
		//����̃R���C�_�����R���C�_�̎�
		CVector adjust;
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				if (o->mpParent->mTag == EPLAYER) {
					mPosition = mPosition + adjust;

					////3�b��ɔ���
					//mCnt -= 1;
					//if (mCnt == 0) {
						mHp -= HP;
					//	mCnt = 30;
					//}
					//return;
					mEnabled = false;
				}
				if (o->mpParent->mTag == EROCK) {
					mPosition = mPosition + adjust;
				}
			}
		}
		break;
	}
}


void CEnemy::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}


//void Render2D() {
//	CVector ret;
//	Camera.WorldToScreen(&ret, mPosition);
//
//	//2D�`��J�n
//	CUtil::Start2D(0, 800, 0, 600);
//
//	//������̕`��
//	mFont.DrawString("TEST", ret.mX, ret.mY, 8, 16);
//
//
//	//2D�̕`��I��
//	CUtil::End2D();
//
//}
