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
/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
	CSound mJump;
//	CBillBoard mBillBoard;
public:
	//�}�b�v�̃C���X�^���X
	CMap mMap;


	CModel mModel;
	CModel mModel2;
	CModel mModel3;
	CModel mModel4;
	CModel mModel5;
	CModel mModel6;
	CModel mModel7;

	//�L�����N�^�̃C���X�^���X
	CXPlayer mPlayer;

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�`�揈��
	void Render();

};

#endif
