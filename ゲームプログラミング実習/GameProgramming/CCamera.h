#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"

/*
�J�����N���X
*/
class CCamera {
public:

	//���_
	CVector mEye;

	//�����_
	CVector mCenter;

	//�����
	CVector mUp;

	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);

	static int CameraPos;
	static CCamera* spThis;

	//�J�����K�p
	void Render();
	void Update();
};

//�J�����̊O���Q��
extern CCamera Camera;
#endif
