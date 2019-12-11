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

////--Block 1�N���X--////

Vector2I Block_1::arrNo		= {};
Vector2I Block_1::saveArryNo	= {};

//--����������--//
void Block_1::init()
{
	for (int h = 0; h < BLOCK_HEIGHT; h++)
	{
		for (int w = 0; w < BLOCK_WIDTH; w++)
		{
			platform[h][w]			= 0;

			block[h][w].no			= GetRand(4);
			block[h][w].pos.x		= w * BLOCK_CHIP_SIZE + 350;
			block[h][w].pos.y		= h * BLOCK_CHIP_SIZE + 150;
			block[h][w].existFrag	= true;
			block[h][w].animeTimer	= block[h][w].no;
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
			platform[h][w]			= block[h][w].no;
			block[h][w].animeTimer	= block[h][w].no;
		}
	}

	//--�z��̍X�V--//
	if (arrNo.x != saveArryNo.x)
	{
		//�`��F�ύX
		int swap								= block[arrNo.y][arrNo.x].no;
		block[arrNo.y][arrNo.x].no				= block[arrNo.y][saveArryNo.x].no;
		block[arrNo.y][saveArryNo.x].no			= swap;

		//���̔z��̒l�̕ύX
		block[arrNo.y][arrNo.x].animeTimer		= block[arrNo.y][arrNo.x].no;
		block[arrNo.y][saveArryNo.x].animeTimer = block[arrNo.y][saveArryNo.x].no;
	}
	if (arrNo.y != saveArryNo.y)
	{
		//�`��F�ύX
		int swap								= block[arrNo.y][arrNo.x].no;
		block[arrNo.y][arrNo.x].no				= block[saveArryNo.y][arrNo.x].no;
		block[saveArryNo.y][arrNo.x].no			= swap;

		//���̔z��̒l�̕ύX
		block[arrNo.y][arrNo.x].animeTimer		= block[arrNo.y][arrNo.x].no;
		block[saveArryNo.y][arrNo.x].animeTimer = block[saveArryNo.y][arrNo.x].no;
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
				block[h][w].pos.x, block[h][w].pos.y,
				BLOCK_CHIP_SIZE * 0.5f, BLOCK_CHIP_SIZE * 0.5f,
				block[h][w].scale.x, block[h][w].scale.y,
				block[h][w].angle,
				n_texture::sprBlock[(block[h][w].animeState * BLOCK_CHIP_W) + block[h][w].animeTimer],
				true,
				block[h][w].revFrag.x,block[h][w].revFrag.y
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
			DrawFormatString((w * 20) + 800, (h * 20) + 100, GetColor(255, 255, 255), "%d", platform[h][w],20);
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
		if (keyTrg && checkBlockWidth(arrNo.x,arrNo.y,platform[arrNo.y][arrNo.x],LEFT) && arrNo.x != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, LEFT);
		}
		if (keyTrg && checkBlockWidth(arrNo.x, arrNo.y, platform[arrNo.y][arrNo.x], RIGHT) && arrNo.x != BLOCK_WIDTH - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, RIGHT);
		}
		if (keyTrg && checkBlockHeight(arrNo.x, arrNo.y, platform[arrNo.y][arrNo.x], BOTTOM) && arrNo.y != BLOCK_HEIGHT - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, BOTTOM);
		}
		if (keyTrg&& checkBlockHeight(arrNo.x, arrNo.y, platform[arrNo.y][arrNo.x], UP) && arrNo.y != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, UP);
		}
		keyTrg = false;
	}
	else
	{
		keyTrg = true;
	}

}

void Block_1::blockClip(const int width, const int height,int* checkNo, e_Direction direction)
{
	//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		for (int w = 0; w < width; w++)
		{
			switch (block[height][w].state)
			{
			case 0:
				block[height][w].no = GetRand(4);
				break;
			}
		}
	}

	//B�����͂��ꂽ��
	if (direction == RIGHT)
	{
		for (int w = BLOCK_WIDTH - 1; w > width; w--)
		{
			switch (block[height][w].state)
			{
			case 0:
				block[height][w].no = GetRand(4);
				break;
			}
		}
	}
	//Y�����͂��ꂽ��
	if (direction == UP)
	{
		for (int h = 0; h < height; h++)
		{
			switch (block[h][width].state)
			{
			case 0:
				block[h][width].no = GetRand(4);
				break;
			}
		}
	}

	//A�����͂��ꂽ��
	if (direction == BOTTOM)
	{
		for (int h = BLOCK_HEIGHT - 1; h > height; h--)
		{
			switch (block[h][width].state)
			{
			case 0:
				block[h][width].no = GetRand(4);
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
					if (saveNo != platform[height][w])	return false;
				}

				saveNo = platform[height][w];
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
					if (saveNo != platform[height][w])	return false;
				}

				saveNo = platform[height][w];
			}
			return true;
		}
		else
		{
			return false;
		}
			
	}
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
					if (saveNo != platform[h][width])	return false;
				}

				saveNo = platform[h][width];
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
					if (saveNo != platform[h][width])	return false;
				}

				saveNo = platform[h][width];
			}
			return true;
		}
		else
		{
			return false;
		}
			
	}
}


////--Block 2�N���X--////

Vector2I Block_2::arrNo;
Vector2I Block_2::saveArryNo;

//�S�̂̊Ǘ�
void Block_2::blockManage()
{
	//Pad���͏���
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//X����
	if (padInput & (PAD_INPUT_C | PAD_INPUT_B | PAD_INPUT_A | PAD_INPUT_4))
	{
		if (keyTrg && checkBlockWidth(arrNo.x, arrNo.y, platform[arrNo.y][arrNo.x], LEFT) && arrNo.x != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, LEFT);
		}
		if (keyTrg && checkBlockWidth(arrNo.x, arrNo.y, platform[arrNo.y][arrNo.x], RIGHT) && arrNo.x != BLOCK_WIDTH - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, RIGHT);
		}
		if (keyTrg && checkBlockHeight(arrNo.x, arrNo.y, platform[arrNo.y][arrNo.x], BOTTOM) && arrNo.y != BLOCK_HEIGHT - 1)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, BOTTOM);
		}
		if (keyTrg&& checkBlockHeight(arrNo.x, arrNo.y, platform[arrNo.y][arrNo.x], UP) && arrNo.y != 0)
		{
			UI::nowCombo++;
			Game::instance()->uiComboManager()->init();
			Game::instance()->uiComboManager()->add(&uiCombo, &n_font::fontTimer, FONT, Vector2F{ 0,0 }, Vector2F{ 64,64 });
			blockClip(arrNo.x, arrNo.y, &block[arrNo.y][arrNo.x].no, UP);
		}
		keyTrg = false;
	}
	else
	{
		keyTrg = true;
	}

}

void Block_2::blockClip(const int width, const int height, int* checkNo, e_Direction direction)
{
	//X�����͂��ꂽ��
	if (direction == LEFT)
	{
		for (int w = 0; w < width; w++)
		{
			switch (block[height][w].state)
			{
			case 0:
				block[height][w].no = GetRand(4);
				break;
			}
		}
	}

	//B�����͂��ꂽ��
	if (direction == RIGHT)
	{
		for (int w = BLOCK_WIDTH - 1; w > width; w--)
		{
			switch (block[height][w].state)
			{
			case 0:
				block[height][w].no = GetRand(4);
				break;
			}
		}
	}
	//Y�����͂��ꂽ��
	if (direction == UP)
	{
		for (int h = 0; h < height; h++)
		{
			switch (block[h][width].state)
			{
			case 0:
				block[h][width].no = GetRand(4);
				break;
			}
		}
	}

	//A�����͂��ꂽ��
	if (direction == BOTTOM)
	{
		for (int h = BLOCK_HEIGHT - 1; h > height; h--)
		{
			switch (block[h][width].state)
			{
			case 0:
				block[h][width].no = GetRand(4);
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
					if (saveNo != platform[height][w])	return false;
				}

				saveNo = platform[height][w];
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
					if (saveNo != platform[height][w])	return false;
				}

				saveNo = platform[height][w];
			}
			return true;
		}
		else
		{
			return false;
		}

	}
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
					if (saveNo != platform[h][width])	return false;
				}

				saveNo = platform[h][width];
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
					if (saveNo != platform[h][width])	return false;
				}

				saveNo = platform[h][width];
			}
			return true;
		}
		else
		{
			return false;
		}

	}
}
