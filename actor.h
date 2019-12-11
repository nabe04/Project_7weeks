#pragma once

struct ActorParam
{
	Vector2F accel;
	float	 speedMax;
	float	 gravityMax;

	float    ladderAccel;
};

class Actor :public MoveAlg
{
//--メンバ変数--//
private:
	char key[KEY_MAX];
	bool keyTrg = false;

private:
	//プレイヤー用
	void playerMoveY(OBJ2D* obj);			//Playerの縦方向移動
	void playerMoveX(OBJ2D* obj);			//Playerの横方向移動
	void playerJump(OBJ2D* obj);			//PlayerのJump処理

	//敵用
	void enemyMoveY(OBJ2D* obj);			//敵の縦方向移動
	void enemyMoveX(OBJ2D* obj);			//敵の横方向移動

	//エリアチェック
	void areaCheck(OBJ2D* obj);

protected:
	ActorParam actorParam;					// 下記の各関数を実行する際に使用されるパラメータ群

	//プレイヤー用
	void playerMove(OBJ2D* obj);			//プレイヤー操作
	
	//敵用
	void enemyTurn(OBJ2D* obj);				//崖で引き返す敵
	void enemyFall(OBJ2D* obj);				//崖で落ちる敵
	void enemyNoMove(OBJ2D* obj);			//動かない敵


	virtual void fixPos(OBJ2D* obj) = 0;	//それぞれのpivotの更新(マップチップの当たり判定などに使用)

public:
	Actor();
};
