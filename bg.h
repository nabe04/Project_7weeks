#pragma once

//***********************************************************
//
//						BG
//
//***********************************************************

////--定数--////

//--マップチップ--//
#define CHIP_WIDTH			(32)
#define CHIP_HEIGHT			(17)
#define CHIP_SIZE			(32)

//--BG--//
#define BG_CHIP_NUM			(16)
#define BG_CHIP_W			(8)
#define BG_CHIP_H			(2)

//--Terrain--//
#define TERRAIN_CHIP_NUM	(32)
#define TERRAIN_CHIP_W		(8)
#define TERRAIN_CHIP_H		(4)

#include "setup.h"
#include "obj2d.h"
////--BGクラス--////

class BG
{
//--メンバ変数--//
private:
	n_setup::Vector2F pos	= {};		//位置
	n_setup::Vector2I size  = {};		//大きさ
	int* data				= nullptr;	//格納するChipデータ
	
	int back[CHIP_HEIGHT][CHIP_WIDTH]		= {};	//背景
	int terrain[CHIP_HEIGHT][CHIP_WIDTH]	= {};	//地形

public:
	//地形(Terrain)の属性
	//--Chipの定数宣言--//
	enum TR_ATTR
	{
		NONE_BLOCK	= -1,	//何もないブロック
		ALL_BLOCK   = 1,	//判定だけあるブロック
		BREAK_BLOCK = 2,	//壊せるブロック
		PUSH_BLOCK	= 6,	//押せるブロック
		WATER		= 7,	//水
		UPPER_BLOCK = 9,	//下方向だけ判定があるブロック
		LADDER		= 16	//はしご,
	};

//--メンバ関数--//
private:
	void draw(int* data, int chipNo[CHIP_HEIGHT][CHIP_WIDTH]);	// BG、Terrain共通の描画関数

	//--当たり判定--//
	bool isHitDown(const float x, const float y, bool hashigo);	//下方向
	bool isHitAll(const float x, const float y);				//全体(最後のチェックに使用)
	bool isUpperQuater(const float y);							//指定したy座標が、マップチップの上側4分の1にあるかどうか

public:
	BG() {};				//コンストラクタ

	void init();			//初期化
	void update();			//更新
	void drawBack();		//描画(背景)
	void drawTerrain();		//描画(地形)

	//--当たり判定--//
	//下方向
	bool isFloor(const float x, const float y,  float width, bool hashigo = (false));		//床にめり込んでるか
	void mapCorrectionDown(OBJ2D* obj);														//下方向補正処理

	//上方向
	bool isCeiling(const float x, const float y, float width);								//天井に当たってるか
	void mapCorrecionUp(OBJ2D* obj);														//上方向補正処理

	//横方向
	bool isWall(const float x, const float y, float height);								//横方向にめり込んでるか
	void mapCorrectionRight(OBJ2D* obj);													//右方向補正処理
	void mapCorrectionLeft(OBJ2D* obj);														//左方向補正処理
			
	//--データ取得--//
	int  getData(const int map[CHIP_HEIGHT][CHIP_WIDTH], const float x, const float y);	//指定した座標のマップチップの種類を取得する

	//--Chipの変化--//

	//Chipの色変更
	void chipChange(const float x, const float y);

	//Chipを押せる
	void chipPush();

	//--抵抗--//
	float calcResistance(const OBJ2D* obj, float speed);
};
