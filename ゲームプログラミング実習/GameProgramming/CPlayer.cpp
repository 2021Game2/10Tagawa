//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include "CKey.h"
//
#include "CBullet.h"
//
#include "CTaskManager.h"
//
#include "CCollisionManager.h"
//
#include "CUtil.h"
//
#include "CEffect.h"

#include "CCharacter.h"

#include "CEnemy.h"

#include "CCamera.h"


CPlayer *CPlayer::spThis = 0;

#define _USE_MATH_DEFINES
#include <math.h>

#include "CEffect.h"
#define G -0.5	//�d��
#define HP 10	//HP
#define INITIALIZE 0	//������


CPlayer::CPlayer(CModel* model, CVector position,
	CVector rotation, CVector scale)
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f)
, mCount(0)
, mHp(HP)

{
	mTag = EPLAYER;	//�^�O�̐ݒ�
	spThis = this;
	//�e�N�X�`���t�@�C���̓ǂݍ��݁i1�s64��j
	mText.LoadTexture("FontWhite.tga", 1, 64);

	mpModel = model;
}

//�X�V����
void CPlayer::Update() {

	//�J�����̍��E�ƑO��̃x�N�g�����擾
	CVector SideVec = Camera.GetMat().GetXVec();
	CVector FrontVec = Camera.GetMat().GetZVec();
	//�����ړ��̓J�b�g����
	//SideVec.mY = 0.0f;
	//FrontVec.mY = 0.0f;
	//���K������
	SideVec.Normalize();
	FrontVec.Normalize();


	float speed = 0.3f;
	CVector Move(0, 0, 0);



	//A�L�[���͂ŉ�]
	if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		//mPosition.mX += 1;
		Move -= SideVec;

	}
	if (CKey::Push('D')) {
		//Y���̉�]�l�𑝉�
		//mPosition.mX -= 1;
		Move += SideVec;

	}
	//W�L�[���͂ŉ�]
	if (CKey::Push('W')) {
		//Y���̉�]�l�𑝉�
		//mPosition.mY += 1;
		Move += FrontVec;

	}
	if (CKey::Push('S')) {
		//Y���̉�]�l�𑝉�
		//mPosition.mY -= 1;
		Move -= FrontVec;

	}

	//����L�[���͂őO�i
	if (CKey::Push(VK_UP)) {
		//Z��������1�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	//�ړ��ʐ��K���@��������Ȃ��Ǝ΂߈ړ��������Ȃ��Ă��܂��̂Œ���
//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
	Move.Normalize();
	//���s�ړ���
	Move = Move * speed;


	//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
	//�[���x�N�g���v�Z
	Check tCheck = CUtil::GetCheck2D(Move.mX, Move.mZ, 0, 0, mRotation.mY * (M_PI / 180.0f));

	//��]���x�@degree�ɒ���
	float turnspeed = (180.0f / M_PI) * 0.5f;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//�ړ������փL��������������
	if (tCheck.cross > 0.0f) {
		mRotation.mY += tCheck.turn * turnspeed;
	}
	if (tCheck.cross < 0.0f) {
		mRotation.mY -= tCheck.turn * turnspeed;
	}

	//���W�ړ�
	mPosition += Move;


	mPosition += Move;


	if (mCount > 0)
	{
		mCount--;
	}

	//mPosition.mY -= 0.03f;

	Camera.SetTarget(mPosition);


	//CTransform�̍X�V
	CTransform::Update();
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
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
				if (o->mpParent->mTag == EENEMY) {
					mHp -= 2;
					if (mHp == 0) {
						mEnabled = false;
					}
				}
				if (o->mpParent->mTag == EROCK) {
					mPosition = mPosition + adjust;
				}
				if (o->mpParent->mTag == EENEMY) {
					mPosition = mPosition + adjust;
				}

			}
		}
		//����̃R���C�_���O�p�R���C�_�̎�
		else if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			CCollider::CollisionTriangleSphere(o, m, &adjust);

			//�ʒu�̍X�V(mPosition + adjust)

			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
		}
		break;
	}
}


//�Փˏ���
void CPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mColSphereHead.ChangePriority();
	mColSphereBody.ChangePriority();

	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mColSphereHead, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereBody, COLLISIONRANGE);
}

void CPlayer::Render()
{
	//�e�̕`�揈��
	CCharacter::Render();

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�i�ΐF�̔������j
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	//������ҏW�G���A�̍쐬
	char buf[64];

	//Y���W�̕\��
	//������̐ݒ�
	sprintf(buf, "PY:%7.2f", mPosition.mY);
	//������̕`��
	mText.DrawString(buf, 100, 30, 8, 16);

	//X����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RX:%7.2f", mRotation.mX);
	//������̕`��
	mText.DrawString(buf, 100, 0, 8, 16);
	
	//Y����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RY:%7.2f", mRotation.mY);
	//������̕`��
	mText.DrawString(buf, 100, -100, 8, 16);

	//2D�̕`��I��
	CUtil::End2D();

}