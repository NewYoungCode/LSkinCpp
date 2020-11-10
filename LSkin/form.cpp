#pragma once
#include "form.h"
namespace LSkin {
	Form::Form() :Control()
	{
		hWnd = CreateWindowA(className.data(), "Helo World", WS_OVERLAPPEDWINDOW,
			0, 0, 100, 30, 0, nullptr, 0, nullptr);
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)this);
		_isForm = true;
		setTransparent(false);
		setBackgroundColor(Color(240, 240, 240));
		setForeColor(Color(0, 0, 0));
		setSize({ (int)(GetSystemMetrics(SM_CXFULLSCREEN) / 2), (int)(GetSystemMetrics(SM_CYFULLSCREEN) / 1.5) });
		setFont(NULL);
		//设置阴影
		const MARGINS shadow = { 1, 1,1,1 };
		DwmExtendFrameIntoClientArea(Hwnd(), &shadow);
	}
	Form::~Form()
	{
	}
	FormBorderStyle Form::formBorderStyle()
	{
		return  _borderStyle;
	}
	void Form::setFormBorderStyle(const FormBorderStyle& formBorderStyle) 
	{
		::SetWindowLong(hWnd, GWL_STYLE, formBorderStyle);
		UpdateWindow(Hwnd());
	}

	LRESULT Form::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		//case WM_NCCALCSIZE: {
		//	//去除标题栏
		//	return 0;
		//}
		//case WM_SIZE: {
		//	if (IsZoomed(Hwnd())) {
		//		setLocation({ 0,0 });
		//		Invalidate();
		//	}
		//	break;
		//}
		case WM_DESTROY:
		{
			runningTotal--;
			if (runningTotal <= 0) {
				PostQuitMessage(0);
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			::ReleaseCapture();
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, NULL);
			break;
		}
	
		//case WM_NCHITTEST: {
		//	const LONG borderWidth = 8; //in pixels
		//	RECT winrect;
		//	GetWindowRect(hwnd, &winrect);
		//	long x = GET_X_LPARAM(lParam);
		//	long y = GET_Y_LPARAM(lParam);
		//	//bottom right corner
		//	if (x < winrect.right && x >= winrect.right - borderWidth &&
		//		y < winrect.bottom && y >= winrect.bottom - borderWidth)
		//	{
		//		return HTBOTTOMRIGHT;
		//	}
		//	break;
		//}
		default:
			break;
		}
		return 	Control::WndProc(hwnd, message, wParam, lParam);
	}
	void Form::show(int nCmdShow)
	{
		setCenter();
		Control::show(nCmdShow);
		if (_fristRun) {
			_fristRun = false;
			runningTotal++;
		}
	}
	Rect Form::rect() {
		RECT r;
		::GetWindowRect(Hwnd(), &r);
		return Rect(r.left, r.top, r.right - r.left, r.bottom - r.top);
	}
	void Form::showDiolog()
	{
		setCenter();
		::UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);
		if (_fristRun) {
			_fristRun = false;
			runningTotal++;
		}
	}
}