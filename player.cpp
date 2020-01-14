#include "generic.h"
#include "obj2d.h"
#include "load_texture.h"
#include "util.h"
#include "actor.h"
#include "player.h"
#include "scene.h"
#include "game.h"

//--���Ԑ錾--//
Player player;

//--�ʏ펞�̃v���C���[�̍s��--//
void Player::move(OBJ2D* obj)
{
	char key[KEY_MAX];
	GetHitKeyStateAll(key);

	obj->existFrag   = true;

#if 1 //Actor�N���X�ŕ���Ă���Ă�
	////--�ʒu�X�V--//
	//obj->pos.x += obj->speed;
	//obj->pos.y += obj->gravity;

	////--�L�[���͏���--//
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
		//�����ݒ�
		obj->state++;

		break;
	case 1:
		//�ʏ펞
		playerMove(obj);	//�����̏���
		fixPos(obj);		//pivot�̍X�V
		
		break;
	}


	if (key[KEY_INPUT_SPACE] && key[KEY_INPUT_UP])
	{
		if (key_trg)
		{
			key_trg = false;

			Game::instance()->playerManager()->add(&player, NO_ANIMATION, n_texture::storePlayer,TEXTURE, Vector2F{ 100,100 }, Vector2F{64,64});
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

//--pivot�̍X�V & pos�̍X�V--//
void Player::fixPos(OBJ2D* obj)
{
	obj->pos.x  += obj->speed;
	obj->pos.y  += obj->gravity;

	obj->pivot.x = obj->pos.x  - 10;
	obj->pivot.y = obj->pos.y  + obj->size.y;
}

//--����--//
void ErasePlayer::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}