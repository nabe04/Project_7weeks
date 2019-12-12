#pragma once

//***********************************************************************//
//																		 //
//							�Q�[��										 //
//																		 //
//***********************************************************************//
#include "bg.h"
#include "block.h"
#include "cursor.h"
#include "ui.h"

//--Game�N���X--//
class Game : public Scene
{
private:
	bool isPausedFrag;	//�|�[�Y
	bool keyTrg;		//�L�[�g���K�[

	//�����o�ϐ��͌���_������
	PlayerManager*	playerManager_;		//Player
	BG*				bgManager_;			//BG
	Block*			block1Manager_;		//Block
	CursorManager*  cursorManager_;		//Cursor
	UiManager*		uiTimerManager_;	//UI Timer
	UiManager*		uiComboManager_;	//UI Combo

	static Game instance_;

public:
	static int  playerNum;		//�v���C���[�̐l��
	static Game* instance() { return &instance_; }

	void init();
	void update();
	void draw();
	void uninit();

	//�Q�b�^�[�͌���_��t���Ȃ�
	PlayerManager*	playerManager()		{ return playerManager_; }
	BG*				bgManager()			{ return bgManager_; }
	Block*			block1Manger()		{ return block1Manager_; }
	CursorManager*	cursorManager()		{ return cursorManager_; }
	UiManager*		uiTimerManager()	{ return uiTimerManager_; }
	UiManager*		uiComboManager()	{ return uiComboManager_; }
};