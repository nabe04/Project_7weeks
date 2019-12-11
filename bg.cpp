#include <algorithm>
#include "generic.h"
#include "obj2d.h"
#include "load_texture.h"
#include "bg.h"
#include "bg_maps.h"


//--初期化--//
void BG::init()
{
	pos  = {};
	data = nullptr;

	for (int h = 0; h < CHIP_HEIGHT; h++)
	{
		for (int w = 0; w < CHIP_WIDTH; w++)
		{
			back[h][w]		= ori_bg[h][w];
			terrain[h][w]	= ori_terrain[h][w];
		} 
	}
}

//--更新--//
void BG :: update()
{
	
}

//--描画(背景)--//
void BG::drawBack()
{
	draw(n_texture::storeBG, back);
}

//--描画(地形)--//
void BG::drawTerrain()
{
	draw(n_texture::storeTerrain, terrain);
}


//--BG、Terrain共通の描画関数--//
void  BG::draw(int* data, int chipNo[CHIP_HEIGHT][CHIP_WIDTH])
{
	for (int h = 0; h < CHIP_HEIGHT; h++)
	{
		for (int w = 0; w < CHIP_WIDTH; w++)
		{
			int posX = pos.x + (w * CHIP_SIZE);			//position X
			int posY = pos.y + (h * CHIP_SIZE);			//position Y
			int hSizeX = static_cast<int>(size.x * 0.5f);	//Harf Size X
			int hSizeY = static_cast<int>(size.y * 0.5f);	//Harf Size Y
			int no = chipNo[h][w];

			if (no == -1)	continue;	//-1(データが入ってなければ処理を飛ばす)

			DrawRotaGraph3(
				posX, posY,
				hSizeX, hSizeY,
				1, 1,
				0,
				data[no],
				true,
				false
				);
		}
	}
}

//--当たり判定--//

//Chipの要素番号を取得
int BG::getData(const int map[CHIP_HEIGHT][CHIP_WIDTH], const float x, const float y)
{
	int data;
	int divX = static_cast<int>(x) / CHIP_SIZE;	//x方向のインデックス
	int divY = static_cast<int>(y) / CHIP_SIZE;	//y方向のインデックス

	data = map[divY][divX];
	return data;
}

//  下方向に向けて、指定した座標が壁であるかどうか
bool BG::isHitDown(const float x, const float y, bool hashigo)
{
	int chipNo = getData(terrain, x, y);	//MapChipの番号取得

	switch (chipNo)				//地形の属性を取得する
	{
	case NONE_BLOCK:  return false;
	case 0:
	case 1:			  return true; 
	case BREAK_BLOCK: return true;				//乗れる(BREAK_BLOCKは下から当たるを壊れるため)
	case PUSH_BLOCK : return true;				//乗れる(PUSH_BLOCKAは横から押すと動くため)
	case UPPER_BLOCK: return isUpperQuater(y);	// 上側４分の１が地形で、上４分の１に含まれるか
	case LADDER:

		//はしご降り始め時に下方向の壁への当たり判定を回避する
		if (hashigo == true)
			break;

		//はしごに乗れるようにしておく
		return isUpperQuater(y);

		break;
	}
	return false;
}

//指定したy座標が、マップチップの上側4分の1にあるかどうかを返す
bool BG::isUpperQuater(const float y)
{
	if (static_cast<int>(y) % CHIP_SIZE < CHIP_SIZE)
		return true;

	return false;
}

//  全て壁であるブロックかどうか
bool BG::isHitAll(const float x, const float y)
{
	int chipNo = getData(terrain, x, y);
	switch (chipNo)
	{
	case NONE_BLOCK:	return false;
	case 0:
	case 1: 
	case BREAK_BLOCK:
	case PUSH_BLOCK:	return true;
	}

	return false;
}

//床方向へのあたり判定
bool BG::isFloor(const float x, const float y,  float width, bool hashigo)
{
	for (; width > 0; width -= CHIP_SIZE)
	{
		const float left  = x - width;
		const float right = x + width;

		//エリアチェック
		if (left < 0)				continue;
		if (right >= SCREEN_WIDTH)	continue;

		if (isHitDown(left , y, hashigo))  return true;	//左端から
		if (isHitDown(right, y, hashigo)) return true;	//右端から
	}

	return isHitDown(x, y, hashigo);					//最後に真ん中で判定
}

//  下方向にあたっている場合の補正処理
void BG::mapCorrectionDown(OBJ2D* obj)
{
	float y			= obj->pivot.y;				//わかりやすく書くため
	int intY		= static_cast<int>(y);
	y				= static_cast<float>(intY - intY % CHIP_SIZE);
	obj->pivot.y	= y;
	obj->gravity	= (std::min)(obj->gravity, 0.0f);
}

//  天井にあたっているか
bool BG::isCeiling(const float x, const float y, float width)
{
	for (; width > 0; width -= CHIP_SIZE)
	{
		const float left  = x - width;
		const float right = x + width;

		//エリアチェック
		if (left < 0)				continue;
		if (right >= SCREEN_WIDTH)	continue;

		if (isHitAll(left, y))	return true;	//左端から
		if (isHitAll(right, y)) return true;	//右端から
	}
	return isHitAll(x, y);						//最後に真ん中で判定
}

//  上方向補正処理
void BG::mapCorrecionUp(OBJ2D* obj)
{
	float y			= obj->pivot.y - obj->texSize.y;
	int intY		= static_cast<int>(y);
	y				= static_cast<float>(intY + (CHIP_SIZE - (intY % CHIP_SIZE)));
	obj->pivot.y	= y + obj->texSize.y;
	if (obj->gravity < 0)
		obj->gravity = 0.0f;
}

//  横方向に壁にあたっているかどうか
bool BG::isWall(const float x, const float y, float height)
{
	for (; height > 0; height -= CHIP_SIZE)
	{
		if (isHitAll(x, y - height)) return true;
	}

	//-10しているのはそのままだとpivotがplayerのサイズよりも下にありうまく判定が取れないため
	return isHitAll(x, y - 10);
}

//  右方向補正処理
void BG::mapCorrectionRight(OBJ2D* obj)
{
	float x		 = obj->pivot.x + obj->size.x;
	x			-= fmodf(x, static_cast<float>(CHIP_SIZE));
	obj->pivot.x = x - obj->size.x;
	obj->speed	 = 0.0f;
}

//  左方向補正処理
void BG::mapCorrectionLeft(OBJ2D* obj)
{
	float x		 = obj->pivot.x - obj->size.x;
	x			+= CHIP_SIZE - fmodf(x, static_cast<float>(CHIP_SIZE));
	obj->pivot.x = x + obj->size.x;
	obj->speed	 = 0.0f;
}

//指定されたChipのアセット変更
void BG::chipChange(const float x, const float y)
{
	//全てをNONE_BLOCKで初期化
	TR_ATTR attr = NONE_BLOCK;

	switch (getData(terrain,x,y))
	{
	case ALL_BLOCK:		attr = BREAK_BLOCK;  break;
	}

	int divX = static_cast<int>(x) / CHIP_SIZE;	//x方向のインデックス
	int divY = static_cast<int>(y) / CHIP_SIZE;	//y方向のインデックス

	if(attr != NONE_BLOCK)	terrain[divY][divX] = attr;
}

float BG::calcResistance(const OBJ2D* obj, float speed)
{
	return -1;
}