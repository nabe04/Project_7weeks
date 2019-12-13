#pragma once
#include <DirectXMath.h>
#include "imgui.h"
#include "imgui_impl_dxlib.h"

#define DEBUG_			//�����Ȃǂ̃f�o�b�N��ifdef�Ɏg�p
#define DEBUG_TEX		//�e�N�X�`���̃f�o�b�N��ifdef�Ɏg�p
#define USE_IMGUI		//imgui�pifdef

//*********************************************//
//		�X�N���[���ݒ� & �ėp�I�ϐ��ݒ�		   //
//*********************************************//

#define SCREEN_WIDTH	(960)
#define SCREEN_HEIGHT	(540)
#define KEY_MAX			(256)

// �p�x�����W�A����
#define ToRadian(x)     DirectX::XMConvertToRadians(x)  

namespace n_setup
{
	//int�^Vector�\����
	struct Vector2I
	{
		int x;
		int y;
	};

	//float�^Vector�\����
	struct Vector2F
	{
		float x;
		float y;
	};

	//bool�^��vector�\����
	struct Vector2B
	{
		bool x;
		bool y;
	};

	//color�̒l������\����
	struct Color4I
	{
		int r;	//Red
		int g;	//Green
		int b;	//Blue
		int a;	//Alpha
	};
}

//�ėp�I�Ȋ֐�
namespace n_general_function
{
	//������FPS�l�ŕԂ�
	inline int setTimer(const int time) noexcept
	{
		return time * 60;
	}
}

