//******************************************************************************
//
//
//      �^�C�g��
//
//
//******************************************************************************

#include "generic.h"
#include "obj2d.h"
#include "player.h"
#include "scene.h"
#include "title.h"
#include "game.h"

////--�ϐ�--////
Title Title::instance_;

////--����������--////
void Title::init()
{
	Scene::init();			//���N���X��init���Ă�

	setSelect(ONE_PLAY);	//�Q�[���̏��

	//�t�H���g�ǉ�
	titleText  = CreateFontToHandle("Nu ��������� �W��-��1", 50, 3, DX_FONTTYPE_NORMAL);
}

////--�X�V����--////
void Title::update()
{
	char key[KEY_MAX];
	GetHitKeyStateAll(key);

	//Pad���͏���
	padInput = GetJoypadInputState(DX_INPUT_PAD1);

	switch (state)
	{
	case 0:
		//--�����ݒ�--//
		timer = 0;			//�^�C�}�[��������
		state++;			//�����������̏I��

		/*fallthrough*/

	case 1:
		//--�ʏ펞�̏���--//

		timer++;			//Title�S�̂̃^�C�}�[

		//START
		if (padInput & PAD_INPUT_R)
		{
			if (keyTrg)
			{
				keyTrg = false;
				changeScene(Game::instance());
				if (select == 0)  setSelect(ONE_PLAY);
				if (select == 1)  setSelect(TOW_PLAY);
			}
		}
		//��
		else if (padInput & PAD_INPUT_DOWN)
		{
			if (keyTrg && select == 0)
			{
				keyTrg = false;
				select = 1;
			}
		}
		//��
		else if (padInput & PAD_INPUT_UP)
		{
			if (keyTrg && select == 1)
			{
				keyTrg = false;
				select = 0;
			}
		}
		else
		{
			keyTrg = true;
		}
		break;
	}
}

////--�`�揈��--////
void Title::draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255),       "Title",        100);
	DrawFormatString(  0,  10, GetColor(255, 255, 255), "Select : %d",select, 100);
}
