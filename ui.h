#pragma once

class UI :public MoveAlg
{
public:
	static int nowCombo;

public :
	void moveTimer(OBJ2D* obj);
	void moveCombo(OBJ2D* obj);
};

class UiTimer :public UI
{
	void move(OBJ2D* obj) override;
};

class UiCombo :public UI
{
	void move(OBJ2D* obj) override;
};

extern UiTimer uiTimer;
extern UiCombo uiCombo;

class EraseUi :public EraseAlg
{
	void erase(OBJ2D* obj) override;
};

class UiManager :public OBJ2DManager
{

};
