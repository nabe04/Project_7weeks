#include <algorithm>
#include "generic.h"
#include "obj2d.h"
#include "load_texture.h"
#include "bg.h"
#include "bg_maps.h"


//--������--//
void BG::init()
{
	pos  = {};
	data = nullptr;

	for (int h = 0; h < CHIP_HEIGHT; h++)
	{
		for (int w = 0; w < CHIP_WIDTH; w++)
		{
			back[h][w]		= ori_bg[h][w];
			terrain[h][w]	= ori_terrain[h][w];
		} 
	}
}

//--�X�V--//
void BG :: update()
{
	
}

//--�`��(�w�i)--//
void BG::drawBack()
{
	draw(n_texture::storeBG, back);
}

//--�`��(�n�`)--//
void BG::drawTerrain()
{
	draw(n_texture::storeTerrain, terrain);
}


//--BG�ATerrain���ʂ̕`��֐�--//
void  BG::draw(int* data, int chipNo[CHIP_HEIGHT][CHIP_WIDTH])
{
	for (int h = 0; h < CHIP_HEIGHT; h++)
	{
		for (int w = 0; w < CHIP_WIDTH; w++)
		{
			int posX   = static_cast<int>(pos.x) + (w * CHIP_SIZE);			//position X
			int posY   = static_cast<int>(pos.y) + (h * CHIP_SIZE);			//position Y
			int hSizeX = static_cast<int>(size.x * 0.5f);	//Harf Size X
			int hSizeY = static_cast<int>(size.y * 0.5f);	//Harf Size Y
			int no = chipNo[h][w];

			if (no == -1)	continue;	//-1(�f�[�^�������ĂȂ���Ώ������΂�)

			DrawRotaGraph3(
				posX, posY,
				hSizeX, hSizeY,
				1, 1,
				0,
				data[no],
				true,
				false
				);
		}
	}
}

//--�����蔻��--//

//Chip�̗v�f�ԍ����擾
int BG::getData(const int map[CHIP_HEIGHT][CHIP_WIDTH], const float x, const float y)
{
	int data;
	int divX = static_cast<int>(x) / CHIP_SIZE;	//x�����̃C���f�b�N�X
	int divY = static_cast<int>(y) / CHIP_SIZE;	//y�����̃C���f�b�N�X

	data = map[divY][divX];
	return data;
}

//  �������Ɍ����āA�w�肵�����W���ǂł��邩�ǂ���
bool BG::isHitDown(const float x, const float y, bool hashigo)
{
	int chipNo = getData(terrain, x, y);	//MapChip�̔ԍ��擾

	switch (chipNo)				//�n�`�̑������擾����
	{
	case NONE_BLOCK:  return false;
	case 0:
	case 1:			  return true; 
	case BREAK_BLOCK: return true;				//����(BREAK_BLOCK�͉����瓖��������邽��)
	case PUSH_BLOCK : return true;				//����(PUSH_BLOCKA�͉����牟���Ɠ�������)
	case UPPER_BLOCK: return isUpperQuater(y);	// �㑤�S���̂P���n�`�ŁA��S���̂P�Ɋ܂܂�邩
	case LADDER:

		//�͂����~��n�ߎ��ɉ������̕ǂւ̓����蔻����������
		if (hashigo == true)
			break;

		//�͂����ɏ���悤�ɂ��Ă���
		return isUpperQuater(y);

		break;
	}
	return false;
}

//�w�肵��y���W���A�}�b�v�`�b�v�̏㑤4����1�ɂ��邩�ǂ�����Ԃ�
bool BG::isUpperQuater(const float y)
{
	if (static_cast<int>(y) % CHIP_SIZE < CHIP_SIZE)
		return true;

	return false;
}

//  �S�ĕǂł���u���b�N���ǂ���
bool BG::isHitAll(const float x, const float y)
{
	int chipNo = getData(terrain, x, y);
	switch (chipNo)
	{
	case NONE_BLOCK:	return false;
	case 0:
	case 1: 
	case BREAK_BLOCK:
	case PUSH_BLOCK:	return true;
	}

	return false;
}

//�������ւ̂����蔻��
bool BG::isFloor(const float x, const float y,  float width, bool hashigo)
{
	for (; width > 0; width -= CHIP_SIZE)
	{
		const float left  = x - width;
		const float right = x + width;

		//�G���A�`�F�b�N
		if (left < 0)				continue;
		if (right >= SCREEN_WIDTH)	continue;

		if (isHitDown(left , y, hashigo))  return true;	//���[����
		if (isHitDown(right, y, hashigo)) return true;	//�E�[����
	}

	return isHitDown(x, y, hashigo);					//�Ō�ɐ^�񒆂Ŕ���
}

//  �������ɂ������Ă���ꍇ�̕␳����
void BG::mapCorrectionDown(OBJ2D* obj)
{
	float y			= obj->pivot.y;				//�킩��₷����������
	int intY		= static_cast<int>(y);
	y				= static_cast<float>(intY - intY % CHIP_SIZE);
	obj->pivot.y	= y;
	obj->gravity	= (std::min)(obj->gravity, 0.0f);
}

//  �V��ɂ������Ă��邩
bool BG::isCeiling(const float x, const float y, float width)
{
	for (; width > 0; width -= CHIP_SIZE)
	{
		const float left  = x - width;
		const float right = x + width;

		//�G���A�`�F�b�N
		if (left < 0)				continue;
		if (right >= SCREEN_WIDTH)	continue;

		if (isHitAll(left, y))	return true;	//���[����
		if (isHitAll(right, y)) return true;	//�E�[����
	}
	return isHitAll(x, y);						//�Ō�ɐ^�񒆂Ŕ���
}

//  ������␳����
void BG::mapCorrecionUp(OBJ2D* obj)
{
	float y			= obj->pivot.y - obj->texSize.y;
	int intY		= static_cast<int>(y);
	y				= static_cast<float>(intY + (CHIP_SIZE - (intY % CHIP_SIZE)));
	obj->pivot.y	= y + obj->texSize.y;
	if (obj->gravity < 0)
		obj->gravity = 0.0f;
}

//  �������ɕǂɂ������Ă��邩�ǂ���
bool BG::isWall(const float x, const float y, float height)
{
	for (; height > 0; height -= CHIP_SIZE)
	{
		if (isHitAll(x, y - height)) return true;
	}

	//-10���Ă���̂͂��̂܂܂���pivot��player�̃T�C�Y�������ɂ��肤�܂����肪���Ȃ�����
	return isHitAll(x, y - 10);
}

//  �E�����␳����
void BG::mapCorrectionRight(OBJ2D* obj)
{
	float x		 = obj->pivot.x + obj->size.x;
	x			-= fmodf(x, static_cast<float>(CHIP_SIZE));
	obj->pivot.x = x - obj->size.x;
	obj->speed	 = 0.0f;
}

//  �������␳����
void BG::mapCorrectionLeft(OBJ2D* obj)
{
	float x		 = obj->pivot.x - obj->size.x;
	x			+= CHIP_SIZE - fmodf(x, static_cast<float>(CHIP_SIZE));
	obj->pivot.x = x + obj->size.x;
	obj->speed	 = 0.0f;
}

//�w�肳�ꂽChip�̃A�Z�b�g�ύX
void BG::chipChange(const float x, const float y)
{
	//�S�Ă�NONE_BLOCK�ŏ�����
	TR_ATTR attr = NONE_BLOCK;

	switch (getData(terrain,x,y))
	{
	case ALL_BLOCK:		attr = BREAK_BLOCK;  break;
	}

	int divX = static_cast<int>(x) / CHIP_SIZE;	//x�����̃C���f�b�N�X
	int divY = static_cast<int>(y) / CHIP_SIZE;	//y�����̃C���f�b�N�X

	if(attr != NONE_BLOCK)	terrain[divY][divX] = attr;
}

float BG::calcResistance(const OBJ2D* obj, float speed)
{
	return -1;
}