#pragma once

//******************************************************************************
//
//
//      �^�C�g���V�[��
//
//
//******************************************************************************

////--Title�N���X--////

class Title :public Scene
{
private:
	static Title	instance_;
	bool			keyTrg = false;

	int titleText;	//�t�H���g�i�[�p

public:
	static Title* instance() { return &instance_; }

	void init()		override;
	void update()	override;
	void draw()		override;

};