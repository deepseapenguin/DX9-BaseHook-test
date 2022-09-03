#include <pch.h>
#include <base.h>
#include <imgui/imgui_impl_dx9.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
		Data::WmKeys[wParam] = uMsg;

	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case Data::Keys::ToggleMenu:
			Data::ShowMenu = !Data::ShowMenu;
			break;
		case Data::Keys::DetachDll:
			Data::ToDetach = true;
			break;
		}
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	if (io.WantCaptureMouse)
	{
		return TRUE;
	}

	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}