#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "algorithm.h"
#include "ui.h"

int UI::nowCombo;

UiTimer uiTimer;
UiCombo uiCombo;

void UI::moveTimer(OBJ2D* obj)
{
	int dispTime;
	const int FPS = 60;

	switch (obj->state)
	{
	case 0:
		//--‰ŠúÝ’è--//
		obj->timer		= n_general_function::setTimer(60);
		obj->existFrag	= true;
		obj->text		= "Time : %.f";
		obj->state++;
		break;
	case 1:
		dispTime		= obj->timer / FPS;
		obj->dispNum	= dispTime;
		obj->pos.x		= SCREEN_WIDTH - 400;
		obj->pos.y		= 0;
		obj->timer--;
		break;
	}
}

void UI::moveCombo(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		obj->text = "Combo : %.f";
		obj->existFrag = true;
		obj->color.a   = 255;
		obj->state++;
		break;
	case 1:
		obj->dispNum = nowCombo;
		obj->color.a--;

		if (obj->color.a < 0)
		{
			obj->mvAlg	= nullptr;
			nowCombo	= 0;
		}
		break;
	}
}

void UiTimer::move(OBJ2D* obj)
{
	moveTimer(obj);
}

void UiCombo::move(OBJ2D* obj)
{
	moveCombo(obj);
}
