#include "setup.h"
#include "MyImgui.h"

#ifdef USE_IMGUI
	
	bool MyImgui::im_uiOpen = true;
		
	MyImgui im_Ui;

	void MyImgui::changeUiTimer()
	{
		if (ImGui::TreeNode("Timer"))
		{
			ImGui::SliderFloat("Timer_x", &im_uiTimer.fParam.x, 0.0f, SCREEN_WIDTH);
			ImGui::SliderFloat("Timer_y", &im_uiTimer.fParam.y, 0.0f, SCREEN_HEIGHT);

			chageColor(&im_uiTimer);

			ImGui::TreePop();
		}	
	}

	void MyImgui::changeUiScore()
	{
		if (ImGui::TreeNode("Score"))
		{
			ImGui::SliderFloat("Score_x", &im_uiScore.fParam.x, 0.0f, SCREEN_WIDTH);
			ImGui::SliderFloat("Score_y", &im_uiScore.fParam.y, 0.0f, SCREEN_HEIGHT);
			ImGui::SliderFloat("Size", &im_uiScore.size, 0.0f, 200.0f);
			ImGui::SliderFloat("Thick", &im_uiScore.thick, 0.0f, 50.0f);
			chageColor(&im_uiScore);

			ImGui::TreePop();
		}
	}

	void MyImgui::chageColor(GuiParam* param)
	{
		static bool my_tool_active;
	
		static float my_color[4] = {0.0f,0.0f,0.0f,100};
		// Edit a color (stored as ~4 floats)
		ImGui::ColorEdit4("Color", my_color);

		// Plot some values
		const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
		ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		//êFÇÃílÇë„ì¸
		for (int i = 0; i < 4;i++)
		{
			static_cast<float>(param->iColor[i]) = static_cast<int>(my_color[i] * 255.0f);
			int a[4];
			a[i] = static_cast<int>(my_color[i] * 255.0f);
		}

		
	}

	void MyImgui::uiPlatform()
	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::Begin("UI", &im_uiOpen);

		changeUiTimer();
		changeUiScore();

		ImGui::End();
		ImGui::PopStyleColor();
	}
#endif // USE_IMGUI

