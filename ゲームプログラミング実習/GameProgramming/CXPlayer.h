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
	//CCollider mColSphereFoot;	//��


	float mVj; //�W�����v�p�ϐ�
	int mJump; ///�W�����v�ʒu�L��
	bool mJflag;	//�W�����v�t���O(false�Ȃ�\,true�Ȃ�s��)
	static bool CXPlayer::mJumping;	//�v���C���[�W�����v���t���O
	int mCount;
	int mHp;	//�q�b�g�|�C���g


	//�f�t�H���g�R���X�g���N�^
	CXPlayer();
	static CXPlayer* spThis;
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
	//�Փˏ���
	void TaskCollision();
	//�`�揈��
	void Render();

	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);

	void Update();
};



#endif
