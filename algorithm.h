#pragma once
#include "obj2d.h"

//前方宣言
class OBJ2D;

//****************************//
//		アルゴリズム管理	  //
//****************************//

//--移動アルゴリズムクラス(抽象クラス)--//
class MoveAlg
{
public:
	virtual void move(OBJ2D* obj) = 0;	// 純粋仮想関数を持つので、MoveAlg型のオブジェクトは宣言できない（派生させて使う）
};

//--消去アルゴリズムクラス(抽象クラス)--//
class EraseAlg
{
public:
	virtual void erase(OBJ2D* obj) = 0;
};




