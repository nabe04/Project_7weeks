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
#include "press.h"
#include "effect.h"

//--Gameクラス--//
class Game : public Scene
{
private:
	bool isPausedFrag	= false;	//ポーズ
	bool keyTrg			= false;	//キートリガー
	bool gameEndFrag	= false;	//ゲーム終了フラグ (true : 終了 , false : ゲーム中)

	//メンバ変数は後ろに_をつける
	PlayerManager*			playerManager_			= nullptr;	//Player
	BG*						bgManager_				= nullptr;	//BG
	BG*						bgFramaManger_1_		= nullptr;	//FeverFrame
	BG*						bgFramaManger_2_		= nullptr;	//FeverFrame
	Block_1*				block1Manager_			= nullptr;	//Block (プレイヤー 1)
	Block_2*				block2Manager_			= nullptr;	//Block (プレイヤー 2)
	CursorManager*			cursorManager_			= nullptr;	//Cursor
	UiManager*				uiTimerManager_1_		= nullptr;	//UI Timer(プレイヤー 1)
	UiManager*				uiTimerManager_2_		= nullptr;	//UI Timer(プレイヤー 2)
	UiManager*				uiComboManager_1_		= nullptr;	//UI Combo(プレイヤー 1)
	UiManager*				uiComboManager_2_		= nullptr;	//UI Combo(プレイヤー 2)
	UiManager*				uiScoreManager_1_		= nullptr;	//UI Score(プレイヤー 1)
	UiManager*				uiScoreManager_2_		= nullptr;  //UI Score(プレイヤー 2)
	UiManager*				uiGaugeManager_1_		= nullptr;	//UI Gauge(プレイヤー 1)
	UiManager*				uiGaugeManager_2_		= nullptr;	//UI Gauge(プレイヤー 2)
	PressMachineManager_1*	pressMachineManager_	= nullptr;	//Press Machine
	PressMachineManager_2* pressMachineManager_2_   = nullptr;  //Press Machine2
	EffectManager*			pressEffectManager_		= nullptr;	//Press Effect
	

	static Game instance_;

public:
	static int  gameMode;		//プレイヤーの人数
	static Game* instance() { return &instance_; }

	void init()		override;
	void update()	override;
	void draw()		override;
	void uninit()	override;

	//ゲッターは後ろに_を付けない
	PlayerManager*			playerManager()			{ return playerManager_; }
	BG*						bgManager()				{ return bgManager_; }
	BG*						bgFrameManager_1()		{ return bgFramaManger_1_; }
	BG*						bgFrameManager_2()		{ return bgFramaManger_2_; }
	Block_1*				block1Manger()			{ return block1Manager_; }
	Block_2*				block2Manger()			{ return block2Manager_; }
	CursorManager*			cursorManager()			{ return cursorManager_; }
	UiManager*				uiTimerManager_1()		{ return uiTimerManager_1_; }
	UiManager*				uiTimerManager_2()		{ return uiTimerManager_2_; }
	UiManager*				uiComboManager_1()		{ return uiComboManager_1_; }
	UiManager*				uiComboManager_2()		{ return uiComboManager_2_; }
	UiManager*				uiScoreManager_1()		{ return uiScoreManager_1_; }
	UiManager*				uiScoreManager_2()		{ return uiScoreManager_2_; }
	UiManager*				uiGaugeManager_1()		{ return uiGaugeManager_1_; }
	UiManager*				uiGaugeManager_2()		{ return uiGaugeManager_2_; }
	PressMachineManager_1*	pressMachineManager_1()	{ return pressMachineManager_; }
	PressMachineManager_2*  pressMachineManager_2() { return pressMachineManager_2_; }
	EffectManager*			pressEffectManager()	{ return pressEffectManager_; }
	
};