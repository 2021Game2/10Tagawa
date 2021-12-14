#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "Ckey.h"
//
#include "CMaterial.h"
//
#include "CCollisionManager.h"

#include"CEnemy.h"

#include "CEnemy2.h"

#include "CSea.h"

#include "CTrash.h"

#include "CRock4.h"

#include "CRock5.h"

#include "CRock6.h"

#include "CSeaweed.h"

#include "CColliderTriangle.h"

#include "CText.h"

#include "CScore.h"

//CMatrix Matrix;

CSceneGame::~CSceneGame()

 {

}

void CSceneGame::Init()
{
	mJump.Load("jump.wav");

//	mBillBoard.Set(CVector(0.0f, 5.0f, 0.0f), 1.0f, 1.0f);

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	CRes::sModelX.Load(MODEL_FILE);


	//�L�����N�^�[�Ƀ��f����ݒ�
	mPlayer.Init(&CRes::sModelX);
	mPlayer.mPosition = CVector(-10, 0, -50);

	mModel.Load("resorce\\sphere.obj","resorce\\sphere.mtl");
	mModel2.Load("resorce\\sea OBJ.obj", "resorce\\sea MTL.mtl");
	mModel3.Load("resorce\\trash.obj", "resorce\\trash.mtl");
	mModel4.Load("resorce\\rock1.obj", "resorce\\rock1.mtl");
	mModel5.Load("resorce\\rock2.obj", "resorce\\rock2.mtl");
	mModel6.Load("resorce\\rock3.obj", "resorce\\rock3.mtl");
	mModel7.Load("resorce\\SeaWeed.obj", "resorce\\SeaWeed.mtl");

						//(�E�� �㉺ �O���)
	new CEnemy(&mModel, CVector(0, 0, 0), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(5, 4, 5), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(20, 0, 20), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(-20, 2, 10), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy(&mModel, CVector(20, 0, 0), CVector(0, 0, 0), CVector(1, 1, 1));

	//���@�㉺
	new CEnemy2(&mModel, CVector(-10, 0, -20), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy2(&mModel, CVector(-20, 5, -10), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy2(&mModel, CVector(20, 5, -10), CVector(0, 0, 0), CVector(1, 1, 1));
	new CEnemy2(&mModel, CVector(10, 0, -10), CVector(0, 0, 0), CVector(1, 1, 1));

	//�X�e�[�W
	//new CSea(&mModel2, CVector(0, -3.3, 0), CVector(0, 0, 0), CVector(25, 25, 25));

	//�S�~��
	//new CTrash(&mModel3, CVector(2, 0, 0), CVector(0, 0, 0), CVector(1, 1, 1));


	new CRock4(&mModel4, CVector(8, -1, -41.5), CVector(0, 0, 0), CVector(0, 0, 0));


	new CRock5(&mModel5, CVector(-15, -1, 43), CVector(0, 0, 0), CVector(1, 1, 1));
	//new CRock5(&mModel5, CVector(50, 0, 37), CVector(0, 0, 0), CVector(1, 1, 1));
	//new CRock5(&mModel5, CVector(-38, 2, 33), CVector(0, 0, 0), CVector(1, 1, 1));
	//new CRock5(&mModel5, CVector(-15.5, 0, -15), CVector(0, 0, 0), CVector(1, 1, 1));
	//new CRock5(&mModel5, CVector(-36.5, 2, -25), CVector(0, 0, 0), CVector(1, 1, 1));
	//new CRock5(&mModel5, CVector(-15, -2, -40), CVector(0, 0, 0), CVector(1, 1, 1));


	new CRock6(&mModel6, CVector(-55, 5, -55), CVector(0, 0, 0), CVector(15, 15, 15));
	new CRock6(&mModel6, CVector(-55, 5, -30), CVector(0, 0, 0), CVector(15, 15, 15));
	new CRock6(&mModel6, CVector(-57, 0, -5), CVector(0, 0, 0), CVector(15, 15, 15));
	new CRock6(&mModel6, CVector(-55, 5, 10), CVector(0, 0, 0), CVector(15, 15, 15));
	new CRock6(&mModel6, CVector(-52, 0, 35), CVector(0, 0, 0), CVector(15, 15, 15));
	new CRock6(&mModel6, CVector(-50, 3, 60), CVector(0, 0, 0), CVector(15, 15, 15));



	//new CSeaweed(&mModel7, CVector(3, 0, 6), CVector(0, 0, 0), CVector(3, 3, 3));

	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�

	//�J����������
	Camera.Init();

}


void CSceneGame::Update() {

	if (CKey::Push(VK_ESCAPE)) {
		exit(0);
	}



	//�X�V
	CTaskManager::Get()->Update();
	//�Փˏ���
	CTaskManager::Get()->TaskCollision();


	Camera.Update();

	//mJump.Play();


//	mBillBoard.Update();
	return;
}

void CSceneGame::Render() {
//	mBillBoard.Render();
	
	Camera.Render();

	//�^�X�N�̕`��
	CTaskManager::Get()->Render();
	CTaskManager::Get()->Render2D();

	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);


	//��
	glColor4f(0.0f, 0.7f, 0.9f, 0.4f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glVertex2d(0, 600);
	glVertex2d(0, 0);
	glVertex2d(800, 0);
	glVertex2d(800, 600);
	glEnd();

	glDisable(GL_BLEND);

	//������̕`��
	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//mFont.DrawString("Score", 20, 20, 10, 20);
	//sprintf(buf, "%d", CScore::mScore);
	//mFont.DrawString(buf, 20, 20, 10, 20);


	//2D�̕`��I��
	CUtil::End2D();

}
