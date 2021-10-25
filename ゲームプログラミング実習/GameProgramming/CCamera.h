#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"

/*
カメラクラス
*/
class CCamera {
public:

	//視点
	CVector mEye;
	CVector ex, ey, ez;

	//注視点
	CVector mCenter;
	CVector cx, cy, cz;

	//上方向
	CVector mUp;
	CVector ux, uy, uz;

	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);

	static int CameraPos;
	static CCamera* spThis;



	//カメラ適用
	void Render();
	void Update();
};

//カメラの外部参照
extern CCamera Camera;
#endif
