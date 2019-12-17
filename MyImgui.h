#pragma once

#ifdef USE_IMGUI
	#include "imgui.h"
	#include "imgui_impl_dxlib.h"

using namespace n_setup;

	struct GuiParam
	{
		 Vector2F fParam;
		 Vector2I iParam;
		 float	  size;
		 float	  thick;
		 float	  iColor[4];
	};

	class MyImgui
	{
	public:
		static bool im_uiOpen;
		GuiParam im_uiTimer = {};
		GuiParam im_uiScore = {};
		
	public:
		void changeUiTimer();
		void changeUiScore();
		void chageColor(GuiParam* param);
		void uiPlatform();
	};

	extern MyImgui im_Ui;
#endif // USE_IMGUI


