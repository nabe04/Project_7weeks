#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "actor.h"
#include "algorithm.h"
#include "cursor.h"
#include "MyImgui.h"
#include "block.h"
#include "player.h"
#include "scene.h"
#include "game.h"

//�v���C���[ 1
CursorH		 cursorH;
CursorW		 cursorW;
CursorPivot  cursorPivot;
CursorCenter cursorCenter;

////�v���C���[ 2
CursorH_2		cursorH_2;
CursorW_2		cuesorW_2;
CursorPivot_2	cursorPivot_2;
CursorCenter_2	cursorCenter_2;

Vector2I Cursor::cursorCenterPos;
Vector2I Cursor_2::cursorCenterPos_2;


void Cursor::cursorMoveY(OBJ2D* obj)
{
	//-- ��l�v���C�� --//
	if (Game::gameMode == Scene::ONE_PLAY)
	{
		//Pad���͏���
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//arrNo�̕ۑ�(����ւ��Ɏg�p)
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
		obj->pos.x = (cursorNo.x * 64) + correction.x;
		obj->pos.y = (cursorNo.y * 64) + correction.y;
		
		obj->arrNo.x = cursorNo.x;		//�v�f�ԍ���ۑ�
		obj->arrNo.y = cursorNo.y;		//�v�f�ԍ���ۑ�

		cursorCenterPos.y = cursorNo.y;

		Block_1::arrNo.y = obj->arrNo.y;	//Block��ύX����v�f�ԍ����擾

		uiTimer_1.setPosY(obj->pos.y - 5);		//�^�C�}�[��pos�w��
	}

	//TODO::�␳(two)
	if (Game::gameMode == Scene::TWO_PLAY)
	{
		//Pad���͏���
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//arrNo�̕ۑ�(����ւ��Ɏg�p)
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
		obj->pos.x = (cursorNo.x * 64) + correction.x;
		obj->pos.y = (cursorNo.y * 64) + correction.y;

		obj->arrNo.x = cursorNo.x;		//�v�f�ԍ���ۑ�
		obj->arrNo.y = cursorNo.y;		//�v�f�ԍ���ۑ�

		cursorCenterPos.y	= cursorNo.y;

		Block_1::arrNo.y		= obj->arrNo.y;		//Block��ύX����v�f�ԍ����擾

		uiTimer_1.setPosY(obj->pos.y - 5);		//�^�C�}�[��pos�w��
	}

	
}

void Cursor::cursorMoveX(OBJ2D* obj)
{
	char keyCursor[KEY_MAX];
	GetHitKeyStateAll(keyCursor);

	if (Game::gameMode == Scene::ONE_PLAY)
	{
		//Pad���͏���
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//obj->color.a = 150;

		obj->angle = ToRadian(90);

		//arrNo�̕ۑ�(����ւ��Ɏg�p)
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

		obj->pos.x = (cursorNo.x * 64) + correction.x;
		obj->pos.y = (cursorNo.y * 64) + correction.y;

		obj->arrNo.x = cursorNo.x;		//�v�f�ԍ���ۑ�
		obj->arrNo.y = cursorNo.y;		//�v�f�ԍ���ۑ�

		cursorCenterPos.x = cursorNo.x;

		Block_1::arrNo.x = obj->arrNo.x;	//Block��ύX����v�f�ԍ����擾

		uiTimer_1.setPosX(obj->pos.x - 17);		//�^�C�}�[��pos�w��
	}

	//TODO::�␳�l(two)
	if (Game::gameMode == Scene::TWO_PLAY)
	{
		//Pad���͏���
		int padInput = GetJoypadInputState(DX_INPUT_PAD1);

		//obj->color.a = 150;

		obj->angle = ToRadian(90);

		//arrNo�̕ۑ�(����ւ��Ɏg�p)
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

		obj->pos.x = (cursorNo.x * 64) + correction.x;
		obj->pos.y = (cursorNo.y * 64) + correction.y;

		obj->arrNo.x = cursorNo.x;		//�v�f�ԍ���ۑ�
		obj->arrNo.y = cursorNo.y;		//�v�f�ԍ���ۑ�

		cursorCenterPos.x = cursorNo.x;

		Block_1::arrNo.x = obj->arrNo.x;	//Block��ύX����v�f�ԍ����擾

		uiTimer_1.setPosX(obj->pos.x - 17);		//�^�C�}�[��pos�w��
	}
}

void CursorH::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//�����ݒ�
		//TODO::�ݒ�
		if(Game::gameMode == Scene::ONE_PLAY) correction = { 350,277 };
		if(Game::gameMode == Scene::TWO_PLAY) correction = { 100,277 };

		obj->existFrag = true;

		obj->state++;
		break;
	case 1:
		cursorMoveX(obj);
		break;
	}

	fixPos(obj);

#ifdef DEBUG_
	/*obj->color.r = 0 + im_Ui.im_cursor.iColor[0];
	obj->color.g = 0 + im_Ui.im_cursor.iColor[1];
	obj->color.b = 0 + im_Ui.im_cursor.iColor[2];*/

#endif // DEBUG_

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
		//�����ݒ�
		//TODO::�ݒ�Q
		if (Game::gameMode == Scene::ONE_PLAY) correction = { 477,150 };
		if (Game::gameMode == Scene::TWO_PLAY) correction = { 230,150 };

		obj->existFrag = true;

		obj->state++;
		break;
	case 1:
		cursorMoveY(obj);
	
		break;
	}
	fixPos(obj);

#ifdef DEBUG_
	//obj->color.r = 0 + im_Ui.im_cursor.iColor[0];
	//obj->color.g = 0 + im_Ui.im_cursor.iColor[1];
	//obj->color.b = 0 + im_Ui.im_cursor.iColor[2];

#endif // DEBUG_

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
	if (Game::gameMode == Scene::ONE_PLAY)
	{
		correction = { 350,150 };

		obj->existFrag	= true;
		obj->pos.x		= cursorCenterPos.x * 64 + correction.x;
		obj->pos.y		= cursorCenterPos.y * 64 + correction.y;

		obj->timer++;
		obj->animeTimer = obj->timer / 15 % 4;
		obj->animeState = 0;
	}
	if (Game::gameMode == Scene::TWO_PLAY)
	{
		correction = { 99,150 };

		obj->existFrag	= true;
		obj->pos.x		= cursorCenterPos.x * 64 + correction.x;
		obj->pos.y		= cursorCenterPos.y * 64 + correction.y;

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
	if (Game::gameMode == Scene::ONE_PLAY)	  correction  = { 350,150 };
	if (Game::gameMode == Scene::TWO_PLAY)  correction = { 100,150 };

	obj->existFrag = true;
	obj->pos.x = cursorCenterPos.x * 64 + correction.x;
	obj->pos.y = cursorCenterPos.y * 64 + correction.y;

	//obj->color.r++;

	if (obj->color.r > 255)
	{
		obj->color.r = 0;
	}
}

////-- ��l�v���C --////
void Cursor_2::cursorMoveY(OBJ2D* obj)
{
	if (Game::gameMode == Scene::TWO_PLAY)
	{
		//Pad���͏���
		int padInput_2 = GetJoypadInputState(DX_INPUT_PAD2);

		//arrNo�̕ۑ�(����ւ��Ɏg�p)
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
		obj->pos.x = (cursorNo.x * 64) + correction.x;
		obj->pos.y = (cursorNo.y * 64) + correction.y;

		obj->arrNo.x = cursorNo.x;		//�v�f�ԍ���ۑ�
		obj->arrNo.y = cursorNo.y;		//�v�f�ԍ���ۑ�

		cursorCenterPos_2.y = cursorNo.y;

		Block_2::arrNo_2.y = obj->arrNo.y;		//Block��ύX����v�f�ԍ����擾

		uiTimer_2.setPosY(obj->pos.y - 5);		//�^�C�}�[��pos�w��	
	}
}

void Cursor_2::cursorMoveX(OBJ2D* obj)
{
	char keyCursor[KEY_MAX];
	GetHitKeyStateAll(keyCursor);

	if (Game::gameMode == Scene::TWO_PLAY)
	{
		//Pad���͏���
		int padInput_2 = GetJoypadInputState(DX_INPUT_PAD2);

		//obj->color.a = 150;

		obj->angle = ToRadian(90);

		//arrNo_2�̕ۑ�(����ւ��Ɏg�p)
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

		obj->pos.x   = (cursorNo.x * 64) + correction.x;
		obj->pos.y   = (cursorNo.y * 64) + correction.y;

		obj->arrNo.x = cursorNo.x;		//�v�f�ԍ���ۑ�
		obj->arrNo.y = cursorNo.y;		//�v�f�ԍ���ۑ�

		cursorCenterPos_2.x = cursorNo.x;

		Block_2::arrNo_2.x = obj->arrNo.x;	//Block��ύX����v�f�ԍ����擾

		uiTimer_2.setPosX(obj->pos.x - 17);		//�^�C�}�[��pos�w��
	}

}

void CursorH_2::move(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//�����ݒ�
		correction = { 600,277 };

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
		//�����ݒ�
		correction = { 730,150 };

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
	if (Game::gameMode == Scene::TWO_PLAY)
	{
		correction = { 600,150 };

		obj->existFrag = true;
		obj->pos.x = cursorCenterPos_2.x * 64 + correction.x;
		obj->pos.y = cursorCenterPos_2.y * 64 + correction.y;

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
	correction		= { 600,150 };

	obj->existFrag	= true;
	obj->pos.x		= cursorCenterPos_2.x * 64 + correction.x;
	obj->pos.y		= cursorCenterPos_2.y * 64 + correction.y;

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
