#include "CMine.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"

#define HP 10	//�ϋv�l

int CMine::sCount = 0;	//�C���X�^���X��


//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CMine::CMine(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mHp(HP)
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
void CMine::Update() {
	//HP��0�ȉ��̎��@���j
	if (mHp <= 0)
	{
		mHp--;
		
		//���~������
		mPosition.mY -= 0.03f;
		CTransform::Update();	//�s��X�V
		return;	//�Ăь��֖߂�
	}

	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	mPosition = CVector(1.0f, 1.0f, 1.0f) * mMatrix;
}
//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CMine::Collision(CCollider* m, CCollider* o) {
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
			//�G�t�F�N�g����
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă��鎞�͖����ɂ���
			//mEnabled = false;
			mHp--;
			if (mHp == 0)
			{
				sCount--;
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
}

void CMine::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
