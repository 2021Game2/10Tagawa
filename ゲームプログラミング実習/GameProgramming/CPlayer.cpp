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
//
#include <math.h>
//
#include "CInput.h"

CPlayer *CPlayer::spThis = 0;

#define FIRECOUNT 15	//���ˊԊu

#define MOS_POS_X 400	//�}�E�X���W��X�␳
#define MOS_POS_Y 300	//�}�E�X���W��Y�␳
#define MOUSE_X_LIM 1024	//�}�E�XX���W�͈̔�
#define MOUSE_Y_LIM 768		//�}�E�XY���W�͈̔�

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f)
, mFireCount(0)
{
	mTag = EPLAYER;	//�^�O�̐ݒ�
	spThis = this;
	//�e�N�X�`���t�@�C���̓ǂݍ��݁i1�s64��j
	mText.LoadTexture("FontWhite.tga", 1, 64);
	//�}�E�X�J�[�\�����W�̎擾
	

}

//�X�V����
void CPlayer::Update() 
{
	//A�L�[���͂ŉ�]
	if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation.mY += 1;
	}
	if (CKey::Push('D')) {
		//Y���̉�]�l�𑝉�
		mRotation.mY -= 1;
	}
	//����L�[���͂őO�i
	if (CKey::Push(VK_UP)) {
		//Z��������1�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	//S�L�[���͂ŏ����
	if (CKey::Push('S')) {
		//X���̉�]�l�����Z
		mRotation.mX -= 1;
	}
	//W�L�[���͂ŏ����
	if (CKey::Push('W')) {
		//X���̉�]�l�����Z
		mRotation.mX += 1;
	}

	if (mFireCount > 0)
	{
		mFireCount--;
	}

	//�X�y�[�X�L�[���͂Œe����
	if (CKey::Push(VK_SPACE) && mFireCount == 0) {
		mFireCount = FIRECOUNT;
		CBullet *bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
		bullet->mRotation = mRotation;
		bullet->Update();
//		TaskManager.Add(bullet);
	}
	//�}�E�X�J�[�\�����W�̎擾
	CInput::GetMousePosD(&mMx, &mMy);

	int mx, my;//�}�E�X�J�[�\�����W�擾�p
		//�}�E�X�J�[�\�����W�̎擾
		CInput::GetMousePos(&mx, &my);

		//�}�E�X�N���b�N���o
		if (CKey::Push(VK_LBUTTON))
		{
			//�}�E�X���W�R���\�[���o��
			printf("%d,%d\n", mx, my);
		}

		//�Q�[����ʒ��S����̍��W�֕ϊ�����
		mx -= MOS_POS_X;
		my = MOS_POS_Y - my;

		//�v���C���[�ƃ}�E�X���W�Ƃ̍������߂�
		mx -= x;
		my -= y;

		//�����������ق��ֈړ�������
		if (abs(mx) > abs(my))
		{
			//X���ňړ�
			if (mx < 0)
			{
				//���ֈړ�
				x -= 3;
				mFx = -1;
				mFy = 0;
			}
			else
			{
				//�E�ֈړ�
				x += 3;
				mFx = 1;
				mFy = 0;
			}
		}

		else
		{
			//Y���ňړ�
			if (my < 0)
			{
				//���ֈړ�
				y -= 3;
				mFx = 0;
				mFy = -1;
			}
			else
			{
				//��ֈړ�
				y += 3;
				mFx = 0;
				mFy = 1;
			}
		}

		//X�������̈ړ�
//�O����E�ɂ���ΉE�ֈړ�
		if (mMx < mx)
		{
			x += mx - mMx;
		}
		else if (mMx > mx)
		{
			x += mx - mMx;
		}

		//Y�������̈ړ�
		//�O���艺�ɂ���Ή��ֈړ�
		if (mMy < my)
		{
			y -= my - mMy;
		}
		else if (mMy > my)
		{
			y -= my - mMy;
		}

		//���E�͈̔͂��ł�Ɣ��Β[�ֈړ�������
		if (my > MOUSE_Y_LIM)
		{
			my = 1;
		}
		else if (my <= 0)
		{
			my = MOUSE_Y_LIM - 1;
		}

		//���W��ޔ�����
		mMx = mx;
		mMy = my;

		//�}�E�X�J�[�\�����W�̍X�V
		CInput::SetMousePosD(mx, my);


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
	case CCollider::ELINE://�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition - adjust * -1;
			//�s��̍X�V
			CTransform::Update();
		}
		break;
	case CCollider::ESPHERE:
		//����̃R���C�_�����R���C�_�̎�
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				//�G�t�F�N�g����
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			}
		}
		break;
	}
}
//�Փˏ���
void CPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
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