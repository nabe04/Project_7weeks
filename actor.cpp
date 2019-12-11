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
	//actorParam�̊e�����o�̃f�t�H���g�l��ݒ�

	actorParam.accel		= {0.5f,0.5f};		//�c�������̉����x
	actorParam.speedMax		= 4.0f;				//�������̍ő呬�x
	actorParam.gravityMax	= 8.0f;				//�c�����̍ő呬�x

	actorParam.ladderAccel	= 0.5f;				//��q�̉����x
}

//--�v���C���[�ړ�����--//

//Y��������
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
		//���x�ɉ����x��������
		obj->gravity += actorParam.accel.y;
	}

	//�ő呬�x�`�F�b�N
	float maxGravity = actorParam.gravityMax;
	if (obj->ladderFrag)	maxGravity /= 4;

	obj->gravity = clamp(obj->gravity, -maxGravity, maxGravity);

	//�ʒu�X�V
	float oldY      = obj->pivot.y;			    //�ړ��O�̈ʒu��ێ�
	obj->pivot.y    += obj->gravity;
	float deltaY    = obj->pivot.y - oldY;		//�ړ���̈ʒu����ړ��O�̈ʒu������	

	if (deltaY > 0)
	{
		//�������`�F�b�N
		if (Game::instance()->bgManager()->isFloor(obj->pivot.x, obj->pivot.y, obj->size.x, obj->ladderFrag))
		{
			//���ɓ������Ă�����
			Game::instance()->bgManager()->mapCorrectionDown(obj);	//�������̕␳����
			obj->grandFrag = true;									//�n�ʃt���O

			Game::instance()->bgManager()->chipChange(obj->pivot.x, obj->pivot.y);
		}
	}

	if (deltaY < 0)
	{
		//������`�F�b�N
		if (Game::instance()->bgManager()->isCeiling(obj->pivot.x, obj->pivot.y - obj->texSize.y, obj->size.x))
		{
			Game::instance()->bgManager()->mapCorrecionUp(obj);		//������̕␳����
			obj->jumpTimer = 0;										//�V��ɂԂ��������߁A����ȏ�W�����v�ł��Ȃ�
		}
	}
}

//TODO::X��������
void Actor::playerMoveX(OBJ2D* obj)
{
	GetHitKeyStateAll(key);

	obj->wallFrag = false;

	//���E���͂̎��o��
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

	//�ő呬�x�`�F�b�N
	float speedMax = actorParam.speedMax;
	if (obj->ladderFrag)  speedMax /= 2;
	obj->speed = clamp(obj->speed, -speedMax, speedMax);

	//X�����ړ�
	float oldX    = obj->pivot.x;
	obj->pivot.x += obj->speed;
	float deltaX  = obj->pivot.x - oldX;

	//�n�`�����蔻��
	if (deltaX > 0)
	{
		if (Game::instance()->bgManager()->isWall(obj->pivot.x + obj->size.x, obj->pivot.y, obj->texSize.y))
		{
			Game::instance()->bgManager()->mapCorrectionRight(obj);		//�E�����̕␳����
			obj->wallFrag = true;										//�ǃt���O��true�ɂ��Ă���
		}
	}
	if (deltaX < 0)
	{
		if (Game::instance()->bgManager()->isWall(obj->pivot.x - obj->size.x, obj->pivot.y, obj->texSize.y))
		{
			Game::instance()->bgManager()->mapCorrectionLeft(obj);		//�������̕␳����
			obj->wallFrag = true;										//�ǃt���O��true�ɂ��Ă���
		}
	}
}

//�v���C���[�W�����v����
void Actor::playerJump(OBJ2D* obj)
{
	GetHitKeyStateAll(key);
	static const float SPEED_JUMP_Y = -6.0f;	//�W�����v���̏㏸�X�s�[�h

	//SPACE�������ꂽ��
	if (key[KEY_INPUT_SPACE])
	{
		if (keyTrg && obj->grandFrag)
		{
			keyTrg = false;
			obj->jumpTimer = 16;                // �W�����v�\�Ȃ̂�jumpTimer�ɒl���Z�b�g
		}
	}
	else
	{
		keyTrg = true;
	}
	//�W�����v��
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

//�G���A����
void Actor::areaCheck(OBJ2D* obj)
{
	float oldX = obj->pos.x;													//x���W���ꎞ�I�ɕۑ�
	obj->pos.x = clamp(obj->pos.x, obj->size.x, SCREEN_WIDTH - obj->size.x);	
	if (oldX != obj->pos.x)	obj->speed = 0;										// �ۑ������l�ƈႦ�Ή�ʒ[�ɂ������Ă���

	float oldY = obj->pos.y;	//y���W���ꎞ�I�ɕۑ�
	obj->pos.y = clamp(obj->pos.y, obj->size.y, SCREEN_HEIGHT);
	if (oldY != obj->pos.y)		//�ۑ������l�ƈႦ�Ή�ʒ[�ɓ������Ă���
	{
		obj->gravity	= 0;	//y�����̑��x��0�ɂ���
		obj->jumpTimer	= 0;	//�W�����v�㏸���ł���΁A�����ɐ؂�ւ��
	}
}

//�v���C���[�̈ړ�����
void Actor::playerMove(OBJ2D* obj)
{
	//�v���C���[�̏c�����̈ړ�����
	playerMoveY(obj);

	//�v���C���[�̉������̈ړ�����
	playerMoveX(obj);

	//�v���C���[�̃W�����v����
	playerJump(obj);

	//�G���A�`�F�b�N
	areaCheck(obj);
}


//--�G�ړ�����--//

//�G�̏c�����ړ�����
void Actor::enemyMoveY(OBJ2D* obj)
{
	//�n�ʃt���O��false�ɂ��Ă���
	obj->grandFrag = false;

	//���x�̌v�Z
	obj->gravity  += actorParam.accel.y;

	//�ő呬�x�`�F�b�N
	obj->gravity   = (std::min)(obj->gravity, actorParam.gravityMax);

	//�ړ�
	float oldY		= obj->pos.y;
	obj->pos.y	   += obj->gravity;
	float deltaY	= obj->pos.y - oldY;	//�ړ��ʂ̌v�Z

	//���n����
	if (deltaY > 0) //���~��
	{
		if (Game::instance()->bgManager()->isFloor(obj->pos.x, obj->pos.y, obj->size.x))
		{
			Game::instance()->bgManager()->mapCorrectionDown(obj);
			obj->grandFrag = true;
		}
	}
	//�V�䔻��
	if (deltaY < 0)
	{
		if (Game::instance()->bgManager()->isCeiling(obj->pos.x, obj->pos.y, obj->size.x))
		{
			Game::instance()->bgManager()->mapCorrecionUp(obj);
		}
	}
}

//�G�̉������ړ�����
void Actor::enemyMoveX(OBJ2D* obj)
{
	//�e�t���O��false�ɂ��Ă���
	obj->wallFrag  = false;
	obj->grandFrag = false;

	//�ő呬�x�`�F�b�N
	obj->speed = clamp(obj->speed, -actorParam.speedMax, actorParam.speedMax);

	//�ړ�
	float oldX = obj->pos.x;
	obj->pos.x += obj->speed;
	float deltaX = obj->pos.x - oldX;

	//�n�`�����蔻��
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


