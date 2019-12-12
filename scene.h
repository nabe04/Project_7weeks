#pragma once

//**********************//
//		Scene�Ǘ�		//
//**********************//

//--Scene�N���X--//
class Scene
{
	//--�����o�ϐ�--//
protected:
	
	int		state			= 0;			//���
	int		timer			= 0;			//�^�C�}�[
	int		select			= 0;			//�I��
	int		padInput		= 0;			//Pad����
	bool	keyTrg			= false;		//�L�[�g���K�[
	Scene*	nextScene		= nullptr;		//���̃V�[��

public:
	enum e_SelectGame
	{
		ONE_PLAY,
		TWO_PLAY,
	};

private:
	static e_SelectGame selectGame;
public:
	Scene* execute();	//���s����

	virtual void init()
	{
		//����������
		state		= 0;
		timer		= 0;
		nextScene	= nullptr;
	}
	virtual void uninit() {};	//�I������
	virtual void update() {};	//�X�V����
	virtual void draw()	  {};	//�`�揈��

	void changeScene(Scene* scene)		{ nextScene = scene; }			//�V�[���ύX����
	Scene* getScene() const				{ return nextScene; }			//nextScene�̃Q�b�^�[
	void setSelect(e_SelectGame select) { selectGame = select; }		//selectGame�̃Q�b�^�[
	e_SelectGame getSelect() const		{ return selectGame; }			//selectGame�̃Z�b�^�[
};

//**********************//
//		�V�[���Ǘ�		//
//**********************//

//--SceneManager�N���X--//
class SceneManager
{
public:
	void execute(Scene*);	//���s����
};