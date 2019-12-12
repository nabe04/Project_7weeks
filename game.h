#pragma once

//***********************************************************************//
//																		 //
//							ゲーム										 //
//																		 //
//***********************************************************************//
#include "bg.h"
#include "block.h"
#include "cursor.h"
#include "ui.h"

//--Gameクラス--//
class Game : public Scene
{
private:
	bool isPausedFrag;	//ポーズ
	bool keyTrg;		//キートリガー

	//メンバ変数は後ろに_をつける
	PlayerManager*	playerManager_;		//Player
	BG*				bgManager_;			//BG
	Block_1*		block1Manager_;		//Block (プレイヤー 1)
	Block_2*		block2Manager_;		//Block (プレイヤー 2)
	CursorManager*  cursorManager_;		//Cursor
	UiManager*		uiTimerManager_;	//UI Timer
	UiManager*		uiComboManager_;	//UI Combo

	static Game instance_;

public:
	static int  playerNum;		//プレイヤーの人数
	static Game* instance() { return &instance_; }

	void init();
	void update();
	void draw();
	void uninit();

	//ゲッターは後ろに_を付けない
	PlayerManager*	playerManager()		{ return playerManager_; }
	BG*				bgManager()			{ return bgManager_; }
	Block_1*		block1Manger()		{ return block1Manager_; }
	Block_2*		block2Manger()		{ return block2Manager_; }
	CursorManager*	cursorManager()		{ return cursorManager_; }
	UiManager*		uiTimerManager()	{ return uiTimerManager_; }
	UiManager*		uiComboManager()	{ return uiComboManager_; }
};