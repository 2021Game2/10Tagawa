#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CBillBoard.h"
#include "CBillBoard2.h"
#include "CSound.h"
#include "CMap.h"
#include "CModel.h"
#include "CColliderTriangle.h"
/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
	CSound mJump;
//	CBillBoard mBillBoard;
public:
	//�}�b�v�̃C���X�^���X
	CMap mMap;


	CModel mModel;	//sphere
	CModel mModel2;	//sea
	CModel mModel3;	//trash
	CModel mModel4;	//rock1
	CModel mModel5;	//rock2
	CModel mModel6;	//rock3
	CModel mModel7;	//SeaWeed
	CModel mModel8;	//Submarine1
	CModel mModel9;	//trash2


	CColliderTriangle mColliderTriangle;

	//���̃V�[���̎擾
	EScene GetNextScene();

	char buf[10];


	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�`�揈��
	void Render();

};

#endif
