#include "gui.hpp"

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "instance.hpp"
#include "imnimation.hpp"

GUI* GUI::GetInstance() {
    if (!m_pInst)
        new GUI();
    return m_pInst;
}

GUI::GUI() {
    if (m_pInst)
        delete m_pInst;
    m_pInst = this;

    auto inst = Instance::GetInstance();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = nullptr;

    ApplyStyles();

    ImGui_ImplWin32_Init(inst->m_hwnd);
    ImGui_ImplDX11_Init(inst->g_pd3dDevice, inst->g_p3dDeviceContext);
}

GUI::~GUI() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void GUI::Destroy() {
    delete m_pInst;
}

static float linearOffset = 400.f;
static bool linearToggle = false;

static float cubicBezierOffset = 400.f;
static float cubicBezierTOffset = 0.f;
static bool cubicBezierToggle = false;

void GUI::Tick() {
    auto inst = Instance::GetInstance();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    {
        ImGui::SetNextWindowPos({ 0.f, 0.f });
        ImGui::SetNextWindowSize({ 900.f, 600.f });
        ImGui::Begin("curvetest", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);

		{
			if (ImGui::Checkbox("linear animation", &linearToggle)) {
				linearOffset = 0.f;
			}
			ImGui::SameLine();
			const auto linearDrawPos = ImGui::GetCursorPos();
			ImGui::Dummy({ 400.f, 25.f });

			imnimation::AnimLerp(&linearOffset, 400.f, 6.f);
			if (linearToggle == true) {
				ImGui::GetWindowDrawList()->AddRectFilled(linearDrawPos, { linearDrawPos.x + linearOffset, linearDrawPos.y + 25.f }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 1.f }));
			} else {
				ImGui::GetWindowDrawList()->AddRectFilled(linearDrawPos, { (linearDrawPos.x + 400.f) - linearOffset, linearDrawPos.y + 25.f }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 1.f }));
			}
		}

		{
			if (ImGui::Checkbox("cubic bezier animation", &cubicBezierToggle)) {
				cubicBezierOffset = 0.f;
				cubicBezierTOffset = 0.f;
			}
			ImGui::SameLine();
			const auto cubicDrawPos = ImGui::GetCursorPos();
			ImGui::Dummy({ 400.f, 25.f });

			imnimation::AnimCubicBezier(&cubicBezierOffset, &cubicBezierTOffset, 400.f, 3.5f);
			if (cubicBezierToggle == true) {
				ImGui::GetWindowDrawList()->AddRectFilled(cubicDrawPos, { cubicDrawPos.x + cubicBezierOffset, cubicDrawPos.y + 25.f }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 1.f }));
			} else {
				ImGui::GetWindowDrawList()->AddRectFilled(cubicDrawPos, { (cubicDrawPos.x + 400.f) - cubicBezierOffset, cubicDrawPos.y + 25.f }, ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 1.f }));
			}
		}
        

        ImGui::End();
    }

    ImGui::Render();

    const float clearColor[4] = { 0.f, 0.f, 0.f, 0.f };

    inst->g_p3dDeviceContext->OMSetRenderTargets(1, &inst->g_mainRenderTargetView, NULL);
    inst->g_p3dDeviceContext->ClearRenderTargetView(inst->g_mainRenderTargetView, clearColor);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    inst->g_pSwapChain->Present(1, 0); // Present with vsync
}

void GUI::ApplyStyles() {
    ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.97f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.54f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.40f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.44f, 0.44f, 0.67f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.14f, 0.14f, 0.14f, 0.50f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.24f, 0.24f, 0.50f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.19f, 0.20f, 0.21f, 0.50f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.45f, 0.45f, 0.45f, 0.31f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.80f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	style->Colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.19f, 0.20f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.57f, 0.57f, 0.57f, 0.67f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.64f, 0.64f, 0.64f, 0.95f);
	style->Colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.31f, 0.31f, 0.31f, 0.80f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.44f, 0.44f, 0.44f, 0.67f);
	style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 0.97f);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	style->Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	style->Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	style->Colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.67f, 0.67f, 0.67f, 0.35f);
	style->Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	style->WindowPadding = ImVec2(10.f, 10.f);
	style->FramePadding = ImVec2(5.f, 5.f);
	style->CellPadding = ImVec2(4.f, 2.f);
	style->ItemSpacing = ImVec2(8.f, 4.f);
	style->ItemInnerSpacing = ImVec2(4.f, 4.f);
	style->TouchExtraPadding = ImVec2(0.f, 0.f);
	style->IndentSpacing = 20.f;
	style->ScrollbarSize = 14.f;
	style->GrabMinSize = 10.f;

	style->WindowBorderSize = 1.f;
	style->ChildBorderSize = 1.f;
	style->PopupBorderSize = 1.f;
	style->FrameBorderSize = 1.f;
	style->TabBorderSize = 0.f;

	style->WindowRounding = 5.f;
	style->ChildRounding = 5.f;
	style->FrameRounding = 5.f;
	style->PopupRounding = 0.f;
	style->ScrollbarRounding = 5.f;
	style->GrabRounding = 5.f;
	style->LogSliderDeadzone = 4.f;
	style->TabRounding = 4.f;

	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->WindowMenuButtonPosition = ImGuiDir_Right;
	style->ColorButtonPosition = ImGuiDir_Right;
	style->ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style->SelectableTextAlign = ImVec2(0.5, 0.5f);
	style->DisplaySafeAreaPadding = ImVec2(3.f, 3.f);
}