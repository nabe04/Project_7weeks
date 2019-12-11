#pragma once
#include "obj2d.h"

//�O���錾
class OBJ2D;

//****************************//
//		�A���S���Y���Ǘ�	  //
//****************************//

//--�ړ��A���S���Y���N���X(���ۃN���X)--//
class MoveAlg
{
public:
	virtual void move(OBJ2D* obj) = 0;	// �������z�֐������̂ŁAMoveAlg�^�̃I�u�W�F�N�g�͐錾�ł��Ȃ��i�h�������Ďg���j
};

//--�����A���S���Y���N���X(���ۃN���X)--//
class EraseAlg
{
public:
	virtual void erase(OBJ2D* obj) = 0;
};




