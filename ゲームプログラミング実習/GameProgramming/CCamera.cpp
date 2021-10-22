#include "CCamera.h"
#include "glut.h"
#include "CPlayer.h"

#define CAMERAPOS 100

//ƒJƒƒ‰‚ÌŠO•”•Ï”
CCamera Camera;

extern CPlayer PlayerPos;

int CCamera::CameraPos = CAMERAPOS;

void CCamera::Set(const CVector &eye, const CVector &center,
	const CVector &up) {
	mEye = eye;
	mCenter = center;
	mUp = up;

	spThis = this;
}

void CCamera::Update() {
	CCamera::spThis->CameraPos = CameraPos + PlayerPos;

}

void CCamera::Render() {
	gluLookAt(mEye.mX, mEye.mY, mEye.mZ,
		mCenter.mX, mCenter.mY, mCenter.mZ,
		mUp.mX, mUp.mY, mUp.mZ);
}
