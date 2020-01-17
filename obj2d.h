#pragma once
#include <list>
#include <string>
#include "setup.h"
#include "algorithm.h"

using namespace n_setup;

//OBJ�̎�� 
const enum e_Category
{
	TEXTURE,	//�摜
	FONT,		//�t�H���g
};

//�摜�̌��� 
const enum e_Direction
{
	TATE,	//�c
	YOKO,	//��
};

//***********************//
//		OBJ2D�N���X		 //
//***********************//

//--OBJ2D�N���X--//
class OBJ2D
{
public:
	Vector2F 	pos			= {};					//�ʒu
	Vector2F	savePos		= {};					//�ʒu�̕ۑ�
	Vector2F	pivot		= {};					//�摜�̊�_
	Vector2F	scale		= {};					//�X�P�[��
	Vector2F	size		= {};					//������p�T�C�Y(�摜�̔����̃T�C�Y��ݒ�)
	Vector2F	texSize		= {};					//�摜�̃T�C�Y(DrawRoteGraph3�̑�3�C4�����Ŏg�p)
	Vector2I	arrNo		= {};					//�z��̗v�f�ԍ���ۑ�
	Vector2I    clipOrigin	= {};					//�摜�̐؂蔲��(��_)
	Vector2I	clipSize	= {};					//�摜�̐؂蔲���T�C�Y
	Vector2B	revFrag		= {};					//�摜�̔��]�t���O
	Color4I		color		= {};					//�`��F

	MoveAlg*	mvAlg		= nullptr;				//�ړ��A���S���Y��
	EraseAlg*	eraseAlg	= nullptr;				//�����A���S���Y��

	e_Category  category	= TEXTURE;
	e_Direction direction	= YOKO;

	int			state		= 0;					//�X�e�C�g
	int			state_2		= 0;					//�X�e�C�g(�\��)
	int			shakeState	= 0;					//�X�N���[���V�F�C�N�X�e�C�g
	int			timer		= 0;					//�^�C�}�[
	int			count		= 0;					//�J�E���g
	int			animeState	= 0;					//�A�j���[�V����State
	int			animeTimer	= 0;					//�A�j���[�V����Timer
	int			chipWidth	= 0;					//�A�j���[�V������������Chip�̐�(��)
	int			no			= 0;					//�ԍ�(��������̂Ƃ��Ɏg�p)
	int			jumpTimer	= 0;					//�������W�����v�̎���
	int			fontSize	= 0;					//�t�H���g�̑傫��
	int			fontThick	= 0;					//�t�H���g�̌���
	int			score		= 0;					//�X�R�A
	int*		data		= nullptr;				//�`�悷�邳���ɓ����Data
	float		speed		= 0;					//���x
	float		gravity		= 0;					//�d��
	float		angle		= 0;					//�p�x
	float		dispNum		= 0;					//�t�H�[�}�b�g�w��q�i�[�p
	float		maxVal		= 0;					//OBJ�����l�̍ő�l(�����Ɏg����悤��)
	bool		existFrag	= false;				//���݃t���O
	bool		grandFrag	= false;				//�n�ʃt���O
	bool		ladderFrag  = false;				//��q�t���O
	bool		wallFrag	= false;				//�ǃt���O
	bool		clipFrag	= false;				//�؂蔲���t���O
	bool		moveFrag	= false;				//�����t���O
	bool		copyFrag	= false;				//�R�s�[�t���O
	bool		shakeFrag	= false;				//�X�N���[���V�F�C�N�t���O
	char*		text		= nullptr;				//�t�H���g�g�p�̍ۂɕ\�����镶��
	char*		loadData	= nullptr;				//load�����Ƃ��̃t�@�C���Q�ƒl


public:
	OBJ2D();		//�R���X�g���N�^
	void move();	//�X�V
	void draw();	//�`��
	void reset();	//���Z�b�g

	void serchSet(OBJ2D* obj, Vector2F pos, Vector2F size, int no, const int maxVal);
	void setMoveFrag(OBJ2D* counter, bool moveFrag);
	void screenShake(OBJ2D* obj, float shakeValue, e_Direction direction);
};

void moveOBJData(OBJ2D* origin, OBJ2D* copy); //�z��f�[�^��������炷

//--OBJ2DManager�N���X--//
class OBJ2DManager
{
protected:
	std::list<OBJ2D> objList;	//���X�g
public:
	~OBJ2DManager();			//�f�X�g���N�^

	void init();				//������
	void update();				//�X�V
	void draw();				//�`��
	
	OBJ2D* add(MoveAlg* mvAlg,int clipWidth, int* data, e_Category category, const n_setup::Vector2F& pos = n_setup::Vector2F{ 0, 0 }, const n_setup::Vector2F& size = n_setup::Vector2F{0,0},char* loadName = nullptr,float maxVal = 0,bool turnFrag = false, e_Direction direction = YOKO);	//objList�ɐV����OBJ2D��ǉ�����
	std::list<OBJ2D>* getList() { return &objList; }							//objList���擾����
};



