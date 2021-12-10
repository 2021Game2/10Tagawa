#ifndef CROCK4_H
#define CROCK4_H
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
#include "CColliderMesh.h"

class CRock4 : public CCharacter {
public:
	//�R���C�_
	CColliderMesh mCollider1;

	//�R���X�g���N�^
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CRock4(CModel* model, CVector position, CVector rotation, CVector scale);


	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};

#endif
