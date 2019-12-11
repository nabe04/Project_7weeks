#include "DxLib.h"
#include "setup.h"
#include "obj2d.h"
#include "player.h"
#include "scene.h"
#include "title.h"
#include "game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SceneManager sceneManager;
	sceneManager.execute(Title::instance());

	return 0;
}