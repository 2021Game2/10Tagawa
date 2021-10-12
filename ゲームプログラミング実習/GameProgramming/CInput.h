#ifndef CINPUT_H
#define CINPUT_H

#include "GLFW/glfw3.h"
class CInput {
	//�E�C���h�D�|�C���^
	static GLFWwindow* mpWindow;
public:
	/*
	������
	Init(�E�C���h�E�|�C���^)
	*/
	static void Init(GLFWwindow* w);
	/*
	GetMousePos(X���W�|�C���^�AY���W�|�C���^)
	�E�B���h�E�̍�������_�Ƃ���
	�}�E�X�J�[�\���̍��W���A�����ɐݒ肷��
	*/
	static void GetMousePos(int* px, int* py);
	/*
	�}�E�X�J�[�\���̍��W���擾����
	GetMousePos(�w���W�|�C���^�A�x���W�|�C���^)
	�f�B�X�v���C�̍�������_(0,0)�Ƃ����A
	�}�E�X�J�[�\���̍��W�������ɐݒ肷��
	��ʉE��������X���v���X
	��ʍ�����Y���v���X
	*/
	static void GetMousePosD(int* px, int* py);

	/*
	�}�E�X�J�[�\���̍��W��ݒ肷��
	SetCursorPosD(X���W�AY���W)
	�f�B�X�v���C�̍��オ���_(0,0)
	*/
	static void SetMousePosD(int x, int y);

};
#endif