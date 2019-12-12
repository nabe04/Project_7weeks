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

			//�`��
			DrawRotaGraph3(
				pos.x, pos.y,
				texSize.x * 0.5f, texSize.y * 0.5f,
				scale.x, scale.y,
				angle,
				data[(animeState * chipWidth) + animeTimer],
				true,
				revFrag.x
				);

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

			//�`��
			DrawFormatStringToHandle(
				static_cast<int>(pos.x), static_cast<int>(pos.y),
				GetColor(color.r, color.g, color.b),
				*data,
				text,
				dispNum
				);

			//��Ԃ�߂�(���̏��������Ȃ��ƑS�̂ɕ������x���e�����邽��)
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(color.a));
		}
	}
}


//--OBJ2DManager�N���X--//

//������
void OBJ2DManager::init()
{
	//���X�g��OBJ2D�����ׂăN���A����
	objList.clear();
}

//���X�g�ւ̒ǉ�(1:OBJ2D�^�̃����o�|�C���^ 2:�`��p�Ɋi�[�����f�[�^ 3:OBJ��position)
OBJ2D* OBJ2DManager::add(MoveAlg* mvAlg,int* data, e_Category category, const Vector2F& pos, const Vector2F& size)
{
	OBJ2D obj;											//OBJ2D��錾����
	obj.mvAlg	 = mvAlg;								//mvAlg�Ɉ�����mvAlg����
	obj.pos		 = pos;									//pos�Ɉ�����pos����
	obj.texSize  = size;
	obj.size     = { size.x * 0.5f,size.y * 0.5f };		//size�Ɉ�����size�̔�������(����ȂǂɎg���Ƃ��Ɏg���₷�����邽��)
	obj.scale	 = Vector2F{ 1, 1 };					//�X�P�[���͓��{
	obj.color	 = Color4I{ 255,255,255,255 };			//�F�͌��F(�s�����x255 = �s�����xMax)
	obj.data	 = data;								//Data�i�[
	obj.category = category;							//��ޑI��(���̎�ނŕ`����@���ς��)

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
