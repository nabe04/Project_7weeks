#pragma once

#define BLOCK_WIDTH			(5)
#define BLOCK_HEIGHT		(5)

#define BLOCK_CHIP_W		(9)
#define BLOCK_CHIP_H		(1)
#define BLOCK_CHIP_NUM		(9)
#define BLOCK_CHIP_SIZE		(64)

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
	//-- 一人目 --//
	OBJ2D block_1[BLOCK_HEIGHT][BLOCK_WIDTH];				//ブロックのデータ格納
	int   platform_1[BLOCK_HEIGHT][BLOCK_WIDTH] = {};		//現在のブロックの番号格納用
	bool  keyTrg_1								= false;	//キートリガー	


	//Data data[2];

	enum e_Direction
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
	
	//--ブロック処理--//
	void blockManage();																						//全体の管理
	void blockClip(const int width, const int height,int* checkNo, e_Direction direction);					//除去処理
	bool checkBlockWidth (const int width, const int height, const int checkNo, e_Direction direction);		//ブロックを除去できるか判定 (横)
	bool checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction);		//ブロックを除去できるか判定 (縦)
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

	OBJ2D block_2[BLOCK_HEIGHT][BLOCK_WIDTH];				//ブロックのデータ格納
	int   platform_2[BLOCK_HEIGHT][BLOCK_WIDTH] = {};		//現在のブロックの番号格納用
	bool  keyTrg_2 = false;	//キートリガー	

						
	//Data data[2];

	enum e_Direction
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
	void blockClip(const int width, const int height, int* checkNo, e_Direction direction);					//除去処理
	bool checkBlockWidth(const int width, const int height, const int checkNo, e_Direction direction);		//ブロックを除去できるか判定 (横)
	bool checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction);		//ブロックを除去できるか判定 (縦)
};

