#pragma once

#ifdef USE_IMGUI
	#include "imgui.h"
	#include "imgui_impl_dxlib.h"

using namespace n_setup;

	struct GuiParam
	{
		 int	  no;
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
		static bool im_cursorOpen;
		GuiParam im_uiTimer		= {};
		GuiParam im_uiScore_1	= {1};
		GuiParam im_uiScore_2	= {2};
		GuiParam im_cursor		= {};
		
	public:
		void changeUiTimer();
		void changeUiScore();
		void changeColor(GuiParam* param);
		void uiPlatform();
		void cursorPlatform();
	};

	extern MyImgui im_Ui;
#endif // USE_IMGUI


