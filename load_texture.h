#pragma once

#include "bg.h"
#include "block.h"
#include "ui.h"
#include "cursor.h"
#include "effect.h"

#define NO_ANIMATION (1)  //アニメーションがないとき →　切り抜く枚数が1枚の時

namespace n_texture
{
	extern int storePlayer[NO_ANIMATION];
	extern int storeBG[BG_CHIP_NUM];
	extern int storeTerrain[TERRAIN_CHIP_NUM];
	extern int sprBlock[BLOCK_CHIP_NUM];
	extern int sprMyBlock[NO_ANIMATION];
	extern int sprCursorW[NO_ANIMATION];
	extern int sprCursorH[NO_ANIMATION];
	extern int sprCursorC[NO_ANIMATION];
	extern int sprCursor[CURSOR_CHIP_NUM];
	extern int sprLine[NO_ANIMATION];
	extern int sprFrame[NO_ANIMATION];
	extern int sprGauge[UI_CHIP_NUM];
	extern int sprGaugeFrame[NO_ANIMATION];
	extern int sprDoorLeft[NO_ANIMATION];			
	extern int sprDoorRight[NO_ANIMATION];		
	extern int sprBG[NO_ANIMATION];
	extern int sprBlokenBLock[BLOKEN_BLOCK_CHIP_NUM];
	extern int sprPressMachine[NO_ANIMATION];
	extern int sprPressEffect[PRESS_EFFECT_CHIP_NUM];	
	extern int sprCounterBlock[COUNTER_BLOCK_CHIP_NUM];
}	

namespace n_texture
{
	static const char* gh_player		= "./Data/Images/test_player.png";
	static const char* gh_bg			= "./Data/Maps/chips/back_chip.png";
	static const char* gh_terrain		= "./Data/Maps/chips/terrain_chip.png";
	static const char* gh_block			= "./Data/Images/blocks.png";
	static const char* gh_my_block		= "./Data/Images/my_block.png";
	static const char* gh_cursor_w		= "./Data/Images/cursor_width.png";
	static const char* gh_cursor_h		= "./Data/Images/cursor_height.png";
	static const char* gh_cursor_c		= "./Data/Images/cursor_center.png";
	static const char* gh_cursor		= "./Data/Images/cursor.png";
	static const char* gh_line			= "./Data/Images/line1.png";
	static const char* gh_press_effect	= "./Data/Images/pless_effect.png";
	static const char* gh_frame			= "./Data/Images/frame2.png";
	static const char* gh_gauge			= "./Data/Images/fever_gauge_ani.png";
	static const char* gh_gauge_frame	= "./Data/Images/fever_back.png";
	static const char* gh_door_left		= "./Data/Images/door_L.png";
	static const char* gh_door_right	= "./Data/Images/door_R.png";
	static const char* gh_back			= "./Data/Images/back.png";
	static const char* gh_bloken_block	= "./Data/Images/broken_block.png";
	static const char* gh_press_machine = "./Data/Images/pless_machine.png";
	static const char* gh_counter_block = "./Data/Images/stock_b.png";
}

namespace n_font
{
	extern int fontYomogi;

	extern char* fh_yomogi;
}
