#ifndef CSCENETITLE_H
#define CSCENETITLE_H
#include "CScene.h"
#include "CText.h"

class CSceneTitle :public CScene {

public:


	char buf[10];

	CSceneTitle();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�`�揈��
	void Render();

	//���̃V�[���̎擾
	EScene GetNextScene();

};


#endif