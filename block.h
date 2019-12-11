#pragma once

#define BLOCK_WIDTH			(5)
#define BLOCK_HEIGHT		(5)

#define BLOCK_CHIP_W		(9)
#define BLOCK_CHIP_H		(1)
#define BLOCK_CHIP_NUM		(9)
#define BLOCK_CHIP_SIZE		(64)

class Block 
{
	
private:	//--�����o�ϐ�--//
	OBJ2D block[BLOCK_HEIGHT][BLOCK_WIDTH];				//�u���b�N�̃f�[�^�i�[
	int   platform[BLOCK_HEIGHT][BLOCK_WIDTH] = {};		//���݂̃u���b�N�̔ԍ��i�[�p
	bool  keyTrg							  = false;	//�L�[�g���K�[	

	enum e_Direction
	{
		LEFT,
		RIGHT,
		UP,
		BOTTOM,
	};

public:
	static Vector2I arrNo;
	static Vector2I saveArryNo;
	
public:		//--�����o�֐�--//
	void init();		//������
	void update();		//�X�V
	void draw();		//�`��
	
	//--�u���b�N����--//
	void blockManage();																						//�S�̂̊Ǘ�
	void blockClip(const int width, const int height,int* checkNo, e_Direction direction);					//��������
	bool checkBlockWidth (const int width, const int height, const int checkNo, e_Direction direction);		//�u���b�N�������ł��邩���� (��)
	bool checkBlockHeight(const int width, const int height, const int checkNo, e_Direction direction);		//�u���b�N�������ł��邩���� (�c)
};
