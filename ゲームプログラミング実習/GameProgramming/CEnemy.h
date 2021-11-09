#ifndef CENEMY_H
#define CENEMY_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
#include "CText.h"

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy : public CCharacter {

	//CText mFont;

public:
	static int sCount;	//�C���X�^���X��
	int mHp;	//�q�b�g�|�C���g
	int mAttack;	//�U���t���O
	int mAttackLag;		//�U���t���O����������̍U���J�n�܂ł̃��O
	int mCnt;

	//����
	int ran;	//�����̒l
	int max;	//�ő�
	int min;	//�ŏ�

	//�R���C�_
	CCollider mCollider1;

	//�R���X�g���N�^
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CEnemy(CModel *model, CVector position, CVector rotation, CVector scale);


	//�X�V����
	void Update();
	////�m�F�p���\�b�h�@�폜�\��
	//void CEnemy::Render() {
	//	CCharacter::Render();
	//	mCollider1.Render();
	//	mCollider2.Render();
	//	mCollider3.Render();
	//}
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider *m, CCollider *o);
	void TaskCollision();
	//void Render2D();
};

#endif
