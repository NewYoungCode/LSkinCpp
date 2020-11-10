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
		//��ȡ������ʽ
		FormBorderStyle formBorderStyle();
		//���ô��ڵı߿���ʽ �����ٴ�����ʾ֮ǰ����
		void setFormBorderStyle(const FormBorderStyle& formBorderStyle);
		LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		void show(int nCmdShow = SW_SHOW) override;
		Rect rect() override;
		void showDiolog();
	};
}

