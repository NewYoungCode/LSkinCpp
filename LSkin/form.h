#pragma once
#include "control.h"
namespace LSkin {

	enum  FormBorderStyle
	{
		NoneBorder = (WS_POPUP),
		DefaultStyle = (WS_OVERLAPPEDWINDOW),
	};
	class export Form :public Control
	{
	private:
		FormBorderStyle _borderStyle = FormBorderStyle::DefaultStyle;
	protected:
		bool _fristRun = true;
	public:
		Form();
		~Form();
		bool _isDialog = false;
		//获取窗口样式
		FormBorderStyle formBorderStyle();
		//设置窗口的边框样式 必须再窗口显示之前设置
		void setFormBorderStyle(const FormBorderStyle& formBorderStyle);
		LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		void show(int nCmdShow = SW_SHOW) override;
		Rect rect() override;
		void showDiolog();
	};
}

