//******************************************************************************
//
//
//      タイトル
//
//
//******************************************************************************

#include "generic.h"
#include "obj2d.h"
#include "player.h"
#include "scene.h"
#include "title.h"
#include "game.h"

////--変数--////
Title Title::instance_;

////--初期化処理--////
void Title::init()
{
	Scene::init();			//基底クラスのinitを呼ぶ

	setSelect(ONE_PLAY);	//ゲームの状態

	//フォント追加
	titleText  = CreateFontToHandle("Nu よもぎもち 標準-丸1", 50, 3, DX_FONTTYPE_NORMAL);
}

////--更新処理--////
void Title::update()
{
	char key[KEY_MAX];
	GetHitKeyStateAll(key);

	//Pad入力処理
	padInput = GetJoypadInputState(DX_INPUT_PAD1);

	switch (state)
	{
	case 0:
		//--初期設定--//
		timer = 0;			//タイマーを初期化
		state++;			//初期化処理の終了

		/*fallthrough*/

	case 1:
		//--通常時の処理--//

		timer++;			//Title全体のタイマー

		//START
		if (padInput & PAD_INPUT_R)
		{
			if (keyTrg)
			{
				keyTrg = false;
				changeScene(Game::instance());
				if (select == 0)  setSelect(ONE_PLAY);
				if (select == 1)  setSelect(TWO_PLAY);
			}
		}
		//下
		else if (padInput & PAD_INPUT_DOWN)
		{
			if (keyTrg && select == 0)
			{
				keyTrg = false;
				select = 1;
			}
		}
		//上
		else if (padInput & PAD_INPUT_UP)
		{
			if (keyTrg && select == 1)
			{
				keyTrg = false;
				select = 0;
			}
		}
		else
		{
			keyTrg = true;
		}
		break;
	}
}

////--描画処理--////
void Title::draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255),       "Title",        100);
	DrawFormatString(  0,  10, GetColor(255, 255, 255), "Select : %d",select, 100);
}
