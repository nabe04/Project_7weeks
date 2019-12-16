#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "algorithm.h"
#include "MyImgui.h"
#include "ui.h"
#include "scene.h"
#include "game.h"


int UI::nowCombo_1;
int UI::nowCombo_2;
int UI::score_1;
int UI::score_2;

UiTimer uiTimer;
UiCombo uiCombo_1;
UiCombo uiCombo_2;
UiScore uiScore_1;
UiScore uiScore_2;

void UI::moveTimer(OBJ2D* obj)
{
	int dispTime;
	const int FPS = 60;

	switch (obj->state)
	{
	case 0:
		//--初期設定--//
		obj->timer		= n_general_function::setTimer(60);
		obj->existFrag	= true;
		obj->text		= "Time : %.f";
		obj->fontSize	= 60;
		obj->fontThick	= 3;
		obj->loadData	= n_font::font_0;
		obj->state++;
		break;
	case 1:
		dispTime		= obj->timer / FPS;
		obj->dispNum	= dispTime;

		if (Game::playerNum == Scene::ONE_PLAY)
		{
	#ifdef USE_IMGUI	//imgui使用時
			obj->pos.x   = SCREEN_WIDTH - 400 + im_Ui.im_uiTimer.fParam.x;
			obj->pos.y   = 0 + im_Ui.im_uiTimer.fParam.y;
			obj->color.r = im_Ui.im_uiTimer.iColor[0];
			obj->color.g = im_Ui.im_uiTimer.iColor[1];
			obj->color.b = im_Ui.im_uiTimer.iColor[2];
			obj->color.a = im_Ui.im_uiTimer.iColor[3];
	#endif  //USE_IMGUI

	#ifndef USE_IMGUI
			obj->pos.x   = SCREEN_WIDTH - 400;
			obj->pos.y   = 0;
	#endif //USE_IMGUI
		}
		if (Game::playerNum == Scene::TWO_PLAY)
		{
			obj->pos.x   = 350;
			obj->pos.y   = 0;
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
		obj->text		= "Combo : %.f";
		obj->existFrag	= true;
		obj->color.a	= 255;
		obj->pos		= { 325,45 };
		obj->fontSize	= 40;//文字の大きさ
		obj->fontThick	= 3; //文字の厚さ
		obj->state		= 1;
		break;

	case 1:
		obj->fontSize	+= 6;
		obj->pos.x		-= 6;
		obj->pos.y		-= 6;
		if (obj->pos.x < 283)
		{
			obj->pos.x = 283;
		}
		if (obj->pos.y < 3)
		{
			obj->pos.y = 3;
		}
		if (obj->fontSize > 82)
		{
			obj->fontSize	= 82;
			obj->state		= 2;
		}
		if (playerNo == Scene::ONE_PLAY)  obj->dispNum = static_cast<float>(nowCombo_1);
		if (playerNo == Scene::TWO_PLAY)  obj->dispNum = static_cast<float>(nowCombo_2);
		break;
	case 2:
		obj->fontSize	-= 3;
		obj->pos.x		+= 3;
		obj->pos.y		+= 3;
		obj->color.a--;
		if (obj->pos.x > 325)
		{
			obj->pos.x = 325;
		}
		if (obj->pos.y > 45)
		{
			obj->pos.y = 45;
		}
		if (obj->fontSize < 40)
		{
			obj->fontSize = 40;
			obj->state = 3;
		}
		break;
	case 3:

		obj->color.a--;

		if (obj->color.a < 0)
		{
			obj->mvAlg = nullptr;
			if (playerNo == Scene::ONE_PLAY) nowCombo_1 = 0;
			if (playerNo == Scene::TWO_PLAY) nowCombo_2 = 0;
		}
		break;
	}
}

void UI::moveScore(OBJ2D* obj)
{
	obj->existFrag = true;

	if (playerNo == Scene::ONE_PLAY)		obj->dispNum = static_cast<float>(score_1);
	if (playerNo == Scene::TWO_PLAY)		obj->dispNum = static_cast<float>(score_2);

	switch (obj->state)
	{
	case 0:
		obj->text		= "  SCORE\n %07.f";
		obj->dispNum	= 200;

		obj->color.a	= 255;
		obj->fontSize	= 100;
		obj->fontThick	= 3;
		obj->loadData	= n_font::font_0;
		obj->state++;
	case 1:
		if (playerNo == Scene::ONE_PLAY)
		{
			obj->dispNum = 200;

#ifdef USE_IMGUI	//imgui使用時
			obj->pos.x		= 0 + im_Ui.im_uiScore.fParam.x;
			obj->pos.y		= 0 + im_Ui.im_uiScore.fParam.y;
			obj->color.r	= static_cast<int>(im_Ui.im_uiScore.iColor[0]);
			obj->color.g	= static_cast<int>(im_Ui.im_uiScore.iColor[1]);
			obj->color.b	= static_cast<int>(im_Ui.im_uiScore.iColor[2]);
			obj->color.a	= static_cast<int>(im_Ui.im_uiScore.iColor[3]);
			obj->fontSize	= 0 + static_cast<int>(im_Ui.im_uiScore.size);
			obj->fontThick  = 0 + static_cast<int>(im_Ui.im_uiScore.thick);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
			obj->pos.x		= 688;
			obj->pos.y		= 117;
			obj->fontSize	= 36;
			obj->fontThick	= 5;
#endif // !USE_IMGUI

			
		}

		break;
	}
}

void moveScoreVal(OBJ2D* obj)
{

}

void UiTimer::move(OBJ2D* obj)
{
	moveTimer(obj);
}

void UiCombo::move(OBJ2D* obj)
{
	moveCombo(obj);
}

void UiScore::move(OBJ2D* obj)
{
	moveScore(obj);
}

void EraseUi::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}