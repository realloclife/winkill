#include <Windows.h>

#include <bit>

auto mouse_hook(int code, WPARAM w, LPARAM l) -> LRESULT CALLBACK {
	if (code >= 0 && w == WM_LBUTTONDOWN) {
		auto mouse = std::bit_cast<MOUSEHOOKSTRUCT*>(l);
		auto window = WindowFromPoint(mouse->pt);
		if (window != nullptr) {
			auto parent = GetAncestor(window, GA_ROOT);
			if (parent != nullptr) SendMessage(window, WM_CLOSE, 0, 0);
		}
		PostQuitMessage(0);
	}

	return CallNextHookEx(nullptr, code, w, l);
}

auto APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) -> int {
	auto cursor = LoadCursor(nullptr, IDC_NO);
	if (cursor == nullptr) return EXIT_FAILURE;

	SetCursor(cursor);

	auto mouse = SetWindowsHookEx(WH_MOUSE_LL, mouse_hook, nullptr, 0);
	if (mouse == nullptr) return EXIT_FAILURE;

	auto message = MSG{};
	while (GetMessage(&message, nullptr, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(mouse);
	return EXIT_SUCCESS;
}
