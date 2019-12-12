#pragma once
#include <DirectXMath.h>

#define DEBUG_			//文字などのデバックのifdefに使用
#define DEBUG_TEX		//テクスチャのデバックのifdefに使用

//*********************************************//
//		スクリーン設定 & 汎用的変数設定		   //
//*********************************************//

#define SCREEN_WIDTH	(960)
#define SCREEN_HEIGHT	(540)
#define KEY_MAX			(256)

// 角度をラジアンに
#define ToRadian(x)     DirectX::XMConvertToRadians(x)  

namespace n_setup
{
	//int型Vector構造体
	struct Vector2I
	{
		int x;
		int y;
	};

	//float型Vector構造体
	struct Vector2F
	{
		float x;
		float y;
	};

	//bool型のvector構造体
	struct Vector2B
	{
		bool x;
		bool y;
	};

	//colorの値を入れる構造体
	struct Color4I
	{
		int r;	//Red
		int g;	//Green
		int b;	//Blue
		int a;	//Alpha
	};
}

//汎用的な関数
namespace n_general_function
{
	//引数をFPS値で返す
	inline int setTimer(const int time) noexcept
	{
		return time * 60;
	}
}
