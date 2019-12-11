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
#include "scene.h"
#include "title.h"
#include "game.h"

////--namespace--////
using namespace n_texture;
using namespace n_font;

////--変数--////
Game Game::instance_;

////--初期化処理--////
void Game::init()
{
	Scene::init();			//基底クラスのinitを呼ぶ

	playerManager_  = new PlayerManager;
	bgManager_		= new BG;
	block1Manager_	= new Block_1;
	cursorManager_  = new CursorManager;
	uiTimerManager_	= new UiManager;
	uiComboManager_ = new UiManager;

	isPausedFrag	= false;	//ポーズフラグの初期化
	keyTrg			= false;	//キートリガーの初期化

	UI::nowCombo	= 0;		//staticメンバ変数の初期化

	//--ロード--//
#ifdef DEBUG_TEX
	//テクスチャ
	LoadDivGraph(gh_player ,  1               , 1             , 1		      , DEBUG_PLAYER_SIZE, DEBUG_PLAYER_SIZE    , storePlayer);		//Player
	LoadDivGraph(gh_bg     ,  BG_CHIP_NUM     , BG_CHIP_W     , BG_CHIP_H     , CHIP_SIZE		 , CHIP_SIZE			, storeBG);			//背景
	LoadDivGraph(gh_terrain,  TERRAIN_CHIP_NUM, TERRAIN_CHIP_W, TERRAIN_CHIP_H, CHIP_SIZE		 , CHIP_SIZE			, storeTerrain);	//地形

	//フォント
	fontTimer = CreateFontToHandle("Nu よもぎもち 標準-丸1", 50, 3, DX_FONTTYPE_NORMAL);

#endif // !DEBUG_TEX
	LoadDivGraph(gh_block	, BLOCK_CHIP_NUM  , BLOCK_CHIP_W   , BLOCK_CHIP_H , BLOCK_CHIP_SIZE ,  BLOCK_CHIP_SIZE		, sprBlock);
	LoadDivGraph(gh_cursor_w,				 1,				  1,			 1,		    CURSOR_W,  CURSOR_CHIP_SIZE		, sprCursorW);
	LoadDivGraph(gh_cursor_h,				 1,				  1,			 1,	CURSOR_CHIP_SIZE,  CURSOR_H				, sprCursorH);
	LoadDivGraph(gh_cursor_c,				 1,				  1,			 1,		 CURSOR_SIZE,			 CURSOR_SIZE, sprCursorC);
	LoadDivGraph(gh_cursor	, CURSOR_CHIP_NUM , CURSOR_CHIP_W  , CURSOR_CHIP_H,      CURSOR_SIZE,  CURSOR_SIZE			, sprCursor);
	LoadDivGraph(gh_line	,				 1,				  1,			 1,	      LINE_WIDTH,  LINE_HEIGHT			, sprLine);
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
	else
	{
		keyTrg = true;
	}
	if (isPausedFrag)  return;				//ポーズ中ならリターン

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
			uiTimerManager()->init();
			uiComboManager()->init();

			//プレイヤー(自分で操作)を追加する
			playerManager()->add(&player, n_texture::storePlayer, TEXTURE, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			cursorManager()->add(&cursorW, n_texture::sprLine, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorH, n_texture::sprLine, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorCenter, n_texture::sprCursorC, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });
			cursorManager()->add(&cursorPivot, n_texture::sprCursor, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });

#ifdef DEBUG_
			uiTimerManager()->add(&uiTimer, &fontTimer, FONT, Vector2F{ -500,-500 }, Vector2F{ 64,64 });

#endif // DEBUG_

			state++;	//初期化処理の終了

						/*fallthrough*/
		case 1:
			/////通常時の処理/////

			timer++;

			playerManager()->update();
			bgManager()->update();
			cursorManager()->update();
			block1Manger()->update();
			uiTimerManager()->update();
			uiComboManager()->update();

			break;
		}
	}
	
}

////--描画処理--////
void Game::draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255), "Game", 100);

	//プレイヤーの描画
	//bgManager()->drawBack();
	//bgManager()->drawTerrain();
	block1Manger()->draw();
	cursorManager()->draw();
	playerManager()->draw();
	uiTimerManager()->draw();
	uiComboManager()->draw();
}

////--終了処理--////
void Game::uninit()
{
	safe_delete(playerManager_);
	safe_delete(bgManager_);
	safe_delete(block1Manager_);
	safe_delete(cursorManager_);
	safe_delete(uiTimerManager_);

	DeleteFontToHandle(fontTimer);
}

