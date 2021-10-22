#include "CInput.h"
#include <Windows.h>

GLFWwindow* CInput::mpWindow = nullptr;

void CInput::Init(GLFWwindow* w) {
	mpWindow = w;
}

void CInput::GetMousePos(int* px, int* py) 
{
	double xpos,ypos;
	glfwGetCursorPos(mpWindow, &xpos, &ypos);
	*px = xpos;
	*py = ypos;
	return;
}

void CInput::GetMousePosD(int* px, int* py)
{
	POINT point;
	//WindowsAPI
	GetCursorPos(&point);
	*px = point.x;
	*py = point.y;
}

void CInput::SetMousePosD(int x, int y)
{
//WindowsAPI
	SetCursorPos(x, y);


}


