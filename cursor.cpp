#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "actor.h"
#include "algorithm.h"
#include "cursor.h"
#include "block.h"
#include "player.h"
#include "scene.h"
#include "game.h"

//プレイヤー 1
CursorH		 cursorH;
CursorW		 cursorW;
CursorPivot  cursorPivot;
CursorCenter cursorCenter;

////プレイヤー 2
CursorH_2		cursorH_2;
CursorW_2		cuesorW_2;
CursorPivot_2	cursorPivot_2;
CursorCenter_2	cursorCenter_2;

Vector2F Cursor::cursorCenterPos;
Vector2F Cursor_2::cursorCenterPos_2;


void Cursor::cursorMoveY(OBJ2D* obj)
{
	//-- 一人プレイ時 --//
	if (Game::playerNum == Scene::ONE_PLAY)
	{
		//Pad入力処理
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//arrNoの保存(入れ替えに使用)
		Block_1::saveArryNo.y = Block_1::arrNo.y;

		if (padInput & PAD_INPUT_DOWN)
		{
			if (keyTrg && cursorNo.y < BLOCK_HEIGHT - 1)
			{
				keyTrg = false;

				cursorNo.y++;

			}
		}
		else if (padInput & PAD_INPUT_UP)
		{
			if (keyTrg && cursorNo.y > 0)
			{
				keyTrg = false;

				cursorNo.y--;
			}
		}
		else
		{
			keyTrg = true;
		}
		obj->pos.x = (cursorNo.x * 64) + 475;
		obj->pos.y = (cursorNo.y * 64) + 150;

		obj->arrNo.x = cursorNo.x;		//要素番号を保存
		obj->arrNo.y = cursorNo.y;		//要素番号を保存

		cursorCenterPos.y = cursorNo.y;

		Block_1::arrNo.y = obj->arrNo.y;		//Blockを変更する要素番号を取得
	}

	if (Game::playerNum == Scene::TWO_PLAY)
	{
		//Pad入力処理
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//arrNoの保存(入れ替えに使用)
		Block_1::saveArryNo.y = Block_1::arrNo.y;

		if (padInput & PAD_INPUT_DOWN)
		{
			if (keyTrg && cursorNo.y < BLOCK_HEIGHT - 1)
			{
				keyTrg = false;

				cursorNo.y++;

			}
		}
		else if (padInput & PAD_INPUT_UP)
		{
			if (keyTrg && cursorNo.y > 0)
			{
				keyTrg = false;

				cursorNo.y--;
			}
		}
		else
		{
			keyTrg = true;
		}
		obj->pos.x = (cursorNo.x * 64) + 475;
		obj->pos.y = (cursorNo.y * 64) + 150;

		obj->arrNo.x = cursorNo.x;		//要素番号を保存
		obj->arrNo.y = cursorNo.y;		//要素番号を保存

		cursorCenterPos.y	= cursorNo.y;

		Block_1::arrNo.y		= obj->arrNo.y;		//Blockを変更する要素番号を取得
	}

	
}

void Cursor::cursorMoveX(OBJ2D* obj)
{
	char keyCursor[KEY_MAX];
	GetHitKeyStateAll(keyCursor);

	if (Game::playerNum == Scene::ONE_PLAY)
	{
		//Pad入力処理
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//obj->color.a = 150;

		obj->angle = ToRadian(90);

		//arrNoの保存(入れ替えに使用)
		Block_1::saveArryNo.x = Block_1::arrNo.x;

		if (padInput & PAD_INPUT_RIGHT)
		{
			if (keyTrg && cursorNo.x < BLOCK_WIDTH - 1)
			{
				keyTrg = false;

				cursorNo.x++;
			}
		}
		else if (padInput & PAD_INPUT_LEFT)
		{
			if (keyTrg && cursorNo.x > 0)
			{
				keyTrg = false;

				cursorNo.x--;
			}
		}
		else
		{
			keyTrg = true;
		}

		obj->pos.x = (cursorNo.x * 64) + 350;
		obj->pos.y = (cursorNo.y * 64) + 277;

		obj->arrNo.x = cursorNo.x;		//要素番号を保存
		obj->arrNo.y = cursorNo.y;		//要素番号を保存

		cursorCenterPos.x = cursorNo.x;

		Block_1::arrNo.x = obj->arrNo.x;	//Blockを変更する要素番号を取得
	}

	if (Game::playerNum == Scene::TWO_PLAY)
	{
		//Pad入力処理
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//obj->color.a = 150;

		obj->angle = ToRadian(90);

		//arrNoの保存(入れ替えに使用)
		Block_1::saveArryNo.x = Block_1::arrNo.x;

		if (padInput & PAD_INPUT_RIGHT)
		{
			if (keyTrg && cursorNo.x < BLOCK_WIDTH - 1)
			{
				keyTrg = false;

				cursorNo.x++;
			}
		}
		else if (padInput & PAD_INPUT_LEFT)
		{
			if (keyTrg && cursorNo.x > 0)
			{
				keyTrg = false;

				cursorNo.x--;
			}
		}
		else
		{
			keyTrg = true;
		}

		obj->pos.x = (cursorNo.x * 64);
		obj->pos.y = (cursorNo.y * 64) + 277;

		obj->arrNo.x = cursorNo.x;		//要素番号を保存
		obj->arrNo.y = cursorNo.y;		//要素番号を保存

		cursorCenterPos.x = cursorNo.x;

		Block_1::arrNo.x = obj->arrNo.x;	//Blockを変更する要素番号を取得
	}
	
}

void CursorH::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->existFrag = true;

		obj->state++;
		break;
	case 1:
		cursorMoveX(obj);
		break;
	}

	fixPos(obj);
}

void CursorH::fixPos(OBJ2D* obj)
{
	/*obj->pivot.x = obj->pos.x - obj->size.x;
	obj->pivot.y = obj->pos.y - obj->size.y;

	obj->pos.x = obj->pivot.x;
	obj->pos.y = obj->pivot.y;*/

	/*obj->pos.x = obj->pos.x - obj->size.x;
	obj->pos.y = obj->pos.y - obj->size.y;*/
}

void CursorW::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->existFrag = true;

		obj->state++;
		break;
	case 1:
		cursorMoveY(obj);
	
		break;
	}
	fixPos(obj);
}

void CursorW::fixPos(OBJ2D* obj)
{
	/*obj->pivot.x = obj->pos.x - obj->size.x;
	obj->pivot.y = obj->pos.y - obj->size.y;*/

	/*obj->pos.x = obj->pos.x - obj->size.x;
	obj->pos.y = obj->pos.y - obj->size.y;*/
}

void CursorPivot::move(OBJ2D* obj)
{
	if (Game::playerNum == Scene::ONE_PLAY)
	{
		obj->existFrag	= true;
		obj->pos.x		= cursorCenterPos.x * 64 + 350;
		obj->pos.y		= cursorCenterPos.y * 64 + 150;

		obj->timer++;
		obj->animeTimer = obj->timer / 15 % 4;
		obj->animeState = 0;
	}
	if (Game::playerNum == Scene::TWO_PLAY)
	{
		obj->existFrag	= true;
		obj->pos.x		= cursorCenterPos.x * 64;
		obj->pos.y		= cursorCenterPos.y * 64 + 150;

		obj->timer++;
		obj->animeTimer = obj->timer / 15 % 4;
		obj->animeState = 0;
	}


}

void CursorPivot::fixPos(OBJ2D* obj)
{

}

void CursorCenter::move(OBJ2D* obj)
{
	obj->existFrag = true;
	obj->pos.x = cursorCenterPos.x * 64 + 350;
	obj->pos.y = cursorCenterPos.y * 64 + 150;

	obj->color.r++;

	if (obj->color.r > 255)
	{
		obj->color.r = 0;
	}
}

//TODO::二人プレイ
////-- 二人プレイ --////
void Cursor_2::cursorMoveY(OBJ2D* obj)
{

	if (Game::playerNum == Scene::TWO_PLAY)
	{
		//Pad入力処理
		int padInput_2 = GetJoypadInputState(DX_INPUT_PAD2);

		//arrNoの保存(入れ替えに使用)
		Block_2::saveArryNo_2.y = Block_2::arrNo_2.y;

		if (padInput_2 & PAD_INPUT_DOWN)
		{
			if (keyTrg && cursorNo.y < BLOCK_HEIGHT - 1)
			{
				keyTrg = false;

				cursorNo.y++;

			}
		}
		else if (padInput_2 & PAD_INPUT_UP)
		{
			if (keyTrg && cursorNo.y > 0)
			{
				keyTrg = false;

				cursorNo.y--;
			}
		}
		else
		{
			keyTrg = true;
		}
		obj->pos.x = (cursorNo.x * 64) + 475;
		obj->pos.y = (cursorNo.y * 64) + 150;

		obj->arrNo.x = cursorNo.x;		//要素番号を保存
		obj->arrNo.y = cursorNo.y;		//要素番号を保存

		cursorCenterPos_2.y = cursorNo.y;

		Block_2::arrNo_2.y = obj->arrNo.y;		//Blockを変更する要素番号を取得
	}


}

void Cursor_2::cursorMoveX(OBJ2D* obj)
{
	char keyCursor[KEY_MAX];
	GetHitKeyStateAll(keyCursor);

	if (Game::playerNum == Scene::ONE_PLAY)
	{
		//Pad入力処理
		int padInput_2 = GetJoypadInputState(DX_INPUT_PAD2);

		//obj->color.a = 150;

		obj->angle = ToRadian(90);

		//arrNo_2の保存(入れ替えに使用)
		Block_2::saveArryNo_2.x = Block_2::arrNo_2.x;

		if (padInput_2 & PAD_INPUT_RIGHT)
		{
			if (keyTrg && cursorNo.x < BLOCK_WIDTH - 1)
			{
				keyTrg = false;

				cursorNo.x++;
			}
		}
		else if (padInput_2 & PAD_INPUT_LEFT)
		{
			if (keyTrg && cursorNo.x > 0)
			{
				keyTrg = false;

				cursorNo.x--;
			}
		}
		else
		{
			keyTrg = true;
		}

		obj->pos.x = (cursorNo.x * 64) + 350;
		obj->pos.y = (cursorNo.y * 64) + 277;

		obj->arrNo.x = cursorNo.x;		//要素番号を保存
		obj->arrNo.y = cursorNo.y;		//要素番号を保存

		cursorCenterPos_2.x = cursorNo.x;

		Block_2::arrNo_2.x = obj->arrNo.x;	//Blockを変更する要素番号を取得
	}

	if (Game::playerNum == Scene::TWO_PLAY)
	{
		//Pad入力処理
		int padInput_2 = GetJoypadInputState(DX_INPUT_PAD2);

		//obj->color.a = 150;

		obj->angle = ToRadian(90);

		//arrNo_2の保存(入れ替えに使用)
		Block_2::saveArryNo_2.x = Block_2::arrNo_2.x;

		if (padInput_2 & PAD_INPUT_RIGHT)
		{
			if (keyTrg && cursorNo.x < BLOCK_WIDTH - 1)
			{
				keyTrg = false;

				cursorNo.x++;
			}
		}
		else if (padInput_2 & PAD_INPUT_LEFT)
		{
			if (keyTrg && cursorNo.x > 0)
			{
				keyTrg = false;

				cursorNo.x--;
			}
		}
		else
		{
			keyTrg = true;
		}

		obj->pos.x = (cursorNo.x * 64) + 100;
		obj->pos.y = (cursorNo.y * 64) + 277;

		obj->arrNo.x = cursorNo.x;		//要素番号を保存
		obj->arrNo.y = cursorNo.y;		//要素番号を保存

		cursorCenterPos_2.x = cursorNo.x;

		Block_2::arrNo_2.x = obj->arrNo.x;	//Blockを変更する要素番号を取得
	}

}

void CursorH_2::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->existFrag = true;

		obj->state++;
		break;
	case 1:
		cursorMoveX(obj);
		break;
	}

	fixPos(obj);
}

void CursorH_2::fixPos(OBJ2D* obj)
{
	/*obj->pivot.x = obj->pos.x - obj->size.x;
	obj->pivot.y = obj->pos.y - obj->size.y;

	obj->pos.x = obj->pivot.x;
	obj->pos.y = obj->pivot.y;*/

	/*obj->pos.x = obj->pos.x - obj->size.x;
	obj->pos.y = obj->pos.y - obj->size.y;*/
}

void CursorW_2::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->existFrag = true;

		obj->state++;
		break;
	case 1:
		cursorMoveY(obj);

		break;
	}
	fixPos(obj);
}

void CursorW_2::fixPos(OBJ2D* obj)
{
	/*obj->pivot.x = obj->pos.x - obj->size.x;
	obj->pivot.y = obj->pos.y - obj->size.y;*/

	/*obj->pos.x = obj->pos.x - obj->size.x;
	obj->pos.y = obj->pos.y - obj->size.y;*/
}

void CursorPivot_2::move(OBJ2D* obj)
{
	if (Game::playerNum == Scene::ONE_PLAY)
	{
		obj->existFrag = true;
		obj->pos.x = cursorCenterPos_2.x * 64 + 350;
		obj->pos.y = cursorCenterPos_2.y * 64 + 150;

		obj->timer++;
		obj->animeTimer = obj->timer / 15 % 4;
		obj->animeState = 0;
	}
	if (Game::playerNum == Scene::TWO_PLAY)
	{
		obj->existFrag = true;
		obj->pos.x = cursorCenterPos_2.x * 64 + 100;
		obj->pos.y = cursorCenterPos_2.y * 64 + 150;

		obj->timer++;
		obj->animeTimer = obj->timer / 15 % 4;
		obj->animeState = 0;
	}


}

void CursorPivot_2::fixPos(OBJ2D* obj)
{

}

void CursorCenter_2::move(OBJ2D* obj)
{
	obj->existFrag = true;
	obj->pos.x = cursorCenterPos_2.x * 64 + 350;
	obj->pos.y = cursorCenterPos_2.y * 64 + 150;

	obj->color.r++;

	if (obj->color.r > 255)
	{
		obj->color.r = 0;
	}
}


void CursorCenter_2::fixPos(OBJ2D* obj)
{

}

void EraseCursor::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}