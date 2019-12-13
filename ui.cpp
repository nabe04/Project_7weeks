#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "algorithm.h"
#include "MyImgui.h"
#include "ui.h"
#include "scene.h"
#include "game.h"

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

		if (Game::playerNum == Scene::ONE_PLAY)
		{
	#ifdef USE_IMGUI
			obj->pos.x = SCREEN_WIDTH - 400 + imUiTimer.im_uiTimer.fParam.x;
			obj->pos.y = 0;
			obj->color.r = imUiTimer.im_uiTimer.iColor[0];
			obj->color.g = imUiTimer.im_uiTimer.iColor[1];
			obj->color.b = imUiTimer.im_uiTimer.iColor[2];
			obj->color.a = imUiTimer.im_uiTimer.iColor[3];
	#endif  //USE_IMGUI
	#ifndef USE_IMGUI
			obj->pos.x = SCREEN_WIDTH - 400;
			obj->pos.y = 0;
	#endif //USE_IMGUI
		}
		if (Game::playerNum == Scene::TWO_PLAY)
		{
			obj->pos.x = 350;
			obj->pos.y = 0;
		}

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