#include <assert.h>
#include "generic.h"
#include "scene.h"

////--Scene�N���X--////

////--�����o�ϐ�--////
Scene::e_SelectGame Scene::selectGame;

////--���s--//
Scene* Scene::execute()
{
	//����������
	init();

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//��ʂ̏�����
		ClearDrawScreen();

		//�X�V����
		update();

		//�`�揈��
		draw();

		//����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		//�I���`�F�b�N
		if (nextScene) break;
	}

	//�I������
	uninit();

	return nextScene;	//���̃V�[����Ԃ�
}


//--SceneManager�N���X--//
//���s
void SceneManager::execute(Scene* scene)
{
	ChangeWindowMode(true);										//�E�B���h�E���[�h�ݒ�(true : �E�B���h�E���[�h , false : �t���X�N���[��)
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);				//��ʂ̃T�C�Y�ݒ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);

	SetBackgroundColor(0, 0, 0);

	if (DxLib_Init() == -1)		//DX���C�u��������������
	{
		assert(!"DxLib�������G���[�ł�!");			//�G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//���C�����[�v
	while (scene)
	{
		scene = scene->execute();
	}

	//DX���C�u�����g�p�̏I��
	DxLib_End();
}