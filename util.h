#pragma once
#include <algorithm>
#include <assert.h>

template <typename T>
inline void safe_delete(T*& p)
{
	if (p != nullptr)
	{
		delete (p);
		(p) = nullptr;
	}
}
//--------------------------------------------------------------
//  値を範囲内に収める関数
//--------------------------------------------------------------
//    引数：const float& v  入力する数値
//        ：const float& lo 最小値
//        ：const float& hi 最大値
//  戻り値：const float&    範囲内に収まった数値
//--------------------------------------------------------------
inline float clamp(const float v, const float lo, const float hi)
{
	assert(hi >= lo);
	return (std::max)((std::min)(v, hi), lo);
}