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

//***********************//
//		OBJ2D�N���X		 //
//***********************//

//--OBJ2D�N���X--//
class OBJ2D
{
public:
	Vector2F 	pos			= {};					//�ʒu
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

	e_Category  category;

	int			state		= 0;					//�X�e�C�g
	int			timer		= 0;					//�^�C�}�[
	int			animeState	= 0;					//�A�j���[�V����State
	int			animeTimer	= 0;					//�A�j���[�V����Timer
	int			chipWidth	= 0;					//�A�j���[�V������������Chip�̐�(��)
	int			no			= 0;					//�ԍ�(��������̂Ƃ��Ɏg�p)
	int			jumpTimer	= 0;					//�������W�����v�̎���
	int			fontSize	= 0;					//�t�H���g�̑傫��
	int			fontThick	= 0;					//�t�H���g�̌���
	int*		data		= nullptr;				//�`�悷�邳���ɓ����Data
	float		speed		= 0;					//���x
	float		gravity		= 0;					//�d��
	float		angle		= 0;					//�p�x
	float		dispNum		= 0;					//�t�H�[�}�b�g�w��q�i�[�p
	bool		existFrag	= false;				//���݃t���O
	bool		grandFrag	= false;				//�n�ʃt���O
	bool		ladderFrag  = false;				//��q�t���O
	bool		wallFrag	= false;				//�ǃt���O
	bool		clipFrag	= false;				//�؂蔲���t���O
	char*		text		= nullptr;				//�t�H���g�g�p�̍ۂɕ\�����镶��
	char*		loadData	= nullptr;				//load�����Ƃ��̃t�@�C���Q�ƒl

public:
	OBJ2D();		//�R���X�g���N�^
	void move();	//�X�V
	void draw();	//�`��
};

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

	OBJ2D* add(MoveAlg* mvAlg, int* data, e_Category category, const n_setup::Vector2F& pos = n_setup::Vector2F{ 0, 0 }, const n_setup::Vector2F& size = n_setup::Vector2F{0,0},char* loadName = nullptr);	//objList�ɐV����OBJ2D��ǉ�����
	std::list<OBJ2D>* getList() { return &objList; }							//objList���擾����
};



