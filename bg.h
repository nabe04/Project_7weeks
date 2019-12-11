#pragma once

//***********************************************************
//
//						BG
//
//***********************************************************

////--�萔--////

//--�}�b�v�`�b�v--//
#define CHIP_WIDTH			(32)
#define CHIP_HEIGHT			(17)
#define CHIP_SIZE			(32)

//--BG--//
#define BG_CHIP_NUM			(16)
#define BG_CHIP_W			(8)
#define BG_CHIP_H			(2)

//--Terrain--//
#define TERRAIN_CHIP_NUM	(32)
#define TERRAIN_CHIP_W		(8)
#define TERRAIN_CHIP_H		(4)

#include "setup.h"
#include "obj2d.h"
////--BG�N���X--////

class BG
{
//--�����o�ϐ�--//
private:
	n_setup::Vector2F pos	= {};		//�ʒu
	n_setup::Vector2I size  = {};		//�傫��
	int* data				= nullptr;	//�i�[����Chip�f�[�^
	
	int back[CHIP_HEIGHT][CHIP_WIDTH]		= {};	//�w�i
	int terrain[CHIP_HEIGHT][CHIP_WIDTH]	= {};	//�n�`

public:
	//�n�`(Terrain)�̑���
	//--Chip�̒萔�錾--//
	enum TR_ATTR
	{
		NONE_BLOCK	= -1,	//�����Ȃ��u���b�N
		ALL_BLOCK   = 1,	//���肾������u���b�N
		BREAK_BLOCK = 2,	//�󂹂�u���b�N
		PUSH_BLOCK	= 6,	//������u���b�N
		WATER		= 7,	//��
		UPPER_BLOCK = 9,	//�������������肪����u���b�N
		LADDER		= 16	//�͂���,
	};

//--�����o�֐�--//
private:
	void draw(int* data, int chipNo[CHIP_HEIGHT][CHIP_WIDTH]);	// BG�ATerrain���ʂ̕`��֐�

	//--�����蔻��--//
	bool isHitDown(const float x, const float y, bool hashigo);	//������
	bool isHitAll(const float x, const float y);				//�S��(�Ō�̃`�F�b�N�Ɏg�p)
	bool isUpperQuater(const float y);							//�w�肵��y���W���A�}�b�v�`�b�v�̏㑤4����1�ɂ��邩�ǂ���

public:
	BG() {};				//�R���X�g���N�^

	void init();			//������
	void update();			//�X�V
	void drawBack();		//�`��(�w�i)
	void drawTerrain();		//�`��(�n�`)

	//--�����蔻��--//
	//������
	bool isFloor(const float x, const float y,  float width, bool hashigo = (false));		//���ɂ߂荞��ł邩
	void mapCorrectionDown(OBJ2D* obj);														//�������␳����

	//�����
	bool isCeiling(const float x, const float y, float width);								//�V��ɓ������Ă邩
	void mapCorrecionUp(OBJ2D* obj);														//������␳����

	//������
	bool isWall(const float x, const float y, float height);								//�������ɂ߂荞��ł邩
	void mapCorrectionRight(OBJ2D* obj);													//�E�����␳����
	void mapCorrectionLeft(OBJ2D* obj);														//�������␳����
			
	//--�f�[�^�擾--//
	int  getData(const int map[CHIP_HEIGHT][CHIP_WIDTH], const float x, const float y);	//�w�肵�����W�̃}�b�v�`�b�v�̎�ނ��擾����

	//--Chip�̕ω�--//

	//Chip�̐F�ύX
	void chipChange(const float x, const float y);

	//Chip��������
	void chipPush();

	//--��R--//
	float calcResistance(const OBJ2D* obj, float speed);
};
