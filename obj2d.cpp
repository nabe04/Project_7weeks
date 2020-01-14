#include "generic.h"
#include "obj2d.h"
#include "algorithm.h"
#include "load_texture.h"

//�R���X�g���N�^
OBJ2D::OBJ2D()
{
	scale = Vector2F{1,1};				//�X�P�[����0�̂Ƃ������\������Ȃ�����
	color = Color4I{ 255,255,255,255 };	//�s�����x��0�̂Ƃ������\������Ȃ�����
}


//�ړ�
void OBJ2D::move()
{
	if (mvAlg)		mvAlg->move(this);			//�ړ��A���S���Y�������݂���΁Amove���\�b�h���Ă�
	if (eraseAlg)	eraseAlg->erase(this);		//�����A���S���Y�������݂���΁Aerase���\�b�h���Ă�
}

//�`��
void OBJ2D::draw()
{
	//--�e�N�X�`���`��--//
	if (this->data != nullptr && category == TEXTURE)
	{
		if (existFrag)
		{
			//�������x�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);
			SetDrawBright(color.r, color.g, color.b);
			
			int sprData = DerivationGraph(clipOrigin.x, clipOrigin.y, clipSize.x, clipSize.y, data[(animeState * chipWidth) + animeTimer]);
			
			//�`��
			DrawRotaGraph3(
				pos.x, pos.y,
				texSize.x * 0.5f, texSize.y * 0.5f,
				scale.x, scale.y,
				angle,
				sprData,
				true,
				revFrag.x
				);
			
			DeleteGraph(sprData);

			//��Ԃ�߂�(���̏��������Ȃ��ƑS�̂ɕ������x���e�����邽��)
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, color.a);

#ifdef DEBUG_
			//�f�o�b�N�p������`��
			DrawFormatString(pos.x, pos.y, GetColor(255, 0, 0), "�E", 3);
			DrawFormatString(pivot.x, pivot.y, GetColor(0, 255, 0), "�E", 3);

			if (data == n_texture::sprCursorW)
			{
				DrawFormatString(0, 20, GetColor(0, 255, 0), "arrNo.y : %d", arrNo.y, 3);
			}
			if (data == n_texture::sprCursorH)
			{
				DrawFormatString(0, 0, GetColor(0, 255, 0), "arrNo.x : %d", arrNo.x, 3);
			}
				
#endif // DEBUG_

			}
	}

	//--�t�H���g�`��--//
	if (this->data != nullptr && category == FONT)
	{
		if (existFrag)
		{
			//�������x�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);

			int fontData = CreateFontToHandle(loadData, fontSize, fontThick, DX_FONTTYPE_NORMAL);

			//�`��
			DrawFormatStringToHandle(
				static_cast<int>(pos.x), static_cast<int>(pos.y),
				GetColor(color.r, color.g, color.b),
				fontData,
				text,
				dispNum
				);

			DeleteFontToHandle(fontData);

			//��Ԃ�߂�(���̏��������Ȃ��ƑS�̂ɕ������x���e�����邽��)
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(color.a));
		}
	}
}

void OBJ2D::reset()
{
	pos			= {};					//�ʒu
	savePos		= {};
	pivot		= {};					//�摜�̊�_
	scale		= {1,1};					//�X�P�[��
	size		= {};					//������p�T�C�Y(�摜�̔����̃T�C�Y��ݒ�)
	texSize		= {};					//�摜�̃T�C�Y(DrawRoteGraph3�̑�3�C4�����Ŏg�p)
	arrNo		= {};					//�z��̗v�f�ԍ���ۑ�
	clipOrigin	= {};					//�摜�̐؂蔲��(��_)
	clipSize	= {};					//�摜�̐؂蔲���T�C�Y
	revFrag		= {};					//�摜�̔��]�t���O
	color		= {255,255,255,255};					//�`��F

	mvAlg		= nullptr;				//�ړ��A���S���Y��
	eraseAlg	= nullptr;				//�����A���S���Y��

	category;

	state		= 0;					//�X�e�C�g
	timer		= 0;					//�^�C�}�[
	animeState	= 0;					//�A�j���[�V����State
	animeTimer	= 0;					//�A�j���[�V����Timer
	chipWidth	= 0;					//�A�j���[�V������������Chip�̐�(��)
	no			= 0;					//�ԍ�(��������̂Ƃ��Ɏg�p)
	jumpTimer	= 0;					//�������W�����v�̎���
	fontSize	= 0;					//�t�H���g�̑傫��
	fontThick	= 0;					//�t�H���g�̌���
	score		= 0;					//�X�R�A
	data		= nullptr;				//�`�悷�邳���ɓ����Data
	speed		= 0;					//���x
	gravity		= 0;					//�d��
	angle		= 0;					//�p�x
	dispNum		= 0;					//�t�H�[�}�b�g�w��q�i�[�p
	existFrag	= false;				//���݃t���O
	grandFrag	= false;				//�n�ʃt���O
	ladderFrag	= false;				//��q�t���O
	wallFrag	= false;				//�ǃt���O
	clipFrag	= false;				//�؂蔲���t���O
	moveFrag	= false;
	copyFrag	= false;
	text		= nullptr;				//�t�H���g�g�p�̍ۂɕ\�����镶��
	loadData	= nullptr;				//load�����Ƃ��̃t�@�C���Q�ƒl
}

void OBJ2D:: serchSet(OBJ2D* obj, Vector2F pos, Vector2F size, int no)
{
	obj->reset();

	obj->pos		= pos;								//Position
	obj->size		= { size.x / 2,size.y / 2 };		//����p�T�C�Y
	obj->texSize	= size;								//�e�N�X�`���{���̃T�C�Y
	obj->no			= no;								//�ԍ�
	obj->existFrag	= true;								//���݃t���O
}

void OBJ2D::setMoveFrag(OBJ2D* obj, bool moveFrag)
{
	if (obj->existFrag)
	{
		obj->moveFrag = moveFrag;
	}
}

void moveOBJData(OBJ2D* origin, OBJ2D* copy)
{
	*origin = *copy;
}

//--OBJ2DManager�N���X--//

//������
void OBJ2DManager::init()
{
	//���X�g��OBJ2D�����ׂăN���A����
	objList.clear();
}

//���X�g�ւ̒ǉ�(1:OBJ2D�^�̃����o�|�C���^ 2:�`��p�Ɋi�[�����f�[�^ 3:OBJ��position)
OBJ2D* OBJ2DManager::add(MoveAlg* mvAlg, int clipWidth,int* data, e_Category category, const Vector2F& pos, const Vector2F& size, char* loadData, float maxVal, bool turnFrag, e_Direction direction)
{
	OBJ2D obj;								//OBJ2D��錾����
	obj.mvAlg		= mvAlg;																	//mvAlg�Ɉ�����mvAlg����
	obj.pos			= pos;																		//pos�Ɉ�����pos����
	obj.texSize		= size;
	obj.size		= { size.x * 0.5f,size.y * 0.5f };											//size�Ɉ�����size�̔�������(����ȂǂɎg���Ƃ��Ɏg���₷�����邽��)
	obj.scale		= Vector2F{ 1, 1 };															//�X�P�[���͓��{
	obj.color		= Color4I{ 255,255,255,255 };												//�F�͌��F(�s�����x255 = �s�����xMax)
	obj.data		= data;																		//Data�i�[
	obj.category	= category;																	//��ޑI��(���̎�ނŕ`����@���ς��)
	obj.clipSize	= { static_cast<int>(size.x),static_cast<int>(size.y) };					//�͂��߂͑S�̂�؂蔲���悤�ɂ���(�S�̂��\�������)
	obj.loadData	= loadData;																	//�摜�̃p�X
	obj.maxVal		= maxVal;																	//�ő�l(�Ȃɂ��łł���悤��)
	obj.revFrag.x	= turnFrag;																	//�摜�̔��]�t���O
	obj.direction	= direction;
	obj.chipWidth	= clipWidth;

	objList.push_back(obj);								//���X�g��obj��ǉ�����
	return &(*objList.rbegin());						//���ǉ�����obj�̃A�h���X��Ԃ�(�����Ŏg����悤��)
}

//�X�V
void OBJ2DManager::update()
{
	//�ړ�
	for (auto& it : objList)		//objList�̂��ׂĂ̗v�f�����[�v���Ait�Ƃ������O�Ŋe�v�f�ɃA�N�Z�X
	{
		it.move();					//it��move���\�b�h���Ă�
	}

	//��m�[�h�̍폜
	auto it = objList.begin();
	while (it != objList.end())
	{
		if (it->mvAlg)
		{
			it++;
		}
		else
		{
			it = objList.erase(it);
		}
	}
}

//�`��
void OBJ2DManager::draw()
{
	for (auto& it : objList)		//objList�̑S�Ă̗v�f�����[�v���Ait�Ƃ������O�Ŋe�v�f�ɃA�N�Z�X
	{
		it.draw();					//it��draw���\�b�h���Ă�
	}
}


//�f�X�g���N�^
OBJ2DManager::~OBJ2DManager()
{
	//���X�g��OBJ2D��S�ăN���A����
	objList.clear();
}
