#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CTreasure.h"

CTreasure::CTreasure(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 0.5f, 0.0f), 5.0f)
{

	mTag = EITEM;

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
void CTreasure::Update() {
	//HP��0�ȉ��̎��@���j

		CTransform::Update();	//�s��X�V
		return;	//�Ăь��֖߂�

	//�s����X�V
	CTransform::Update();
}


//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CTreasure::Collision(CCollider* m, CCollider* o) {
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
			}

		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}

	//mCollider1.mpMatrix = &mpCombinedMatrix[1];
}

void CTreasure::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
