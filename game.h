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
#include "player.h"

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
	UiManager*		uiComboManager_1_;	//UI Combo(プレイヤー 1)
	UiManager*		uiComboManager_2_;	//UI Combo(プレイヤー 2)
	UiManager*		uiScoreManager_1_;	//UI Score(プレイヤー 1)
	UiManager*		uiScoreManager_2_;  //UI Score(プレイヤー 2)

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
	UiManager*		uiComboManager_1()	{ return uiComboManager_1_; }
	UiManager*		uiComboManager_2()	{ return uiComboManager_2_; }
	UiManager*		uiScoreManager_1()	{ return uiScoreManager_1_; }
	UiManager*		uiScoreManager_2()	{ return uiScoreManager_2_; }
};