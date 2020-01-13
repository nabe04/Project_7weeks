#include "generic.h"
#include "util.h"
#include "obj2d.h"
#include "actor.h"
#include "algorithm.h"
#include "cursor.h"
#include "effect.h"
#include "MyImgui.h"
#include "player.h"
#include "scene.h"
#include "game.h"

PressEffect pressEffect;

void PressEffect::move(OBJ2D* obj)
{
	obj->existFrag = true;

}