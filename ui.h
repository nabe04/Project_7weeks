#pragma once

#include "load_texture.h"

class UI :public MoveAlg
{
private:
	int playerNo = 0;

public:
	//コンボ数
	static int nowCombo_1;	//プレイヤー 1	
	static int nowCombo_2;  //プレイヤー 2
	//スコア
	static int score_1;		//プレイヤー 1	
	static int score_2;		//プレイヤー 2


public :
	void moveTimer(OBJ2D* obj);
	void moveCombo(OBJ2D* obj);
	void moveScore(OBJ2D* obj);

	void moveScoreVal(OBJ2D* obj);
	
	void setPlayerNo(int no) { playerNo = no; }
	int	 getPlayerNo() { return playerNo; }
};

class UiTimer :public UI
{
	void move(OBJ2D* obj) override;
};

class UiCombo :public UI
{
	void move(OBJ2D* obj) override;
};

class UiScore :public UI
{
	void move(OBJ2D* obj) override;
};

extern UiTimer uiTimer;
extern UiCombo uiCombo_1;
extern UiCombo uiCombo_2;
extern UiScore uiScore_1;
extern UiScore uiScore_2;


class EraseUi :public EraseAlg
{
	void erase(OBJ2D* obj) override;
};

class UiManager :public OBJ2DManager
{

};
