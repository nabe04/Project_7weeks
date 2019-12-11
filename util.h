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
//  �l��͈͓��Ɏ��߂�֐�
//--------------------------------------------------------------
//    �����Fconst float& v  ���͂��鐔�l
//        �Fconst float& lo �ŏ��l
//        �Fconst float& hi �ő�l
//  �߂�l�Fconst float&    �͈͓��Ɏ��܂������l
//--------------------------------------------------------------
inline float clamp(const float v, const float lo, const float hi)
{
	assert(hi >= lo);
	return (std::max)((std::min)(v, hi), lo);
}