#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter
{
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��

	float mVj; //�W�����v�p�ϐ�
	int mJump; ///�W�����v�ʒu�L��
	bool mJflag;	//�W�����v�t���O(false�Ȃ�\,true�Ȃ�s��)
	static bool CXPlayer::mJumping;	//�v���C���[�W�����v���t���O


	CXPlayer();

	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);

	void Update();
};

#endif
