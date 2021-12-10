#ifndef CROCK4_H
#define CROCK4_H
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"

class CRock4 : public CCharacter {

	CMatrix mMatrixCol;

public:
	//�R���C�_
	CCollider mCollider1;

	//�R���X�g���N�^
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CRock4(CModel* model, CVector position, CVector rotation, CVector scale);
	CRock4 Set();

	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};

#endif
