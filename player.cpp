#include "generic.h"
#include "obj2d.h"
#include "load_texture.h"
#include "util.h"
#include "actor.h"
#include "player.h"
#include "scene.h"
#include "game.h"

//--実態宣言--//
Player player;

//--通常時のプレイヤーの行動--//
void Player::move(OBJ2D* obj)
{
	char key[KEY_MAX];
	GetHitKeyStateAll(key);

	obj->existFrag   = true;

#if 1 //Actorクラスで補ってくれてる
	////--位置更新--//
	//obj->pos.x += obj->speed;
	//obj->pos.y += obj->gravity;

	////--キー入力処理--//
	//if (key[KEY_INPUT_RIGHT])
	//{
	//	obj->speed   = 5;
	//}
	//else if (key[KEY_INPUT_LEFT])
	//{
	//	obj->speed   = -5;
	//}
	//else if (key[KEY_INPUT_DOWN])
	//{
	//	obj->gravity = 5;
	//}
	//else if (key[KEY_INPUT_UP])
	//{
	//	obj->gravity = -5;
	//}
	//else
	//{
	//	obj->gravity	= 0;
	//	obj->speed		= 0;
	//}

	//if (obj->pos.x > SCREEN_WIDTH)
	//{
	//	obj->pos.x = 0;
	//}
	//if (obj->pos.y < 0)
	//{
	//	obj->pos.y = 0;
	//}
#endif
	
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->state++;

		break;
	case 1:
		//通常時
		playerMove(obj);	//動きの処理
		fixPos(obj);		//pivotの更新
		
		break;
	}


	if (key[KEY_INPUT_SPACE] && key[KEY_INPUT_UP])
	{
		if (key_trg)
		{
			key_trg = false;

			Game::instance()->playerManager()->add(&player, n_texture::storePlayer,TEXTURE, Vector2F{ 100,100 }, Vector2F{64,64});
		}
	}
	else if (key[KEY_INPUT_DOWN] && key[KEY_INPUT_RETURN])
	{
		if (key_trg)
		{
			key_trg    = false;
			obj->mvAlg = nullptr;
		}
	}
	else
	{
		key_trg = true;
	}
}

//--pivotの更新 & posの更新--//
void Player::fixPos(OBJ2D* obj)
{
	obj->pos.x  += obj->speed;
	obj->pos.y  += obj->gravity;

	obj->pivot.x = obj->pos.x  - 10;
	obj->pivot.y = obj->pos.y  + obj->size.y;
}

//--消去--//
void ErasePlayer::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}