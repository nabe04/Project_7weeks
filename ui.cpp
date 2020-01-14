#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "algorithm.h"
#include "MyImgui.h"
#include "ui.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "scene_result.h"
#include "load_texture.h"


int		UI::nowCombo_1		= 0;
int		UI::nowCombo_2		= 0;
int		UI::score_1			= 0;
int		UI::score_2			= 0;
float	UI::eraseBlockPow_1 = 0;
float	UI::eraseBlockPow_2 = 0;

UiTimer uiTimer_1;
UiTimer uiTimer_2;
UiCombo uiCombo_1;
UiCombo uiCombo_2;
UiScore uiScore_1;
UiScore uiScore_2;
UiGauge uiGauge_1;
UiGauge uiGauge_2;

UiCounter uiCounter_1;		//カウンター
UiCounter uiCounter_2;

//タイマー(UI)の制御
void UI::moveTimer(OBJ2D* obj,Vector2F pos)
{
	int			dispTime;
	const int	FPS = 60;

	//位置
	obj->pos = pos;

	switch (obj->state)
	{
	case 0:
		//--初期設定--//
		obj->pos		= pos;
		obj->timer		= n_general_function::setTimer(60);
		obj->existFrag	= true;
		obj->text		= "%.f";
		obj->fontSize	= 22;
		obj->fontThick	= 3;
		obj->color		= { 0, 0, 0, 255 };
		obj->loadData	= n_font::fh_yomogi;
		obj->state++;
		break;
	case 1:
		dispTime		= obj->timer / FPS;
		obj->dispNum	= static_cast<float>(dispTime);

		if (Game::gameMode == Scene::ONE_PLAY)
		{
	#ifdef USE_IMGUI	//imgui使用時
			/*obj->pos.x   = SCREEN_WIDTH - 400 + im_Ui.im_uiTimer.fParam.x;
			obj->pos.y   = 0 + im_Ui.im_uiTimer.fParam.y;*/
			obj->color.r = static_cast<int>(im_Ui.im_uiTimer.iColor[0]);
			obj->color.g = static_cast<int>(im_Ui.im_uiTimer.iColor[1]);
			obj->color.b = static_cast<int>(im_Ui.im_uiTimer.iColor[2]);
			obj->color.a = static_cast<int>(im_Ui.im_uiTimer.iColor[3]);
	#endif  //USE_IMGUI

	#ifndef USE_IMGUI
			/*obj->pos.x   = SCREEN_WIDTH - 400;
			obj->pos.y   = 0;*/
	#endif //USE_IMGUI
		}
		if (Game::gameMode == Scene::TWO_PLAY)
		{
			/*obj->pos.x   = 350;
			obj->pos.y   = 0;*/
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
		obj->fontSize	= 40;//文字の大きさ
		obj->fontThick	= 3; //文字の厚さ
		if (Game::gameMode == Scene::ONE_PLAY) obj->pos = { 320,48 };
		if (Game::gameMode == Scene::TWO_PLAY)
		{
			if (playerNo == Scene::ONE_PLAY) obj->pos = { 100,48 };
			if (playerNo == Scene::TWO_PLAY) obj->pos = { 600,48 };
		}
		move = { 0,0 };

		obj->state = 1;
		break;

	case 1:
		obj->fontSize += 6;
		move.x -= 4;
		move.y -= 4;
		//-- 一人プレイ時 --//
		if (Game::gameMode == Scene::ONE_PLAY)
		{
			/*if (obj->pos.x < 283)
			{
			move.x = 0;
			obj->pos.x = 283;
			}
			if (obj->pos.y < 3)
			{
			move.y = 0;
			obj->pos.y = 3;
			}*/

			/*if (move.x < -20)
			{
			move.x = 0;
			}
			if (move.y < -20)
			{
			move.y = 0;
			}*/
		}

		if (obj->fontSize > 82)
		{
			move = { 0,0 };
			obj->fontSize = 82;
			obj->state = 2;
		}
		if (playerNo == Scene::ONE_PLAY)  obj->dispNum = static_cast<float>(nowCombo_1);
		if (playerNo == Scene::TWO_PLAY)  obj->dispNum = static_cast<float>(nowCombo_2);
		break;
	case 2:
		obj->fontSize -= 4;
		move.x += 2;
		move.y += 2;
		obj->color.a--;

		//-- 一人プレイ時 --//

		/*if (obj->pos.x > 325)
		{
		move.x = 0;
		obj->pos.x = 325;
		}
		if (obj->pos.y > 45)
		{
		move.y = 0;
		obj->pos.y = 45;
		}*/

		/* if (move.x > 15)
		{
		move.x = 0;
		}
		if (move.y > 15)
		{
		move.y = 0;
		}*/
		if (obj->fontSize < 40)
		{
			if (Game::gameMode == Scene::ONE_PLAY)
			{
				obj->pos = { 320,48 };
			}
			if (Game::gameMode == Scene::TWO_PLAY)
			{
				if (playerNo == Scene::ONE_PLAY) obj->pos = { 100,48 };
				if (playerNo == Scene::TWO_PLAY) obj->pos = { 600,48 };
			}
			move = { 0,0 };
			obj->fontSize = 40;
			obj->state = 3;
		}


		break;
	case 3:

		obj->color.a--;

		move = { 0,0 };

		if (obj->color.a < 0)
		{
			obj->mvAlg = nullptr;
			if (playerNo == Scene::ONE_PLAY)
			{
				nowCombo_1 = 0;
				UI::eraseBlockPow_1 = 1.0f;
			}
			if (playerNo == Scene::TWO_PLAY)
			{
				nowCombo_2 = 0;
				UI::eraseBlockPow_2 = 1.0f;
			}
		}
		break;
	}

	obj->pos.x += move.x;
	obj->pos.y += move.y;

}
void UI::moveScore(OBJ2D* obj)
{
	obj->existFrag = true;
	int holdScore_1;	//1Pの獲得した総スコアを保持する変数
	int holdScore_2;	//2Pの獲得した総スコアを保持する変数
	switch (obj->state)
	{
	case 0:
		obj->text = "   SCORE\n %07.f";
		obj->dispNum = 0;
		holdScore_1 = 0;
		holdScore_2 = 2;

		obj->color.a = 255;
		obj->fontSize = 100;
		obj->fontThick = 3;
		obj->loadData = n_font::fh_yomogi;
		obj->state++;
	case 1:
		if (Game::gameMode == Scene::ONE_PLAY)
		{
#ifdef USE_IMGUI //imgui使用時
			obj->pos.x = 688 + im_Ui.im_uiScore_1.fParam.x;
			obj->pos.y = 117 + im_Ui.im_uiScore_1.fParam.y;
			obj->color.r = static_cast<int>(im_Ui.im_uiScore_1.iColor[0]);
			obj->color.g = static_cast<int>(im_Ui.im_uiScore_1.iColor[1]);
			obj->color.b = static_cast<int>(im_Ui.im_uiScore_1.iColor[2]);
			obj->color.a = static_cast<int>(im_Ui.im_uiScore_1.iColor[3]);
			obj->fontSize = 36 + static_cast<int>(im_Ui.im_uiScore_1.size);
			obj->fontThick = 5 + static_cast<int>(im_Ui.im_uiScore_1.thick);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
			obj->pos.x = 688;
			obj->pos.y = 117;
			obj->fontSize = 36;
			obj->fontThick = 5;
#endif // !USE_IMGUI
			holdScore_1 = score_1;

			if (holdScore_1 == 0)
			{
				holdScore_1 = 1;
			}

			int calcScore = holdScore_1 / 5;

			if (calcScore <= 0) calcScore = 1;

			// obj->dispNum += score_1 / (holdScore_1/30);
			obj->dispNum += score_1 / calcScore;
			if (obj->dispNum > holdScore_1)
			{
				obj->dispNum = holdScore_1;
			}
		}

		if (Game::gameMode == Scene::TWO_PLAY)
		{
			if (playerNo == Scene::ONE_PLAY)
			{
				holdScore_1 = score_1;

				if (holdScore_1 == 0) holdScore_1 = 1;

				int calcScore = holdScore_1 / 5;

				if (calcScore <= 0) calcScore = 1;

				// obj->dispNum += score_1 / (holdScore_1/30);

				obj->dispNum += score_1 / calcScore;

				if (obj->dispNum > holdScore_1)
				{
					obj->dispNum = static_cast<float>(holdScore_1);  //プレイヤー 1
				}
			}

			if (playerNo == Scene::TWO_PLAY)
			{
				holdScore_2 = score_2;

				if (holdScore_2 == 0)
				{
					holdScore_2 = 1;
				}

				int calcScore = holdScore_2 / 5;

				if (calcScore <= 0) calcScore = 1;

				// obj->dispNum += score_1 / (holdScore_1/30);

				obj->dispNum += score_2 / calcScore;

				if (obj->dispNum > holdScore_2)
				{
					obj->dispNum = static_cast<float>(holdScore_2);  //プレイヤー 2
				}
		}
			//操作しているプレイヤーのNo
			if (playerNo == Scene::ONE_PLAY)
			{
#ifdef USE_IMGUI //imgui使用時
				obj->pos.x		= 396 + im_Ui.im_uiScore_1.fParam.x;
				obj->pos.y		= 122 + im_Ui.im_uiScore_1.fParam.y;
				obj->color.r	= static_cast<int>(im_Ui.im_uiScore_1.iColor[0]);
				obj->color.g	= static_cast<int>(im_Ui.im_uiScore_1.iColor[1]);
				obj->color.b	= static_cast<int>(im_Ui.im_uiScore_1.iColor[2]);
				obj->color.a	= static_cast<int>(im_Ui.im_uiScore_1.iColor[3]);
				obj->fontSize	= 25 + static_cast<int>(im_Ui.im_uiScore_1.size);
				obj->fontThick	= 8 + static_cast<int>(im_Ui.im_uiScore_1.thick);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
				obj->pos.x		= 396;
				obj->pos.y		= 122;
				obj->fontSize	= 25;
				obj->fontThick	= 8;
#endif // !USE_IMGUI

			}

			if (playerNo == Scene::TWO_PLAY)
			{
#ifdef USE_IMGUI //imgui使用時
				obj->pos.x		= 396 + im_Ui.im_uiScore_2.fParam.x;
				obj->pos.y		= 360 + im_Ui.im_uiScore_2.fParam.y;
				obj->color.r	= static_cast<int>(im_Ui.im_uiScore_2.iColor[0]);
				obj->color.g	= static_cast<int>(im_Ui.im_uiScore_2.iColor[1]);
				obj->color.b	= static_cast<int>(im_Ui.im_uiScore_2.iColor[2]);
				obj->color.a	= static_cast<int>(im_Ui.im_uiScore_2.iColor[3]);
				obj->fontSize	= 25 + static_cast<int>(im_Ui.im_uiScore_2.size);
				obj->fontThick = 8 + static_cast<int>(im_Ui.im_uiScore_2.thick);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
				obj->pos.x = 396;
				obj->pos.y = 360;
				obj->fontSize = 25;
				obj->fontThick = 8;
#endif // !USE_IMGUI
			}
	}
		break;
}
}
//add.end
////////////////////////////////////

void UI::moveGauge(OBJ2D* obj)
{
	obj->existFrag = true;
	int adjustGauge;
	switch (obj->state)
	{
	case 0:
		//-- 初期設定 --//
		//一人プレイ時
		if (Game::gameMode == Scene::ONE_PLAY)
		{
			obj->pos.x = 480;
			obj->pos.y = 480;
		}

		//二人プレイ時
		if (Game::gameMode == Scene::TWO_PLAY)
		{
			if (playerNo == Scene::ONE_PLAY)
			{
				obj->pos.x = 225;
				obj->pos.y = 480;
			}

			if (playerNo == Scene::TWO_PLAY)
			{
				obj->pos.x = 730;
				obj->pos.y = 480;
			}
		}

		addGauge	= 0;
		feverCount	= 0;
		adjustGauge = 0;

		obj->timer		= 0;
		obj->clipSize.x = 0;
		obj->clipSize.y = 100;
		obj->state++;
	case 1:
		//-- ゲージたまり中 --//

		obj->clipOrigin.x = 0;
		obj->clipOrigin.y = 0;

		//アニメーション処理
		obj->animeState = 1;
		obj->animeTimer = obj->timer / 5 % 4;
		obj->timer++;

		adjustGauge = (3 * feverCount);

		if (adjustGauge > 10)
		{
			adjustGauge = 10;
		}

		obj->clipSize.x = addGauge * (20 - adjustGauge);

		if (obj->clipSize.x > 320)
		{
			obj->clipSize.x = 320;
			obj->timer		= 0;
			addGauge		= 0;
			feverCount++;
			obj->state++;
		}
		
		break;
	case 2:
		//-- フィーバー中 --//
		addGauge = 0;
		obj->animeState = 0;
		obj->animeTimer = 0;

		obj->timer++;
		if (obj->timer % 20 == 0)
		{
			obj->clipSize.x -= 10;
		}

		if (obj->clipSize.x <= 0)
		{
			obj->clipSize.x = 0;
			obj->timer = 0;
			obj->state = 1;
		}

		break;
	}
}

//SCOREの計算　　(1: 現在のコンボ数 2: ブロックの消した個数 3: 現在の消す数倍率)
int UiScore::calcScore(const int combo, const int blockNum,float* eraseBlockPow)
{
	float powCombo = 1 + (static_cast<float>(combo) / 10);	//コンボ数による倍率(前の1は等倍になるように)
	if (blockNum == 3) *eraseBlockPow += 0.2f;
	if (blockNum == 4) *eraseBlockPow += 0.5f;

	float score = 100 * powCombo * (*eraseBlockPow);

	return static_cast<int>(score);
}

//ゲージの増加 (1 : 一回で消したブロックの数 , 2: プレイヤー番号)
void UiGauge::calcGauge(const int eraseNum, const int playerNo)
{
	addGauge += eraseNum;
}

void UiTimer::move(OBJ2D* obj)
{
	moveTimer(obj,pos);
}

void UiCombo::move(OBJ2D* obj)
{
	moveCombo(obj);
}

void UiScore::move(OBJ2D* obj)
{
	moveScore(obj);
}

void UiGauge::move(OBJ2D* obj)
{
	moveGauge(obj);
}

////-- デストラクタ --////
UiScore :: ~UiScore()
{
	if (score_1 != 0)	Result::resultScore_1 = score_1;
	if (score_2 != 0)	Result::resultScore_2 = score_2;
	
	score_1					= 0;
	score_2					= 0;
	eraseBlockPow_1			= 0;
	eraseBlockPow_2			= 0;
}

void EraseUi::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}

void UiCounter::init()
{
	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			counter[h][w].reset();
		}
	}
}

void UiCounter::update()
{
	bool moveFrag = false;

	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if (counter[h][w].existFrag)
			{
				switch (counter[h][w].state)
				{
				case 0:
					counter[h][w].timer			= n_general_function::setTimer(10);
					counter[h][w].animeState	= 0;
					counter[h][w].animeTimer	= 0;

					counter[h][w].state++;
					break;
				case 1:
					if (h == 0)
					{
						counter[h][w].timer--;

						if (counter[h][w].timer < n_general_function::setTimer(7))  counter[h][w].animeTimer = 1;
						if (counter[h][w].timer < n_general_function::setTimer(3))  counter[h][w].animeTimer = 2;

						if (counter[h][w].timer <= 0)
						{
							counter[h][w].state++;
						}
					}
					break;
				case 2:
					counter[h][w].existFrag = false;
					counter[h][w].moveFrag  = true;
					counter[h][w].savePos   = counter[h][w].pos;
					moveFrag				= true;
					break;
				}
			}
			
			//-- 一列ブロックが消えると下に動く処理 --//
			if (counter[h][w].moveFrag)
			{
				counter[h][w].gravity += 0.025f;
				counter[h][w].pos.y += counter[h][w].gravity;

				//-- 一定のpos以上いけば止まる --//
				if (counter[h][w].pos.y > counter[h][w].savePos.y + COUNTER_BLOCK_SPACE)
				{
					counter[h][w].pos.y    = counter[h][w].savePos.y + COUNTER_BLOCK_SPACE;
					counter[h][w].gravity  = 0;
					counter[h][w].moveFrag = false;
					counter[h][w].copyFrag = true;
				}
			}
		}
	}

	for (int h = 1; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if (counter[h][w].existFrag)
			{
				counter[h][w].pos.y		= counter[h - 1][0].pos.y - COUNTER_BLOCK_SPACE;

				if (counter[h - 1][0].moveFrag)
				{
					counter[h][w].moveFrag = true;
				}
			}
		}
	}

	bool eraseFrag = false;
		
	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if(counter[h][w].existFrag)
			{
				if (moveFrag)
				{
					counter[h][w].setMoveFrag(&counter[h][w], true);
					counter[h][w].savePos = counter[h][w].pos;
				}
				if (counter[h][w].copyFrag)
				{
					counter[h][w].copyFrag = false;
					moveOBJData(&counter[h - 1][w], &counter[h][w]);
					counter[h][w].reset();
					eraseFrag = true;
				}
			}
		}
	}

	if (eraseFrag)
	{
		int maxHeight = 0;

		for (int h = COUNTER_MAX_H; h > 0; h--)
		{
			if (counter[h][0].existFrag)
			{
				maxHeight = h;
				break;
			}
		}

		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			//counter[maxHeight][w].reset();
		}
	}
}

void UiCounter::draw()
{
	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if (counter[h][w].existFrag)
			{
				DrawRotaGraph3
				(
					counter[h][w].pos.x, counter[h][w].pos.y,
					counter[h][w].size.x, counter[h][w].size.y,
					counter[h][w].scale.x, counter[h][w].scale.y,
					counter[h][w].angle,
					n_texture::sprCounterBlock[counter[h][w].animeState + counter[h][w].animeTimer],
					true,
					false
				);
			}
		}
	}
}

void UiCounter::calcCounterBlockNum(UiCounter* counter, int posX, int height, bool center)
{
	//-- カーソル中央時 --//
	if (center)
	{
		//-- 相手に送るブロックの個数指定 --//
		switch (counter->breakBlock_2)
		{
		case 1:
			counter->arrNo_W = 1;
			break;
		case 2:
			counter->arrNo_W = 3;
			break;
		case 3:
			counter->arrNo_W = 4;
			break;
		case 4:
			counter->arrNo_W = 5;
			break;
		}
		counter->breakBlock_2 = 0;
	}
	else
	{
		int num1 = 0;
		int num2 = 0;
		int num3 = 0;

		//-- 生成するカウンターブロックの個数  (いくつのブロックを消したか * 生成するブロック数) --//
		num1 = counter->breakBlock_2 * 1;
		num2 = counter->breakBlock_3 * 2;
		num3 = counter->breakBlock_4 * 3;

		counter->arrNo_W = num1 + num2 + num3;

		counter->breakBlock_2 = 0;
		counter->breakBlock_3 = 0;
		counter->breakBlock_4 = 0;
	}

	for (int w = 0; w < counter->arrNo_W; w++)
	{
		counter->counter[height][w].serchSet(&counter->counter[height][w], { static_cast<float>(posX + w * 32) ,static_cast<float>(-(height * COUNTER_BLOCK_SPACE) + 80) }, { COUNTER_BLOCK_CHIP_SIZE_W ,COUNTER_BLOCK_CHIP_SIZE_H }, w);
	}
}

void UiCounter::addCounterBlock(UiCounter* counter,const int blockNum)
{
	if (blockNum == 2)
	{
		counter->breakBlock_2++;
	}
	if (blockNum == 3)
	{
		counter->breakBlock_3++;
	}
	if (blockNum == 4)
	{
		counter->breakBlock_4++;
	}
}



