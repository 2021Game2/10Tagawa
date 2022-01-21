#include "CTrash.h"
#include "CCollisionManager.h"
#include "CSceneGame.h"
#include "CScore.h"


#define SCORE 100			//�X�R�A

//�R���X�g���N�^
//CTrash(���f��, �ʒu, ��], �g�k)
CTrash::CTrash(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider1(this, &mMatrix, CVector(0.5f, 0.5f, 0.0f), 1.5f)
	, mCnt(60)
{


	mTag = EITEM;

	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�

	//�D��x��1�ɕύX����
	mPriority = 1;

	//mFont.LoadTexture("FontG.png", 1, 4096 / 64);



}

//�X�V����
void CTrash::Update() {
	mTag = EITEM;

	mPosition.mY -= 0.1;
	if (mPosition.mY < 1) {
		mPosition.mY = 150;

		//	mCnt -= 1;
		//if (mCnt == 0) {
		//	mEnabled;
		//	}

	}
	CTransform::Update();	//�s��X�V
	return;	//�Ăь��֖߂�

//�s����X�V
	CTransform::Update();
}


//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CTrash::Collision(CCollider* m, CCollider* o) {
	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType) {
	case CCollider::ESPHERE:
		//����̃R���C�_�����R���C�_�̎�
		CVector adjust;
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				mPosition = mPosition + adjust;

				if (o->mpParent->mTag == EPLAYER) {
					CScore::mScore += SCORE;
					mPosition.mY = 150;

				}
			}
		}


		//����̃R���C�_���O�p�R���C�_�̎�
		else if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
		}
		break;
	}
}

void CTrash::TaskCollision()
{
	mCollider1.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
}
