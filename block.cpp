#include <assert.h>
#include "generic.h"
#include "obj2d.h"
#include "util.h"
#include "load_texture.h"
#include "actor.h"
#include "player.h"
#include "block.h"
#include "scene.h"
#include "game.h"

int original[BLOCK_HEIGHT][BLOCK_WIDTH] = {};

////--Block �N���X--////

Vector2I Block_1::arrNo			= {};	//��l��
Vector2I Block_1::saveArryNo	= {};
Vector2I Block_2::arrNo_2		= {};	//��l��
Vector2I Block_2::saveArryNo_2	= {};

////-- �v���C���[ 1 --////�@
//--����������--//
void Block_1::init()
{
	if (Game::gameMode == Scene::ONE_PLAY)
	{
		correction = { 350,150 };

		for (int h = 0; h < BLOCK_HEIGHT; h++)
		{
			for (int w = 0; w < BLOCK_WIDTH; w++)
			{
				platform_1[h][w]			= 0;

				block_1[h][w].no			= GetRand(4);
				block_1[h][w].pos.x			= static_cast<float>(w * BLOCK_CHIP_SIZE + correction.x);
				block_1[h][w].pos.y			= static_cast<float>(h * BLOCK_CHIP_SIZE + correction.y);
				block_1[h][w].existFrag		= true;
				block_1[h][w].animeState	= block_1[h][w].no;
			}
		}
	}

	if (Game::gameMode == Scene::TWO_PLAY)
	{
		correction = { 100,150 };

		for (int h = 0; h < BLOCK_HEIGHT; h++)
		{
			for (int w = 0; w < BLOCK_WIDTH; w++)
			{
				platform_1[h][w] = 0;

				block_1[h][w].no = GetRand(4);
				block_1[h][w].pos.x = static_cast<float>(w * BLOCK_CHIP_SIZE + correction.x);
				block_1[h][w].pos.y = static_cast<float>(h * BLOCK_CHIP_SIZE + correction.y);
				block_1[h][w].existFrag = true;
				block_1[h][w].animeState = block_1[h][w].no;
			}
		}
	}
}

//--�X�V����--//
void Block_1::update()
{
	blockManage();
	blokenBlockMove();
	
#ifdef DEBUG_
	static int size = 64;
	//size++;
	if (size > 64)	size = 0;
#endif //DEBUG_
	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			platform_1[h][w]			= block_1[h][w].no;
			block_1[h][w].animeState	= block_1[h][w].no;
#ifdef DEBUG_
			block_1[h][w].clipSize		= { size,size };
#endif //DEBUG_
		}
	}

	//--�z��̍X�V--//
	if (arrNo.x != saveArryNo.x)
	{
		//�`��F�ύX
		int swap									= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][arrNo.x].no				= block_1[arrNo.y][saveArryNo.x].no;
		block_1[arrNo.y][saveArryNo.x].no			= swap;

		//���̔z��̒l�̕ύX
		block_1[arrNo.y][arrNo.x].animeState		= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][saveArryNo.x].animeState	= block_1[arrNo.y][saveArryNo.x].no;
	}
	if (arrNo.y != saveArryNo.y)
	{
		//�`��F�ύX
		int swap									= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][arrNo.x].no				= block_1[saveArryNo.y][arrNo.x].no;
		block_1[saveArryNo.y][arrNo.x].no			= swap;

		//���̔z��̒l�̕ύX
		block_1[arrNo.y][arrNo.x].animeState		= block_1[arrNo.y][arrNo.x].no;
		block_1[saveArryNo.y][arrNo.x].animeState	= block_1[saveArryNo.y][arrNo.x].no;
	}

}

//--�`�揈��--//
void Block_1::draw()
{
	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			if (block_1[h][w].existFrag)
			{
				int sprData = DerivationGraph(block_1[h][w].clipOrigin.x, block_1[h][w].clipOrigin.y, block_1[h][w].clipSize.x, block_1[h][w].clipSize.y, n_texture::sprBlock[(block_1[h][w].animeState * BLOCK_CHIP_W) + block_1[h][w].animeTimer]);

				DrawRotaGraph3(
					block_1[h][w].pos.x, block_1[h][w].pos.y,
					BLOCK_CHIP_SIZE / 2, BLOCK_CHIP_SIZE / 2,
					block_1[h][w].scale.x, block_1[h][w].scale.y,
					block_1[h][w].angle,
					sprData,
					true,
					block_1[h][w].revFrag.x, block_1[h][w].revFrag.y
				);

				DeleteGraph(sprData);
			}
		}
	}

#ifdef DEBUG_
	DrawFormatString(0, 40, GetColor(0, 255, 0), "arrNo x : %d", arrNo.x);
	DrawFormatString(0, 60, GetColor(0, 255, 0), "arrNo y : %d", arrNo.y);
	DrawFormatString(0, 80, GetColor(0, 255, 0), "eraseBlockNum : %d", eraseBlockCount);

	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			DrawFormatString((w * 20) + 800, (h * 20) + 100, GetColor(255, 255, 255), "%d", platform_1[h][w],20);
		}
	}
#endif //DEBUG_
}

//--�u���b�N��������--//

//�S�̂̊Ǘ�
void Block_1::blockManage()
{
	uiCombo_1.setPlayerNo(0); //���݂̃v���C���[�ԍ��ݒ�
	uiScore_1.setPlayerNo(0); //���݂̃v���C���[�ԍ��ݒ�
	uiGauge_1.setPlayerNo(0); //���݂̃v���C���[�ԍ��ݒ�
	uiCounter_2.calcFrag = false;	//�v�Z�����̏�����

	int eraseBlockPerOneLoop = 0;

	//Pad���͏���
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//����
	if (padInput & (PAD_INPUT_C | PAD_INPUT_B | PAD_INPUT_A | PAD_INPUT_4))
	{
		
		//-- ������ׂ��Ƃ� --//
		if (keyTrg_1 && checkBlockWidth(arrNo.x, arrNo.y, platform_1[arrNo.y][arrNo.x], LEFT) && arrNo.x != 0)
		{
			UI::nowCombo_1++;  //�R���{���Z
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_1()->init(); //�R���{UI�̏�����
			if (Game::gameMode == Scene::ONE_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1,NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0, 0 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveL, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>(445), static_cast<float>((CursorH::cursorCenterPos.y * 64) + 150) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", (CursorH::cursorCenterPos.y * 64) + 150);  //�v���X(������)
			}
			if (Game::gameMode == Scene::TWO_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0,40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveL, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>(195), static_cast<float>((CursorH::cursorCenterPos.y * 64) + 150) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", (CursorH::cursorCenterPos.y * 64) + 150);  //�v���X(������)
				uiCounter_2.addCounterBlock(&uiCounter_2, eraseBlockCount);	
				uiCounter_2.calcFrag = true;
			}
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, LEFT);        //�u���b�N��������
			uiScore_1.score_1 += uiScore_1.calcScore(UI::nowCombo_1, eraseBlockCount, &UI::eraseBlockPow_1); //�X�R�A�v�Z����
		}
		//�E����ׂ��Ƃ�
		if (keyTrg_1 && checkBlockWidth(arrNo.x, arrNo.y, platform_1[arrNo.y][arrNo.x], RIGHT) && arrNo.x != BLOCK_WIDTH - 1)
		{
			UI::nowCombo_1++;
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_1()->init();

			if (Game::gameMode == Scene::ONE_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveR, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>(509), static_cast<float>((CursorH::cursorCenterPos.y * 64) + 150) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", (CursorH::cursorCenterPos.y * 64) + 150);  //�v���X(�E����)
			}
			if (Game::gameMode == Scene::TWO_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0,40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveR, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>(262), static_cast<float>((CursorH::cursorCenterPos.y * 64) + 150) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", (CursorH::cursorCenterPos.y * 64) + 150);  //�v���X(�E����)
				uiCounter_2.addCounterBlock(&uiCounter_2, eraseBlockCount);
				uiCounter_2.calcFrag = true;
			}
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, RIGHT);
			uiScore_1.score_1 += uiScore_1.calcScore(UI::nowCombo_1, eraseBlockCount, &UI::eraseBlockPow_1);
		}
		//������ׂ��Ƃ�
		if (keyTrg_1 && checkBlockHeight(arrNo.x, arrNo.y, platform_1[arrNo.y][arrNo.x], BOTTOM) && arrNo.y != BLOCK_HEIGHT - 1)
		{
			UI::nowCombo_1++;
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_1()->init();

			if (Game::gameMode == Scene::ONE_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveB, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>((CursorH::cursorCenterPos.x * 64) + 349), static_cast<float>(312) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", 312);  //�v���X(������)
			}
			if (Game::gameMode == Scene::TWO_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0,40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveB, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>((CursorH::cursorCenterPos.x * 64) + 100), static_cast<float>(312) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", 312);  //�v���X(������)
				uiCounter_2.addCounterBlock(&uiCounter_2, eraseBlockCount);
				uiCounter_2.calcFrag = true;
			}
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, BOTTOM);
			uiScore_1.score_1 += uiScore_1.calcScore(UI::nowCombo_1, eraseBlockCount, &UI::eraseBlockPow_1);
		}
		//�ォ��ׂ��Ƃ�
		if (keyTrg_1&& checkBlockHeight(arrNo.x, arrNo.y, platform_1[arrNo.y][arrNo.x], UP) && arrNo.y != 0)
		{
			UI::nowCombo_1++;
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_1()->init();

			if (Game::gameMode == Scene::ONE_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveT, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>((CursorW::cursorCenterPos.x * 64) + 349), static_cast<float>(244) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", 244);  //�v���X(�ォ��)
			}
			if (Game::gameMode == Scene::TWO_PLAY)
			{
				Game::instance()->uiComboManager_1()->add(&uiCombo_1, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ 0,40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
				Game::instance()->pressMachineManager_1()->add(&pressMachineMoveT, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>((CursorW::cursorCenterPos.x * 64) + 100), static_cast<float>(244) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", 244);  //�v���X(�ォ��)
				uiCounter_2.addCounterBlock(&uiCounter_2, eraseBlockCount);
				uiCounter_2.calcFrag = true;
			}
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, UP);
			uiScore_1.score_1 += uiScore_1.calcScore(UI::nowCombo_1, eraseBlockCount, &UI::eraseBlockPow_1);
		}
		keyTrg_1 = false;

		uiGauge_1.calcGauge(eraseBlockPerOneLoop, Scene::ONE_PLAY); //�t�B�[�o�[�Q�[�W�̑���

		if (Game::gameMode == Scene::TWO_PLAY && uiCounter_2.calcFrag)
		{
			int counterArrNo_H = 0;	//�J�E���^�[�u���b�N�̔z��i�[�p�ϐ� (Height)

			//-- �J�E���^�[�u���b�N�������i�[����z��̍����̕������o�� --//
			for (int h = 0; h < COUNTER_MAX_H; h++)
			{
				if (uiCounter_2.counter[h][0].existFrag)	continue;	//���݂��Ă���Ƃ�(�ՖʂɃu���b�N������Ƃ�)�͔�΂�
				if (uiCounter_2.counter[h][0].moveFrag)		continue;	//�����Ă���Ƃ�(���̃u���b�N�������ĉ��ɗ������Ă���Ƃ�)�͔�΂�
				counterArrNo_H = h;
				break;
			}
		
			bool center = false;
			if (arrNo.x == BOARD_CENTER && arrNo.y == BOARD_CENTER)	center = true;
			uiCounter_2.calcCounterBlockNum(&uiCounter_2, SCREEN_WIDTH / 2 + 150, counterArrNo_H, center);
		}
	}
	else
	{
		keyTrg_1 = true;
	}
}

void Block_1::blockClip(const int width, const int height,int* checkNo, e_Direction direction)
{
	//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		for (int w = 0; w < width; w++)
		{
			switch (block_1[height][w].state)
			{
			case 0:
				block_1[height][w].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_1[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_1[i][0], block_1[height][w].pos,i);
					break;
				}
			}
		}
	}

	//B�����͂��ꂽ��
	if (direction == RIGHT)
	{
		for (int w = BLOCK_WIDTH - 1; w > width; w--)
		{
			switch (block_1[height][w].state)
			{
			case 0:
				block_1[height][w].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_1[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_1[i][0], block_1[height][w].pos, i);
					break;
				}
			}
		}
	}
	//Y�����͂��ꂽ��
	if (direction == UP)
	{
		for (int h = 0; h < height; h++)
		{
			switch (block_1[h][width].state)
			{
			case 0:
				block_1[h][width].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_1[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_1[i][0], block_1[h][width].pos, i);
					break;
				}
			}
		}
	}

	//A�����͂��ꂽ��
	if (direction == BOTTOM)
	{
		for (int h = BLOCK_HEIGHT - 1; h > height; h--)
		{
			switch (block_1[h][width].state)
			{
			case 0:
				block_1[h][width].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_1[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_1[i][0], block_1[h][width].pos, i);
					break;
				}
			}
		}
	}

	const int saveNo = *checkNo;
	while (1)
	{
		*checkNo = GetRand(4);

		if (*checkNo != saveNo)	break;
	}
	
}

//�����ł��邩���� (��)  
// Chip�̉��AChip�̏c�AChip�̗v�f�ԍ��A����
bool Block_1::checkBlockWidth(const int width, const int height, const int checkNo, e_Direction direction)
{
	//��O�`�F�b�N
	if (direction == UP || direction == BOTTOM)
	{
		assert(!"���� direciton �̒l���Ԉ���Ă��܂�");
	}

	int saveNo = -1;

	eraseBlockCount = 0;	//�������u���b�N�̌��J�E���g�p

	//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		if (width > 1)
		{
			for (int w = 0; w < width; w++)
			{
				eraseBlockCount++;

				if (w > 0)
				{
					if (saveNo != platform_1[height][w])
					{
						eraseBlockCount = 0;
						return false;
					}
				}

				saveNo = platform_1[height][w];
			}
			eraseBlockCount = eraseBlockCount;
			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}
			
	}

	//B�����͂��ꂽ��
	if (direction == RIGHT)
	{
		if (width < BLOCK_WIDTH - 2)
		{
			for (int w = BLOCK_WIDTH - 1; w > width; w--)
			{
				eraseBlockCount++;

				if (w < BLOCK_WIDTH - 1)
				{
					if (saveNo != platform_1[height][w])
					{
						eraseBlockCount = 0;
						return false;
					}
				}
				eraseBlockCount = eraseBlockCount;;
				saveNo = platform_1[height][w];
			}
			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}
			
	}

	return false;
}

//�����ł��邩���� (�c)
// Chip�̉��AChip�̏c�AChip�̗v�f�ԍ��A����
bool Block_1::checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction)
{
	//��O�`�F�b�N
	if (direction == RIGHT || direction == LEFT)
	{
		assert(!"���� direciton �̒l���Ԉ���Ă��܂�");
	}

	int saveNo = -1;

	eraseBlockCount = 0;	//�������u���b�N�̌��J�E���g�p

	//Y�����͂��ꂽ��
	if (direction == UP)
	{
		if (height > 1)
		{
			for (int h = 0; h < height; h++)
			{
				eraseBlockCount++;

				if (h > 0)
				{
					if (saveNo != platform_1[h][width])
					{
						eraseBlockCount = 0;
						return false;
					}
				}
				eraseBlockCount	= eraseBlockCount;
				saveNo			= platform_1[h][width];
			}

			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}
	}

	//A�����͂��ꂽ��
	if (direction == BOTTOM)
	{
		if (height < BLOCK_HEIGHT - 2)
		{
			for (int h = BLOCK_HEIGHT - 1; h > height; h--)
			{
				eraseBlockCount++;

				if (h < BLOCK_HEIGHT - 1)
				{
					if (saveNo != platform_1[h][width])
					{
						eraseBlockCount = 0;
						return false;
					}
				}

				eraseBlockCount	= eraseBlockCount;
				saveNo			= platform_1[h][width];
			}
			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}	
	}

	return false;
}

void Block_1::serchSet(OBJ2D* obj, Vector2F pos, const int no)
{
	for (int i = 0; i < BLOKEN_BLOCK_CHIP_NUM; i++)
	{
		blokenBlock_1[no][i].pos		= pos;
		blokenBlock_1[no][i].animeState = i;
		blokenBlock_1[no][i].existFrag	= true;
	}
}

////-- �j��u���b�N���� --////
void Block_1::blokenBlockMove()
{
	for (int h = 0; h < BOARD_CHIP_NUM; h++)
	{
		for (int w = 0; w < BLOKEN_BLOCK_CHIP_NUM; w++)
		{
			if (blokenBlock_1[h][w].existFrag)
			{
				switch (blokenBlock_1[h][w].state)
				{
				//-- �����ݒ� --//
				case 0:
					//-- �ǂ����̕����Ƀu���b�N���i�ނ����w�� --//
					blokenBlock_1[h][w].speed =  3;			

					if (w % 2 == 0) blokenBlock_1[h][w].speed *= -1;	//�����Ȃ�speed���}�C�i�X��
					
					//-- Block���オ�鍂����ݒ� --//
					blokenBlock_1[h][w].gravity = -20;

					blokenBlock_1[h][w].state++;
					break;

				//-- �X�V���� --//
				case 1:
					blokenBlock_1[h][w].gravity += 2;							//gravity
					blokenBlock_1[h][w].pos.x	+= blokenBlock_1[h][w].speed;	//position_x
					blokenBlock_1[h][w].pos.y	+= blokenBlock_1[h][w].gravity; //position_y
					blokenBlock_1[h][w].angle	+= ToRadian(15);				//angle

					if (blokenBlock_1[h][w].pos.y > SCREEN_HEIGHT + 50)
					{
						blokenBlock_1[h][w].state++;
					}
					break;

				//-- �I������ --//
				case 2:
					blokenBlock_1[h][w].existFrag	= false;
					blokenBlock_1[h][w].state		= 0;

					break;
				}
			}
		}
	}
}

void Block_1::drawBloken()
{
	for (int h = 0; h < BOARD_CHIP_NUM; h++)
	{
		for (int w = 0; w < BLOKEN_BLOCK_CHIP_NUM; w++)
		{
			if (blokenBlock_1[h][w].existFrag)
			{
				//int sprData = DerivationGraph(blokenBlock_1[h][w].clipOrigin.x, blokenBlock_1[h][w].clipOrigin.y, blokenBlock_1[h][w].clipSize.x, blokenBlock_1[h][w].clipSize.y, n_texture::sprBlokenBLock[(blokenBlock_1[h][w].animeState * BLOCK_CHIP_W) + blokenBlock_1[h][w].animeTimer]);

				DrawRotaGraph3(
					blokenBlock_1[h][w].pos.x, blokenBlock_1[h][w].pos.y,
					BLOKEN_BLOCK_SIZE / 2, BLOKEN_BLOCK_SIZE / 2,
					blokenBlock_1[h][w].scale.x, blokenBlock_1[h][w].scale.y,
					blokenBlock_1[h][w].angle,
					n_texture::sprBlokenBLock[blokenBlock_1[h][w].animeState],
					true,
					blokenBlock_1[h][w].revFrag.x, blokenBlock_1[h][w].revFrag.y
				);

				//DeleteGraph(sprData);
			}
		}
	}
}


////-- �v���C���[ 2 --////�@
//--����������--//
void Block_2::init()
{
	correction = { 600,150 };

	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			platform_2[h][w] = 0;

			block_2[h][w].no = GetRand(4);
			block_2[h][w].pos.x = static_cast<float>(w * BLOCK_CHIP_SIZE + correction.x);
			block_2[h][w].pos.y = static_cast<float>(h * BLOCK_CHIP_SIZE + correction.y);
			block_2[h][w].existFrag = true;
			block_2[h][w].animeState = block_2[h][w].no;
		}
	}
	

}

//--�X�V����--//
void Block_2::update()
{
	blockManage();
	blokenBlockMove();

	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			platform_2[h][w] = block_2[h][w].no;
			block_2[h][w].animeState = block_2[h][w].no;
		}
	}

	//--�z��̍X�V--//
	if (arrNo_2.x != saveArryNo_2.x)
	{
		//�`��F�ύX
		int swap = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][arrNo_2.x].no = block_2[arrNo_2.y][saveArryNo_2.x].no;
		block_2[arrNo_2.y][saveArryNo_2.x].no = swap;

		//���̔z��̒l�̕ύX
		block_2[arrNo_2.y][arrNo_2.x].animeState = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][saveArryNo_2.x].animeState = block_2[arrNo_2.y][saveArryNo_2.x].no;
	}
	if (arrNo_2.y != saveArryNo_2.y)
	{
		//�`��F�ύX
		int swap = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][arrNo_2.x].no = block_2[saveArryNo_2.y][arrNo_2.x].no;
		block_2[saveArryNo_2.y][arrNo_2.x].no = swap;

		//���̔z��̒l�̕ύX
		block_2[arrNo_2.y][arrNo_2.x].animeState = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[saveArryNo_2.y][arrNo_2.x].animeState = block_2[saveArryNo_2.y][arrNo_2.x].no;
	}

}

//--�`�揈��--//
void Block_2::draw()
{
	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			if(block_2[h][w].existFrag)
			{
				DrawRotaGraph3(
					block_2[h][w].pos.x, block_2[h][w].pos.y,
					BLOCK_CHIP_SIZE / 2, BLOCK_CHIP_SIZE / 2,
					block_2[h][w].scale.x, block_2[h][w].scale.y,
					block_2[h][w].angle,
					n_texture::sprBlock[(block_2[h][w].animeState * BLOCK_CHIP_W) + block_2[h][w].animeTimer],
					true,
					block_2[h][w].revFrag.x, block_2[h][w].revFrag.y
				);
			}
		}
	}

#ifdef DEBUG_
	DrawFormatString(0, 40, GetColor(0, 255, 0), "arrNo_2 x : %d", arrNo_2.x);
	DrawFormatString(0, 60, GetColor(0, 255, 0), "arrNo_2 y : %d", arrNo_2.y);

	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			DrawFormatString((w * 20) + 800, (h * 20) + 100, GetColor(255, 255, 255), "%d", platform_2[h][w], 20);
		}
	}
#endif //DEBUG_
}

//--�u���b�N��������--//

//�S�̂̊Ǘ�
void Block_2::blockManage()
{
	uiCombo_2.setPlayerNo(Scene::TWO_PLAY); //���݂̃v���C���[�ԍ��ݒ�
	uiScore_2.setPlayerNo(Scene::TWO_PLAY); //���݂̃v���C���[�ԍ��ݒ�
	uiGauge_2.setPlayerNo(Scene::TWO_PLAY); //���݂̃v���C���[�ԍ��ݒ�
	uiCounter_1.calcFrag = false;	//�v�Z�����̏�����

	int eraseBlockPerOneLoop = 0;

	//Pad���͏���
	int padInput = GetJoypadInputState(DX_INPUT_PAD2);

	//X����
	if (padInput & (PAD_INPUT_C | PAD_INPUT_B | PAD_INPUT_A | PAD_INPUT_4))
	{
		if (keyTrg_2 && checkBlockWidth(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], LEFT) && arrNo_2.x != 0)
		{
			//TODO::�ύX
			UI::nowCombo_2++;
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_2()->init();
			Game::instance()->pressMachineManager_2()->add(&pressMachineMoveL_2, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>(700), static_cast<float>((CursorH_2::cursorCenterPos_2.y * 64) + 148) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", (CursorH_2::cursorCenterPos_2.y * 64) + 148);  //�v���X(������)
			Game::instance()->uiComboManager_2()->add(&uiCombo_2, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ SCREEN_WIDTH - 400, 40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
			uiCounter_1.addCounterBlock(&uiCounter_1, eraseBlockCount);
			uiCounter_1.calcFrag = true;
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, LEFT);  //�u���b�N�폜
			uiScore_2.score_2 += uiScore_2.calcScore(UI::nowCombo_2, eraseBlockCount, &UI::eraseBlockPow_2);  //Score���Z   
		}
		if (keyTrg_2 && checkBlockWidth(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], RIGHT) && arrNo_2.x != BLOCK_WIDTH - 1)
		{
			UI::nowCombo_2++;
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_2()->init();
			Game::instance()->pressMachineManager_2()->add(&pressMachineMoveR_2, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>(762), static_cast<float>((CursorH_2::cursorCenterPos_2.y * 64) + 148) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", (CursorH_2::cursorCenterPos_2.y * 64) + 148);  //�v���X(�E����)
			Game::instance()->uiComboManager_2()->add(&uiCombo_2, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ SCREEN_WIDTH - 400, 40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
			uiCounter_1.addCounterBlock(&uiCounter_1, eraseBlockCount);
			uiCounter_1.calcFrag = true;
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, RIGHT);
			uiScore_2.score_2 += uiScore_2.calcScore(UI::nowCombo_2, eraseBlockCount, &UI::eraseBlockPow_2);  //Score���Z
		}
		if (keyTrg_2 && checkBlockHeight(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], BOTTOM) && arrNo_2.y != BLOCK_HEIGHT - 1)
		{
			UI::nowCombo_2++;
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_2()->init();
			Game::instance()->pressMachineManager_2()->add(&pressMachineMoveB_2, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>((CursorH_2::cursorCenterPos_2.x * 64) + 602), static_cast<float>(311) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", 312);  //�v���X(������)
			Game::instance()->uiComboManager_2()->add(&uiCombo_2, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ SCREEN_WIDTH - 400, 40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
			uiCounter_1.addCounterBlock(&uiCounter_1, eraseBlockCount);
			uiCounter_1.calcFrag = true;
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, BOTTOM);
			uiScore_2.score_2 += uiScore_2.calcScore(UI::nowCombo_2, eraseBlockCount, &UI::eraseBlockPow_2);  //Score���Z
		}
		if (keyTrg_2&& checkBlockHeight(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], UP) && arrNo_2.y != 0)
		{
			UI::nowCombo_2++;
			eraseBlockPerOneLoop++;

			Game::instance()->uiComboManager_2()->init();
			Game::instance()->pressMachineManager_2()->add(&pressMachineMoveT_2, NO_ANIMATION, n_texture::sprPressMachine, TEXTURE, Vector2F{ static_cast<float>((CursorW_2::cursorCenterPos_2.x * 64) + 600), static_cast<float>(243) }, Vector2F{ PRESS_SIZE_W,PRESS_SIZE_H }, "./Data/Images/pless_machine.png", 244);  //�v���X(�ォ��)
			Game::instance()->uiComboManager_2()->add(&uiCombo_2, NO_ANIMATION, &n_font::fontYomogi, FONT, Vector2F{ SCREEN_WIDTH - 400, 40 }, Vector2F{ 64,64 }, "Nu ��������� �W��-��1");
			uiCounter_1.addCounterBlock(&uiCounter_1, eraseBlockCount);
			uiCounter_1.calcFrag = true;
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, UP);
			uiScore_2.score_2 += uiScore_2.calcScore(UI::nowCombo_2, eraseBlockCount, &UI::eraseBlockPow_2);  //Score���Z
		}
		keyTrg_2 = false;
		uiGauge_2.calcGauge(eraseBlockPerOneLoop, Scene::TWO_PLAY); //�t�B�[�o�[�Q�[�W�̑���
	
		if (uiCounter_1.calcFrag)
		{
			int counterArrNo_H = 0;	//�J�E���^�[�u���b�N�̔z��i�[�p�ϐ� (Height)

									//-- �J�E���^�[�u���b�N�������i�[����z��̍����̕������o��
			for (int h = 0; h < COUNTER_MAX_H; h++)
			{
				if (uiCounter_1.counter[h][0].existFrag)	continue;	//���݂��Ă���Ƃ�(�ՖʂɃu���b�N������Ƃ�)�͔�΂�

				counterArrNo_H = h;
				break;
			}

			bool center = false;
			if (arrNo_2.x == BOARD_CENTER && arrNo_2.y == BOARD_CENTER)	center = true;
			uiCounter_1.calcCounterBlockNum(&uiCounter_1, 150, counterArrNo_H, center);
		}
	}
	else
	{
		keyTrg_2 = true;
	}
}
void Block_2::blockClip(const int width, const int height, int* checkNo, e_Direction direction)
{
	//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		for (int w = 0; w < width; w++)
		{
			switch (block_2[height][w].state)
			{
			case 0:
				block_2[height][w].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_2[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_2[i][0], block_2[height][w].pos, i);
					break;
				}
			}
		}
	}

	//B�����͂��ꂽ��
	if (direction == RIGHT)
	{
		for (int w = BLOCK_WIDTH - 1; w > width; w--)
		{
			switch (block_2[height][w].state)
			{
			case 0:
				block_2[height][w].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_2[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_2[i][0], block_2[height][w].pos, i);
					break;
				}
			}
		}
	}
	//Y�����͂��ꂽ��
	if (direction == UP)
	{
		for (int h = 0; h < height; h++)
		{
			switch (block_2[h][width].state)
			{
			case 0:
				block_2[h][width].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_2[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_2[i][0], block_2[h][width].pos, i);
					break;
				}
			}
		}
	}

	//A�����͂��ꂽ��
	if (direction == BOTTOM)
	{
		for (int h = BLOCK_HEIGHT - 1; h > height; h--)
		{
			switch (block_2[h][width].state)
			{
			case 0:
				block_2[h][width].no = GetRand(4);
				break;
			}

			//BlokenBlock�̒ǉ�
			for (int i = 0; i < BOARD_CHIP_NUM; i++)
			{
				if (blokenBlock_2[i][0].existFrag == false)
				{
					serchSet(&blokenBlock_2[i][0], block_2[h][width].pos, i);
					break;
				}
			}
		}
	}

	const int saveNo = *checkNo;
	while (1)
	{
		*checkNo = GetRand(4);

		if (*checkNo != saveNo)	break;
	}

}

//�����ł��邩���� (��)  
// Chip�̉��AChip�̏c�AChip�̗v�f�ԍ��A����
bool Block_2::checkBlockWidth(const int width, const int height, const int checkNo, e_Direction direction)
{
	//��O�`�F�b�N
	if (direction == UP || direction == BOTTOM)
	{
		assert(!"���� direciton �̒l���Ԉ���Ă��܂�");
	}

	int saveNo = -1;

	eraseBlockCount = 0;	//�������u���b�N�̌��J�E���g�p

							//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		if (width > 1)
		{
			for (int w = 0; w < width; w++)
			{
				eraseBlockCount++;

				if (w > 0)
				{
					if (saveNo != platform_2[height][w])
					{
						eraseBlockCount = 0;
						return false;
					}
				}

				saveNo = platform_2[height][w];
			}
			eraseBlockCount = eraseBlockCount;
			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}

	}

	//B�����͂��ꂽ��
	if (direction == RIGHT)
	{
		if (width < BLOCK_WIDTH - 2)
		{
			for (int w = BLOCK_WIDTH - 1; w > width; w--)
			{
				eraseBlockCount++;

				if (w < BLOCK_WIDTH - 1)
				{
					if (saveNo != platform_2[height][w])
					{
						eraseBlockCount = 0;
						return false;
					}
				}
				eraseBlockCount = eraseBlockCount;;
				saveNo = platform_2[height][w];
			}
			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}

	}

	return false;
}

//�����ł��邩���� (�c)
// Chip�̉��AChip�̏c�AChip�̗v�f�ԍ��A����
bool Block_2::checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction)
{
	//��O�`�F�b�N
	if (direction == RIGHT || direction == LEFT)
	{
		assert(!"���� direciton �̒l���Ԉ���Ă��܂�");
	}

	int saveNo = -1;

	eraseBlockCount = 0;	//�������u���b�N�̌��J�E���g�p

							//Y�����͂��ꂽ��
	if (direction == UP)
	{
		if (height > 1)
		{
			for (int h = 0; h < height; h++)
			{
				eraseBlockCount++;

				if (h > 0)
				{
					if (saveNo != platform_2[h][width])
					{
						eraseBlockCount = 0;
						return false;
					}
				}
				eraseBlockCount = eraseBlockCount;
				saveNo = platform_2[h][width];
			}

			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}
	}

	//A�����͂��ꂽ��
	if (direction == BOTTOM)
	{
		if (height < BLOCK_HEIGHT - 2)
		{
			for (int h = BLOCK_HEIGHT - 1; h > height; h--)
			{
				eraseBlockCount++;

				if (h < BLOCK_HEIGHT - 1)
				{
					if (saveNo != platform_2[h][width])
					{
						eraseBlockCount = 0;
						return false;
					}
				}

				eraseBlockCount = eraseBlockCount;
				saveNo = platform_2[h][width];
			}
			return true;
		}
		else
		{
			eraseBlockCount = 0;
			return false;
		}
	}

	return false;
}

void Block_2::serchSet(OBJ2D* obj, Vector2F pos, const int no)
{
	for (int i = 0; i < BLOKEN_BLOCK_CHIP_NUM; i++)
	{
		blokenBlock_2[no][i].pos = pos;
		blokenBlock_2[no][i].animeState = i;
		blokenBlock_2[no][i].existFrag = true;
	}
}

////-- �j��u���b�N���� --////
void Block_2::blokenBlockMove()
{
	for (int h = 0; h < BOARD_CHIP_NUM; h++)
	{
		for (int w = 0; w < BLOKEN_BLOCK_CHIP_NUM; w++)
		{
			if (blokenBlock_2[h][w].existFrag)
			{
				switch (blokenBlock_2[h][w].state)
				{
					//-- �����ݒ� --//
				case 0:
					//-- �ǂ����̕����Ƀu���b�N���i�ނ����w�� --//
					blokenBlock_2[h][w].speed = 3;

					if (w % 2 == 0) blokenBlock_2[h][w].speed *= -1;	//�����Ȃ�speed���}�C�i�X��

																		//-- Block���オ�鍂����ݒ� --//
					blokenBlock_2[h][w].gravity = -20;

					blokenBlock_2[h][w].state++;
					break;

					//-- �X�V���� --//
				case 1:
					blokenBlock_2[h][w].gravity += 2;							//gravity
					blokenBlock_2[h][w].pos.x += blokenBlock_2[h][w].speed;	//position_x
					blokenBlock_2[h][w].pos.y += blokenBlock_2[h][w].gravity; //position_y
					blokenBlock_2[h][w].angle += ToRadian(15);				//angle

					if (blokenBlock_2[h][w].pos.y > SCREEN_HEIGHT + 50)
					{
						blokenBlock_2[h][w].state++;
					}
					break;

					//-- �I������ --//
				case 2:
					blokenBlock_2[h][w].existFrag = false;
					blokenBlock_2[h][w].state = 0;

					break;
				}
			}
		}
	}
}

void Block_2::drawBloken()
{
	for (int h = 0; h < BOARD_CHIP_NUM; h++)
	{
		for (int w = 0; w < BLOKEN_BLOCK_CHIP_NUM; w++)
		{
			if (blokenBlock_2[h][w].existFrag)
			{
				//int sprData = DerivationGraph(blokenBlock_1[h][w].clipOrigin.x, blokenBlock_1[h][w].clipOrigin.y, blokenBlock_1[h][w].clipSize.x, blokenBlock_1[h][w].clipSize.y, n_texture::sprBlokenBLock[(blokenBlock_1[h][w].animeState * BLOCK_CHIP_W) + blokenBlock_1[h][w].animeTimer]);

				DrawRotaGraph3(
					blokenBlock_2[h][w].pos.x, blokenBlock_2[h][w].pos.y,
					BLOKEN_BLOCK_SIZE / 2, BLOKEN_BLOCK_SIZE / 2,
					blokenBlock_2[h][w].scale.x, blokenBlock_2[h][w].scale.y,
					blokenBlock_2[h][w].angle,
					n_texture::sprBlokenBLock[blokenBlock_2[h][w].animeState],
					true,
					blokenBlock_2[h][w].revFrag.x, blokenBlock_2[h][w].revFrag.y
				);

				//DeleteGraph(sprData);
			}
		}
	}
}
