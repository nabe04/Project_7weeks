#pragma once

#define BLOCK_WIDTH				(5)
#define BLOCK_HEIGHT			(5)

#define BLOCK_CHIP_NUM			(5)
#define BLOCK_CHIP_W			(1)
#define BLOCK_CHIP_H			(5)
#define BLOCK_CHIP_SIZE			(64)

#define BLOKEN_BLOCK_CHIP_NUM	(7)
#define BLOKEN_BLOCK_CHIP_W		(1)
#define BLOKEN_BLOCK_CHIP_H		(7)
#define BLOKEN_BLOCK_SIZE		(64)

#define BOARD_CHIP_NUM			(100)
#define BOARD_SIZE				(320)	//ブロック全部のサイズ
#define BOARD_CENTER			(2)		//盤面の中心


//-- プレイヤー 1 --//
class Block_1 
{
	//struct Data
	//{
	//	OBJ2D block[BLOCK_HEIGHT][BLOCK_WIDTH];				//ブロックのデータ格納
	//	int   platform[BLOCK_HEIGHT][BLOCK_WIDTH] = {};		//現在のブロックの番号格納用
	//	bool  keyTrg = false;	//キートリガー	
	//	OBJ2D* getBlockData(int x, int y) { return &block[y][x]; }
	//};
private:	//--メンバ変数--//
	
	OBJ2D		block_1[BLOCK_HEIGHT][BLOCK_WIDTH]						= {};		//ブロックのデータ格納
	OBJ2D		blokenBlock_1[BOARD_CHIP_NUM][BLOKEN_BLOCK_CHIP_NUM]	= {};		//*ブロックが壊されたときのデータ格納
	Vector2F	correction												= {};		//補正値
	int			platform_1[BLOCK_HEIGHT][BLOCK_WIDTH]					= {};		//現在のブロックの番号格納用
	int			eraseBlockCount											= 0;		//消したブロックの個数
	bool		keyTrg_1												= false;	//キートリガー	

	enum e_BlockDirection
	{
		LEFT,
		RIGHT,
		UP,
		BOTTOM,
	};

public:
	//--番号保存--//
	static Vector2I arrNo;			//一人
	static Vector2I saveArryNo;
	
public:		//--メンバ関数--//
	void init();		//初期化
	void update();		//更新
	void draw();		//描画
	
	//-- ブロック処理 --//
	void blockManage();																						//全体の管理
	void blockClip(const int width, const int height,int* checkNo, e_BlockDirection direction);					//除去処理
	bool checkBlockWidth (const int width, const int height, const int checkNo, e_BlockDirection direction);		//ブロックを除去できるか判定 (横)
	bool checkBlockHeight(const int width, const int height, const int checkNo, e_BlockDirection direction);		//ブロックを除去できるか判定 (縦)
	void serchSet(OBJ2D* obj, Vector2F pos,const int no);														//BlokenBlockのデータ格納用

	//-- 破壊ブロック処理 --//
	void blokenBlockMove();		//BlokenBlockのMove処理(updateに加える)
	void drawBloken();			//BlokenBlockの描画(drawに加える)
};

////-- プレイヤー 2用 --////
class Block_2
{
	//struct Data
	//{
	//	OBJ2D block[BLOCK_HEIGHT][BLOCK_WIDTH];				//ブロックのデータ格納
	//	int   platform[BLOCK_HEIGHT][BLOCK_WIDTH] = {};		//現在のブロックの番号格納用
	//	bool  keyTrg = false;	//キートリガー	
	//	OBJ2D* getBlockData(int x, int y) { return &block[y][x]; }
	//};
private:	//--メンバ変数--//

	OBJ2D		block_2[BLOCK_HEIGHT][BLOCK_WIDTH]						= {};				//ブロックのデータ格納
	OBJ2D		blokenBlock_2[BOARD_CHIP_NUM][BLOKEN_BLOCK_CHIP_NUM]	= {};				//ブロックが壊されたときのデータ格納
	Vector2F	correction												= {};				//補正値
	int			platform_2[BLOCK_HEIGHT][BLOCK_WIDTH]					= {};				//現在のブロックの番号格納用
	int			eraseBlockCount											= 0;				//消したブロックの数
	bool		keyTrg_2												= false;			//キートリガー	

	enum e_BlockDirection
	{
		LEFT,
		RIGHT,
		UP,
		BOTTOM,
	};

public:
	//--番号保存--//
	static Vector2I arrNo_2;			//一人
	static Vector2I saveArryNo_2;

public:		//--メンバ関数--//
	void init();		//初期化
	void update();		//更新
	void draw();		//描画

	//--ブロック処理--//
	void blockManage();																						//全体の管理
	void blockClip(const int width, const int height, int* checkNo, e_BlockDirection direction);					//除去処理
	bool checkBlockWidth(const int width, const int height, const int checkNo, e_BlockDirection direction);		//ブロックを除去できるか判定 (横)
	bool checkBlockHeight(const int width, const int height, const int checkNo, e_BlockDirection direction);		//ブロックを除去できるか判定 (縦)
	void serchSet(OBJ2D* obj, Vector2F pos, const int no);													//BlokenBlockのデータ格納用

	//-- 破壊ブロック処理 --//
	void blokenBlockMove();		//BlokenBlockのMove処理(updateに加える)
	void drawBloken();			//BlokenBlockの描画(drawに加える)
};

