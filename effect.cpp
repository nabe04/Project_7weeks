#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "actor.h"
#include "algorithm.h"
#include "cursor.h"
#include "effect.h"
#include "MyImgui.h"
#include "player.h"
#include "scene.h"
#include "game.h"

PressEffectMoveR pressEffectMoveR;
PressEffectMoveT pressEffectMoveT;
PressEffectMoveL pressEffectMoveL;
PressEffectMoveB pressEffectMoveB;

void PressEffect::moveR(OBJ2D* obj)
{
	obj->existFrag = true;
	switch (obj->state)
	{
	case 0:
		obj->angle = 0;
		obj->scale = { 1,1 };
		obj->animeState = 0;
		obj->state++;
		break;
	case 1:
		obj->timer++;
		obj->animeTimer = obj->timer / 5 % 4;
		if (obj->animeTimer == 3)
		{
			obj->mvAlg = nullptr;
		}
		break;
	}
}
void PressEffect::moveT(OBJ2D* obj)
{
	obj->existFrag = true;
	switch (obj->state)
	{
	case 0:
		obj->angle = ToRadian(-90);
		obj->scale = { 1,1 };
		obj->animeState = 0;
		obj->state++;
		break;
	case 1:
		obj->timer++;
		obj->animeTimer = obj->timer / 5 % 4;
		if (obj->animeTimer == 3)
		{
			obj->mvAlg = nullptr;
		}
		break;
	}
}
void PressEffect::moveL(OBJ2D* obj)
{
	obj->existFrag = true;
	switch (obj->state)
	{
	case 0:
		obj->angle = 0;
		obj->scale = { -1,1 };
		obj->animeState = 0;
		obj->state++;
		break;
	case 1:
		obj->timer++;
		obj->animeTimer = obj->timer / 5 % 4;
		if (obj->animeTimer == 3)
		{
			obj->mvAlg = nullptr;
		}
		break;
	}
}
void PressEffect::moveB(OBJ2D* obj)
{
	obj->existFrag = true;
	switch (obj->state)
	{
	case 0:
		obj->angle = ToRadian(90);
		obj->scale = { 1,-1 };
		obj->animeState = 0;
		obj->state++;
		break;
	case 1:
		obj->timer++;
		obj->animeTimer = obj->timer / 5 % 4;
		if (obj->animeTimer == 3)
		{
			obj->mvAlg = nullptr;
		}
		break;
	}
}

void PressEffectMoveR::move(OBJ2D* obj)
{
	moveR(obj);
}
void PressEffectMoveT::move(OBJ2D* obj)
{
	moveT(obj);
}
void PressEffectMoveL::move(OBJ2D* obj)
{
	moveL(obj);
}
void PressEffectMoveB::move(OBJ2D* obj)
{
	moveB(obj);
}

