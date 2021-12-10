#include "CRock4.h"
#include "CCollisionManager.h"
#include "CColliderMesh.h"


//�R���X�g���N�^
//CTrash(���f��, �ʒu, ��], �g�k)
CRock4::CRock4(CModel* model, CVector position,
	CVector rotation, CVector scale)
	//: mCollider1(this, &mMatrix, CVector(0.0f, -0.1f, 0.0f), 7.7f)
{

	mTag = EROCK;

	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�

	//�D��x��1�ɕύX����
	mPriority = 1;

	CTransform::Update();

	//mFont.LoadTexture("FontG.png", 1, 4096 / 64);
	mCollider1.Set(this, &mMatrix, mpModel);


}

//�X�V����
void CRock4::Update() {
	mTag = EENEAT;
	CTransform::Update();	//�s��X�V
	return;	//�Ăь��֖߂�

//�s����X�V
	CTransform::Update();
}


//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CRock4::Collision(CCollider* m, CCollider* o) {

}

void CRock4::TaskCollision()
{
}
