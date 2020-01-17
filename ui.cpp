#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "algorithm.h"
#include "MyImgui.h"
#include "ui.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "scene_result.h"
#include "load_texture.h"


int		UI::nowCombo_1 = 0;
int		UI::nowCombo_2 = 0;
int		UI::score_1 = 0;
int		UI::score_2 = 0;
float	UI::eraseBlockPow_1 = 0;
float	UI::eraseBlockPow_2 = 0;
bool    UI::feverFrag = false;

UiTimer uiTimer_1;
UiTimer uiTimer_2;
UiCombo uiCombo_1;
UiCombo uiCombo_2;
UiScore uiScore_1;
UiGauge uiGauge_1;
UiGauge uiGauge_2;

UiCounter uiCounter_1;		//�J�E���^�[
UiCounter uiCounter_2;

//�^�C�}�[(UI)�̐���
void UI::moveTimer(OBJ2D* obj, Vector2F pos)
{
	int			dispTime;
	const int	FPS = 60;

	switch (obj->state)
	{
	case 0:
		//--�����ݒ�--//
		obj->pos = obj->savePos;
		obj->timer = n_general_function::setTimer(60);
		obj->existFrag = true;
		obj->text = "%.f";
		obj->fontSize = 22;
		obj->fontThick = 3;
		obj->color = { 0, 0, 0, 255 };
		colorState = 0;
		colorTimer = 0;
		obj->loadData = n_font::fh_yomogi;
		obj->state++;
		break;
	case 1:

		obj->savePos = pos;

		dispTime = obj->timer / FPS;
		obj->dispNum = static_cast<float>(dispTime);

		if (Game::gameMode == Scene::ONE_PLAY)
		{
#ifdef USE_IMGUI	//imgui�g�p��
			/*obj->pos.x   = SCREEN_WIDTH - 400 + im_Ui.im_uiTimer.fParam.x;
			obj->pos.y   = 0 + im_Ui.im_uiTimer.fParam.y;*/
			obj->color.r = static_cast<int>(im_Ui.im_uiTimer.iColor[0]);
			obj->color.g = static_cast<int>(im_Ui.im_uiTimer.iColor[1]);
			obj->color.b = static_cast<int>(im_Ui.im_uiTimer.iColor[2]);
			obj->color.a = static_cast<int>(im_Ui.im_uiTimer.iColor[3]);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
			/*obj->pos.x   = SCREEN_WIDTH - 400;
			obj->pos.y   = 0;*/
#endif //USE_IMGUI
		}
		if (Game::gameMode == Scene::TWO_PLAY)
		{
			/*obj->pos.x   = 350;
			obj->pos.y   = 0;*/
		}

		int attention = n_general_function::setTimer(30);//����

		int warning = n_general_function::setTimer(10);//�x��

													   //�^�C�}�[���O�ɋ߂Â����Ƃɕω����N����
													   //�I��10�b�O
		if (obj->timer < warning)
		{
			switch (colorState)
			{
			case 0:
				colorTimer++;
				obj->fontSize++;
				obj->savePos.x -= 2;
				obj->savePos.y -= 2;

				obj->color = { 255,0,0,255 };
				if (colorTimer > 10)
				{
					colorTimer = 0;
					colorState = 1;
				}
				break;
			case 1:
				colorTimer++;
				obj->fontSize--;
				/* obj->savePos.x++;
				obj->savePos.y++;*/
				obj->color = { 0,0,0,255 };
				if (colorTimer > 10)
				{
					colorTimer = 0;
					colorState = 0;
				}
				break;
			}
			//�^�C�}�[��1���̎��̈ʒu�␳
			obj->pos.x = obj->savePos.x + 8;
			obj->pos.y = obj->savePos.y - 4;
		}
		//�I���R�O�b�O
		else if (obj->timer < attention)
		{
			//�ʒu
			obj->pos.x = obj->savePos.x;
			obj->pos.y = obj->savePos.y - 4;
			obj->color = { 255,0,0,255 };
		}
		else
		{
			//�ʒu
			obj->pos.x = obj->savePos.x;
			obj->pos.y = obj->savePos.y - 4;
			obj->color = { 0, 0, 0, 255 };
		}

		//�ʏ펞�̂݃^�C�}�[�����炵������
		if (feverFrag == false)
		{
			obj->timer--;
		}
		//�t�B�[�o�[���A�܂��͂O�b�ɂȂ�����^�C�����~�߂�
		else;

		if (obj->timer <= 0)
		{
			obj->timer = 0;
		}

		break;
	}
}

void UI::moveCombo(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		obj->text = "Combo : %.f";
		obj->existFrag = true;
		obj->color.a = 255;
		obj->fontSize = 40;//�����̑傫��
		obj->fontThick = 3; //�����̌���
		if (Game::gameMode == Scene::ONE_PLAY) obj->pos = { 320,48 };
		if (Game::gameMode == Scene::TWO_PLAY)
		{
			if (playerNo == Scene::ONE_PLAY) obj->pos = { 100,48 };
			if (playerNo == Scene::TWO_PLAY) obj->pos = { 600,48 };
		}
		move = { 0,0 };

		obj->state = 1;
		break;

	case 1:
		obj->fontSize += 6;
		move.x -= 4;
		move.y -= 4;
		//-- ��l�v���C�� --//
		if (Game::gameMode == Scene::ONE_PLAY)
		{
			/*if (obj->pos.x < 283)
			{
			move.x = 0;
			obj->pos.x = 283;
			}
			if (obj->pos.y < 3)
			{
			move.y = 0;
			obj->pos.y = 3;
			}*/

			/*if (move.x < -20)
			{
			move.x = 0;
			}
			if (move.y < -20)
			{
			move.y = 0;
			}*/
		}

		if (obj->fontSize > 82)
		{
			move = { 0,0 };
			obj->fontSize = 82;
			obj->state = 2;
		}
		if (playerNo == Scene::ONE_PLAY)  obj->dispNum = static_cast<float>(nowCombo_1);
		if (playerNo == Scene::TWO_PLAY)  obj->dispNum = static_cast<float>(nowCombo_2);
		break;
	case 2:
		obj->fontSize -= 4;
		move.x += 2;
		move.y += 2;
		obj->color.a--;

		//-- ��l�v���C�� --//

		/*if (obj->pos.x > 325)
		{
		move.x = 0;
		obj->pos.x = 325;
		}
		if (obj->pos.y > 45)
		{
		move.y = 0;
		obj->pos.y = 45;
		}*/

		/* if (move.x > 15)
		{
		move.x = 0;
		}
		if (move.y > 15)
		{
		move.y = 0;
		}*/
		if (obj->fontSize < 40)
		{
			if (Game::gameMode == Scene::ONE_PLAY)
			{
				obj->pos = { 320,48 };
			}
			if (Game::gameMode == Scene::TWO_PLAY)
			{
				if (playerNo == Scene::ONE_PLAY) obj->pos = { 100,48 };
				if (playerNo == Scene::TWO_PLAY) obj->pos = { 600,48 };
			}
			move = { 0,0 };
			obj->fontSize = 40;
			obj->state = 3;
		}


		break;
	case 3:

		obj->color.a--;

		move = { 0,0 };

		if (obj->color.a < 0)
		{
			obj->mvAlg = nullptr;
			if (playerNo == Scene::ONE_PLAY)
			{
				nowCombo_1 = 0;
				UI::eraseBlockPow_1 = 1.0f;
			}
			if (playerNo == Scene::TWO_PLAY)
			{
				nowCombo_2 = 0;
				UI::eraseBlockPow_2 = 1.0f;
			}
		}
		break;
	}

	obj->pos.x += move.x;
	obj->pos.y += move.y;

}
void UI::moveScore(OBJ2D* obj)
{
	obj->existFrag = true;
	int holdScore_1;	//1P�̊l���������X�R�A��ێ�����ϐ�
	int holdScore_2;	//2P�̊l���������X�R�A��ێ�����ϐ�
	switch (obj->state)
	{
	case 0:
		obj->text = "   SCORE\n %07.f";
		obj->dispNum = 0;
		holdScore_1 = 0;
		holdScore_2 = 2;

		obj->color.a = 255;
		obj->fontSize = 100;
		obj->fontThick = 3;
		obj->loadData = n_font::fh_yomogi;
		obj->state++;
	case 1:
		if (Game::gameMode == Scene::ONE_PLAY)
		{
#ifdef USE_IMGUI //imgui�g�p��
			obj->pos.x = 688 + im_Ui.im_uiScore_1.fParam.x;
			obj->pos.y = 117 + im_Ui.im_uiScore_1.fParam.y;
			obj->color.r = static_cast<int>(im_Ui.im_uiScore_1.iColor[0]);
			obj->color.g = static_cast<int>(im_Ui.im_uiScore_1.iColor[1]);
			obj->color.b = static_cast<int>(im_Ui.im_uiScore_1.iColor[2]);
			obj->color.a = static_cast<int>(im_Ui.im_uiScore_1.iColor[3]);
			obj->fontSize = 36 + static_cast<int>(im_Ui.im_uiScore_1.size);
			obj->fontThick = 5 + static_cast<int>(im_Ui.im_uiScore_1.thick);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
			obj->pos.x = 688;
			obj->pos.y = 117;
			obj->fontSize = 36;
			obj->fontThick = 5;
#endif // !USE_IMGUI
			holdScore_1 = score_1;

			if (holdScore_1 == 0)
			{
				holdScore_1 = 1;
			}

			int calcScore = holdScore_1 / 50;

			if (calcScore <= 0) calcScore = 1;

			// obj->dispNum += score_1 / (holdScore_1/30);
			obj->dispNum += score_1 / calcScore;
			if (obj->dispNum > holdScore_1)
			{
				obj->dispNum = holdScore_1;
			}
		}

		if (Game::gameMode == Scene::TWO_PLAY)
		{
			if (playerNo == Scene::ONE_PLAY)
			{
				holdScore_1 = score_1;

				if (holdScore_1 == 0) holdScore_1 = 1;

				int calcScore = holdScore_1 / 5;

				if (calcScore <= 0) calcScore = 1;

				// obj->dispNum += score_1 / (holdScore_1/30);

				obj->dispNum += score_1 / calcScore;

				if (obj->dispNum > holdScore_1)
				{
					obj->dispNum = static_cast<float>(holdScore_1);  //�v���C���[ 1
				}
			}

			if (playerNo == Scene::TWO_PLAY)
			{
				holdScore_2 = score_2;

				if (holdScore_2 == 0)
				{
					holdScore_2 = 1;
				}

				int calcScore = holdScore_2 / 5;

				if (calcScore <= 0) calcScore = 1;

				// obj->dispNum += score_1 / (holdScore_1/30);

				obj->dispNum += score_2 / calcScore;

				if (obj->dispNum > holdScore_2)
				{
					obj->dispNum = static_cast<float>(holdScore_2);  //�v���C���[ 2
				}
			}
			//���삵�Ă���v���C���[��No
			if (playerNo == Scene::ONE_PLAY)
			{
#ifdef USE_IMGUI //imgui�g�p��
				obj->pos.x = 396 + im_Ui.im_uiScore_1.fParam.x;
				obj->pos.y = 122 + im_Ui.im_uiScore_1.fParam.y;
				obj->color.r = static_cast<int>(im_Ui.im_uiScore_1.iColor[0]);
				obj->color.g = static_cast<int>(im_Ui.im_uiScore_1.iColor[1]);
				obj->color.b = static_cast<int>(im_Ui.im_uiScore_1.iColor[2]);
				obj->color.a = static_cast<int>(im_Ui.im_uiScore_1.iColor[3]);
				obj->fontSize = 25 + static_cast<int>(im_Ui.im_uiScore_1.size);
				obj->fontThick = 8 + static_cast<int>(im_Ui.im_uiScore_1.thick);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
				obj->pos.x = 396;
				obj->pos.y = 122;
				obj->fontSize = 25;
				obj->fontThick = 8;
#endif // !USE_IMGUI

			}

			if (playerNo == Scene::TWO_PLAY)
			{
#ifdef USE_IMGUI //imgui�g�p��
				obj->pos.x = 396 + im_Ui.im_uiScore_2.fParam.x;
				obj->pos.y = 360 + im_Ui.im_uiScore_2.fParam.y;
				obj->color.r = static_cast<int>(im_Ui.im_uiScore_2.iColor[0]);
				obj->color.g = static_cast<int>(im_Ui.im_uiScore_2.iColor[1]);
				obj->color.b = static_cast<int>(im_Ui.im_uiScore_2.iColor[2]);
				obj->color.a = static_cast<int>(im_Ui.im_uiScore_2.iColor[3]);
				obj->fontSize = 25 + static_cast<int>(im_Ui.im_uiScore_2.size);
				obj->fontThick = 8 + static_cast<int>(im_Ui.im_uiScore_2.thick);
#endif  //USE_IMGUI

#ifndef USE_IMGUI
				obj->pos.x = 396;
				obj->pos.y = 360;
				obj->fontSize = 25;
				obj->fontThick = 8;
#endif // !USE_IMGUI
			}
		}
		break;
	}
}
//add.end
////////////////////////////////////

void UI::moveGauge(OBJ2D* obj)
{
	obj->existFrag = true;
	int adjustGauge;
	switch (obj->state)
	{
	case 0:
		//-- �����ݒ� --//
		//��l�v���C��
		if (Game::gameMode == Scene::ONE_PLAY)
		{
			obj->pos.x = 480;
			obj->pos.y = 480;
		}

		//��l�v���C��
		if (Game::gameMode == Scene::TWO_PLAY)
		{
			if (playerNo == Scene::ONE_PLAY)
			{
				obj->pos.x = 225;
				obj->pos.y = 480;
			}

			if (playerNo == Scene::TWO_PLAY)
			{
				obj->pos.x = 730;
				obj->pos.y = 480;
			}
		}

		feverFrag = false;
		addGauge = 0;
		feverCount = 0;
		adjustGauge = 0;

		obj->timer = 0;
		obj->clipSize.x = 0;
		obj->clipSize.y = 100;
		obj->state++;
	case 1:
		//-- �Q�[�W���܂蒆 --//
		feverFrag = false;
		obj->clipOrigin.x = 0;
		obj->clipOrigin.y = 0;

		//�A�j���[�V��������
		obj->animeState = 1;
		obj->animeTimer = obj->timer / 5 % 4;
		obj->timer++;

		adjustGauge = (3 * feverCount);

		if (adjustGauge > 10)
		{
			adjustGauge = 10;
		}

		obj->clipSize.x = addGauge * (20 - adjustGauge);

		if (obj->clipSize.x > 320)
		{
			obj->clipSize.x = 320;
			obj->timer = 0;
			addGauge = 0;
			feverCount++;
			obj->state++;
		}

		break;
	case 2:
		//-- �t�B�[�o�[�� --//
		feverFrag = true;
		addGauge = 0;
		obj->animeState = 0;
		obj->animeTimer = 0;

		obj->timer++;
		if (obj->timer % 20 == 0)
		{
			obj->clipSize.x -= 10;
		}

		if (obj->clipSize.x <= 0)
		{
			obj->clipSize.x = 0;
			obj->timer = 0;
			obj->state = 1;
		}

		break;
	}
}

//SCORE�̌v�Z�@�@(1: ���݂̃R���{�� 2: �u���b�N�̏������� 3: ���݂̏������{��)
int UiScore::calcScore(const int combo, const int blockNum, float* eraseBlockPow)
{
	float powCombo = 1 + (static_cast<float>(combo) / 10);	//�R���{���ɂ��{��(�O��1�͓��{�ɂȂ�悤��)
	if (blockNum == 3) *eraseBlockPow += 0.2f;
	if (blockNum == 4) *eraseBlockPow += 0.5f;

	if (feverFrag == true)
	{
		feverMgnfication = 2;
	}
	else
	{
		feverMgnfication = 1;
	}

	float score = 100 * powCombo * (*eraseBlockPow)*feverMgnfication;

	return static_cast<int>(score);
}

//�Q�[�W�̑��� (1 : ���ŏ������u���b�N�̐� , 2: �v���C���[�ԍ�)
void UiGauge::calcGauge(const int eraseNum, const int playerNo)
{
	addGauge += eraseNum;
}

void UiTimer::move(OBJ2D* obj)
{
	moveTimer(obj, pos);
}

void UiCombo::move(OBJ2D* obj)
{
	moveCombo(obj);
}

void UiScore::move(OBJ2D* obj)
{
	moveScore(obj);
}

void UiGauge::move(OBJ2D* obj)
{
	moveGauge(obj);
}

////-- �f�X�g���N�^ --////
UiScore :: ~UiScore()
{
	if (Game::gameMode == Scene::ONE_PLAY)
	{
		Result::resultScore_1 = 0;
		Result::resultScore_1 = score_1;
		score_1 = 0;
	}
	if (score_2 != 0)
	{
		Result::resultScore_2 = 0;
		Result::resultScore_2 = score_2;
	}


	score_2 = 0;
	eraseBlockPow_1 = 0;
	eraseBlockPow_2 = 0;
}

void EraseUi::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}

void UiCounter::init()
{
	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			counter[h][w].reset();
		}
	}
}

void UiCounter::update()
{
	bool moveFrag = false;

	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if (counter[h][w].existFrag)
			{
				switch (counter[h][w].state)
				{
				case 0:
					counter[h][w].timer			= n_general_function::setTimer(10);
					counter[h][w].animeState	= 0;
					counter[h][w].animeTimer	= 0;

					counter[h][w].state++;
					break;
				case 1:
					if (h == 0)
					{
						//counter[h][w].timer--;

						if (counter[h][w].timer < n_general_function::setTimer(7))  counter[h][w].animeTimer = 1;
						if (counter[h][w].timer < n_general_function::setTimer(3))  counter[h][w].animeTimer = 2;

						if (counter[h][w].timer <= 0)
						{
							counter[h][w].state++;
						}
					}
					break;
				case 2:
					counter[h][w].existFrag = false;
					counter[h][w].moveFrag  = true;
					counter[h][w].savePos   = counter[h][w].pos;
					moveFrag				= true;
					break;
				}
			}
			
			//-- ���u���b�N��������Ɖ��ɓ������� --//
			if (counter[h][w].moveFrag)
			{
				counter[h][w].gravity++;
				counter[h][w].pos.y += counter[h][w].gravity;

				//-- ����pos�ȏア���Ύ~�܂� --//
				if (counter[h][w].pos.y > counter[h][w].savePos.y + COUNTER_BLOCK_SPACE)
				{
					counter[h][w].pos.y    = counter[h][w].savePos.y + COUNTER_BLOCK_SPACE;
					counter[h][w].gravity  = 0;
					counter[h][w].moveFrag = false;
					counter[h][w].copyFrag = true;
				}
			}
		}
	}

	for (int h = 1; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if (counter[h][w].existFrag)
			{
				counter[h][w].pos.y		= counter[h - 1][0].pos.y - COUNTER_BLOCK_SPACE;

				if (counter[h - 1][0].moveFrag)
				{
					counter[h][w].moveFrag = true;
				}
			}
		}
	}

	bool eraseFrag = false;
		
	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if(counter[h][w].existFrag)
			{
				if (moveFrag)
				{
					counter[h][w].setMoveFrag(&counter[h][w], true);
					counter[h][w].savePos = counter[h][w].pos;
				}
				if (counter[h][w].copyFrag)
				{
					counter[h][w].copyFrag = false;
					moveOBJData(&counter[h - 1][w], &counter[h][w]);
					counter[h][w].reset();
					eraseFrag = true;
				}
			}
		}
	}

	if (eraseFrag)
	{
		int maxHeight = 0;

		for (int h = COUNTER_MAX_H; h > 0; h--)
		{
			if (counter[h][0].existFrag)
			{
				maxHeight = h;
				break;
			}
		}

		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			//counter[maxHeight][w].reset();
		}
	}
}

void UiCounter::draw()
{
	for (int h = 0; h < COUNTER_MAX_H; h++)
	{
		for (int w = 0; w < COUNTER_MAX_W; w++)
		{
			if (counter[h][w].existFrag)
			{
				DrawRotaGraph3
				(
					counter[h][w].pos.x, counter[h][w].pos.y,
					counter[h][w].size.x, counter[h][w].size.y,
					counter[h][w].scale.x, counter[h][w].scale.y,
					counter[h][w].angle,
					n_texture::sprCounterBlock[counter[h][w].animeState + counter[h][w].animeTimer],
					true,
					false
				);
			}
		}
	}
}

void UiCounter::calcCounterBlockNum(UiCounter* rivalCounter, UiCounter* myCounter, int posX, int height, bool center)
{
	//-- �J�[�\�������� --//
	if (center)
	{
		//-- ����ɑ���u���b�N�̌��w�� --//
		switch (rivalCounter->breakBlock_2)
		{
		case 1:
			rivalCounter->arrNo_W = 1;
			break;
		case 2:
			rivalCounter->arrNo_W = 3;
			break;
		case 3:
			rivalCounter->arrNo_W = 4;
			break;
		case 4:
			rivalCounter->arrNo_W = 5;
			break;
		}
		rivalCounter->breakBlock_2 = 0;
	}
	else
	{
		int num1 = 0;
		int num2 = 0;
		int num3 = 0;

		//-- ��������J�E���^�[�u���b�N�̌�  (�����̃u���b�N���������� * ��������u���b�N��) --//
		num1 = rivalCounter->breakBlock_2 * 1;
		num2 = rivalCounter->breakBlock_3 * 2;
		num3 = rivalCounter->breakBlock_4 * 3;

		rivalCounter->arrNo_W = num1 + num2 + num3;

		rivalCounter->breakBlock_2 = 0;
		rivalCounter->breakBlock_3 = 0;
		rivalCounter->breakBlock_4 = 0;
	}
	if (myCounter->counter[0][0].existFrag)
	{
		int beginArrNo = 0;

		for (int w = COUNTER_MAX_W - 1; w >= 0; w--)
		{
			if (myCounter->counter[0][w].existFrag)
			{
				beginArrNo = w;
				break;
			}
		}

		int count = 0;

		bool generateFrag = false;

		for (int w = beginArrNo; w >= 0; w--)
		{
			if (w != 0)
			{
				myCounter->counter[0][w].existFrag = false;
			}
			else
			{
				myCounter->counter[0][w].state = 2;

				generateFrag = true;
			}
			
			count++;

			if (count == rivalCounter->arrNo_W)  break;
		}
		if (generateFrag)
		{
			//�S�ẴJ�E���^�[�u���b�N����������������u���b�N�v���X�P�̃u���b�N�𑊎�ɕԂ�
			for (int w = 0; w < myCounter->counter[0][0].maxVal + 1; w++)
			{
				rivalCounter->counter[height][w].serchSet(&rivalCounter->counter[height][w], { static_cast<float>(posX + w * 32) ,static_cast<float>(-(height * COUNTER_BLOCK_SPACE) + 80) }, { COUNTER_BLOCK_CHIP_SIZE_W ,COUNTER_BLOCK_CHIP_SIZE_H }, w, myCounter->counter[0][w].maxVal + 1);
			}
		}
	}
	else
	{
		for (int w = 0; w < rivalCounter->arrNo_W; w++)
		{
			rivalCounter->counter[height][w].serchSet(&rivalCounter->counter[height][w], { static_cast<float>(posX + w * 32) ,static_cast<float>(-(height * COUNTER_BLOCK_SPACE) + 80) }, { COUNTER_BLOCK_CHIP_SIZE_W ,COUNTER_BLOCK_CHIP_SIZE_H }, w, rivalCounter->arrNo_W);
		}
	}
}

void UiCounter::addCounterBlock(UiCounter* counter,const int blockNum)
{
	if (blockNum == 2)
	{
		counter->breakBlock_2++;
	}
	if (blockNum == 3)
	{
		counter->breakBlock_3++;
	}
	if (blockNum == 4)
	{
		counter->breakBlock_4++;
	}
}

void UiCounter::deleteCounterBlock(OBJ2D* counter)
{
	switch (counter->state_2)
	{
	case 0:
		//-- �A�j���[�V���������Ȃ�(����) --//

		counter->state_2++;
		break;
	case 1:
		counter->existFrag = false;
		break;
	}
}



