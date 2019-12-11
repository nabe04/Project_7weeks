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

Vector2I Block::arrNo		= {};
Vector2I Block::saveArryNo	= {};

//--初期化処理--//
void Block::init()
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

//--更新処理--//
void Block::update()
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

	//--配列の更新--//
	if (arrNo.x != saveArryNo.x)
	{
		//描画色変更
		int swap								= block[arrNo.y][arrNo.x].no;
		block[arrNo.y][arrNo.x].no				= block[arrNo.y][saveArryNo.x].no;
		block[arrNo.y][saveArryNo.x].no			= swap;

		//元の配列の値の変更
		block[arrNo.y][arrNo.x].animeTimer		= block[arrNo.y][arrNo.x].no;
		block[arrNo.y][saveArryNo.x].animeTimer = block[arrNo.y][saveArryNo.x].no;
	}
	if (arrNo.y != saveArryNo.y)
	{
		//描画色変更
		int swap								= block[arrNo.y][arrNo.x].no;
		block[arrNo.y][arrNo.x].no				= block[saveArryNo.y][arrNo.x].no;
		block[saveArryNo.y][arrNo.x].no			= swap;

		//元の配列の値の変更
		block[arrNo.y][arrNo.x].animeTimer		= block[arrNo.y][arrNo.x].no;
		block[saveArryNo.y][arrNo.x].animeTimer = block[saveArryNo.y][arrNo.x].no;
	}
}

//--描画処理--//
void Block::draw()
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

//--ブロック除去処理--//

//全体の管理
void Block::blockManage()
{
	//Pad入力処理
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//X入力
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

void Block::blockClip(const int width, const int height,int* checkNo, e_Direction direction)
{
	//Xが入力されたら
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

	//Bが入力されたら
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
	//Yが入力されたら
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

	//Aが入力されたら
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

//除去できるか判定 (横)  
// Chipの横、Chipの縦、Chipの要素番号、向き
bool Block::checkBlockWidth(const int width, const int height, const int checkNo, e_Direction direction)
{
	//例外チェック
	if (direction == UP || direction == BOTTOM)
	{
		assert(!"引数 direciton の値が間違っています");
	}

	int saveNo = -1;

	//Xが入力されたら
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

	//Bが入力されたら
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

//除去できるか判定 (縦)
// Chipの横、Chipの縦、Chipの要素番号、向き
bool Block::checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction)
{
	//例外チェック
	if (direction == RIGHT || direction == LEFT)
	{
		assert(!"引数 direciton の値が間違っています");
	}

	int saveNo = -1;

	//Yが入力されたら
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

	//Aが入力されたら
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
