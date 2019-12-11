#pragma once

//******************************************************************************
//
//
//      タイトルシーン
//
//
//******************************************************************************

////--Titleクラス--////

class Title :public Scene
{
private:
	static Title	instance_;
	bool			keyTrg = false;

	int titleText;	//フォント格納用

public:
	static Title* instance() { return &instance_; }

	void init()		override;
	void update()	override;
	void draw()		override;

};