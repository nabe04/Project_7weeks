#pragma once

#define PRESS_EFFECT_CHIP_NUM (4)
#define PRESS_EFFECT_CHIP_W   (4)
#define PRESS_EFFECT_CHIP_H   (1)
#define PRESS_EFFECT_SIZE_W   (80)
#define PRESS_EFFECT_SIZE_H   (192)

class Effect :public MoveAlg
{
	virtual void move(OBJ2D* obj) override {};
};

class PressEffect :public Effect
{
	void move(OBJ2D* obj) override;
};

extern PressEffect pressEffect;

class EraseEffect :public EraseAlg
{
	void erase(OBJ2D* obj) override;
};

class EffectManager :public OBJ2DManager
{
private:

public:

};

