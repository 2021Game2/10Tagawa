#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "CCamera.h"
#include "CUtil.h"


#define HP 10	//�ϋv�l

int CEnemy2::sCount = 0;	//�C���X�^���X��

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy2::CEnemy2(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 8.0f)
	, mHp(HP)
	, mAttack(false)
	, mCnt(20)
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
void CEnemy2::Update() {
	//HP��0�̎��@���j
	if (mHp = 0)
	{
		mTag = EENEAT;

			//�G�t�F�N�g����
		new CEffect(mPosition, 5.0f, 5.0f, "exp.tga", 4, 4, 2);

		CTransform::Update();	//�s��X�V
		//return;	//�Ăь��֖߂�

		mEnabled = false;

	}

	int i;
	srand((unsigned)time(NULL)); //�����̎d�g�݂�������

	for (i = 0; i <= 1; i++)	//1��J��Ԃ�
	{
		ran = ((rand() % (max - min + 1)) / 4.0 - 0.25) / 10; //�����̐���

		mPosition.mY += ran;
		//mPosition.mX += ran;
		//mPosition.mZ += ran;

		CEnemy2::mMoving = true;

		if (mPosition.mX > 10) {
			mPosition.mX - 1;
		}
	}


	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	//mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;
}


//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy2::Collision(CCollider* m, CCollider* o) {
	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//����̃R���C�_�^�C�v�̔���
	switch (o->mType)
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//����̃R���C�_�����R���C�_�̎�
		CVector adjust;
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				if (o->mpParent->mTag == EPLAYER) {
					////1�b��ɔ���
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
		//case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		//	//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		//	if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		//	{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
		//		mPosition = mPosition + adjust;
		//		//���j�Œn�ʂɏՓ˂���Ɩ���
		//		if (mHp <= 0)
		//		{
		//			mEnabled = false;
		//		}
		//	}
		//	break;
		//}

		//mCollider1.mpMatrix = &mpCombinedMatrix[1];
	}
}


void CEnemy2::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
