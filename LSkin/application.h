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
	  // ժҪ:
	  //     �ÿؼ���ê�������������κα�Ե��
		None = 0,
		//
		// ժҪ:
		//     �ÿؼ���λ���������ϱ�Ե��
		Top = 1,
		//
		// ժҪ:
		//     �ÿؼ���λ�����������±�Ե��
		Bottom = 2,
		//
		// ժҪ:
		//     �ÿؼ���λ�����������Ե��
		Left = 4,
		//
		// ժҪ:
		//     �ؼ���λ�����������ұ�Ե��
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
		LogFont.lfHeight = 20; // �����С
		LogFont.lfCharSet = 134;
		LogFont.lfOutPrecision = 3;
		LogFont.lfClipPrecision = 2;
		LogFont.lfOrientation = 45;
		LogFont.lfQuality = 1;
		LogFont.lfPitchAndFamily = 2;
		// ��������
		HFONT hFont = CreateFontIndirect(&LogFont);
		// ȡ�ÿؼ����
		SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
	}
	//������Ϣѭ��
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