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

////--Block クラス--////

Vector2I Block_1::arrNo			= {};	//一人目
Vector2I Block_1::saveArryNo	= {};
Vector2I Block_2::arrNo_2		= {};	//二人目
Vector2I Block_2::saveArryNo_2	= {};

////-- プレイヤー 1 --////　
//--初期化処理--//
void Block_1::init()
{
	if (Game::playerNum == Scene::ONE_PLAY)
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
				block_1[h][w].animeTimer	= block_1[h][w].no;
			}
		}
	}

	if (Game::playerNum == Scene::TWO_PLAY)
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
				block_1[h][w].animeTimer = block_1[h][w].no;
			}
		}
	}
}

//--更新処理--//
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

	//--配列の更新--//
	if (arrNo.x != saveArryNo.x)
	{
		//描画色変更
		int swap									= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][arrNo.x].no				= block_1[arrNo.y][saveArryNo.x].no;
		block_1[arrNo.y][saveArryNo.x].no			= swap;

		//元の配列の値の変更
		block_1[arrNo.y][arrNo.x].animeTimer		= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][saveArryNo.x].animeTimer	= block_1[arrNo.y][saveArryNo.x].no;
	}
	if (arrNo.y != saveArryNo.y)
	{
		//描画色変更
		int swap									= block_1[arrNo.y][arrNo.x].no;
		block_1[arrNo.y][arrNo.x].no				= block_1[saveArryNo.y][arrNo.x].no;
		block_1[saveArryNo.y][arrNo.x].no			= swap;

		//元の配列の値の変更
		block_1[arrNo.y][arrNo.x].animeTimer		= block_1[arrNo.y][arrNo.x].no;
		block_1[saveArryNo.y][arrNo.x].animeTimer	= block_1[saveArryNo.y][arrNo.x].no;
	}

}

//--描画処理--//
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

//--ブロック除去処理--//

//全体の管理
void Block_1::blockManage()
{
	//Pad入力処理
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	//X入力
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
	//Xが入力されたら
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

	//Bが入力されたら
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
	//Yが入力されたら
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

	//Aが入力されたら
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

//除去できるか判定 (横)  
// Chipの横、Chipの縦、Chipの要素番号、向き
bool Block_1::checkBlockWidth(const int width, const int height, const int checkNo, e_Direction direction)
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

	//Bが入力されたら
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

//除去できるか判定 (縦)
// Chipの横、Chipの縦、Chipの要素番号、向き
bool Block_1::checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction)
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

	//Aが入力されたら
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


////-- プレイヤー 2 --////　
//--初期化処理--//
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
			block_2[h][w].animeTimer = block_2[h][w].no;
		}
	}
	

}

//--更新処理--//
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

	//--配列の更新--//
	if (arrNo_2.x != saveArryNo_2.x)
	{
		//描画色変更
		int swap = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][arrNo_2.x].no = block_2[arrNo_2.y][saveArryNo_2.x].no;
		block_2[arrNo_2.y][saveArryNo_2.x].no = swap;

		//元の配列の値の変更
		block_2[arrNo_2.y][arrNo_2.x].animeTimer = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][saveArryNo_2.x].animeTimer = block_2[arrNo_2.y][saveArryNo_2.x].no;
	}
	if (arrNo_2.y != saveArryNo_2.y)
	{
		//描画色変更
		int swap = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[arrNo_2.y][arrNo_2.x].no = block_2[saveArryNo_2.y][arrNo_2.x].no;
		block_2[saveArryNo_2.y][arrNo_2.x].no = swap;

		//元の配列の値の変更
		block_2[arrNo_2.y][arrNo_2.x].animeTimer = block_2[arrNo_2.y][arrNo_2.x].no;
		block_2[saveArryNo_2.y][arrNo_2.x].animeTimer = block_2[saveArryNo_2.y][arrNo_2.x].no;
	}

}

//--描画処理--//
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

//--ブロック除去処理--//

//全体の管理
void Block_2::blockManage()
{
	//Pad入力処理
	int padInput = GetJoypadInputState(DX_INPUT_PAD2);

	//X入力
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
	//Xが入力されたら
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

	//Bが入力されたら
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
	//Yが入力されたら
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

	//Aが入力されたら
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

//除去できるか判定 (横)  
// Chipの横、Chipの縦、Chipの要素番号、向き
bool Block_2::checkBlockWidth(const int width, const int height, const int checkNo, e_Direction direction)
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

	//Bが入力されたら
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

//除去できるか判定 (縦)
// Chipの横、Chipの縦、Chipの要素番号、向き
bool Block_2::checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction)
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

	//Aが入力されたら
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

