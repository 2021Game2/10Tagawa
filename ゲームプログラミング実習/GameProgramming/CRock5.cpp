#include "CRock5.h"
#include "CCollisionManager.h"

//�R���X�g���N�^
//CTrash(���f��, �ʒu, ��], �g�k)
CRock5::CRock5(CModel* model, CVector position,
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
	mCollider2.Set(this, &mMatrix, mpModel);


}

//�X�V����
void CRock5::Update() {
	mTag = EENEAT;
	CTransform::Update();	//�s��X�V
	return;	//�Ăь��֖߂�

//�s����X�V
	CTransform::Update();
}


//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CRock5::Collision(CCollider* m, CCollider* o) {

}

void CRock5::TaskCollision()
{
}
