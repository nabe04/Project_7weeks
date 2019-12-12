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
	if (Game::playerNum == Scene::ONE_PLAY)
	{
		for (int h = 0; h < BLOCK_HEIGHT; h++)
		{
			for (int w = 0; w < BLOCK_WIDTH; w++)
			{
				platform_1[h][w]			= 0;

				block_1[h][w].no			= GetRand(4);
				block_1[h][w].pos.x			= static_cast<float>(w * BLOCK_CHIP_SIZE + 350);
				block_1[h][w].pos.y			= static_cast<float>(h * BLOCK_CHIP_SIZE + 150);
				block_1[h][w].existFrag		= true;
				block_1[h][w].animeTimer	= block_1[h][w].no;
			}
		}
	}

	if (Game::playerNum == Scene::TWO_PLAY)
	{
		for (int h = 0; h < BLOCK_HEIGHT; h++)
		{
			for (int w = 0; w < BLOCK_WIDTH; w++)
			{
				platform_1[h][w] = 0;

				block_1[h][w].no = GetRand(4);
				block_1[h][w].pos.x = static_cast<float>(w * BLOCK_CHIP_SIZE);
				block_1[h][w].pos.y = static_cast<float>(h * BLOCK_CHIP_SIZE + 150);
				block_1[h][w].existFrag = true;
				block_1[h][w].animeTimer = block_1[h][w].no;
			}
		}
	}
}

//--�X�V����--//
void Block_1::update()
{
	blockManage();

	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			platform_1[h][w]			= block_1[h][w].no;
			block_1[h][w].animeTimer	= block_1[h][w].no;
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
		block_1[arrNo.y][arrNo.x].animeTimer		= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][saveArryNo.x].animeTimer	= block_1[arrNo.y][saveArryNo.x].no;
	}
	if (arrNo.y != saveArryNo.y)
	{
		//�`��F�ύX
		int swap									= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][arrNo.x].no				= block_1[saveArryNo.y][arrNo.x].no;
		block_1[saveArryNo.y][arrNo.x].no			= swap;

		//���̔z��̒l�̕ύX
		block_1[arrNo.y][arrNo.x].animeTimer		= block_1[arrNo.y][arrNo.x].no;
		block_1[saveArryNo.y][arrNo.x].animeTimer	= block_1[saveArryNo.y][arrNo.x].no;
	}

}

//--�`�揈��--//
void Block_1::draw()
{
	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			DrawRotaGraph3(
				block_1[h][w].pos.x, block_1[h][w].pos.y,
				BLOCK_CHIP_SIZE / 2, BLOCK_CHIP_SIZE / 2,
				block_1[h][w].scale.x, block_1[h][w].scale.y,
				block_1[h][w].angle,
				n_texture::sprBlock[(block_1[h][w].animeState * BLOCK_CHIP_W) + block_1[h][w].animeTimer],
				true,
				block_1[h][w].revFrag.x,block_1[h][w].revFrag.y
				);
		}
	}

#ifdef DEBUG_
	DrawFormatString(0, 40, GetColor(0, 255, 0), "arrNo x : %d", arrNo.x);
	DrawFormatString(0, 60, GetColor(0, 255, 0), "arrNo y : %d", arrNo.y);

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
	//Pad���͏���
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//X����
	if (padInput & (PAD_INPUT_C | PAD_INPUT_B | PAD_INPUT_A | PAD_INPUT_4))
	{
		if (keyTrg_1 && checkBlockWidth(arrNo.x,arrNo.y,platform_1[arrNo.y][arrNo.x],LEFT) && arrNo.x != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, LEFT);
		}
		if (keyTrg_1 && checkBlockWidth(arrNo.x, arrNo.y, platform_1[arrNo.y][arrNo.x], RIGHT) && arrNo.x != BLOCK_WIDTH - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, RIGHT);
		}
		if (keyTrg_1 && checkBlockHeight(arrNo.x, arrNo.y, platform_1[arrNo.y][arrNo.x], BOTTOM) && arrNo.y != BLOCK_HEIGHT - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, BOTTOM);
		}
		if (keyTrg_1&& checkBlockHeight(arrNo.x, arrNo.y, platform_1[arrNo.y][arrNo.x], UP) && arrNo.y != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block_1[arrNo.y][arrNo.x].no, UP);
		}
		keyTrg_1 = false;
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

	//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		if (width > 1)
		{
			for (int w = 0; w < width; w++)
			{
				if (w > 0)
				{
					if (saveNo != platform_1[height][w])	return false;
				}

				saveNo = platform_1[height][w];
			}

			return true;
		}
		else
		{
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
				if (w < BLOCK_WIDTH - 1)
				{
					if (saveNo != platform_1[height][w])	return false;
				}

				saveNo = platform_1[height][w];
			}
			return true;
		}
		else
		{
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

	//Y�����͂��ꂽ��
	if (direction == UP)
	{
		if (height > 1)
		{
			for (int h = 0; h < height; h++)
			{
				if (h > 0)
				{
					if (saveNo != platform_1[h][width])	return false;
				}

				saveNo = platform_1[h][width];
			}

			return true;
		}
		else
		{
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
				if (h < BLOCK_HEIGHT - 1)
				{
					if (saveNo != platform_1[h][width])	return false;
				}

				saveNo = platform_1[h][width];
			}
			return true;
		}
		else
		{
			return false;
		}
			
	}

	return false;
}


////-- �v���C���[ 2 --////�@
//--����������--//
void Block_2::init()
{
	
	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			platform_2[h][w] = 0;

			block_2[h][w].no = GetRand(4);
			block_2[h][w].pos.x = static_cast<float>(w * BLOCK_CHIP_SIZE + 450);
			block_2[h][w].pos.y = static_cast<float>(h * BLOCK_CHIP_SIZE + 150);
			block_2[h][w].existFrag = true;
			block_2[h][w].animeTimer = block_2[h][w].no;
		}
	}
	

}

//--�X�V����--//
void Block_2::update()
{
	blockManage();

	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			platform_2[h][w] = block_2[h][w].no;
			block_2[h][w].animeTimer = block_2[h][w].no;
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
		block_2[arrNo_2.y][arrNo_2.x].animeTimer = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][saveArryNo_2.x].animeTimer = block_2[arrNo_2.y][saveArryNo_2.x].no;
	}
	if (arrNo_2.y != saveArryNo_2.y)
	{
		//�`��F�ύX
		int swap = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][arrNo_2.x].no = block_2[saveArryNo_2.y][arrNo_2.x].no;
		block_2[saveArryNo_2.y][arrNo_2.x].no = swap;

		//���̔z��̒l�̕ύX
		block_2[arrNo_2.y][arrNo_2.x].animeTimer = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[saveArryNo_2.y][arrNo_2.x].animeTimer = block_2[saveArryNo_2.y][arrNo_2.x].no;
	}

}

//--�`�揈��--//
void Block_2::draw()
{
	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
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
	//Pad���͏���
	int padInput = GetJoypadInputState(DX_INPUT_PAD2);

	//X����
	if (padInput & (PAD_INPUT_C | PAD_INPUT_B | PAD_INPUT_A | PAD_INPUT_4))
	{
		if (keyTrg_2 && checkBlockWidth(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], LEFT) && arrNo_2.x != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, LEFT);
		}
		if (keyTrg_2 && checkBlockWidth(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], RIGHT) && arrNo_2.x != BLOCK_WIDTH - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, RIGHT);
		}
		if (keyTrg_2 && checkBlockHeight(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], BOTTOM) && arrNo_2.y != BLOCK_HEIGHT - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, BOTTOM);
		}
		if (keyTrg_2&& checkBlockHeight(arrNo_2.x, arrNo_2.y, platform_2[arrNo_2.y][arrNo_2.x], UP) && arrNo_2.y != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo_2.x, arrNo_2.y, &block_2[arrNo_2.y][arrNo_2.x].no, UP);
		}
		keyTrg_2 = false;
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

	//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		if (width > 1)
		{
			for (int w = 0; w < width; w++)
			{
				if (w > 0)
				{
					if (saveNo != platform_2[height][w])	return false;
				}

				saveNo = platform_2[height][w];
			}

			return true;
		}
		else
		{
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
				if (w < BLOCK_WIDTH - 1)
				{
					if (saveNo != platform_2[height][w])	return false;
				}

				saveNo = platform_2[height][w];
			}
			return true;
		}
		else
		{
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

	//Y�����͂��ꂽ��
	if (direction == UP)
	{
		if (height > 1)
		{
			for (int h = 0; h < height; h++)
			{
				if (h > 0)
				{
					if (saveNo != platform_2[h][width])	return false;
				}

				saveNo = platform_2[h][width];
			}

			return true;
		}
		else
		{
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
				if (h < BLOCK_HEIGHT - 1)
				{
					if (saveNo != platform_2[h][width])	return false;
				}

				saveNo = platform_2[h][width];
			}
			return true;
		}
		else
		{
			return false;
		}

	}

	return false;
}

