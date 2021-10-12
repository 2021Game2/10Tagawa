#ifndef CINPUT_H
#define CINPUT_H

#include "GLFW/glfw3.h"
class CInput {
	//ウインドゥポインタ
	static GLFWwindow* mpWindow;
public:
	/*
	初期化
	Init(ウインドウポインタ)
	*/
	static void Init(GLFWwindow* w);
	/*
	GetMousePos(X座標ポインタ、Y座標ポインタ)
	ウィンドウの左上を原点とした
	マウスカーソルの座標を、因数に設定する
	*/
	static void GetMousePos(int* px, int* py);
	/*
	マウスカーソルの座標を取得する
	GetMousePos(Ｘ座標ポインタ、Ｙ座標ポインタ)
	ディスプレイの左上を原点(0,0)とした、
	マウスカーソルの座標を引数に設定する
	画面右下方向がX軸プラス
	画面左下がY軸プラス
	*/
	static void GetMousePosD(int* px, int* py);

	/*
	マウスカーソルの座標を設定する
	SetCursorPosD(X座標、Y座標)
	ディスプレイの左上が原点(0,0)
	*/
	static void SetMousePosD(int x, int y);

};
#endif