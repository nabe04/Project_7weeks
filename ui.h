#pragma once

#define UI_GAUGE_SIZE_W (320)
#define UI_GAUGE_SIZE_H (50)
#define UI_CHIP_NUM		(8)
#define UI_CHIP_W		(4)
#define UI_CHIP_H		(2)

#define COUNTER_MAX_W				(7)
#define COUNTER_MAX_H				(100)
#define COUNTER_BLOCK_CHIP_NUM		(3)
#define COUNTER_BLOCK_CHIP_W		(3)
#define COUNTER_BLOCK_CHIP_H		(1)
#define COUNTER_BLOCK_CHIP_SIZE_W	(32)
#define COUNTER_BLOCK_CHIP_SIZE_H	(32)
#define COUNTER_BLOCK_SPACE			(40)	//ブロックを配置する位置の間隔

class UI :public MoveAlg
{
private:
	int		 playerNo = 0;		//操作しているプレイヤーの番号
	Vector2F move = {};		//UIの移動値
protected:
	int addGauge = 0;		//フィーバーゲージの増加量
	int feverCount = 0;		//フィーバー回数
	int colorState = 0;        //色の状態
	int colorTimer = 0;        //点滅等、カラーに関するタイマー
public:
	//コンボ数
	static int nowCombo_1;	//プレイヤー 1	
	static int nowCombo_2;  //プレイヤー 2

							//スコア
	static int score_1;		//プレイヤー 1	
	static int score_2;		//プレイヤー 2

							//ブロックの消した数の倍率
	static float eraseBlockPow_1;
	static float eraseBlockPow_2;

	//フィーバーフラグ
	static bool	 feverFrag;	//(true : fever , false : Nomal)

public:

	void moveTimer(OBJ2D* obj, Vector2F pos);
	void moveCombo(OBJ2D* obj);
	void moveScore(OBJ2D* obj);
	void moveGauge(OBJ2D* obj);
	void moveHp(OBJ2D* obj);
	void moveCounter(OBJ2D* obj);

	void setPlayerNo(int no) { playerNo = no; }		//現在のプレイヤーの番号取得(これで今のプレイヤーが 1なのか2なのかを調べる)
	int	 getPlayerNo() { return playerNo; }

	//void setFeverFrag(bool frag) { feverFrag = frag; }		//現在のプレイヤーの番号取得(これで今のプレイヤーが 1なのか2なのかを調べる)
	//bool getFeverFrag() { return feverFrag; }

};

class UiTimer :public UI
{
private:
	Vector2F pos;

public:
	void move(OBJ2D* obj) override;

	//-- セッター --//
	void setPosX(float pos) { this->pos.x = pos; }
	void setPosY(float pos) { this->pos.y = pos; }

};

class UiCombo :public UI
{
public:
	void move(OBJ2D* obj) override;

	//デストラクタ(メンバ変数の初期化)
	~UiCombo()
	{
		nowCombo_1 = 0;
		nowCombo_2 = 0;
	};
};

class UiScore :public UI
{
public:
	void move(OBJ2D* obj) override;

	int feverMgnfication = 1;//1なら通常時のスコア倍率、2ならフィーバー時のスコア倍率

	int calcScore(const int combo, const int blockNum, float* eraseBlockPow);	//SCOREの計算　　(1: 現在のコンボ数 2: ブロックの消した個数)

																				//デストラクタ(メンバ変数の初期化)
	~UiScore();
	/*~UiScore()
	{
	score_1					= 0;
	score_2					= 0;
	eraseBlockPow_1			= 0;
	eraseBlockPow_2			= 0;
	}*/
};

class UiGauge :public UI
{
public:
	void move(OBJ2D* obj) override;

	void calcGauge(const int eraseNum, const int playerNo);
};

class UiHp :public UI
{
public:
	void move(OBJ2D* obj) override;
};

extern UiTimer uiTimer_1;
extern UiTimer uiTimer_2;
extern UiCombo uiCombo_1;
extern UiCombo uiCombo_2;
extern UiScore uiScore_1;
extern UiGauge uiGauge_1;
extern UiGauge uiGauge_2;


class EraseUi :public EraseAlg
{
	void erase(OBJ2D* obj) override;
};

class UiManager :public OBJ2DManager
{

};



class UiCounter
{
private:
	int arrNo_H			= 0;	 //配列の番号格納用(Height)
	int arrNo_W			= 0;	 //配列の番号格納用(Width)
	int counterBlockNum = 0;	 //相手に送るカウンターブロックの個数
	int breakBlock_2	= 0;	 //2個消し個数
	int breakBlock_3	= 0;	 //3個消し個数
	int breakBlock_4	= 0;	 //4個消し個数

public:
	OBJ2D counter[COUNTER_MAX_H][COUNTER_MAX_W] = {};
	bool calcFrag = false; //計算処理を行うかのフラグ

public:
	void init();
	void update();
	void draw();

	void move(OBJ2D* obj);

	void calcCounterBlockNum(UiCounter* rivalCounter ,UiCounter* myCounter,int posX ,int height, bool center);		//カウンターブロックの個数計算 (1 : 何個消したか 2 : カーソルが真ん中にあるか)
	void addCounterBlock(UiCounter* counter,const int blockNum);													//一度に消されたブロックの個数の追加(コンボ数じゃなくてブロックの数)
	void deleteCounterBlock(OBJ2D* counter);
	

	//-- ゲッター --//
	int getArrNo_H() { return arrNo_H; }
	int getArrNo_W() { return arrNo_W; }

	//-- セッター --//
	void setArrNo_H(int no) { arrNo_H = no; }
	void setArrNo_W(int no) { arrNo_W = no; }
};

extern UiCounter uiCounter_1;		//カウンター
extern UiCounter uiCounter_2;

