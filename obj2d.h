#pragma once
#include <list>
#include <string>
#include "setup.h"
#include "algorithm.h"

using namespace n_setup;


//OBJの種類 
const enum e_Category
{
	TEXTURE,	//画像
	FONT,		//フォント
};

//***********************//
//		OBJ2Dクラス		 //
//***********************//

//--OBJ2Dクラス--//
class OBJ2D
{
public:
	Vector2F 	pos			= {};					//位置
	Vector2F	pivot		= {};					//画像の基準点
	Vector2F	scale		= {};					//スケール
	Vector2F	size		= {};					//当たり用サイズ(画像の半分のサイズを設定)
	Vector2F	texSize		= {};					//画像のサイズ(DrawRoteGraph3の第3，4引数で使用)
	Vector2I	arrNo		= {};					//配列の要素番号を保存
	Vector2I    clipOrigin	= {};					//画像の切り抜き(基準点)
	Vector2I	clipSize	= {};					//画像の切り抜きサイズ
	Vector2B	revFrag		= {};					//画像の反転フラグ
	Color4I		color		= {};					//描画色

	MoveAlg*	mvAlg		= nullptr;				//移動アルゴリズム
	EraseAlg*	eraseAlg	= nullptr;				//消去アルゴリズム

	e_Category  category;

	int			state		= 0;					//ステイト
	int			timer		= 0;					//タイマー
	int			animeState	= 0;					//アニメーションState
	int			animeTimer	= 0;					//アニメーションTimer
	int			chipWidth	= 0;					//アニメーションさせたいChipの数(横)
	int			no			= 0;					//番号(情報を入れるのとかに使用)
	int			jumpTimer	= 0;					//長押しジャンプの時間
	int			fontSize	= 0;					//フォントの大きさ
	int			fontThick	= 0;					//フォントの厚さ
	int*		data		= nullptr;				//描画するさいに入れるData
	float		speed		= 0;					//速度
	float		gravity		= 0;					//重力
	float		angle		= 0;					//角度
	float		dispNum		= 0;					//フォーマット指定子格納用
	bool		existFrag	= false;				//存在フラグ
	bool		grandFrag	= false;				//地面フラグ
	bool		ladderFrag  = false;				//梯子フラグ
	bool		wallFrag	= false;				//壁フラグ
	bool		clipFrag	= false;				//切り抜きフラグ
	char*		text		= nullptr;				//フォント使用の際に表示する文字
	char*		loadData	= nullptr;				//loadしたときのファイル参照値

public:
	OBJ2D();		//コンストラクタ
	void move();	//更新
	void draw();	//描画
};

//--OBJ2DManagerクラス--//
class OBJ2DManager
{
protected:
	std::list<OBJ2D> objList;	//リスト
public:
	~OBJ2DManager();			//デストラクタ

	void init();				//初期化
	void update();				//更新
	void draw();				//描画

	OBJ2D* add(MoveAlg* mvAlg, int* data, e_Category category, const n_setup::Vector2F& pos = n_setup::Vector2F{ 0, 0 }, const n_setup::Vector2F& size = n_setup::Vector2F{0,0},char* loadName = nullptr);	//objListに新たなOBJ2Dを追加する
	std::list<OBJ2D>* getList() { return &objList; }							//objListを取得する
};



