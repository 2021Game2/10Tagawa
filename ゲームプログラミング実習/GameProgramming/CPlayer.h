#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//
#include "CBullet.h"
//
#include "CColliderLine.h"
//
#include "CText.h"
/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CCharacter {
public:

	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��

	int mCount;
	int mHp;	//�q�b�g�|�C���g

	CCollider mCollider;
	CText mText;
	static CPlayer *spThis;

	CPlayer(CModel* model, CVector position, CVector rotation, CVector scale);

	 
	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider *m, CCollider *o);
	//�Փˏ���
	void TaskCollision();
	//�`�揈��
	void Render();

};

#endif

