#include <algorithm>
#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "actor.h"
#include "player.h"
#include "load_texture.h"
#include "bg.h"
#include "bg_maps.h"
#include "scene.h"
#include "game.h"

using namespace n_setup;

Actor::Actor():actorParam()
{
	//actorParamの各メンバのデフォルト値を設定

	actorParam.accel		= {0.5f,0.5f};		//縦横方向の加速度
	actorParam.speedMax		= 4.0f;				//横方向の最大速度
	actorParam.gravityMax	= 8.0f;				//縦方向の最大速度

	actorParam.ladderAccel	= 0.5f;				//梯子の加速度
}

//--プレイヤー移動処理--//

//Y方向処理
void Actor::playerMoveY(OBJ2D* obj)
{
	GetHitKeyStateAll(key);

	obj->grandFrag = false;

	if (obj->ladderFrag)
	{
		if (key[KEY_INPUT_UP])
		{
			obj->gravity -= actorParam.ladderAccel;
		}
		else if (key[KEY_INPUT_DOWN])
		{
			obj->gravity += actorParam.ladderAccel;
		}
		else
		{
			if (obj->gravity > 0)
			{
				obj->gravity -= actorParam.ladderAccel / 2;
				obj->gravity  = (std::max)(obj->gravity, 0.0f);
			}
			if (obj->gravity < 0)
			{
				obj->gravity += actorParam.ladderAccel / 2;
				obj->gravity  = (std::min)(obj->gravity, 0.0f);
			}
		}
	}
	else
	{
		//速度に加速度を加える
		obj->gravity += actorParam.accel.y;
	}

	//最大速度チェック
	float maxGravity = actorParam.gravityMax;
	if (obj->ladderFrag)	maxGravity /= 4;

	obj->gravity = clamp(obj->gravity, -maxGravity, maxGravity);

	//位置更新
	float oldY      = obj->pivot.y;			    //移動前の位置を保持
	obj->pivot.y    += obj->gravity;
	float deltaY    = obj->pivot.y - oldY;		//移動後の位置から移動前の位置を引く	

	if (deltaY > 0)
	{
		//下方向チェック
		if (Game::instance()->bgManager()->isFloor(obj->pivot.x, obj->pivot.y, obj->size.x, obj->ladderFrag))
		{
			//床に当たっていたら
			Game::instance()->bgManager()->mapCorrectionDown(obj);	//下方向の補正処理
			obj->grandFrag = true;									//地面フラグ

			Game::instance()->bgManager()->chipChange(obj->pivot.x, obj->pivot.y);
		}
	}

	if (deltaY < 0)
	{
		//上方向チェック
		if (Game::instance()->bgManager()->isCeiling(obj->pivot.x, obj->pivot.y - obj->texSize.y, obj->size.x))
		{
			Game::instance()->bgManager()->mapCorrecionUp(obj);		//上方向の補正処理
			obj->jumpTimer = 0;										//天井にぶつかったため、それ以上ジャンプできない
		}
	}
}

//TODO::X方向処理
void Actor::playerMoveX(OBJ2D* obj)
{
	GetHitKeyStateAll(key);

	obj->wallFrag = false;

	//左右入力の取り出し
	if (key[KEY_INPUT_LEFT])
	{
		obj->speed -= actorParam.accel.x;
	}
	else if (key[KEY_INPUT_RIGHT])
	{
		obj->speed += actorParam.accel.x;
	}
	else
	{
		if (obj->speed > 0)
		{
			obj->speed -= actorParam.accel.x / 2;
			obj->speed = (std::max)(obj->speed, 0.0f);
		}
		if (obj->speed < 0)
		{
			obj->speed += actorParam.accel.x / 2;
			obj->speed = (std::min)(obj->speed, 0.0f);
		}
	}

	//最大速度チェック
	float speedMax = actorParam.speedMax;
	if (obj->ladderFrag)  speedMax /= 2;
	obj->speed = clamp(obj->speed, -speedMax, speedMax);

	//X方向移動
	float oldX    = obj->pivot.x;
	obj->pivot.x += obj->speed;
	float deltaX  = obj->pivot.x - oldX;

	//地形当たり判定
	if (deltaX > 0)
	{
		if (Game::instance()->bgManager()->isWall(obj->pivot.x + obj->size.x, obj->pivot.y, obj->texSize.y))
		{
			Game::instance()->bgManager()->mapCorrectionRight(obj);		//右方向の補正処理
			obj->wallFrag = true;										//壁フラグをtrueにしておく
		}
	}
	if (deltaX < 0)
	{
		if (Game::instance()->bgManager()->isWall(obj->pivot.x - obj->size.x, obj->pivot.y, obj->texSize.y))
		{
			Game::instance()->bgManager()->mapCorrectionLeft(obj);		//左方向の補正処理
			obj->wallFrag = true;										//壁フラグをtrueにしておく
		}
	}
}

//プレイヤージャンプ処理
void Actor::playerJump(OBJ2D* obj)
{
	GetHitKeyStateAll(key);
	static const float SPEED_JUMP_Y = -6.0f;	//ジャンプ中の上昇スピード

	//SPACEが押されたら
	if (key[KEY_INPUT_SPACE])
	{
		if (keyTrg && obj->grandFrag)
		{
			keyTrg = false;
			obj->jumpTimer = 16;                // ジャンプ可能なのでjumpTimerに値をセット
		}
	}
	else
	{
		keyTrg = true;
	}
	//ジャンプ中
	if (obj->jumpTimer > 0)
	{
		if (key[KEY_INPUT_SPACE])
		{
			obj->gravity = SPEED_JUMP_Y;
			obj->jumpTimer--;
		}
		else
		{
			obj->jumpTimer = 0;
		}
	}
}

//エリア制限
void Actor::areaCheck(OBJ2D* obj)
{
	float oldX = obj->pos.x;													//x座標を一時的に保存
	obj->pos.x = clamp(obj->pos.x, obj->size.x, SCREEN_WIDTH - obj->size.x);	
	if (oldX != obj->pos.x)	obj->speed = 0;										// 保存した値と違えば画面端にあたっている

	float oldY = obj->pos.y;	//y座標を一時的に保存
	obj->pos.y = clamp(obj->pos.y, obj->size.y, SCREEN_HEIGHT);
	if (oldY != obj->pos.y)		//保存した値と違えば画面端に当たっている
	{
		obj->gravity	= 0;	//y方向の速度を0にする
		obj->jumpTimer	= 0;	//ジャンプ上昇中であれば、落下に切り替わる
	}
}

//プレイヤーの移動処理
void Actor::playerMove(OBJ2D* obj)
{
	//プレイヤーの縦方向の移動処理
	playerMoveY(obj);

	//プレイヤーの横方向の移動処理
	playerMoveX(obj);

	//プレイヤーのジャンプ処理
	playerJump(obj);

	//エリアチェック
	areaCheck(obj);
}


//--敵移動処理--//

//敵の縦方向移動処理
void Actor::enemyMoveY(OBJ2D* obj)
{
	//地面フラグをfalseにしておく
	obj->grandFrag = false;

	//速度の計算
	obj->gravity  += actorParam.accel.y;

	//最大速度チェック
	obj->gravity   = (std::min)(obj->gravity, actorParam.gravityMax);

	//移動
	float oldY		= obj->pos.y;
	obj->pos.y	   += obj->gravity;
	float deltaY	= obj->pos.y - oldY;	//移動量の計算

	//着地判定
	if (deltaY > 0) //下降中
	{
		if (Game::instance()->bgManager()->isFloor(obj->pos.x, obj->pos.y, obj->size.x))
		{
			Game::instance()->bgManager()->mapCorrectionDown(obj);
			obj->grandFrag = true;
		}
	}
	//天井判定
	if (deltaY < 0)
	{
		if (Game::instance()->bgManager()->isCeiling(obj->pos.x, obj->pos.y, obj->size.x))
		{
			Game::instance()->bgManager()->mapCorrecionUp(obj);
		}
	}
}

//敵の横方向移動処理
void Actor::enemyMoveX(OBJ2D* obj)
{
	//各フラグをfalseにしておく
	obj->wallFrag  = false;
	obj->grandFrag = false;

	//最大速度チェック
	obj->speed = clamp(obj->speed, -actorParam.speedMax, actorParam.speedMax);

	//移動
	float oldX = obj->pos.x;
	obj->pos.x += obj->speed;
	float deltaX = obj->pos.x - oldX;

	//地形当たり判定
	if (deltaX > 0)
	{
		if (Game::instance()->bgManager()->isWall(obj->pos.x + obj->size.x, obj->pos.y, obj->size.y))
		{
			Game::instance()->bgManager()->mapCorrectionRight(obj);
			obj->wallFrag = true;
		}
	}
	if (deltaX < 0)
	{
		if (Game::instance()->bgManager()->isWall(obj->pos.x - obj->size.x, obj->pos.y, obj->size.y))
		{
			Game::instance()->bgManager()->mapCorrectionLeft(obj);
			obj->wallFrag = true;
		}
	}
}


