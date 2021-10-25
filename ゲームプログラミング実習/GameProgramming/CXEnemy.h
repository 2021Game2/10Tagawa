#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CText.h"

class CXEnemy : public CXCharacter
{
	CText mFont;

;

	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
//	CCollider mColSphereSword;	//��

	CXEnemy();
	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);
	void Update();
	void Render();
	void Render2D();
	//�Փˏ���
	//m:�����̃R���C�_ o:����̃R���C�_
	void Collision(CCollider* m, CCollider* o);


};

#endif
