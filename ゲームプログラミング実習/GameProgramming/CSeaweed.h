#ifndef CSEAWEED_H
#define CSEAWEED_H
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"

class CSeaweed : public CCharacter {

	//CText mFont;

public:
	//�R���C�_
	CCollider mCollider1;

	//�R���X�g���N�^
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CSeaweed(CModel* model, CVector position, CVector rotation, CVector scale);

	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};

#endif



