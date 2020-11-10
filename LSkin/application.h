#pragma once
#include "paintconnector.h"
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <vector>
#include <functional>
#include "paintconnector.h"
#ifdef _WINDLL
#define export __declspec(dllexport)
#else // _WINDLL
#define export __declspec(dllimport)
#endif

namespace LSkin {
	enum    AnchorStyle : char
	{
		//
	  // 摘要:
	  //     该控件不锚定到其容器的任何边缘。
		None = 0,
		//
		// 摘要:
		//     该控件定位到其容器上边缘。
		Top = 1,
		//
		// 摘要:
		//     该控件定位到其容器的下边缘。
		Bottom = 2,
		//
		// 摘要:
		//     该控件定位到其容器左边缘。
		Left = 4,
		//
		// 摘要:
		//     控件定位到其容器的右边缘。
		Right = 8
	};
	enum class MouseType :unsigned char {
		None,
		MouseDown,
		MouveUp,
		MouseMove,
		MouseEnter,
		MouveLeave,
		MouseHover,
		MouseClick,
		MouseDoubleClick
	};

	enum class MouseButton :unsigned char {
		None,
		LeftButton,
		RightButton
	};
	class MouseEventArgs {
	public:
		int msgCode = 0;
		Point point = {};
		MouseType mouseType = MouseType::None;
		MouseButton  mouseButton = MouseButton::None;
	};
	class KeyboardEventArgs {
	public:
		int msgCode = 0;
		int keyCode = 0;
	};
	class PaintEventArgs {
	public:
		Graphics *graphics = NULL;
		HDC hdc = NULL;
		PAINTSTRUCT pst;
	};
	class WindowActiveEventArgs {
	public:
		int msgCode = 0;
		Rect rect = {};
		bool	Cancel = false;
	};

	static std::string className = "LSkinForm";
	extern int runningTotal;
	static	bool regClass = false;
	extern LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	inline UINT msgBox(const wchar_t *title, const wchar_t *text, UINT type = 0) {
		return	MessageBoxW(GetActiveWindow(), text, title, type);
	}
	inline UINT msgBox(const std::string &title, const std::string &text, UINT type = 0) {
		return	MessageBoxA(GetActiveWindow(), text.c_str(), title.c_str(), type);
	}
	inline SIZE getScreenSize() {
		return (SIZE{ GetSystemMetrics(SM_CXFULLSCREEN),GetSystemMetrics(SM_CYFULLSCREEN) });
	}
	inline std::wstring getApplicationDir() {
		WCHAR exeFullPath[MAX_PATH];
		GetModuleFileNameW(NULL, exeFullPath, MAX_PATH);
		return exeFullPath;
	}
	inline void SetFontWin32(HWND hWnd) {
		LOGFONT LogFont;
		memset(&LogFont, 0, sizeof(LOGFONT));
		lstrcpy(LogFont.lfFaceName, "Microsoft YaHei");
		LogFont.lfWeight = FW_NORMAL;//FW_NORMAL;
		LogFont.lfHeight = 20; // 字体大小
		LogFont.lfCharSet = 134;
		LogFont.lfOutPrecision = 3;
		LogFont.lfClipPrecision = 2;
		LogFont.lfOrientation = 45;
		LogFont.lfQuality = 1;
		LogFont.lfPitchAndFamily = 2;
		// 创建字体
		HFONT hFont = CreateFontIndirect(&LogFont);
		// 取得控件句柄
		SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
	}
	//进行消息循环
	class export Application{
	private:
		PaintConnector *_paintConnector = NULL;
	public:
		Application();
		~Application();
		int exec();
		void exit();
	};
};