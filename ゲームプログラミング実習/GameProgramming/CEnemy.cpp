#include "CEnemy.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define HP 10	//�ϋv�l

int CEnemy::sCount = 0;	//�C���X�^���X��
#define ATTACKLAG 100	//�U���J�n�܂ł̃��O
#define HP 10

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy::CEnemy(CModel *model, CVector position,
	CVector rotation, CVector scale)
: mCollider1(this, &mMatrix, CVector(0.0f, 0.5f, 0.0f), 5.0f)
, mHp(HP)
, mAttack(false)
, mAttackLag(ATTACKLAG)
,mCnt(30)
,kai(5)
,fkai(5)
,max(5)
,min(0)
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


}

//�X�V����
void CEnemy::Update() {
	//HP��0�ȉ��̎��@���j
	if (mHp <= 0)
	{
		mTag = EENEAT;

		//15�t���[�����ɃG�t�F�N�g
		//if (mHp % 60 == 0)
			//�G�t�F�N�g����
			new CEffect(mPosition, 5.0f, 5.0f, "exp.tga", 4, 4, 2);
		////���~������
		//mPosition.mY -= 0.03f;
		CTransform::Update();	//�s��X�V
		return;	//�Ăь��֖߂�

		
	}


	srand((unsigned)time(NULL)); //�����̎d�g�݂��������B
	for (fkai = 5; fkai <= kai; fkai = fkai + 1)	//kai���J��Ԃ�
	{
		ran = (rand() % (max - min + 1)) + min; //�����̐���
	}
			mPosition.mY = ran;
			mPosition.mX = ran;

	return;

	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	//mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;
}
//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy::Collision(CCollider *m, CCollider *o) {
	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//����̃R���C�_�^�C�v�̔���
	switch (o->mType)
	{	
	case CCollider::ESPHERE: //���R���C�_�̎�
//		if (o->mpParent->mTag == EENEMY)
//			return;
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			if (o->mpParent->mTag == EPLAYER) 
			{
				//3�b��ɔ���
				mCnt -=1;
				if (mCnt == 0) {
					mHp -= 1;
					mCnt = 30;
				}
				return;
			}

		else {
				mCnt = 30;
				mHp = 10;
			}
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
			//���j�Œn�ʂɏՓ˂���Ɩ���
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}

	//mCollider1.mpMatrix = &mpCombinedMatrix[1];
}

void CEnemy::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
