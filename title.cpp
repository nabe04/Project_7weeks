//******************************************************************************
//
//
//      �^�C�g��
//
//
//******************************************************************************

#include "imgui.h"
#include "imgui_impl_dxlib.h"

#include "generic.h"
#include "obj2d.h"
#include "player.h"
#include "scene.h"
#include "title.h"
#include "game.h"

////--�ϐ�--////
Title Title::instance_;

////--����������--////
void Title::init()
{
	Scene::init();			//���N���X��init���Ă�

	setSelect(ONE_PLAY);	//�Q�[���̏��

	//�t�H���g�ǉ�
	titleText  = CreateFontToHandle("Nu ��������� �W��-��1", 50, 3, DX_FONTTYPE_NORMAL);
}

////--�X�V����--////
void Title::update()
{
	char key[KEY_MAX];
	GetHitKeyStateAll(key);

	//Pad���͏���
	padInput = GetJoypadInputState(DX_INPUT_PAD1);

	switch (state)
	{
	case 0:
		//--�����ݒ�--//
		timer = 0;			//�^�C�}�[��������
		state++;			//�����������̏I��

		/*fallthrough*/

	case 1:
		//--�ʏ펞�̏���--//
#ifdef  USE_IMGUI
		static bool f_open = true;
		ImGui::Begin("Test", &f_open);
		static float foobar = 1.0f;
		static float foo = 1.0f;
		ImGui::SliderFloat("testfloat", &foo, -1.0f, 1.0f);
		ImGui::SliderFloat("testfloat2", &foobar, -1.0f, 1.0f);
		ImGui::SliderAngle("Angle", &foobar, -1.0f, 1.0f);
		ImGui::End();

		ImGui::Begin("Test 2", &f_open);
		ImGui::SliderFloat("testfloat", &foobar, -1.0f, 1.0f);
		ImGui::SliderAngle("Angle", &foobar, -1.0f, 1.0f);
		ImGui::End();
#endif //  USE_IMGUI

	
		timer++;			//Title�S�̂̃^�C�}�[

		//START
		if (padInput & PAD_INPUT_R)
		{
			if (keyTrg)
			{
				keyTrg = false;
				changeScene(Game::instance());
				if (select == 0)  setSelect(ONE_PLAY);
				if (select == 1)  setSelect(TWO_PLAY);
			}
		}
		//��
		else if (padInput & PAD_INPUT_DOWN)
		{
			if (keyTrg && select == 0)
			{
				keyTrg = false;
				select = 1;
			}
		}
		//��
		else if (padInput & PAD_INPUT_UP)
		{
			if (keyTrg && select == 1)
			{
				keyTrg = false;
				select = 0;
			}
		}
		else
		{
			keyTrg = true;
		}
		break;
	}

#ifdef USE_IMGUI
	static bool my_tool_active = true;
	ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	static float my_color[4] = {};
	// Edit a color (stored as ~4 floats)
	ImGui::ColorEdit4("Color", my_color);

	// Plot some values
	const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
	ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();
#endif // USE_IMGUI
}

////--�`�揈��--////
void Title::draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255),       "Title",        100);
	DrawFormatString(  0,  10, GetColor(255, 255, 255), "Select : %d",select, 100);
}
