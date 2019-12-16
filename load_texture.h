#pragma once


#include "bg.h"
#include "block.h"
#include "cursor.h"

namespace n_texture
{
	extern int storePlayer[1];
	extern int storeBG[BG_CHIP_NUM];
	extern int storeTerrain[TERRAIN_CHIP_NUM];
	extern int sprBlock[BLOCK_CHIP_NUM];
	extern int sprMyBlock[1];
	extern int sprCursorW[1];
	extern int sprCursorH[1];
	extern int sprCursorC[1];
	extern int sprCursor[CURSOR_CHIP_NUM];
	extern int sprLine[1];

}	

namespace n_texture
{
	static const char* gh_player	   = "./Data/Images/test_player.png";
	static const char* gh_bg		   = "./Data/Maps/chips/back_chip.png";
	static const char* gh_terrain	   = "./Data/Maps/chips/terrain_chip.png";
	static const char* gh_block		   = "./Data/Images/blocks.png";
	static const char* gh_my_block     = "./Data/Images/my_block.png";
	static const char* gh_cursor_w     = "./Data/Images/cursor_width.png";
	static const char* gh_cursor_h     = "./Data/Images/cursor_height.png";
	static const char* gh_cursor_c     = "./Data/Images/cursor_center.png";
	static const char* gh_cursor	   = "./Data/Images/cursor.png";
	static const char* gh_line		   = "./Data/Images/line1.png";
	static const char* gh_press_effect = "./Data/Images/pless_effect.png";
}

namespace n_font
{
	extern int fontTimer;

	extern char* font_0;
}
