#pragma once

#define PRESS_EFFECT_CHIP_NUM (4)
#define PRESS_EFFECT_CHIP_W   (4)
#define PRESS_EFFECT_CHIP_H   (1)
#define PRESS_EFFECT_SIZE_W   (80)
#define PRESS_EFFECT_SIZE_H   (192)

#define COUNTER_EFFECT_CHIP_NUM (3)
#define COUNTER_EFFECT_CHIP_W	(3)
#define COUNTER_EFFECT_CHIP_H	(1)
#define COUNTER_EFFECT_SIZE		(32)

class Effect :public MoveAlg
{
	void move(OBJ2D* obj) override {};
};

class PressEffect :public Effect
{
public:
	void moveR(OBJ2D* obj);
	void moveT(OBJ2D* obj);
	void moveL(OBJ2D* obj);
	void moveB(OBJ2D* obj);
};

class PressEffectMoveR :public PressEffect
{
	void move(OBJ2D* obj)override;
};
class PressEffectMoveT :public PressEffect
{
	void move(OBJ2D* obj)override;
};
class PressEffectMoveL :public PressEffect
{
	void move(OBJ2D* obj)override;
};
class PressEffectMoveB :public PressEffect
{
	void move(OBJ2D* obj)override;
};

extern PressEffectMoveR pressEffectMoveR;
extern PressEffectMoveT pressEffectMoveT;
extern PressEffectMoveL pressEffectMoveL;
extern PressEffectMoveB pressEffectMoveB;

class EraseEffect :public EraseAlg
{
	void erase(OBJ2D* obj) override;
};

class EffectManager :public OBJ2DManager
{
private:

public:

};

