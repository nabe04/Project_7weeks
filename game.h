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
	Block*			blockManager_;		//Block
	CursorManager*  cursorManager_;		//Cursor
	UiManager*		uiTimerManager_;	//UI Timer
	UiManager*		uiComboManager_;	//UI Combo

	static Game instance_;

public:
	static Game* instance() { return &instance_; }

	void init();
	void update();
	void draw();
	void uninit();

	//ゲッターは後ろに_を付けない
	PlayerManager*	playerManager()		{ return playerManager_; }
	BG*				bgManager()			{ return bgManager_; }
	Block*			blockManger()		{ return blockManager_; }
	CursorManager*	cursorManager()		{ return cursorManager_; }
	UiManager*		uiTimerManager()	{ return uiTimerManager_; }
	UiManager*		uiComboManager()	{ return uiComboManager_; }
};