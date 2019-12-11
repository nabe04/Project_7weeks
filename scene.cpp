#include <assert.h>
#include "generic.h"
#include "scene.h"

////--Sceneクラス--////

////--メンバ変数--////
Scene::e_SelectGame Scene::selectGame;

////--実行--//
Scene* Scene::execute()
{
	//初期化処理
	init();

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//画面の初期化
		ClearDrawScreen();

		//更新処理
		update();

		//描画処理
		draw();

		//裏画面の内容を表画面に反映させる
		ScreenFlip();

		//終了チェック
		if (nextScene) break;
	}

	//終了処理
	uninit();

	return nextScene;	//次のシーンを返す
}


//--SceneManagerクラス--//
//実行
void SceneManager::execute(Scene* scene)
{
	ChangeWindowMode(true);										//ウィンドウモード設定(true : ウィンドウモード , false : フルスクリーン)
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);				//画面のサイズ設定
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);

	SetBackgroundColor(0, 0, 0);

	if (DxLib_Init() == -1)		//DXライブラリ初期化処理
	{
		assert(!"DxLib初期化エラーです!");			//エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//メインループ
	while (scene)
	{
		scene = scene->execute();
	}

	//DXライブラリ使用の終了
	DxLib_End();
}