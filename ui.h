#pragma once

#define UI_GAUGE_SIZE_W (320)
#define UI_GAUGE_SIZE_H (50)
#define UI_CHIP_NUM		(8)
#define UI_CHIP_W		(4)
#define UI_CHIP_H		(2)

#define COUNTER_MAX_W				(7)
#define COUNTER_MAX_H				(100)
#define COUNTER_BLOCK_CHIP_NUM		(3)
#define COUNTER_BLOCK_CHIP_W		(3)
#define COUNTER_BLOCK_CHIP_H		(1)
#define COUNTER_BLOCK_CHIP_SIZE_W	(32)
#define COUNTER_BLOCK_CHIP_SIZE_H	(32)
#define COUNTER_BLOCK_SPACE			(40)	//�u���b�N��z�u����ʒu�̊Ԋu

class UI :public MoveAlg
{
private:
	int		 playerNo	= 0;		//���삵�Ă���v���C���[�̔ԍ�
	bool	 feverFrag	= false;	//�t�B�[�o�[�t���O(true : fever , false : Nomal)
	Vector2F move		= {};		//UI�̈ړ��l
protected:
	int addGauge		= 0;		//�t�B�[�o�[�Q�[�W�̑�����
	int feverCount		= 0;		//�t�B�[�o�[��

public:
	//�R���{��
	static int nowCombo_1;	//�v���C���[ 1	
	static int nowCombo_2;  //�v���C���[ 2

	//�X�R�A
	static int score_1;		//�v���C���[ 1	
	static int score_2;		//�v���C���[ 2

	//�u���b�N�̏��������̔{��
	static float eraseBlockPow_1;
	static float eraseBlockPow_2;

public :

	void moveTimer(OBJ2D* obj, Vector2F pos);
	void moveCombo(OBJ2D* obj);
	void moveScore(OBJ2D* obj);
	void moveGauge(OBJ2D* obj);
	void moveHp(OBJ2D* obj);
	void moveCounter(OBJ2D* obj);

	void setPlayerNo(int no) { playerNo = no; }		//���݂̃v���C���[�̔ԍ��擾(����ō��̃v���C���[�� 1�Ȃ̂�2�Ȃ̂��𒲂ׂ�)
	int	 getPlayerNo() { return playerNo; }

};

class UiTimer :public UI
{
private:
	Vector2F pos;

public:
	void move(OBJ2D* obj) override;

	//-- �Z�b�^�[ --//
	void setPosX(float pos) { this->pos.x = pos; }
	void setPosY(float pos) { this->pos.y = pos; }
	
};

class UiCombo :public UI
{
public:
	void move(OBJ2D* obj) override;

	//�f�X�g���N�^(�����o�ϐ��̏�����)
	~UiCombo()
	{ 
		nowCombo_1 = 0;
		nowCombo_2 = 0;
	};
};

class UiScore :public UI
{
public:
	void move(OBJ2D* obj) override;

	int calcScore(const int combo, const int blockNum,float* eraseBlockPow);	//SCORE�̌v�Z�@�@(1: ���݂̃R���{�� 2: �u���b�N�̏�������)

	//�f�X�g���N�^(�����o�ϐ��̏�����)
	~UiScore();
	/*~UiScore()
	{
		score_1					= 0;
		score_2					= 0;
		eraseBlockPow_1			= 0;
		eraseBlockPow_2			= 0;
	}*/
};

class UiGauge :public UI
{
public:
	void move(OBJ2D* obj) override;

	void calcGauge(const int eraseNum,const int playerNo);
};

class UiHp :public UI
{
public:
	void move(OBJ2D* obj) override;
};

extern UiTimer uiTimer_1;
extern UiTimer uiTimer_2;
extern UiCombo uiCombo_1;
extern UiCombo uiCombo_2;
extern UiScore uiScore_1;
extern UiScore uiScore_2;
extern UiGauge uiGauge_1;
extern UiGauge uiGauge_2;


class EraseUi :public EraseAlg
{
	void erase(OBJ2D* obj) override;
};

class UiManager :public OBJ2DManager
{

};


class UiCounter
{
private:
	int arrNo_H			= 0;	 //�z��̔ԍ��i�[�p(Height)
	int arrNo_W			= 0;	 //�z��̔ԍ��i�[�p(Width)
	int counterBlockNum = 0;	 //����ɑ���J�E���^�[�u���b�N�̌�
	int breakBlock_2	= 0;	 //2������
	int breakBlock_3	= 0;	 //3������
	int breakBlock_4	= 0;	 //4������

public:
	OBJ2D counter[COUNTER_MAX_H][COUNTER_MAX_W] = {};
	bool calcFrag = false; //�v�Z�������s�����̃t���O

public:
	void init();
	void update();
	void draw();

	void move(OBJ2D* obj);

	void calcCounterBlockNum(UiCounter* counter ,int posX ,int height, bool center);		//�J�E���^�[�u���b�N�̌��v�Z (1 : ���������� 2 : �J�[�\�����^�񒆂ɂ��邩)
	void addCounterBlock(UiCounter* counter,const int blockNum);							//��x�ɏ����ꂽ�u���b�N�̌��̒ǉ�(�R���{������Ȃ��ău���b�N�̐�)
	

	//-- �Q�b�^�[ --//
	int getArrNo_H() { return arrNo_H; }
	int getArrNo_W() { return arrNo_W; }

	//-- �Z�b�^�[ --//
	void setArrNo_H(int no) { arrNo_H = no; }
	void setArrNo_W(int no) { arrNo_W = no; }
};

extern UiCounter uiCounter_1;		//�J�E���^�[
extern UiCounter uiCounter_2;

