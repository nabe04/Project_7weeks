#pragma once

#include "actor.h"
//*****************************************************************
//
//
//						�v���C���[
//
//
//******************************************************************

////--�萔�錾--////
//Debug�p
#ifdef  DEBUG_TEX
#define DEBUG_PLAYER_SIZE (64)
#endif // DEBUG


////--�v���C���[����N���X--////
class Player :public Actor
{
private:
	bool key_trg = false;

public :
	void move(OBJ2D* obj);
	void fixPos(OBJ2D* obj) override;

	int storePlayer[1];
};

extern Player player;

////--�����A���S���Y��--////
class ErasePlayer :public EraseAlg
{
	void erase(OBJ2D* obj);
};

////--PlayerManager�N���X--////
class PlayerManager :public OBJ2DManager
{
private:
	//--�����o�ϐ�--//

public:
	//OBJ2DManager�N���X�̂��̂��Ăяo�����Ηǂ��̂ŁA���L�I�[�o�[���C�h�͕s�v�ł���
};