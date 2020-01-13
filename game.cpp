//***********************************************************************//
//																		 //
//							ゲーム										 //
//																		 //
//***********************************************************************//

#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "actor.h"
#include "player.h"
#include "block.h"
#include "cursor.h"
#include "ui.h"
#include "load_texture.h"
#include "bg.h"
#include "bg_maps.h"
#include "press.h"
#include "effect.h"
#include "MyImgui.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "scene_result.h"

////--namespace--////
using namespace n_texture;
using namespace n_font;

////--変数--////
Game Game::instance_;
int  Game::gameMode;

////--初期化処理--////
void Game::init()
{
	Scene::init();			//基底クラスのinitを呼ぶ

	playerManager_			= new PlayerManager;
	bgManager_				= new BG;
	bgFramaManger_1_		= new BG;
	bgFramaManger_2_		= new BG;
	block1Manager_			= new Block_1;
	block2Manager_			= new Block_2;
	cursorManager_			= new CursorManager;
	uiTimerManager_1_		= new UiManager;
	uiTimerManager_2_		= new UiManager;
	uiComboManager_1_		= new UiManager;
	uiComboManager_2_		= new UiManager;
	uiScoreManager_1_		= new UiManager;
	uiScoreManager_2_		= new UiManager;
	uiGaugeManager_1_		= new UiManager;
	uiGaugeManager_2_		= new UiManager;
	pressMachineManager_	= new PressMachineManager_1;
	pressMachineManager_2_	= new PressMachineManager_2;
	pressEffectManager_		= new EffectManager;	

	isPausedFrag		= false;		//ポーズフラグの初期化
	keyTrg				= false;		//キートリガーの初期化

	UI::nowCombo_1		= 0;			//staticメンバ変数の初期化
	UI::nowCombo_2		= 0;
	UI::eraseBlockPow_1 = 1.0f;			//掛ける倍率の初期化なので1.0fでいい
	UI::eraseBlockPow_2 = 1.0f;

	gameMode			= getSelect();	//ゲームモード取得(0 : 一人プレイ 1:二人プレイ)

	//--ロード--//
#ifdef DEBUG_TEX
	//テクスチャ
	LoadDivGraph(gh_player ,  1               , 1             , 1		      , DEBUG_PLAYER_SIZE, DEBUG_PLAYER_SIZE    , storePlayer);		//Player
	LoadDivGraph(gh_bg     ,  BG_CHIP_NUM     , BG_CHIP_W     , BG_CHIP_H     , CHIP_SIZE		 , CHIP_SIZE			, storeBG);			//背景
	LoadDivGraph(gh_terrain,  TERRAIN_CHIP_NUM, TERRAIN_CHIP_W, TERRAIN_CHIP_H, CHIP_SIZE		 , CHIP_SIZE			, storeTerrain);	//地形

	//フォント
	fontYomogi = CreateFontToHandle("Nu よもぎもち 標準-丸1", 50, 3, DX_FONTTYPE_NORMAL);

#endif // !DEBUG_TEX
	LoadDivGraph(gh_block		,		 BLOCK_CHIP_NUM  ,	    BLOCK_CHIP_W   ,		  BLOCK_CHIP_H ,     	  BLOCK_CHIP_SIZE ,           BLOCK_CHIP_SIZE, sprBlock);
	LoadDivGraph(gh_cursor_w	,						1,				      1,					  1,     		      CURSOR_W,          CURSOR_CHIP_SIZE, sprCursorW);
	LoadDivGraph(gh_cursor_h	,						1,					  1,					  1,     	  CURSOR_CHIP_SIZE,                  CURSOR_H, sprCursorH);
	LoadDivGraph(gh_my_block	,						1,					  1,					  1,     		   CURSOR_SIZE,			      CURSOR_SIZE, sprCursorC);
	LoadDivGraph(gh_cursor		,		 CURSOR_CHIP_NUM ,	    CURSOR_CHIP_W  ,		  CURSOR_CHIP_H,     		   CURSOR_SIZE,               CURSOR_SIZE, sprCursor);
	LoadDivGraph(gh_line		,						1,					  1,				      1,     	        LINE_WIDTH,               LINE_HEIGHT, sprLine);
	LoadDivGraph(gh_frame		,						1,					  1,					  1,     	    	FRAME_SIZE,			       FRAME_SIZE, sprFrame);
	LoadDivGraph(gh_gauge		,			  UI_CHIP_NUM,		      UI_CHIP_W,			  UI_CHIP_H,      	   UI_GAUGE_SIZE_W,		      UI_GAUGE_SIZE_H, sprGauge);
	LoadDivGraph(gh_gauge_frame	,						1,					  1,					  1,     	   UI_GAUGE_SIZE_W,		      UI_GAUGE_SIZE_H, sprGaugeFrame);
	LoadDivGraph(gh_back		,						1,					  1,					  1,     	 	   BACK_SIZE_W,	  		      BACK_SIZE_H, sprBG);
	LoadDivGraph(gh_bloken_block,	BLOKEN_BLOCK_CHIP_NUM,	BLOKEN_BLOCK_CHIP_W,	BLOKEN_BLOCK_CHIP_H,         BLOKEN_BLOCK_SIZE,	        BLOKEN_BLOCK_SIZE, sprBlokenBLock);
	LoadDivGraph(gh_press_machine,						1,					  1,				      1,     		  PRESS_SIZE_W,			     PRESS_SIZE_H, sprPressMachine);
	LoadDivGraph(gh_press_effect,	PRESS_EFFECT_CHIP_NUM,	PRESS_EFFECT_CHIP_W,    PRESS_EFFECT_CHIP_H,       PRESS_EFFECT_SIZE_W,		  PRESS_EFFECT_SIZE_H, sprPressEffect);
	LoadDivGraph(gh_counter_block, COUNTER_BLOCK_CHIP_NUM, COUNTER_BLOCK_CHIP_W,   COUNTER_BLOCK_CHIP_H, COUNTER_BLOCK_CHIP_SIZE_W, COUNTER_BLOCK_CHIP_SIZE_H, sprCounterBlock);
}

////--更新処理--////
void Game::update()
{
	char key[KEY_MAX];
	GetHitKeyStateAll(key);

	//Pad入力処理
	padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//ソフトリセット(START)
	if (padInput & PAD_INPUT_R)
	{
		if (keyTrg)
		{
			keyTrg = false;
			changeScene(Title::instance());   // タイトルシーンに切り替える
			return;
		}
	}
	//ポーズ処理(Back)
	else if (key[KEY_INPUT_DOWN])
	{
		if (keyTrg)
		{
			keyTrg		  = false;
			isPausedFrag != isPausedFrag;		//Backボタンが押されたらポーズ状態が反転
		}
	}
	else if (padInput & PAD_INPUT_L)
	{
		if (keyTrg)
		{
			keyTrg = false;
			changeScene(Result::instance());   // タイトルシーンに切り替える
			return;
		}
	}
	else
	{
		keyTrg = true;
	}
	if (isPausedFrag)  return;				//ポーズ中ならリターン

	//-- 一人プレイ時 --//
	if (getSelect() == ONE_PLAY)
	{
		switch (state)
		{
		case 0:
			//////初期設定//////

			timer = 0;

			//プレイヤーマネージャの初期化
			playerManager()->init();

			//BGマネージャの初期化
			bgManager()->init();

			//Blockマネージャの初期化
			block1Manger()->init();

			//Cursorマネージャの初期化
			cursorManager()->init();

			//UI
			uiTimerManager_1()->init();
			uiComboManager_1()->init();
			uiScoreManager_1()->init();

			//Press Machine
			pressMachineManager_1()->init();

			//Press Effect
			pressEffectManager()->init();

			//プレイヤー(自分で操作)を追加する (プレイヤー 1)
			playerManager()->add(&player		, n_texture::storePlayer	, TEXTURE, Vector2F{ 0,0 }		, Vector2F{ 64,64 });
			cursorManager()->add(&cursorW		, n_texture::sprLine		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorH		, n_texture::sprLine		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorCenter	, n_texture::sprCursorC		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });
			cursorManager()->add(&cursorPivot	, n_texture::sprCursor		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });

			//UI
			uiTimerManager_1()->add(	&uiTimer_1	, &fontYomogi		, FONT		, Vector2F{ -500,-500 }, Vector2F{ 64,64 });
			uiScoreManager_1()->add(&uiScore_1	, &fontYomogi		, FONT		, Vector2F{ -500,-500 }, Vector2F{ 64,64 });
			uiGaugeManager_1()->add(&uiGauge_1  ,n_texture::sprGauge, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ UI_GAUGE_SIZE_W,UI_GAUGE_SIZE_H });

			state++;	//初期化処理の終了

						/*fallthrough*/
		case 1:
			/////通常時の処理/////

			timer++;

			playerManager()->update();
			bgManager()->update();
			cursorManager()->update();
			block1Manger()->update();
			uiTimerManager_1()->update();
			uiComboManager_1()->update();
			uiScoreManager_1()->update();
			uiGaugeManager_1()->update();
			pressMachineManager_1()->update();
			pressEffectManager()->update();

	#ifdef USE_IMGUI
			im_Ui.uiPlatform();
			im_Ui.cursorPlatform();
	#endif // USE_IMGUI

			break;
		}
	}

	////-- 二人プレイ時 --////
	if (getSelect() == TWO_PLAY)
	{
		switch (state)
		{
		case 0:
			//////初期設定//////

			timer = 0;

			//プレイヤーマネージャの初期化
			playerManager()->init();

			//BGマネージャの初期化
			bgManager()->init();

			//Blockマネージャの初期化
			block1Manger()->init();
			block2Manger()->init();
			
			//Cursorマネージャの初期化
			cursorManager()->init();

			//UI
			uiTimerManager_1()->init();
			uiTimerManager_2()->init();
			uiComboManager_1()->init();
			uiComboManager_2()->init();
			uiScoreManager_1()->init();
			uiScoreManager_2()->init();

			uiCounter_1.init();
			uiCounter_2.init();

			//要らん
			//uiCounterManager_1()->init();	//Counter
			//uiCounterManager_2()->init();

			//Press Machine
			pressMachineManager_1()->init();
			pressMachineManager_2()->init();

			//Press Effect
			pressEffectManager()->init();

			//プレイヤー(自分で操作)を追加する
			playerManager()->add(&player		, n_texture::storePlayer, TEXTURE	, Vector2F{ 0,0 }		, Vector2F{ 64,64 });
			cursorManager()->add(&cursorW		, n_texture::sprLine	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorH		, n_texture::sprLine	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorCenter	, n_texture::sprCursorC	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });
			cursorManager()->add(&cursorPivot	, n_texture::sprCursor	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });

			//プレイヤー 2
			cursorManager()->add(&cuesorW_2		, n_texture::sprLine	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorH_2		, n_texture::sprLine	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorCenter_2, n_texture::sprCursorC	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });
			cursorManager()->add(&cursorPivot_2	, n_texture::sprCursor	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });

			//UI
			uiTimerManager_1()->add(&uiTimer_1	, &fontYomogi			, FONT		, Vector2F{ -500,-500 }, Vector2F{ 64,64 }, "Nu よもぎもち 標準-丸1");
			uiTimerManager_2()->add(&uiTimer_2	, &fontYomogi			, FONT		, Vector2F{ -500,-500 }, Vector2F{ 64,64 }, "Nu よもぎもち 標準-丸1");
			uiScoreManager_1()->add(&uiScore_1	, &fontYomogi			, FONT		, Vector2F{ -500,-500 }, Vector2F{ 64,64 }, "Nu よもぎもち 標準-丸1");
			uiScoreManager_2()->add(&uiScore_2	, &fontYomogi			, FONT		, Vector2F{ -500,-500 }, Vector2F{ 64,64 }, "Nu よもぎもち 標準-丸1");
			uiGaugeManager_1()->add(&uiGauge_1	, n_texture::sprGauge	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ UI_GAUGE_SIZE_W,UI_GAUGE_SIZE_H });
			uiGaugeManager_2()->add(&uiGauge_2	, n_texture::sprGauge	, TEXTURE	, Vector2F{ -500,-500 }, Vector2F{ UI_GAUGE_SIZE_W,UI_GAUGE_SIZE_H });

			state++;	//初期化処理の終了
						/*fallthrough*/
		case 1:
			/////通常時の処理/////

			timer++;

			playerManager()->update();
			bgManager()->update();
			cursorManager()->update();
			block1Manger()->update();
			block2Manger()->update();
			uiTimerManager_1()->update();
			uiTimerManager_2()->update();
			uiComboManager_1()->update();
			uiComboManager_2()->update();
			uiScoreManager_1()->update();
			uiScoreManager_2()->update();
			uiGaugeManager_1()->update();
			uiGaugeManager_2()->update();
			pressMachineManager_1()->update();
			pressMachineManager_2()->update();
			pressEffectManager()->update();
			uiCounter_1.update();
			uiCounter_2.update();

			//要らん
			//uiCounterManager_1()->update();			//Counter
			//uiCounterManager_2()->update();


#ifdef USE_IMGUI
			im_Ui.uiPlatform();
			im_Ui.cursorPlatform();
#endif // USE_IMGUI
			break;
		}
	}
}

////--描画処理--////
void Game::draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255), "Game", 100);

	//プレイヤーの描画
	bgManager()->drawBack();
	//bgManager()->drawTerrain();
	block1Manger()->draw();
	block1Manger()->drawBloken();
	if (gameMode == TWO_PLAY)
	{
		block2Manger()->draw();
		block2Manger()->drawBloken();
	}
	pressMachineManager_1()->draw();
	if (gameMode == TWO_PLAY)
	{
		pressMachineManager_2()->draw();
	}
	cursorManager()->draw();
	playerManager()->draw();
	uiTimerManager_1()->draw();
	if (gameMode == TWO_PLAY)
	{
		uiTimerManager_2()->draw();
	}
	uiComboManager_1()->draw();
	if (gameMode == TWO_PLAY)	uiComboManager_2()->draw();
	uiScoreManager_1()->draw();
	if (gameMode == TWO_PLAY)   uiScoreManager_2()->draw();
	uiGaugeManager_1()->draw();
	if (gameMode == TWO_PLAY)   uiGaugeManager_2()->draw();
	bgFrameManager_1()->draw(n_texture::sprGaugeFrame, &gaugeFrame_1.obj);
	if(gameMode == TWO_PLAY)	bgFrameManager_2()->draw(n_texture::sprGaugeFrame, &gaugeFrame_2.obj);
	pressEffectManager()->draw();
	if (gameMode == TWO_PLAY)
	{
		uiCounter_1.draw();
		uiCounter_2.draw();

		//要らん
		/*uiCounterManager_1()->draw();
		uiCounterManager_2()->draw();*/
	}

}

////--終了処理--////
void Game::uninit()
{
	safe_delete(playerManager_);
	safe_delete(bgManager_);
	safe_delete(bgFramaManger_1_);
	safe_delete(bgFramaManger_2_);
	safe_delete(block1Manager_);
	safe_delete(block2Manager_);
	safe_delete(cursorManager_);
	safe_delete(uiTimerManager_1_);
	safe_delete(uiTimerManager_2_);
	safe_delete(uiComboManager_1_);
	safe_delete(uiComboManager_2_);
	safe_delete(uiScoreManager_1_);
	safe_delete(uiScoreManager_2_);
	safe_delete(uiGaugeManager_1_);
	safe_delete(uiGaugeManager_2_);
	safe_delete(pressMachineManager_);
	safe_delete(pressMachineManager_2_);
	safe_delete(pressEffectManager_);

	uiCombo_1.~UiCombo();
	uiCombo_2.~UiCombo();
	uiScore_1.~UiScore();
	uiScore_2.~UiScore();

	//グラフィックハンドルの削除
	DeleteGraph(storePlayer[NO_ANIMATION]);
	DeleteGraph(storeBG[BG_CHIP_NUM]);
	DeleteGraph(storeTerrain[TERRAIN_CHIP_NUM]);
	DeleteGraph(sprBlock[BLOCK_CHIP_NUM]);
	DeleteGraph(sprMyBlock[NO_ANIMATION]);
	DeleteGraph(sprCursorW[NO_ANIMATION]);
	DeleteGraph(sprCursorH[NO_ANIMATION]);
	DeleteGraph(sprCursorC[NO_ANIMATION]);
	DeleteGraph(sprLine[NO_ANIMATION]);
	DeleteGraph(sprCursor[CURSOR_CHIP_NUM]);
	DeleteGraph(sprFrame[NO_ANIMATION]);
	DeleteGraph(sprGauge[NO_ANIMATION]);
	DeleteGraph(sprGaugeFrame[NO_ANIMATION]);
	DeleteGraph(sprBG[NO_ANIMATION]);
	DeleteGraph(sprBlokenBLock[BLOKEN_BLOCK_CHIP_NUM]);
	DeleteGraph(sprPressMachine[NO_ANIMATION]);
	DeleteGraph(sprPressEffect[PRESS_EFFECT_CHIP_NUM]);
	DeleteGraph(sprCounterBlock[COUNTER_BLOCK_CHIP_NUM]);

	//フォントハンドルの削除
	DeleteFontToHandle(fontYomogi);
}

