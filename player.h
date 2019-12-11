#pragma once

#include "actor.h"
//*****************************************************************
//
//
//						プレイヤー
//
//
//******************************************************************

////--定数宣言--////
//Debug用
#ifdef  DEBUG_TEX
#define DEBUG_PLAYER_SIZE (64)
#endif // DEBUG


////--プレイヤー操作クラス--////
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

////--消去アルゴリズム--////
class ErasePlayer :public EraseAlg
{
	void erase(OBJ2D* obj);
};

////--PlayerManagerクラス--////
class PlayerManager :public OBJ2DManager
{
private:
	//--メンバ変数--//

public:
	//OBJ2DManagerクラスのものが呼び出されれば良いので、下記オーバーライドは不要である
};