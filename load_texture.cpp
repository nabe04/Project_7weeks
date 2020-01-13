#include "load_texture.h"

namespace n_texture
{
	int storePlayer[NO_ANIMATION];				 //プレイヤー
	int storeBG[BG_CHIP_NUM];					 //BG
	int storeTerrain[TERRAIN_CHIP_NUM];			 //マップチップ
	int sprBlock[BLOCK_CHIP_NUM];				 //ブロック
	int sprMyBlock[NO_ANIMATION];				 //時計
	int sprCursorW[NO_ANIMATION];				 //カーソル(横)
	int sprCursorH[NO_ANIMATION];				 //カーソル(縦)
	int sprCursorC[NO_ANIMATION];				 //カーソル(中央)
	int sprLine[NO_ANIMATION];					 //カーソルライン
	int sprCursor[CURSOR_CHIP_NUM];				 //カーソル
	int sprFrame[NO_ANIMATION];					 //盤面の枠
	int sprGauge[UI_CHIP_NUM];					 //ゲージ
	int sprGaugeFrame[NO_ANIMATION];			 //ゲージ枠
	int sprDoorLeft[NO_ANIMATION];				 //ドア(左)
	int sprDoorRight[NO_ANIMATION];				 //ドア(右)
	int sprBG[NO_ANIMATION];					 //BG(本物)
	int sprBlokenBLock[BLOKEN_BLOCK_CHIP_NUM];	 //ブロック破壊(アセット)
	int sprPressMachine[NO_ANIMATION];			 //プレス機
	int sprPressEffect[PRESS_EFFECT_CHIP_NUM];	 //プレスエフェクト
	int sprCounterBlock[COUNTER_BLOCK_CHIP_NUM]; //カウンターブロック
}

namespace n_font
{
	int fontYomogi;

	char* fh_yomogi = "Nu よもぎもち 標準-丸1";
}