#pragma once

//**********************//
//		Scene管理		//
//**********************//

//--Sceneクラス--//
class Scene
{
	//--メンバ変数--//
protected:
	
	int		state			= 0;			//状態
	int		timer			= 0;			//タイマー
	int		select			= 0;			//選択
	int		padInput		= 0;			//Pad入力
	bool	keyTrg			= false;		//キートリガー
	Scene*	nextScene		= nullptr;		//次のシーン

public:
	enum e_SelectGame
	{
		ONE_PLAY,
		TOW_PLAY,
	};

private:
	static e_SelectGame selectGame;
public:
	Scene* execute();	//実行処理

	virtual void init()
	{
		//初期化処理
		state		= 0;
		timer		= 0;
		nextScene	= nullptr;
	}
	virtual void uninit() {};	//終了処理
	virtual void update() {};	//更新処理
	virtual void draw()	  {};	//描画処理

	void changeScene(Scene* scene)		{ nextScene = scene; }			//シーン変更処理
	Scene* getScene() const				{ return nextScene; }			//nextSceneのゲッター
	void setSelect(e_SelectGame select) { selectGame = select; }		//selectGameのゲッター
	e_SelectGame getSelect() const		{ return selectGame; }			//selectGameのセッター
};

//**********************//
//		シーン管理		//
//**********************//

//--SceneManagerクラス--//
class SceneManager
{
public:
	void execute(Scene*);	//実行処理
};