//***********************************************************************//
//																		 //
//							�Q�[��										 //
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

////--�ϐ�--////
Game Game::instance_;
int  Game::playerNum;

////--����������--////
void Game::init()
{
	Scene::init();			//���N���X��init���Ă�

	playerManager_  = new PlayerManager;
	bgManager_		= new BG;
	block1Manager_	= new Block;
	cursorManager_  = new CursorManager;
	uiTimerManager_	= new UiManager;
	uiComboManager_ = new UiManager;

	isPausedFrag	= false;	//�|�[�Y�t���O�̏�����
	keyTrg			= false;	//�L�[�g���K�[�̏�����

	UI::nowCombo	= 0;		//static�����o�ϐ��̏�����

	playerNum		= getSelect();	//�v���C���[�̐l���擾

	//--���[�h--//
#ifdef DEBUG_TEX
	//�e�N�X�`��
	LoadDivGraph(gh_player ,  1               , 1             , 1		      , DEBUG_PLAYER_SIZE, DEBUG_PLAYER_SIZE    , storePlayer);		//Player
	LoadDivGraph(gh_bg     ,  BG_CHIP_NUM     , BG_CHIP_W     , BG_CHIP_H     , CHIP_SIZE		 , CHIP_SIZE			, storeBG);			//�w�i
	LoadDivGraph(gh_terrain,  TERRAIN_CHIP_NUM, TERRAIN_CHIP_W, TERRAIN_CHIP_H, CHIP_SIZE		 , CHIP_SIZE			, storeTerrain);	//�n�`

	//�t�H���g
	fontTimer = CreateFontToHandle("Nu ��������� �W��-��1", 50, 3, DX_FONTTYPE_NORMAL);

#endif // !DEBUG_TEX
	LoadDivGraph(gh_block	, BLOCK_CHIP_NUM  , BLOCK_CHIP_W   , BLOCK_CHIP_H , BLOCK_CHIP_SIZE ,  BLOCK_CHIP_SIZE		, sprBlock);
	LoadDivGraph(gh_cursor_w,				 1,				  1,			 1,		    CURSOR_W,  CURSOR_CHIP_SIZE		, sprCursorW);
	LoadDivGraph(gh_cursor_h,				 1,				  1,			 1,	CURSOR_CHIP_SIZE,  CURSOR_H				, sprCursorH);
	LoadDivGraph(gh_cursor_c,				 1,				  1,			 1,		 CURSOR_SIZE,			 CURSOR_SIZE, sprCursorC);
	LoadDivGraph(gh_cursor	, CURSOR_CHIP_NUM , CURSOR_CHIP_W  , CURSOR_CHIP_H,      CURSOR_SIZE,  CURSOR_SIZE			, sprCursor);
	LoadDivGraph(gh_line	,				 1,				  1,			 1,	      LINE_WIDTH,  LINE_HEIGHT			, sprLine);
}

////--�X�V����--////
void Game::update()
{
	char key[KEY_MAX];
	GetHitKeyStateAll(key);

	//Pad���͏���
	padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//�\�t�g���Z�b�g(START)
	if (padInput & PAD_INPUT_R)
	{
		if (keyTrg)
		{
			keyTrg = false;
			changeScene(Title::instance());   // �^�C�g���V�[���ɐ؂�ւ���
			return;
		}
	}
	//�|�[�Y����(Back)
	else if (key[KEY_INPUT_DOWN])
	{
		if (keyTrg)
		{
			keyTrg		  = false;
			isPausedFrag != isPausedFrag;		//Back�{�^���������ꂽ��|�[�Y��Ԃ����]
		}
	}
	else
	{
		keyTrg = true;
	}
	if (isPausedFrag)  return;				//�|�[�Y���Ȃ烊�^�[��

	//-- ��l�v���C�� --//
	if (getSelect() == ONE_PLAY)
	{
		switch (state)
		{
		case 0:
			//////�����ݒ�//////

			timer = 0;

			//�v���C���[�}�l�[�W���̏�����
			playerManager()->init();

			//BG�}�l�[�W���̏�����
			bgManager()->init();

			//Block�}�l�[�W���̏�����
			block1Manger()->init();

			//Cursor�}�l�[�W���̏�����
			cursorManager()->init();

			//UI
			uiTimerManager()->init();
			uiComboManager()->init();

			//�v���C���[(�����ő���)��ǉ����� (�v���C���[ 1)
			playerManager()->add(&player		, n_texture::storePlayer	, TEXTURE, Vector2F{ 0,0 }		, Vector2F{ 64,64 });
			cursorManager()->add(&cursorW		, n_texture::sprLine		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorH		, n_texture::sprLine		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorCenter	, n_texture::sprCursorC		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });
			cursorManager()->add(&cursorPivot	, n_texture::sprCursor		, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });


#ifdef DEBUG_
			uiTimerManager()->add(&uiTimer, &fontTimer, FONT, Vector2F{ -500,-500 }, Vector2F{ 64,64 });

#endif // DEBUG_

			state++;	//�����������̏I��

						/*fallthrough*/
		case 1:
			/////�ʏ펞�̏���/////

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

	if (getSelect() == TWO_PLAY)
	{
		switch (state)
		{
		case 0:
			//////�����ݒ�//////

			timer = 0;

			//�v���C���[�}�l�[�W���̏�����
			playerManager()->init();

			//BG�}�l�[�W���̏�����
			bgManager()->init();

			//Block�}�l�[�W���̏�����
			block1Manger()->init();

			//Cursor�}�l�[�W���̏�����
			cursorManager()->init();

			//UI
			uiTimerManager()->init();
			uiComboManager()->init();

			//�v���C���[(�����ő���)��ǉ�����
			playerManager()->add(&player, n_texture::storePlayer, TEXTURE, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			cursorManager()->add(&cursorW, n_texture::sprLine, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorH, n_texture::sprLine, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorCenter, n_texture::sprCursorC, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });
			cursorManager()->add(&cursorPivot, n_texture::sprCursor, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });

			//�v���C���[ 2
			cursorManager()->add(&cuesorW_2, n_texture::sprLine, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorH_2, n_texture::sprLine, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ LINE_WIDTH,LINE_HEIGHT });
			cursorManager()->add(&cursorCenter_2, n_texture::sprCursorC, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });
			cursorManager()->add(&cursorPivot_2, n_texture::sprCursor, TEXTURE, Vector2F{ -500,-500 }, Vector2F{ CURSOR_SIZE,CURSOR_SIZE });

#ifdef DEBUG_
			uiTimerManager()->add(&uiTimer, &fontTimer, FONT, Vector2F{ -500,-500 }, Vector2F{ 64,64 });

#endif // DEBUG_

			state++;	//�����������̏I��

						/*fallthrough*/
		case 1:
			/////�ʏ펞�̏���/////

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

////--�`�揈��--////
void Game::draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255), "Game", 100);

	//�v���C���[�̕`��
	//bgManager()->drawBack();
	//bgManager()->drawTerrain();
	block1Manger()->draw();
	cursorManager()->draw();
	playerManager()->draw();
	uiTimerManager()->draw();
	uiComboManager()->draw();
}

////--�I������--////
void Game::uninit()
{
	safe_delete(playerManager_);
	safe_delete(bgManager_);
	safe_delete(block1Manager_);
	safe_delete(cursorManager_);
	safe_delete(uiTimerManager_);

	DeleteFontToHandle(fontTimer);
}

