#include "CXPlayer.h"
#include "CKey.h"
#include "CCamera.h"
#include "CUtil.h"
#include "CCollisionManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "CEffect.h"
#define G -0.5	//�d��
#define VJ0 16	//�W�����v��
#define HP 10	//HP
#define INITIALIZE 0	//������

bool CXPlayer::mJumping;

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereFoot(this, nullptr, CVector(0.0f, -5.0f, 0.0f), 0.5f)

	, mJump(0)
	, mJflag(false)
	, mCount(1)
	, mHp(HP)


{
	//�^�O�Ƀv���C���[��ݒ肵�܂�
	mTag = EPLAYER;

	mJumping = false;

}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.mpMatrix = &mpCombinedMatrix[9];
	mColSphereHead.mpMatrix = &mpCombinedMatrix[12];
	mColSphereFoot.mpMatrix = &mpCombinedMatrix[15];

	mRotation.mY = 0.01f;
}

void CXPlayer::Update()
{
	if (mAnimationIndex == 3)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(4, false, 30);
		}
	}
	else if (mAnimationIndex == 4)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(0, true, 60);
		}
	}
	else
	{


		//��]�ړ� �ʏ̃o�C�I�ړ�

		//if (CKey::Push('A'))
		//{
		//	mRotation.mY += 2.0f;
		//}
		//if (CKey::Push('D'))
		//{
		//	mRotation.mY -= 2.0f;
		//}
		//if (CKey::Push(' '))
		//{
		//	ChangeAnimation(3, true, 30);
		//}
		//else if (CKey::Push('W'))
		//{
		//	ChangeAnimation(1, true, 60);
		//	mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		//}
		//else {
		//	ChangeAnimation(0, true, 60);
		//}

		//�J�������_�ړ��@�ʏ̖��o�ړ�

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


		if (CKey::Push('A'))
		{
			//			mRotation.mY += 2.0f;
			Move -= SideVec;
		}
		else if (CKey::Push('D'))
		{
			//			mRotation.mY -= 2.0f;
			Move += SideVec;
		}

		if (CKey::Push('W'))
		{
			Move += FrontVec;
			//			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		}

		else if (CKey::Push('S'))
		{
			Move -= FrontVec;
			//			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		}


		//if (CKey::Push('Q'))
		//{
		//	//Move += FrontVec;
		//				mPosition += CVector(0.0f, 0.05f, 0.0f) * mMatrixRotate;
		//}
		//else if (CKey::Push('X'))
		//{
		//	Move -= FrontVec;
		//				mPosition += CVector(0.0f, -0.05f, 0.0f) * mMatrixRotate;
		//}



		//if ()
		//{
		//	//�ʒu����
		//	CVector tpos = mPosition;
		//	tpos.mY += 2.0f;
		//	mVj = VJ0;
		//	mJflag = true;
		//	mJumping = true;

		//	ChangeAnimation(3, true, 30);
		//}else if (Move.Length() != 0.0f){
		//	ChangeAnimation(1, true, 60);
		//}else {
		//	ChangeAnimation(0, true, 60);
		//}
		//mPosition.mY += mVj;
		//if (mPosition.mY > mJump) {
		//	mVj += G;
		//}
		//else {
		//	mVj = INITIALIZE;
		//	mJump = INITIALIZE;
		//	mJflag = false;
		//	mJumping = false;
		//}


		//�ړ��ʐ��K���@��������Ȃ��Ǝ΂߈ړ��������Ȃ��Ă��܂��̂Œ���
		//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
		Move.Normalize();
		//���s�ړ���
		Move = Move*speed;

		
		//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
		//�[���x�N�g���v�Z
		Check tCheck = CUtil::GetCheck2D(Move.mX,Move.mZ,0,0, mRotation.mY*(M_PI/180.0f));
		
		//��]���x�@degree�ɒ���
		float turnspeed = (180.0f / M_PI)*0.5f;

		//�}�ȐU��Ԃ��}��
		if (tCheck.turn > 1.5f) tCheck.turn =1.5f;

		//�ړ������փL��������������
		if (tCheck.cross > 0.0f) {
			mRotation.mY += tCheck.turn * turnspeed;
		}
		if (tCheck.cross < 0.0f) {
			mRotation.mY -= tCheck.turn * turnspeed;
		}

		//���W�ړ�
		mPosition += Move;
	}


	//�����_�ݒ�
	Camera.SetTarget(mPosition);

	CXCharacter::Update();
}


void CXPlayer::Collision(CCollider* m, CCollider* o) {
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
					mHp -= HP;
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
void CXPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mColSphereHead.ChangePriority();
	mColSphereBody.ChangePriority();

	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mColSphereHead, COLLISIONRANGE); 
	CCollisionManager::Get()->Collision(&mColSphereBody, COLLISIONRANGE); 
}

void CXPlayer::Render()
{
	//�e�̕`�揈��
	CXCharacter::Render();

	////2D�̕`��J�n
	//CUtil::Start2D(-400, 400, -300, 300);
	////�`��F�̐ݒ�i�ΐF�̔������j
	//glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	////������ҏW�G���A�̍쐬
	//char buf[64];

	////Y���W�̕\��
	////������̐ݒ�
	//sprintf(buf, "PY:%7.2f", mPosition.mY);
	////������̕`��
	//mText.DrawString(buf, 100, 30, 8, 16);

	////X����]�l�̕\��
	////������̐ݒ�
	//sprintf(buf, "RX:%7.2f", mRotation.mX);
	////������̕`��
	//mText.DrawString(buf, 100, 0, 8, 16);

	////Y����]�l�̕\��
	////������̐ݒ�
	//sprintf(buf, "RY:%7.2f", mRotation.mY);
	////������̕`��
	//mText.DrawString(buf, 100, -100, 8, 16);

	////2D�̕`��I��
	//CUtil::End2D();

}