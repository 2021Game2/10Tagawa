#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CText.h"

class CXEnemy : public CXCharacter
{
	CText mFont;


public:
	//�R���C�_�̐錾
	CCollider mColSphereHead;	//��

	CXEnemy();
	static int mCount;			//�U���܂ł̃��O
	bool mCflag;	//�t���O(false�Ȃ�\,true�Ȃ�s��)


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
