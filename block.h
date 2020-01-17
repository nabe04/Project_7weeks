#pragma once

#define BLOCK_WIDTH				(5)
#define BLOCK_HEIGHT			(5)

#define BLOCK_CHIP_NUM			(5)
#define BLOCK_CHIP_W			(1)
#define BLOCK_CHIP_H			(5)
#define BLOCK_CHIP_SIZE			(64)

#define BLOKEN_BLOCK_CHIP_NUM	(7)
#define BLOKEN_BLOCK_CHIP_W		(1)
#define BLOKEN_BLOCK_CHIP_H		(7)
#define BLOKEN_BLOCK_SIZE		(64)

#define BOARD_CHIP_NUM			(100)
#define BOARD_SIZE				(320)	//�u���b�N�S���̃T�C�Y
#define BOARD_CENTER			(2)		//�Ֆʂ̒��S


//-- �v���C���[ 1 --//
class Block_1 
{
	//struct Data
	//{
	//	OBJ2D block[BLOCK_HEIGHT][BLOCK_WIDTH];				//�u���b�N�̃f�[�^�i�[
	//	int   platform[BLOCK_HEIGHT][BLOCK_WIDTH] = {};		//���݂̃u���b�N�̔ԍ��i�[�p
	//	bool  keyTrg = false;	//�L�[�g���K�[	
	//	OBJ2D* getBlockData(int x, int y) { return &block[y][x]; }
	//};
private:	//--�����o�ϐ�--//
	
	OBJ2D		block_1[BLOCK_HEIGHT][BLOCK_WIDTH]						= {};		//�u���b�N�̃f�[�^�i�[
	OBJ2D		blokenBlock_1[BOARD_CHIP_NUM][BLOKEN_BLOCK_CHIP_NUM]	= {};		//*�u���b�N���󂳂ꂽ�Ƃ��̃f�[�^�i�[
	Vector2F	correction												= {};		//�␳�l
	int			platform_1[BLOCK_HEIGHT][BLOCK_WIDTH]					= {};		//���݂̃u���b�N�̔ԍ��i�[�p
	int			eraseBlockCount											= 0;		//�������u���b�N�̌�
	bool		keyTrg_1												= false;	//�L�[�g���K�[	

	enum e_BlockDirection
	{
		LEFT,
		RIGHT,
		UP,
		BOTTOM,
	};

public:
	//--�ԍ��ۑ�--//
	static Vector2I arrNo;			//��l
	static Vector2I saveArryNo;
	
public:		//--�����o�֐�--//
	void init();		//������
	void update();		//�X�V
	void draw();		//�`��
	
	//-- �u���b�N���� --//
	void blockManage();																						//�S�̂̊Ǘ�
	void blockClip(const int width, const int height,int* checkNo, e_BlockDirection direction);					//��������
	bool checkBlockWidth (const int width, const int height, const int checkNo, e_BlockDirection direction);		//�u���b�N�������ł��邩���� (��)
	bool checkBlockHeight(const int width, const int height, const int checkNo, e_BlockDirection direction);		//�u���b�N�������ł��邩���� (�c)
	void serchSet(OBJ2D* obj, Vector2F pos,const int no);														//BlokenBlock�̃f�[�^�i�[�p

	//-- �j��u���b�N���� --//
	void blokenBlockMove();		//BlokenBlock��Move����(update�ɉ�����)
	void drawBloken();			//BlokenBlock�̕`��(draw�ɉ�����)
};

////-- �v���C���[ 2�p --////
class Block_2
{
	//struct Data
	//{
	//	OBJ2D block[BLOCK_HEIGHT][BLOCK_WIDTH];				//�u���b�N�̃f�[�^�i�[
	//	int   platform[BLOCK_HEIGHT][BLOCK_WIDTH] = {};		//���݂̃u���b�N�̔ԍ��i�[�p
	//	bool  keyTrg = false;	//�L�[�g���K�[	
	//	OBJ2D* getBlockData(int x, int y) { return &block[y][x]; }
	//};
private:	//--�����o�ϐ�--//

	OBJ2D		block_2[BLOCK_HEIGHT][BLOCK_WIDTH]						= {};				//�u���b�N�̃f�[�^�i�[
	OBJ2D		blokenBlock_2[BOARD_CHIP_NUM][BLOKEN_BLOCK_CHIP_NUM]	= {};				//�u���b�N���󂳂ꂽ�Ƃ��̃f�[�^�i�[
	Vector2F	correction												= {};				//�␳�l
	int			platform_2[BLOCK_HEIGHT][BLOCK_WIDTH]					= {};				//���݂̃u���b�N�̔ԍ��i�[�p
	int			eraseBlockCount											= 0;				//�������u���b�N�̐�
	bool		keyTrg_2												= false;			//�L�[�g���K�[	

	enum e_BlockDirection
	{
		LEFT,
		RIGHT,
		UP,
		BOTTOM,
	};

public:
	//--�ԍ��ۑ�--//
	static Vector2I arrNo_2;			//��l
	static Vector2I saveArryNo_2;

public:		//--�����o�֐�--//
	void init();		//������
	void update();		//�X�V
	void draw();		//�`��

	//--�u���b�N����--//
	void blockManage();																						//�S�̂̊Ǘ�
	void blockClip(const int width, const int height, int* checkNo, e_BlockDirection direction);					//��������
	bool checkBlockWidth(const int width, const int height, const int checkNo, e_BlockDirection direction);		//�u���b�N�������ł��邩���� (��)
	bool checkBlockHeight(const int width, const int height, const int checkNo, e_BlockDirection direction);		//�u���b�N�������ł��邩���� (�c)
	void serchSet(OBJ2D* obj, Vector2F pos, const int no);													//BlokenBlock�̃f�[�^�i�[�p

	//-- �j��u���b�N���� --//
	void blokenBlockMove();		//BlokenBlock��Move����(update�ɉ�����)
	void drawBloken();			//BlokenBlock�̕`��(draw�ɉ�����)
};

